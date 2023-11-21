/// @file Event.hpp
/// @brief Contient la classe Event
/// @author Clément Lebeau (clementlebeau13@gmail.com)

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#define GAME_LOST 32769
#define GAME_WON 32770

#define MENU_JOUER_CLICK 32771
#define MENU_QUITTER_CLICK 32772

/// @class Event
/// @brief Implémentation orientée objet du type SDL_Event de SDL2
class Event {
private:
	static SDL_Event sdlEvent;	 /// Contenant d'informations concernant les évènements

public:
	/// @brief Stock de l'information sur l'évènement actuel
	/// @return 0 lorsqu'il ne reste plus d'évènements dans la file
	static int poll() {
		return SDL_PollEvent(&sdlEvent);
	}

	static void pushCustomEvent(unsigned int customCode) {
		SDL_Event event;
		event.type = SDL_USEREVENT;
		event.window.windowID = 1;
		event.user.code = customCode;
		SDL_PushEvent(&event);
	}

	static void pushQuitEvent() {
		SDL_Event event;
		event.type = SDL_QUIT;
		event.window.windowID = 1;
		SDL_PushEvent(&event);
	}

	/// @brief Retourne le type d'évènement
	/// @return Type d'évènement
	static unsigned int getType() {
		return sdlEvent.type;
	}

	static int getCustomType() {
		return sdlEvent.user.code;
	}

	/// @brief Retourne le type d'évènement de fenêtre
	/// @return Type d'évènement de fenêtre
	static unsigned char getWindowEvent() {
		return sdlEvent.window.event;
	}

	/// @brief Retourne l'ID de la fenêtre où s'est produit l'évènement
	/// @return ID de la fenêtre
	static unsigned int getWindowID() {
		return sdlEvent.window.windowID;
	}

	/// @brief Retourne le bouton de souris qui a déclenché l'évènement
	/// @return Bouton de souris
	static unsigned char getMouseButton() {
		return sdlEvent.button.button;
	}

	/// @brief Retourne la position en X de la souris lors d'un déplacement de souris
	/// @return Position en X de la souris
	static int getMouseMotionX() {
		return sdlEvent.motion.x;
	}

	/// @brief Retourne la position en Y de la souris lors d'un déplacement de souris
	/// @return Position en Y de la souris
	static int getMouseMotionY() {
		return sdlEvent.motion.y;
	}

	/// @brief Retourne la position relative en X de la souris lors d'un déplacement de souris
	/// @return Position relative en X de la souris
	static int getMouseMotionXRel() {
		return sdlEvent.motion.xrel;
	}

	/// @brief Retourne la position relative en Y de la souris lors d'un déplacement de souris
	/// @return Position relative en Y de la souris
	static int getMouseMotionYRel() {
		return sdlEvent.motion.yrel;
	}

	/// @brief Retourne la position en X de la souris lors d'un click
	/// @return Position en X de la souris
	static int getMouseClickX() {
		return sdlEvent.button.x;
	}

	/// @brief Retourne la position en Y de la souris lors d'un click
	/// @return Position en Y de la souris
	static int getMouseClickY() {
		return sdlEvent.button.y;
	}

	/// @brief Retourne la touche cliquée sur le clavier
	/// @return Code de la touche enfoncée
	static int getKeyBoardKey() {
		return sdlEvent.key.keysym.sym;
	}
};
SDL_Event Event::sdlEvent;