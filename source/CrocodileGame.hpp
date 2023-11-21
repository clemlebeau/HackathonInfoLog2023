/// @file CrocodileGame.hpp
/// @brief Contient la classe CrocodileGame
/// @author Clément Lebeau (clementlebeau13@gmail.com)

#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <SDL2/SDL_image.h>

#include "Renderer.hpp"
#include "RessourceManager.hpp"
#include "Scene.hpp"

/// @class CrocodileGame
/// @brief Contient les différentes scènes du projet et affiche/met à jour seulement la scène actuelle
class CrocodileGame : public Renderer {
private:
	Scene *currentScene;					 /// Scène actuelle
	std::map<std::string, Scene *> scenes;	 /// Contient toutes les scène du projet, identifiées par un nom

public:
	CrocodileGame() :
		Renderer("CrocodileGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720) {
		currentScene = nullptr;

		// Ajout des ressources au gestionnaire de ressources
		RessourceManager::add("Cursor", loadTextureFromImage("./assets/images/cursor.png"));
		Cursor::getInstance()->setTexture(RessourceManager::get<SDL_Texture *>("Cursor"));

    RessourceManager::add("CrocoFrontTexture", loadTextureFromImage("./assets/images/croco/CrocoFront.png"));
    RessourceManager::add("CrocoMiddleTexture", loadTextureFromImage("./assets/images/croco/CrocoMiddle.png"));
    RessourceManager::add("CrocoBackTexture", loadTextureFromImage("./assets/images/croco/CrocoBack.png"));
    RessourceManager::add("WaterTexture", loadTextureFromImage("./assets/images/backgrounds/Water.png"));
	}

	virtual ~CrocodileGame() {
    SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("Cursor"));
    RessourceManager::remove("Cursor");
		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("CrocoFrontTexture"));
    RessourceManager::remove("CrocoFrontTexture");
		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("CrocoMiddleTexture"));
    RessourceManager::remove("CrocoMiddleTexture");
		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("CrocoBackTexture"));
    RessourceManager::remove("CrocoBackTexture");
		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("WaterTexture"));
    RessourceManager::remove("WaterTexture");
  }

	/// @brief Change la scène actuelle
	/// @param sceneName Nom de la scène pour laquelle changer
	/// @return Code d'erreur (0 en temps normal, -1 si la scène n'existe pas)
	char swapScene(std::string sceneName) {
		if (scenes.find(sceneName) != scenes.end()) {
			currentScene = scenes[sceneName];
			return 0;
		}
		return -1;
	}

	/// @brief Retourne la scène actuelle
	/// @return Pointeur vers la scène actuelle
	Scene *getScene() {
		return currentScene;
	}

	/// @brief Ajouter une scène si elle n'existe pas déja
	/// @param scene Scène à ajouter
	/// @param sceneName Nom de la scène à ajouter
	void addScene(Scene *scene, std::string sceneName) {
		if (scenes.find(sceneName) == scenes.end()) {
			if (!currentScene)
				currentScene = scene;
			scenes[sceneName] = scene;
		}
	}

	/// @brief Gère les évènements de la scène actuelle
	void handleEvent() {
		currentScene->handleEvent();
	}

	/// @brief Gère les mises à jour de la scène actuelle
	/// @param deltaTime Intervalle de temps depuis la dernière frame (en secondes)
	void handleUpdate(double deltaTime) {
		currentScene->handleUpdate(deltaTime);
	}

	/// @brief Gère l'affichage de la scène actuelle
	void handleDraw() {
		currentScene->handleDraw(this);
	}
};