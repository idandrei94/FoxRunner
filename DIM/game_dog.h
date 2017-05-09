#pragma once

#include "game_object.h"

class DogObject : public GameObject {
public:
	static const int FRAMES = 4;
private:
	const int frameskip = 10;
	SDL_Rect frames[FRAMES];
	int frameCounter = 0;
	int currentFrame = 0;
	int speed;
public:
	DogObject(int speed, SDL_Texture* srf, SDL_Rect pos);
	void advance(const int &frameCount);
	SDL_Rect* getRect();
};