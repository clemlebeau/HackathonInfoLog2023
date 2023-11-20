#pragma once

#include "Image.hpp"

class Tooth : public Image {
private:
	bool isSelected;
	int xExtended;
	int yExtended;
	int xRetracted;
	int yRetracted;

	bool isOnTooth(int x, int y) {
    // Translate according to component position to get texture coordinates
    int texX = x - this->rectangle.x;
		int texY = y - this->rectangle.y;
		
    if (texX < 0 || texX >= surface->w || texY < 0 || texY >= surface->h) return false; // Out of texture bounds 

		unsigned long pixelIndex = texX * surface->w + texY;
		unsigned int pixelColor = ((unsigned int *) (surface->pixels))[pixelIndex];
		unsigned char buffer, alpha; // buffer is only necessary because the next function doesn't support nullptr for unused values
		SDL_GetRGBA(pixelColor, surface->format, &buffer, &buffer, &buffer, &alpha);

		return (bool)alpha; // Only on tooth if corresponding pixel is non transparent
	}

public:
	Tooth(int xExtended, int yExtended, int xRetracted, int yRetracted, SDL_Surface *surface) :
		Image(xExtended, yExtended, surface) {
		this->xExtended = xExtended;
		this->yExtended = yExtended;
		this->xRetracted = xRetracted;
		this->yRetracted = yRetracted;
		isSelected = false;
	}

	virtual ~Tooth() {}

	virtual void update(double deltaTime) {}

	virtual void draw(Renderer *renderer) {
		Image::draw(renderer);
		// Draw selected rectangle if necessary
	}

	virtual void notification() {
		switch (Event::getType()) {
			case SDL_MOUSEMOTION:
				SDL_Point mousePos = {Event::getMouseMotionX(), Event::getMouseMotionY()};
				isSelected = isOnTooth(mousePos.x, mousePos.y);
				break;
			case SDL_MOUSEBUTTONUP:
        
				break;
		}
	}
};