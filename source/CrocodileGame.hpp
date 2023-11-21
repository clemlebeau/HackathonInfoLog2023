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
		Renderer("CrocodileGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RENDER_WIDTH, RENDER_HEIGHT) {
		currentScene = nullptr;

		// Ajout des ressources au gestionnaire de ressources
		RessourceManager::add("Cursor", loadTextureFromImage("../assets/images/cursor.png"));
		Cursor::getInstance()->setTexture(RessourceManager::get<SDL_Texture *>("Cursor"));

    RessourceManager::add("CrocoFrontTexture", loadTextureFromImage("../assets/images/croco/CrocoFront.png"));
    RessourceManager::add("CrocoMiddleTexture", loadTextureFromImage("../assets/images/croco/CrocoMiddle.png"));
    RessourceManager::add("CrocoBackTexture", loadTextureFromImage("../assets/images/croco/CrocoBack.png"));
    RessourceManager::add("WaterTexture", loadTextureFromImage("../assets/images/size720p/Water.png"));

    RessourceManager::add("EndGagnantTexture", loadTextureFromImage("../assets/images/size720p/EndGagnant.png"));
    RessourceManager::add("EndPerdantTexture", loadTextureFromImage("../assets/images/size720p/EndPerdant.png"));
    RessourceManager::add("EndQuitterTexture", loadTextureFromImage("../assets/images/buttons/EndQuitter.png"));
    RessourceManager::add("EndRejouerTexture", loadTextureFromImage("../assets/images/buttons/EndRejouer.png"));

    RessourceManager::add("MenuJouerTexture", loadTextureFromImage("../assets/images/buttons/MenuJouer.png"));
    RessourceManager::add("MenuQuitterTexture", loadTextureFromImage("../assets/images/buttons/MenuQuitter.png"));
    RessourceManager::add("MenuCrocoTexture", loadTextureFromImage("../assets/images/size720p/MenuCroco.png"));
    RessourceManager::add("CrocoNoBackgroundTexture", loadTextureFromImage("../assets/images/size720p/CrocoNoBackground.png"));
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

		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("MenuJouerTexture"));
    RessourceManager::remove("MenuJouerTexture");
		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("MenuQuitterTexture"));
    RessourceManager::remove("MenuQuitterTexture");
		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("MenuCrocoTexture"));
    RessourceManager::remove("MenuCrocoTexture");
		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("EndRejouerTexture"));
    RessourceManager::remove("EndRejouerTexture");

		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("EndGagnantTexture"));
    RessourceManager::remove("EndGagnantTexture");
		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("EndPerdantTexture"));
    RessourceManager::remove("EndPerdantTexture");
		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("EndQuitterTexture"));
    RessourceManager::remove("EndQuitterTexture");
		SDL_DestroyTexture(RessourceManager::get<SDL_Texture *>("CrocoNoBackgroundTexture"));
    RessourceManager::remove("CrocoNoBackgroundTexture");
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