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

	SDL_Rect rec;
	rec.x = 50;
	rec.y = 25;
	rec.w = 128;
	rec.h = 128;
	position = rec;
}

SDL_Rect* SunObject::getRect(const int &frameCount) {
	return &frames[(frameCount/frameskip)%FRAMES];
}