#pragma once

#include "game_object.h"
#include <deque>

class BackgroundObject {
private:
	int speed;
	std::deque<SDL_Texture*> textures;
	SDL_Rect leftRec, rightRec;
	int offset;

public:
	BackgroundObject(const int &speed, SDL_Surface* surface, SDL_Renderer* renderer);
	void advance();
	SDL_Texture* getLeftTexture();
	SDL_Texture* getRightTexture();
	SDL_Rect* getLeftOffset();
	SDL_Rect* getRightOffset();
	void addBackground(SDL_Surface *surface, SDL_Renderer *renderer);
};