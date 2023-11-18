#pragma once

#include "Image.hpp"
#include "Scene.hpp"

class GameScene : public Scene {
private:
	bool imageTexturesRefreshed;

public:
	GameScene() :
		Scene() {
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Surface *>("BlueRoosterSurface")), "BlueRoosterImage");
		components["BlueRoosterImage"]->resize(1024);
		imageTexturesRefreshed = false;
	}

	void setParams(int argc, ...) {}

	void notification() {
	}

	void handleUpdate(double deltaTime) {}

	void handleDraw(Renderer *renderer) {
		if (!imageTexturesRefreshed) {
      ((Image *)components["BlueRoosterImage"])->refreshTexture(renderer);
		}
		renderer->clear();

		for (auto it: components) {
			(it.second)->draw(renderer);
		}

		renderer->refresh();
	}
};