#include "game_manager.h"
#include "game_coin.h"
#include "game_dog.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <memory>
#include "object_over.h"

// List containing all game objects
std::list<std::shared_ptr<GameObject> > gameObjects;
//
// List containing foreground game objects (displayed on top of the others)
std::list<std::shared_ptr<GameObject> >foregroundGameObjects;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(1, 10000);

std::shared_ptr<DogObject> lastDog;

const int COIN_CHANCE = 500;
int DOG_CHANCE = 100;
const int DOG_MIN_DISTANCE = 350;
int immunityFrames = 60;


GameManager::GameManager(const int &gSpeed, std::shared_ptr<FoxObject> gFox, std::shared_ptr<ScoreObject> gScore) : fox(gFox), score(gScore), speed(gSpeed) {}

GameManagerCodes GameManager::manage() {
	if (status == GameState::STATUS_PLAYING && !immunityFrames) {
		for (std::list<std::shared_ptr<GameObject> >::iterator it = gameObjects.begin(); it != gameObjects.end(); it++) {
			if (GameObject::collide(*fox->getCollider(), *(*it)->getCollider())) {
				// Objects collide
				// Check if it's a coin or not
				if (!std::dynamic_pointer_cast<CoinObject>(*it)) {
					// It's not a coin
					// Remove the fox with the Game Over screen
					foregroundGameObjects.remove(fox);
					SDL_Rect pos = { 0,0,640,480 };
					std::shared_ptr<GameObject> obj(new GameObject(gOver, pos));
					foregroundGameObjects.push_back(obj);
					pos = {230, 320, 180, 140};
					score->setPosition(pos);
					status = GameState::STATUS_DEAD;
					return GameManagerCodes::GAME_END;
				}
				else {
					// It's a coin, destroy it and increase the score
					it = gameObjects.erase(it);
					score->increaseScore();
				}
			}
		}
	}
	return GameManagerCodes::GAME_CONTINUE;
}


void GameManager::generate(SDL_Texture* coinTexture, SDL_Texture* dogTexture, SDL_Texture* cloudTexture, SDL_Renderer *renderer) {
	if(immunityFrames > 0)
		immunityFrames--;
	int random = dis(gen);
	bool ok = true;
	if (random < COIN_CHANCE) {
		random = dis(gen);
		SDL_Rect position = { 640, 230-(random/500), 32, 32 };
		std::shared_ptr<GameObject> coin(new CoinObject(speed, coinTexture, position));
		for (std::list<std::shared_ptr<GameObject> >::iterator it = gameObjects.begin(); it != gameObjects.end(); it++) {
			if (GameObject::collide(*coin->getCollider(), *(*it)->getCollider())) {
				ok = false;
			}
		}
		if (ok) {
			gameObjects.push_back(coin);
		}
	}
	ok = true;
	random = dis(gen);
	if (random < DOG_CHANCE) {
		SDL_Rect position = { 640,255,130,130 };
		std::shared_ptr<DogObject> dog(new DogObject(speed, dogTexture, position));
		if (lastDog != nullptr && lastDog->getCollider()->x.x > DOG_MIN_DISTANCE) {
			ok = false;
		}
		if (ok ) {
			gameObjects.push_back(dog);
			lastDog = dog;
			DOG_CHANCE++;
		}
	}
}

int GameManager::cleanup() {
	int count = 0;
	for (std::list<std::shared_ptr<GameObject> >::iterator it = gameObjects.begin(); it != gameObjects.end();) {
		if ((*it)->getPosition()->x < -200) {
			it = gameObjects.erase(it);
			count++;
		}
		else ++it;
	}
	for (std::list<std::shared_ptr<GameObject> >::iterator it = foregroundGameObjects.begin(); it != foregroundGameObjects.end();) {
		if ((*it)->getPosition()->x < -200) {
			it = foregroundGameObjects.erase(it);
			count++;
		}
		else ++it;
	}
	return count;
}

int GameManager::getSpeed() {
	return speed;
}

void GameManager::doAction(const KeyAction &action) {
	switch (action) {
	case KeyAction::JUMP:
		if (status == GameState::STATUS_PLAYING) {
			printf("Jumping\n");
			fox->jump();
		}
		break;
	case KeyAction::START_GAME:
		if (status != GameState::STATUS_PLAYING) {
			score->reset();
			score->setPosition({ 475,410,140,70 });
			status = GameState::STATUS_PLAYING;
			foregroundGameObjects.clear();
			foregroundGameObjects.push_front(score);
			SDL_Rect pos = { 5, 280, 120, 100 };
			fox->setPosition(pos);
			fox->reset();
			foregroundGameObjects.push_front(fox);
			immunityFrames = 60;
		}
		break;
	}
}