#include "game_object.h"

// Constructor, init the surface attribute with srf
GameObject::GameObject(SDL_Surface* srf) : surface(srf) {}

SDL_Surface* GameObject::getSurface() {
	return surface;
}

const SDL_Rect* GameObject::getRect() {
	return NULL;
}

void GameObject::setPosition(const SDL_Rect &rec) {
	position = rec;
}

SDL_Rect* GameObject::getPosition() {
	return &position;
}