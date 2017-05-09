#include "game_object.h"
#include <stdio.h>
#include <math.h>

// Constructor, init the surface attribute with srf
GameObject::GameObject(SDL_Texture* srf, SDL_Rect pos) : texture(srf), position(pos) {
	collider.radius = -1;
	collider.x = { -1, -1 };
}

SDL_Texture* GameObject::getTexture() {
	return texture;
}

const SDL_Rect* GameObject::getRect() {
	return NULL;
}

void GameObject::setPosition(const SDL_Rect &rec) {
	position = rec;
	if (collider.radius > 0) {
		collider.x = { position.x + position.w / 2, position.y + position.h / 2 };
	}
}

SDL_Rect* GameObject::getPosition() {
	return &position;
}

void GameObject::advance(const int &frameCount) {

}

float distance(const SDL_Point &a, const SDL_Point &b) {
	float res =  static_cast<float>(sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)));
	return res;
}

//Returns true in case of collision
bool GameObject::collide(const CircularCollider &collider, const CircularCollider &other) {
	if (collider.radius < 0 || other.radius < 0) {
		// One of the objects does not have collisions
		return false;
	}
	float dst = distance(collider.x, other.x);
	float rad = static_cast<float>(collider.radius + other.radius);
	return dst <= rad;
}

CircularCollider* GameObject::getCollider() {
	return &collider;
}