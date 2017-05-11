#include "object_cloud.h"

CloudObject::CloudObject(int &speed, SDL_Texture* texture, SDL_Rect &position) : GameObject(texture, position) {
	this->speed = speed;
}

void CloudObject::advance(const int &frameCount) {
	position.x -= speed;
}

const SDL_Rect* CloudObject::getRect() {
	return &rect;
}