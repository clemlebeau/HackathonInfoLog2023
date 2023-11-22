#pragma once

#include "Image.hpp"
#include "Lerp.h"

#define TOOTH_RETRACTION_DURATION 0.35

class Tooth : public Image {
private:
	static int extendedCounter;

	bool isAnimating;
	double tAnim;

	SDL_Surface *selectedSurface;
	SDL_Surface *unselectedSurface;
	bool isLethal;
	bool isHovered;
	bool isExtended;
	int xExtended;
	int yExtended;
	int xRetracted;
	int yRetracted;

	bool isOnTooth(int x, int y) {
		// Translate according to component position to get texture coordinates
		int texX = x - this->rectangle.x;
		int texY = y - this->rectangle.y;

		if (texX < 0 || texX >= surface->w || texY < 0 || texY >= surface->h) return false;	  // Out of texture bounds

		unsigned long pixelIndex = texY * surface->w + texX;
		unsigned int pixelColor = ((unsigned int *) (surface->pixels))[pixelIndex];
		unsigned char buffer, alpha;   // buffer is only necessary because the next function doesn't support nullptr for unused values
		SDL_GetRGBA(pixelColor, surface->format, &buffer, &buffer, &buffer, &alpha);

		return alpha != 0;	 // Only on tooth if corresponding pixel is non transparent
	}

	SDL_Surface *generateHighlightedSurface(SDL_Surface *surface) {
		const unsigned char DELTA_COLOR = 35;
		unsigned int *newPixels = new unsigned int[surface->w * surface->h]();
		for (int y = 0; y < surface->h; y++) {
			for (int x = 0; x < surface->w; x++) {
				int pixelIndex = y * surface->w + x;
				unsigned int pixelColor = ((unsigned int *) (surface->pixels))[pixelIndex];
				unsigned char r, g, b, a;
				SDL_GetRGBA(pixelColor, surface->format, &r, &g, &b, &a);

				if (a) {   // Don't modify transparent pixels
					unsigned short avg = ((short) (r + g + b)) / 3;
					if (avg > 150) {   // Only modify light colors
						r = r < DELTA_COLOR ? 0 : r - DELTA_COLOR;
						g = r < DELTA_COLOR ? 0 : r - DELTA_COLOR;
						b = r < DELTA_COLOR ? 0 : r - DELTA_COLOR;
					}
					newPixels[pixelIndex] = SDL_MapRGBA(surface->format, r, g, b, 255);
				}
			}
		}

		return SDL_CreateRGBSurfaceWithFormatFrom(newPixels, surface->w, surface->h, 32, surface->pitch, surface->format->format);
	}

	void select() {
		setSurface(selectedSurface);
		setTexture(nullptr);   // Forces Texture to refresh next frame
	}

	void unselect() {
		setSurface(unselectedSurface);
		setTexture(nullptr);
	}

	void retract() {
		isAnimating = false;
		Tooth::extendedCounter--;
		if (isLethal) {
			Event::pushCustomEvent(GAME_LOST);
		}
		else if (Tooth::extendedCounter == 1) {
			Event::pushCustomEvent(GAME_WON);
		}
	}

	void startRetract() {
		isAnimating = true;
	}

	void lerpBetweenPositions(int xFrom, int yFrom, int xTo, int yTo, double t) {
		int newX = (int) lerp((double) xFrom, (double) xTo, t);
		int newY = (int) lerp((double) yFrom, (double) yTo, t);

		rectangle.x = newX;
		rectangle.y = newY;
	}

	void updateAnimation(double deltaTime) {
		if (tAnim >= 1.0)
			retract();
		else {
			tAnim += deltaTime / TOOTH_RETRACTION_DURATION;
			if (tAnim > 1.0) tAnim = 1.0;

			lerpBetweenPositions(xExtended, yExtended, xRetracted, yRetracted, cbrt(tAnim));
		}
	}

public:
	Tooth(int xExtended, int yExtended, int xRetracted, int yRetracted, SDL_Surface *surface, bool isLethal = false) :
		Image(xExtended, yExtended, surface) {
		this->xExtended = xExtended;
		this->yExtended = yExtended;
		this->xRetracted = xRetracted;
		this->yRetracted = yRetracted;
		this->isLethal = isLethal;
		isExtended = true;
		isHovered = false;

		Tooth::extendedCounter++;

		isAnimating = false;
		tAnim = 0.0;

		unselectedSurface = surface;
		selectedSurface = generateHighlightedSurface(surface);
	}

	virtual ~Tooth() {
		SDL_FreeSurface(unselectedSurface);
		SDL_FreeSurface(selectedSurface);

		if (isExtended)
			Tooth::extendedCounter--;
	}

	virtual void update(double deltaTime) {
		if (isAnimating)
			updateAnimation(deltaTime);
	}

	virtual void draw(Renderer *renderer) {
		Image::draw(renderer);
	}

	virtual void notification() {
		switch (Event::getType()) {
			case SDL_MOUSEMOTION: {
				SDL_Point mousePos = {Event::getMouseMotionX(), Event::getMouseMotionY()};
				isHovered = isOnTooth(mousePos.x, mousePos.y);
				if (isExtended) {
					if (isHovered && surface == unselectedSurface)
						select();
					else if (!isHovered && surface == selectedSurface)
						unselect();
				}
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				SDL_Point mousePos = {Event::getMouseClickX(), Event::getMouseClickY()};
				if (isExtended && isOnTooth(mousePos.x, mousePos.y)) {
					isExtended = false;
					unselect();
					startRetract();
				}
				break;
			}
		}
	}
};
int Tooth::extendedCounter = 0;