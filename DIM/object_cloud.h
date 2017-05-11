#pragma once
#include "game_object.h"

class CloudObject : public GameObject {
private:
	int speed;
	SDL_Rect rect = { 0,0,330,227 };
public:
	CloudObject(int &speed, SDL_Texture* texture, SDL_Rect &pos);
	void advance(const int &frameCount);
	const SDL_Rect* getRect();
};
