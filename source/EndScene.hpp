#pragma once

#include <string>

#include "Application.hpp"
#include "ClickableImage.hpp"
#include "CrocodileGame.hpp"
#include "GameScene.hpp"
#include "Image.hpp"
#include "ImageAnimation.hpp"
#include "Scene.hpp"

#define ENDSCENE_TRANSITION_ANIMATION_OUT_DURATION 0.5
#define ENDSCENE_TRANSITION_ANIMATION_OUT_WIDTH_FROM 550
#define ENDSCENE_TRANSITION_ANIMATION_OUT_WIDTH_TO RENDER_WIDTH

#define ENDSCENE_TRANSITION_ANIMATION_IN_DURATION 0.5
#define ENDSCENE_TRANSITION_ANIMATION_IN_WIDTH_FROM RENDER_WIDTH
#define ENDSCENE_TRANSITION_ANIMATION_IN_WIDTH_TO 550

class EndScene : public Scene {
private:
	ImageAnimation *imageAnimationOut;
	ImageAnimation *imageAnimationIn;
public:
	EndScene() :
		Scene() {
		imageAnimationOut = new ImageAnimation(ENDSCENE_TRANSITION_ANIMATION_OUT_WIDTH_FROM, ENDSCENE_TRANSITION_ANIMATION_OUT_WIDTH_TO, ENDSCENE_TRANSITION_ANIMATION_OUT_DURATION, MENU_NEXT_SCENE);
		subscribeComponent(MENU_NEXT_SCENE, this);

		imageAnimationIn = new ImageAnimation(ENDSCENE_TRANSITION_ANIMATION_IN_WIDTH_FROM, ENDSCENE_TRANSITION_ANIMATION_IN_WIDTH_TO, ENDSCENE_TRANSITION_ANIMATION_IN_DURATION, EVENT_NO_OP);
		subscribeComponent(ALL_TEETH_EXTENDED, this);

		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("WaterTexture")), "aWaterImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("EndGagnantTexture"), false), "bEndGagnantImage");
		addComponent(new Image(0, 0, RessourceManager::get<SDL_Texture *>("EndPerdantTexture"), false), "bEndPerdantImage");

		Image *crocoNoBackground = new Image(0, 0, RessourceManager::get<SDL_Texture *>("CrocoNoBackgroundTexture"));
		crocoNoBackground->resize(ENDSCENE_TRANSITION_ANIMATION_IN_WIDTH_FROM);
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
		delete imageAnimationOut;
		delete imageAnimationIn;
	}

	void setParams(int argc, ...) {
		va_list argl;

		va_start(argl, argc);
		bool isWinning = (bool) va_arg(argl, int);
		((Image *) (components["bEndGagnantImage"]))->setVisibility(isWinning);
		((Image *) (components["bEndPerdantImage"]))->setVisibility(!isWinning);
		va_end(argl);

		imageAnimationOut->reset();
		imageAnimationIn->reset();

		Event::pushCustomEvent(ALL_TEETH_EXTENDED); // Start transition from end of game to endgame menu
	}

	void notification() {
		switch (Event::getCustomType()) {
			case ALL_TEETH_EXTENDED:
				imageAnimationIn->start();
			break;
			case MENU_JOUER_CLICK:
				imageAnimationOut->start();
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
		if(imageAnimationIn->isOver())
			imageAnimationOut->update(deltaTime, (Image *) components["zCrocoNoBackgroundImage"]);
		else
			imageAnimationIn->update(deltaTime, (Image *) components["zCrocoNoBackgroundImage"]);
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