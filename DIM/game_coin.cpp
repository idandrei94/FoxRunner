#include "game_coin.h"

CoinObject::CoinObject(int speed, SDL_Surface* srf, SDL_Renderer *renderer) : GameObject(srf, renderer) {
	this->speed = speed;

	frames[0].w = frames[1].w = frames[2].w = frames[3].w = frames[0].h = frames[1].h = frames[2].h = frames[3].h = 32;
	frames[0].x = 0;
	frames[0].y = 0;
	frames[1].x = 32;
	frames[1].y = 0;
	frames[2].x = 0;
	frames[2].y = 32;
	frames[3].x = 32;
	frames[3].y = 32;

	position = { 320, 240, 32, 32 };
}


void CoinObject::advance(const int &frameCount) {
	currentFrame = (frameCount / frameskip) % FRAMES;
	position.x -= speed;
	
	if (position.x < 30)
		position.x = 600;
}
SDL_Rect* CoinObject::getRect() { 
	return &frames[currentFrame]; 
}