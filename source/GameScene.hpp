#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Image.hpp"
#include "Scene.hpp"
#include "Tooth.hpp"

class GameScene : public Scene {
private:
	// std::vector<Tooth *> teeth;

	void loadTeeth(std::string path) {
		std::ifstream positionFile(path);

		int x, y;
		unsigned short line = 0;
		while(positionFile >> x >> y) {
			std::string img_path = "assets/images/teeth/" + std::to_string(line) + ".png";
			SDL_Surface *toothSurface = IMG_Load(img_path.c_str());
			Tooth *tooth = new Tooth(x, y, x, y+50, toothSurface);

			subscribeComponent(SDL_MOUSEMOTION, tooth);
			subscribeComponent(SDL_MOUSEBUTTONUP, tooth);
			// components["tooth" + std::to_string(line)] = teeth[line] = tooth;
			components["tooth" + std::to_string(line)] = tooth;

			line++;
		}
	}

public:
	GameScene() :
		Scene() {
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("BlueRoosterTexture")), "BlueRoosterImage");
		components["BlueRoosterImage"]->resize(1024);

		loadTeeth("assets/images/teeth/position.txt");
	}

  virtual ~GameScene() {}

	void setParams(int argc, ...) {}

	void notification() {
	}

	void handleUpdate(double deltaTime) {}

	void handleDraw(Renderer *renderer) {
		renderer->clear();

		for (auto it: components) {
			(it.second)->draw(renderer);
		}

		Cursor::getInstance()->draw(renderer);
		renderer->refresh();
	}
};