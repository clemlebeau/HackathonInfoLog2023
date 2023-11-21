#pragma once

#include "Image.hpp"

class ClickableImage : public Image {
private:
	int customEventCode;

public:
	ClickableImage(int x, int y, SDL_Texture *texture, int customEventCode) :
		Image(x, y, texture) {
		this->customEventCode = customEventCode;
	}

	virtual void notification() {
		if (Event::getMouseClickX() >= this->rectangle.x && Event::getMouseClickX() < this->rectangle.x + this->rectangle.w &&
			  Event::getMouseClickY() >= this->rectangle.y && Event::getMouseClickY() < this->rectangle.y + this->rectangle.y)
			Event::pushCustomEvent(customEventCode);
	}
};