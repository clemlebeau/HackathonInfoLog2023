#pragma once

#include "Event.hpp"
#include "Image.hpp"
#include "Lerp.h"
#include "Scene.hpp"

class ImageAnimation {
private:
	int widthFrom;
	int widthTo;
	int overEventCode;
	double t;
	double duration;

	bool isAnimating;

	void animateImage(Image *image) {
		int width = (int) lerp((double) widthFrom, (double) widthTo, t);
		image->resize(width);
		image->move(image->getRectangle().x, RENDER_HEIGHT - image->getRectangle().h);
	}

public:
	ImageAnimation(int widthFrom, int widthTo, double duration, int overEventCode = ANIMATION_END, bool isAnimating = false) {
		this->widthFrom = widthFrom;
		this->widthTo = widthTo;
		this->duration = duration;

		this->overEventCode = overEventCode;
		this->isAnimating = isAnimating;

		this->t = 0;
	}

	void update(double deltaTime, Image *image) {
		if (isAnimating && t <= 0.0) {
			Event::pushCustomEvent(overEventCode);
		}
		if (isAnimating) {
			t -= deltaTime / duration;
			if (t < 0.0) t = 0.0;
			animateImage(image);
		}
	}

	void start() { isAnimating = true; }

	void stop() { isAnimating = false; }
};