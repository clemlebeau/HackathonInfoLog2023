#pragma once

#include <string>

#include "Application.hpp"
#include "ClickableImage.hpp"
#include "CrocodileGame.hpp"
#include "GameScene.hpp"
#include "Image.hpp"
#include "ImageAnimation.hpp"
#include "Scene.hpp"

#define ENDSCENE_TRANSITION_ANIMATION_DURATION 0.5
#define ENDSCENE_TRANSITION_ANIMATION_WIDTH_FROM 550
#define ENDSCENE_TRANSITION_ANIMATION_WIDTH_TO RENDER_WIDTH

class EndScene : public Scene {
private:
	ImageAnimation *imageAnimation;

public:
	EndScene() :
		Scene() {
		imageAnimation = new ImageAnimation(ENDSCENE_TRANSITION_ANIMATION_WIDTH_FROM, ENDSCENE_TRANSITION_ANIMATION_WIDTH_TO, ENDSCENE_TRANSITION_ANIMATION_DURATION, MENU_NEXT_SCENE);
		subscribeComponent(MENU_NEXT_SCENE, this);

		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("WaterTexture")), "aWaterImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("EndGagnantTexture"), false), "bEndGagnantImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("EndPerdantTexture"), false), "bEndPerdantImage");

		Image *crocoNoBackground = new Image(0, 0, RessourceManager::get<SDL_Texture *>("CrocoNoBackgroundTexture"));
		crocoNoBackground->resize(ENDSCENE_TRANSITION_ANIMATION_WIDTH_FROM);
		crocoNoBackground->move(0, RENDER_HEIGHT - crocoNoBackground->getRectangle().h);
		addComponent(crocoNoBackground, "zCrocoNoBackgroundImage");

		ClickableImage *endRejouer = new ClickableImage(534, 329, RessourceManager::get<SDL_Texture *>("EndRejouerTexture"), MENU_JOUER_CLICK);
		subscribeComponent(SDL_MOUSEBUTTONUP, endRejouer);
		subscribeComponent(MENU_JOUER_CLICK, this);
		ClickableImage *endQuitter = new ClickableImage(533, 408, RessourceManager::get<SDL_Texture *>("EndQuitterTexture"), MENU_QUITTER_CLICK);
		subscribeComponent(SDL_MOUSEBUTTONUP, endQuitter);
		subscribeComponent(MENU_QUITTER_CLICK, this);
		addComponent(endRejouer, "bEndRejouerImage");
		addComponent(endQuitter, "bEndQuitterImage");
	}

	virtual ~EndScene() {
		delete imageAnimation;
	}

	void setParams(int argc, ...) {
		va_list argl;

		va_start(argl, argc);
		bool isWinning = (bool) va_arg(argl, int);
		((Image *) (components["bEndGagnantImage"]))->setVisibility(isWinning);
		((Image *) (components["bEndPerdantImage"]))->setVisibility(!isWinning);
		va_end(argl);

		imageAnimation->reset();
	}

	void notification() {
		switch (Event::getCustomType()) {
			case MENU_JOUER_CLICK:
				imageAnimation->start();
				break;
			case MENU_QUITTER_CLICK:
				Event::pushQuitEvent();
				break;
			case MENU_NEXT_SCENE:
				((CrocodileGame *) (Application::getInstance().getWindow(1)))->resetScene<GameScene>("GameScene");
				((CrocodileGame *) (Application::getInstance().getWindow(1)))->swapScene("GameScene");
				break;
		}
	}

	void handleUpdate(double deltaTime) {
		imageAnimation->update(deltaTime, (Image *) components["zCrocoNoBackgroundImage"]);
	}

	void handleDraw(Renderer *renderer) {
		renderer->clear();

		for (auto it: components) {
			if (it.second)
				it.second->draw(renderer);
		}

		Cursor::getInstance()->draw(renderer);
		renderer->refresh();
	}
};