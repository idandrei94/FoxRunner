#include "game_object.h"

// Constructor, init the surface attribute with srf
GameObject::GameObject(SDL_Surface* srf, SDL_Renderer* renderer) : texture(SDL_CreateTextureFromSurface(renderer, srf)) {}

SDL_Texture* GameObject::getTexture() {
	return texture;
}

const SDL_Rect* GameObject::getRect(const int &frameCount) {
	return NULL;
}

void GameObject::setPosition(const SDL_Rect &rec) {
	position = rec;
}

SDL_Rect* GameObject::getPosition() {
	return &position;
}