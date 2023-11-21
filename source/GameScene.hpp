#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Image.hpp"
#include "Scene.hpp"
#include "Tooth.hpp"

#define FRONT_TOOTH_MAX 16

class GameScene : public Scene {
private:
	// std::vector<Tooth *> teeth;

	void loadTeeth(std::string path) {
		std::ifstream positionFile(path);

		int xExtended, yExtended, xRetracted, yRetracted;
		unsigned short line = 0;
		while(positionFile >> xExtended >> yExtended >> xRetracted >> yRetracted) {
			std::string img_path = "assets/images/teeth/" + std::to_string(line) + ".png";
			SDL_Surface *toothSurface = IMG_Load(img_path.c_str());
			Tooth *tooth = new Tooth(xExtended, yExtended, xRetracted, yRetracted, toothSurface);

			subscribeComponent(SDL_MOUSEMOTION, tooth);
			subscribeComponent(SDL_MOUSEBUTTONUP, tooth);
			std::string toothName = "tooth" + std::to_string(line);
			toothName = (line > FRONT_TOOTH_MAX ? "c" : "e") + toothName; // Separates the drawing of the front teeth from that of the back teeth for texturing reasons.
			components[toothName] = tooth;

			line++;
		}
	}

public:
	GameScene() :
		Scene() {
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("WaterTexture")), "aWaterImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("CrocoBackTexture")), "bCrocoBackImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("CrocoMiddleTexture")), "dCrocoMiddleImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("CrocoFrontTexture")), "zWaterImage");
		

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