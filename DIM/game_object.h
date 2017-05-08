#pragma once
#include <SDL.h>

class GameObject {
public:
	GameObject(SDL_Surface* srf, SDL_Renderer *renderer);
	SDL_Texture* getTexture();
	virtual const SDL_Rect* getRect(const int &frameCount);
	SDL_Rect* getPosition();
	void setPosition(const SDL_Rect &rec);
protected:
	SDL_Texture* texture;
	SDL_Rect position;
};