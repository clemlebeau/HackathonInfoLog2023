#pragma once

#include <string>

#include "Image.hpp"
#include "ClickableImage.hpp"
#include "Scene.hpp"
#include "CrocodileGame.hpp"
#include "Application.hpp"
#include "Lerp.h"

#include "Label.hpp"

#define FRONT_TOOTH_MAX 16

class MainMenuScene : public Scene {
private:
  Label *debugLabel;
  

public:
	MainMenuScene() :
		Scene() {
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("WaterTexture")), "aWaterImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("MenuCrocoTexture")), "bMenuCrocoImage");
		
    debugLabel = new Label(TTF_OpenFont("D:/Code/arial.ttf", 24), {255, 0, 0, 255}, 0, 0, "TEST");
    addComponent(debugLabel, "zzDebugLabel");

    Image *crocoNoBackground = new Image(0, 0, RessourceManager::get<SDL_Texture *>("CrocoNoBackgroundTexture"));
    crocoNoBackground->resize(800);
    crocoNoBackground->move(0, RENDER_HEIGHT - crocoNoBackground->getRectangle().h);
    addComponent(crocoNoBackground, "zCrocoNoBackgroundImage");
    
    ClickableImage *menuJouer= new ClickableImage(831, 329, RessourceManager::get<SDL_Texture *>("MenuJouerTexture"), MENU_JOUER_CLICK);
    subscribeComponent(SDL_MOUSEBUTTONUP, menuJouer);
    subscribeComponent(MENU_JOUER_CLICK, this);
    ClickableImage *menuQuitter= new ClickableImage(791, 476, RessourceManager::get<SDL_Texture *>("MenuQuitterTexture"), MENU_QUITTER_CLICK);
    subscribeComponent(SDL_MOUSEBUTTONUP, menuQuitter);
    subscribeComponent(MENU_QUITTER_CLICK, this);
		addComponent(menuJouer, "bMenuJouerImage");
		addComponent(menuQuitter, "bMenuQuitterImage");
	}

  virtual ~MainMenuScene() {}

	void setParams(int argc, ...) {}

	void notification() {
    switch(Event::getCustomType()) {
      case MENU_JOUER_CLICK:
        ((CrocodileGame *)(Application::getInstance().getWindow(1)))->swapScene("GameScene");
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