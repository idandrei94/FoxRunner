#include "game_sun.h"

SunObject::SunObject(SDL_Surface* srf, SDL_Renderer *renderer) : GameObject(srf, renderer) {
	frames[0].w = frames[1].w = frames[2].w = 64;
	frames[0].h = frames[1].h = frames[2].h = 64;
	frames[0].x = 0;
	frames[0].y = 0;
	frames[1].x = 0;
	frames[1].y = 64;
	frames[2].x = 64;
	frames[2].y = 0;

	position.x = 50;
	position.y = 25;
	position.w = 128;
	position.h = 128;
}

void SunObject::advance(const int &frameCount) {
	currentFrame = (frameCount/frameskip)%FRAMES;
}

SDL_Rect* SunObject::getRect() {
	return &frames[currentFrame];
}