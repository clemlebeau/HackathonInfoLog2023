/// @file Component.hpp
/// @brief Contient la classe Component
/// @author Mikaël Bureau (mikael.bureau00@gmail.com)

#pragma once

#include "Observer.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"

///\class Component
///\brief Classe abstraite qui peut être affichée, actualisée et être notifiée
class Component : public Observer {
protected:
	SDL_Rect rectangle;	  ///< Rectangle de destination qui permet d'afficher des textures
	bool toDelete;		  ///< Si true, le Component devra être libéré par la scène qui le gère

public:
	Component(int x, int y, int w = 0, int h = 0) {
		toDelete = false;
		rectangle.x = x;
		rectangle.y = y;
		if (w > 0 && h > 0) {
			rectangle.w = w;
			rectangle.h = h;
		}
	}

	bool shouldDelete() { return toDelete; }

	Component() {}

	virtual ~Component() {}

	/// @brief Redimensionne le composant en gardant les bonnes proportions
	/// @param newWidth Nouvelle largeur du composant
	/// @param newHeight Nouvelle hauteur du composant, si laissée à -1, la hauteur sera déterminée par la largeur et les proportions
	virtual void resize(int newWidth, int newHeight = -1) {
		if (newHeight != -1) {
			rectangle.w = newWidth;
			rectangle.h = newHeight;
		}
		else {
			double ratio = (double) rectangle.h / (double) rectangle.w;
			rectangle.w = newWidth;
			rectangle.h = ratio * rectangle.w;
		}
	}

	virtual void resizeRatio(int newWidth, double ratio = 9.0 / 16.0) {
		rectangle.w = newWidth;
		rectangle.h = ratio * rectangle.w;
	}

	/// @brief Déplace le composant aux coordonnées indiquées
	/// @param x Coordonnée en X où déplacer le composant
	/// @param y Coordonnée en Y où déplacer le composant
	/// @param centered Si true, centre le composant aux coordonnées passées en paramètre au lieu de déplacer le coin supérieur gauche de la texture
	virtual void move(int x, int y, bool centered = false) {
		if (centered) {
			rectangle.x = x - rectangle.w / 2;
			rectangle.y = y - rectangle.h / 2;
		}
		else {
			rectangle.x = x;
			rectangle.y = y;
		}
	}

	virtual SDL_Rect getRectangle() {
		return rectangle;
	}

	virtual void update(double deltaTime) = 0;
	virtual void draw(Renderer *renderer) = 0;
	virtual void notification() = 0;
};