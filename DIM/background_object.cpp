#include "background_object.h"

// Speed should be a divisor of the screen width, for convenience 
BackgroundObject::BackgroundObject(const int &speed, SDL_Surface* surface, SDL_Renderer* renderer) {
	textures.push_back(SDL_CreateTextureFromSurface(renderer, surface));
	leftRec = { speed,0,640,480 };
	rightRec = { 640+speed,0, 640, 480 };
	int offset = 0;
	this->speed = speed;
}

void BackgroundObject::addBackground(SDL_Surface *surface, SDL_Renderer *renderer) {
	textures.push_back(SDL_CreateTextureFromSurface(renderer, surface));
}

void BackgroundObject::advance() {
	leftRec.x -= speed;
	if (leftRec.x < -640) {
		textures.push_back(*textures.begin());
		textures.pop_front();
		leftRec.x = rightRec.x-speed;
		rightRec.x = 640-speed;
	}
	else {
		rightRec.x -= speed;
	}
}

SDL_Rect* BackgroundObject::getLeftOffset() {
	return &leftRec;
}

SDL_Rect* BackgroundObject::getRightOffset() {
	return &rightRec;
}

SDL_Texture* BackgroundObject::getLeftTexture() {
	return *textures.begin();
}

SDL_Texture* BackgroundObject::getRightTexture() {
	if (textures.size() > 1)
		return *(textures.begin() + 1);
	else
		return *textures.begin();
}