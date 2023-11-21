#pragma once

#include <string>

#include "Application.hpp"
#include "ClickableImage.hpp"
#include "CrocodileGame.hpp"
#include "GameScene.hpp"
#include "Image.hpp"
#include "Scene.hpp"

#define FRONT_TOOTH_MAX 16

class EndScene : public Scene {
private:
public:
	EndScene() :
		Scene() {
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("WaterTexture")), "aWaterImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("EndGagnantTexture"), false), "bEndGagnantImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("EndPerdantTexture"), false), "bEndPerdantImage");

		Image *crocoNoBackground = new Image(0, 0, RessourceManager::get<SDL_Texture *>("CrocoNoBackgroundTexture"));
		crocoNoBackground->resize(550);
		crocoNoBackground->move(0, RENDER_HEIGHT - crocoNoBackground->getRectangle().h);
		addComponent(crocoNoBackground, "zCrocoNoBackgroundImage");

		ClickableImage *endRejouer = new ClickableImage(831, 329, RessourceManager::get<SDL_Texture *>("EndRejouerTexture"), MENU_JOUER_CLICK);
		subscribeComponent(SDL_MOUSEBUTTONUP, endRejouer);
		subscribeComponent(MENU_JOUER_CLICK, this);
		ClickableImage *endQuitter = new ClickableImage(791, 476, RessourceManager::get<SDL_Texture *>("EndQuitterTexture"), MENU_QUITTER_CLICK);
		subscribeComponent(SDL_MOUSEBUTTONUP, endQuitter);
		subscribeComponent(MENU_QUITTER_CLICK, this);
		addComponent(endRejouer, "bEndRejouerImage");
		addComponent(endQuitter, "bEndQuitterImage");
	}

	virtual ~EndScene() {}

	void setParams(int argc, ...) {
		va_list argl;

		va_start(argl, argc);
    bool isWinning = (bool)va_arg(argl, int);
		((Image *)(components["bEndGagnantImage"]))->setVisibility(isWinning);
		((Image *)(components["bEndPerdantImage"]))->setVisibility(!isWinning);
		va_end(argl);
	}

	void notification() {
		switch (Event::getCustomType()) {
			case MENU_JOUER_CLICK:
				((CrocodileGame *) (Application::getInstance().getWindow(1)))->resetScene<GameScene>("GameScene");
				((CrocodileGame *) (Application::getInstance().getWindow(1)))->swapScene("GameScene");
				break;
			case MENU_QUITTER_CLICK:
				Event::pushQuitEvent();
				break;
		}
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