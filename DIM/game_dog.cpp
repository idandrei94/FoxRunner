#include "game_dog.h"
#include <stdio.h>

DogObject::DogObject(int speed, SDL_Texture* srf, SDL_Rect pos) : GameObject(srf, pos) {
	this->speed = speed;

	frames[0].w = frames[1].w = frames[2].w = frames[3].w = frames[0].h = frames[1].h = frames[2].h = frames[3].h = 90;
	frames[0].x = 0;
	frames[0].y = 0;
	frames[1].x = 90;
	frames[1].y = 0;
	frames[2].x = 0;
	frames[2].y = 90;
	frames[3].x = 90;
	frames[3].y = 90;


	collider.radius = 25;
	collider.x = { position.x + position.w / 2, position.y + position.h / 2 };
}


void DogObject::advance(const int &frameCount) {
	currentFrame = (frameCount / frameskip) % FRAMES;
	position.x -= speed;
	collider.x = { position.x + position.w / 2, position.y + position.h / 2 };
}
SDL_Rect* DogObject::getRect() {
	return &frames[currentFrame];
}