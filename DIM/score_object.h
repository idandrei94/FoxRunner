#pragma once

#include "game_object.h"
#include <SDL_ttf.h>

class ScoreObject : public GameObject {
private:
	int score = 0;
	TTF_Font* gFont;
public:
	ScoreObject(SDL_Rect &pos, TTF_Font* font);
	int getScore();
	void increaseScore();
	void reset();
	SDL_Texture* getTexture();
};