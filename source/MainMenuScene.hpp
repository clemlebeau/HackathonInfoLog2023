#pragma once

#include <string>

#include "Application.hpp"
#include "ClickableImage.hpp"
#include "CrocodileGame.hpp"
#include "Image.hpp"
#include "ImageAnimation.hpp"
#include "Lerp.h"
#include "Scene.hpp"

#include "Label.hpp"

#define MAINMENUSCENE_TRANSITION_ANIMATION_DURATION 0.8
#define MAINMENUSCENE_TRANSITION_ANIMATION_WIDTH_FROM 800
#define MAINMENUSCENE_TRANSITION_ANIMATION_WIDTH_TO RENDER_WIDTH

class MainMenuScene : public Scene {
private:
	ImageAnimation *imageAnimation;

public:
	MainMenuScene() :
		Scene() {
		imageAnimation = new ImageAnimation(MAINMENUSCENE_TRANSITION_ANIMATION_WIDTH_FROM, MAINMENUSCENE_TRANSITION_ANIMATION_WIDTH_TO, MAINMENUSCENE_TRANSITION_ANIMATION_DURATION, MENU_NEXT_SCENE);
		subscribeComponent(MENU_NEXT_SCENE, this);

		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("WaterTexture")), "aWaterImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("MenuCrocoTexture")), "bMenuCrocoImage");

		Image *crocoNoBackground = new Image(0, 0, RessourceManager::get<SDL_Texture *>("CrocoNoBackgroundTexture"));
		crocoNoBackground->resize(800);
		crocoNoBackground->move(0, RENDER_HEIGHT - crocoNoBackground->getRectangle().h);
		addComponent(crocoNoBackground, "zCrocoNoBackgroundImage");

		ClickableImage *menuJouer = new ClickableImage(876, 315, RessourceManager::get<SDL_Texture *>("MenuJouerTexture"), MENU_JOUER_CLICK);
		subscribeComponent(SDL_MOUSEBUTTONUP, menuJouer);
		subscribeComponent(MENU_JOUER_CLICK, this);
		ClickableImage *menuQuitter = new ClickableImage(853, 454, RessourceManager::get<SDL_Texture *>("MenuQuitterTexture"), MENU_QUITTER_CLICK);
		subscribeComponent(SDL_MOUSEBUTTONUP, menuQuitter);
		subscribeComponent(MENU_QUITTER_CLICK, this);
		addComponent(menuJouer, "bMenuJouerImage");
		addComponent(menuQuitter, "bMenuQuitterImage");
	}

	virtual ~MainMenuScene() {
		delete imageAnimation;
	}

	void setParams(int argc, ...) {}

	void notification() {
		switch (Event::getCustomType()) {
			case MENU_JOUER_CLICK:
				imageAnimation->start();
        break;
			case MENU_NEXT_SCENE:
				((CrocodileGame *) (Application::getInstance().getWindow(1)))->swapScene("GameScene");
				break;
			case MENU_QUITTER_CLICK:
				Event::pushQuitEvent();
				break;
		}
	}

	void handleUpdate(double deltaTime) {
		imageAnimation->update(deltaTime, (Image *) components["zCrocoNoBackgroundImage"]);
	}

	void handleDraw(Renderer *renderer) {
		renderer->clear();

		for (auto it: components) {
			(it.second)->draw(renderer);
		}

		Cursor::getInstance()->draw(renderer);
		renderer->refresh();
	}
};