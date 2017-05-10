#pragma once
#include "game_fox.h"
#include "score_object.h"
#include <list>
#include <memory>

enum class GameManagerCodes{ GAME_CONTINUE, GAME_END};

enum class KeyAction {
	JUMP
};

class GameManager {
private:
	std::shared_ptr<FoxObject> fox;
	std::shared_ptr<ScoreObject> score;
	int speed;
public:
	GameManager(const int &gSpeed, std::shared_ptr<FoxObject> gFox, std::shared_ptr<ScoreObject> gScore);
	GameManagerCodes manage(std::list<std::shared_ptr<GameObject> > &gameObjects);
	void generate(std::list<std::shared_ptr<GameObject> > &gameObjects, std::list<std::shared_ptr<GameObject> > &foregroundGameObjects, SDL_Texture* coinTexture, SDL_Texture* dogTexture, SDL_Texture* cloudTexture, SDL_Renderer *renderer);
	int cleanup(std::list<std::shared_ptr<GameObject> > &gameObjects, std::list<std::shared_ptr<GameObject> > &foregroundGameObjects);
	int getSpeed();
	void doAction(const KeyAction &action);
};