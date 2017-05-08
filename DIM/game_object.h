#pragma once
#include <SDL.h>
class GameObject {
public:
	GameObject(SDL_Surface* srf);
	SDL_Surface* getSurface();
	virtual const SDL_Rect* getRect();
	SDL_Rect* getPosition();
	void setPosition(const SDL_Rect &rec);
protected:
	SDL_Surface* surface;
	SDL_Rect position;
};