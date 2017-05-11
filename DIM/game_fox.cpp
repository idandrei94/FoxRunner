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

	collider.radius = 50;
	collider.x = { position.x + position.w/2, position.y + position.h/2 };

	GROUND_LEVEL = pos.y;
}


void FoxObject::advance(const int &frameCount) {
	collider.x = { position.x + position.w / 2, position.y + position.h / 2 };
	currentFrame = (frameCount / frameskip) % FRAMES;
	if (isJumping) {
		verticalAcc -= 45;
		if (position.y - verticalAcc / 100 <= GROUND_LEVEL) {
			position.y -= verticalAcc / 100; 
		}
		else
		{
			position.y = GROUND_LEVEL;
			isJumping = false;
			verticalAcc = 0;
		}

	}
}
SDL_Rect* FoxObject::getRect() {
	if (isJumping) {
		if (verticalAcc > 0) {
			return &frames[1];
		}
		else {
			return &frames[3];
		}
	}
	else {
		return &frames[currentFrame];
	}
}


void FoxObject::jump() {
	if (!isJumping) {
		verticalAcc = JUMP_STRENGTH;
		isJumping = true;
	}
}

void FoxObject::reset() {
	verticalAcc = 0;
	isJumping = false;
}