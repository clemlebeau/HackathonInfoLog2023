/// @file Image.hpp
/// @brief Contient la classe Image
/// @author Mikaël Bureau (mikael.bureau00@gmail.com)

#pragma once

#include "Component.hpp"

/// @class Image
/// @brief Dérive de la classe Component. Peut être ajoutée à une position avec une certaine taille en respectant les proportions
class Image : public Component {
private:
	bool isVisible;

protected:
	SDL_Texture *texture;	///< Pointeur de la texture de l'image qui peut être affichée
	SDL_Surface *surface;	///< Surface qui devra être transformée en texture pour affichage

public:
	Image(int x, int y, SDL_Texture *texture, bool isVisible = true) :
		Component(x, y) {
		this->texture = texture;
		SDL_QueryTexture(texture, nullptr, nullptr, &(this->rectangle.w), &(this->rectangle.h));
		surface = nullptr;
		this->isVisible = isVisible;
	}

	Image(int x, int y, SDL_Surface *surface, bool isVisible = true) :
		Component(x, y) {
		this->surface = surface;
		this->rectangle.w = surface->w;
		this->rectangle.h = surface->h;
		texture = nullptr;
		this->isVisible = isVisible;
	}

	virtual ~Image() {}

	void setTexture(SDL_Texture *texture) {
		this->texture = texture;
	}

	void setSurface(SDL_Surface *surface) {
		this->surface = surface;
	}

	/// @brief Met à jour la texture de l'image depuis sa surface. Note: Si possible, appeler cette méthode uniquement au changement de la surface, pas à chaque frame.
	/// @param renderer Moteur de rendu dans lequel l'image est affichée
	void refreshTexture(Renderer *renderer) {
		if (!surface)
			return;

		if (texture)
			SDL_DestroyTexture(texture);

		texture = renderer->createTextureFromSurface(surface);
	}

	/// @brief Mise à jour de l'image à afficher
	/// @param deltaTime Écart de temps entre deux mises à jour
	virtual void update(double deltaTime) {}

	/// @brief Affichage de l'image
	/// @param renderer Permet d'afficher l'image dans le moteur de rendu
	virtual void draw(Renderer *renderer) {
		if (isVisible) {
			if (!texture && surface) refreshTexture(renderer);	 // If the image was initialized with a surface, we need to create its texture on the first frame to draw it.

			if (texture) renderer->copy(texture, nullptr, &rectangle);
		}
	}

	void setVisibility(bool isVisible = true) {
		this->isVisible = isVisible;
	}

	/// @brief Notifie si on clique sur l'image
	virtual void notification() {}
};