#include "game_coin.h"

CoinObject::CoinObject(int speed, SDL_Texture* srf, SDL_Rect pos) : GameObject(srf, pos) {
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

	collider.radius = 16;
	collider.x = { position.x + position.w / 2, position.y + position.h / 2 };
}


void CoinObject::advance(const int &frameCount) {
	currentFrame = (frame++ / frameskip) % FRAMES;
	position.x -= speed;
	collider.x = { position.x + position.w / 2, position.y + position.h / 2 };
}
SDL_Rect* CoinObject::getRect() { 
	return &frames[currentFrame]; 
}