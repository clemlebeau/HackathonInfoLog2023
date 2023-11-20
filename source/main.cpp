#include <SDL2/SDL.h>

#include "Application.hpp"
#include "CrocodileGame.hpp"
#include "GameScene.hpp"
#include "Random.hpp"

int main(int argc, char **argv) {
	CrocodileGame *game = new CrocodileGame();
  Scene *gameScene = new GameScene();

  Application::getInstance().addWindow(game);
  
  game->addScene(gameScene, "GameScene");

  Application::getInstance().start();

  delete gameScene;

	return 0;
}