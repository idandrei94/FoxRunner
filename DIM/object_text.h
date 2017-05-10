#pragma once

#include "game_object.h"
#include <SDL_ttf.h>

class TextObject : public GameObject {
public:
	TextObject(SDL_Rect &pos, TTF_Font* gFont, SDL_Renderer *gRenderer);
private:
};