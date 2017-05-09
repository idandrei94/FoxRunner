#include "game_fox.h"
#include <stdio.h>

FoxObject::FoxObject(SDL_Texture* srf, SDL_Rect pos) : GameObject(srf, pos) {
	this->speed = speed;

	frames[0].w = frames[1].w = frames[2].w = frames[3].w = frames[0].h = frames[1].h = frames[2].h = frames[3].h = 220;
	frames[0].x = 0;
	frames[0].y = 0;
	frames[1].x = 220;
	frames[1].y = 0;
	frames[2].x = 0;
	frames[2].y = 220;
	frames[3].x = 220;
	frames[3].y = 220;

	collider.radius = 40;
	collider.x = { position.x + position.w/2, position.y + position.h/2 };
}


void FoxObject::advance(const int &frameCount) {
	currentFrame = (frameCount / frameskip) % FRAMES;
}
SDL_Rect* FoxObject::getRect() {
	return &frames[currentFrame];
}