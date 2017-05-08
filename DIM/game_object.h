#pragma once
#include <SDL.h>

class GameObject {
public:
	GameObject(SDL_Surface* srf, SDL_Renderer *renderer);
	SDL_Texture* getTexture();
	// What area of the texture to show
	virtual const SDL_Rect* getRect();
	// Where is it on screen
	SDL_Rect* getPosition();
	void setPosition(const SDL_Rect &rec);
	virtual void advance(const int& frameCount);
protected:
	SDL_Texture* texture;
	SDL_Rect position;
};