#include "object_text.h"
#include <string>

TextObject::TextObject(SDL_Rect &pos, TTF_Font* gFont, SDL_Renderer *gRenderer) : GameObject(nullptr, pos) {
	std::string s = "Press R to (re)start the game. \nPress SPACE to jump.\nPress M to (un)mute.";
	SDL_Surface* srf = TTF_RenderText_Blended_Wrapped(gFont, s.c_str(), { 0,0,0 }, 640);
	texture = SDL_CreateTextureFromSurface(gRenderer, srf);
}