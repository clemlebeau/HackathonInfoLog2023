#pragma once

#include <cstdlib>
#include <ctime>
#include <curl/curl.h>
#include <iostream>
#include <stdio.h>
#include <string>

struct MemoryStruct {
	char *memory;
	size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *) userp;

	mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		/* out of memory! */
		std::cout << "not enough memory (realloc returned NULL)" << std::endl;
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

class Random {
private:
	static Random instance;
	std::string Answer;
	int seed;

public:
	Random() {
		CURL *curl_handle;
		CURLcode res;

		struct MemoryStruct chunk;

		chunk.memory = new char; /* will be grown as needed by the realloc above */
		chunk.size = 0;			 /* no data at this point */

		curl_global_init(CURL_GLOBAL_ALL);

		/* init the curl session */
		curl_handle = curl_easy_init();

		/* specify URL to get */
		curl_easy_setopt(curl_handle, CURLOPT_URL, "https://qrng.anu.edu.au/API/jsonI.php?length=1&type=uint16&size=6");

		/* send all data to this function  */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) &chunk);

		/* some servers don't like requests that are made without a user-agent
			field, so we provide one */
		curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

		/* get it! */
		res = curl_easy_perform(curl_handle);

		/* check for errors */
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			srand(time(0));
			// seed par time car on arrive pas a contacter le serveur
		}
		else {
			Answer = chunk.memory;
			// Answer devrait ressembler a {"type":"uint16","length":1,"data":[24379],"success":true}
			std::size_t pos = Answer.find("[");
			if (pos == std::string::npos || pos >= Answer.length() - 1) {
                std::cout << "Answer is received in unexpected format: " << Answer;
			}
			else {
				std::string cutAnswer = Answer.substr(pos + 1);
				seed = stoi(cutAnswer);
				std::cout << Answer << std::endl;
				std::cout << (long) chunk.size << "bytes retrieved" << std::endl;
				srand(seed);
				// seed par serveur
			}
		}

		/* cleanup curl stuff */
		curl_easy_cleanup(curl_handle);

		if (chunk.memory)
			free(chunk.memory);

		/* we're done with libcurl, so clean it up */
		curl_global_cleanup();
		srand(time(0));
	}

	static Random &getInstance() {
		return instance;
	}

	int range(int min, int max) {
		return rand() % (max - min + 1) + min;
	}
};
Random Random::instance;
