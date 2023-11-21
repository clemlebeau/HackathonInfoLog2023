#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_main.h>

#include "Application.hpp"
#include "Random.hpp"
#include "CrocodileGame.hpp"
#include "GameScene.hpp"

int main(int argc, char **argv) {
	CrocodileGame *game = new CrocodileGame();
  Scene *gameScene = new GameScene();

  Application::getInstance().addWindow(game);
  
  game->addScene(gameScene, "GameScene");

  Application::getInstance().start();

  delete gameScene;

	return 0;
}