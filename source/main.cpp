#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_main.h>

#include "Application.hpp"
#include "Random.hpp"
#include "CrocodileGame.hpp"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "EndScene.hpp"

int main(int argc, char **argv) {
	CrocodileGame *game = new CrocodileGame();
  
  Scene *mainMenuScene = new MainMenuScene();
  Scene *gameScene = new GameScene();
  Scene *endScene = new EndScene();

  Application::getInstance().addWindow(game);
  
  game->addScene(mainMenuScene, "MainMenuScene");
  game->addScene(gameScene, "GameScene");
  game->addScene(endScene, "EndScene");

  Application::getInstance().start();

	return 0;
}