#pragma once
#include <SDL.h>

struct CircularCollider {
	SDL_Point x;
	int radius;
};

class GameObject {
public:
	GameObject(SDL_Texture* srf, SDL_Rect pos);
	SDL_Texture* getTexture();
	// What area of the texture to show
	virtual const SDL_Rect* getRect();
	// Where is it on screen
	SDL_Rect* getPosition();
	void setPosition(const SDL_Rect &rec);
	virtual void advance(const int& frameCount);
	static bool collide(const CircularCollider &collider, const CircularCollider &other);
	CircularCollider* getCollider();
protected:
	SDL_Texture* texture;
	SDL_Rect position;
	CircularCollider collider;
};