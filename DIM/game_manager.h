#pragma once
#include "game_fox.h"
#include "score_object.h"
#include <list>
#include <SDL_ttf.h>
#include <memory>

// List containing all game objects
extern std::list<std::shared_ptr<GameObject> > gameObjects;

// List containing foreground game objects (displayed on top of the others)
extern std::list<std::shared_ptr<GameObject> >foregroundGameObjects;

extern TTF_Font* gFont;

extern SDL_Texture* gOver;

extern SDL_Renderer* gRenderer;

enum class GameManagerCodes{ GAME_CONTINUE, GAME_END};

enum class KeyAction {
	JUMP,
	START_GAME
};

enum class GameState {
	STATUS_DEAD, 
	STATUS_PLAYING,
	STATUS_MENU,
	STATUS_SCORE
};

class GameManager {
private:
	GameState status = GameState :: STATUS_MENU;
	std::shared_ptr<FoxObject> fox = nullptr;
	std::shared_ptr<ScoreObject> score = nullptr;
	int speed;
public:
	GameManager(const int &gSpeed, std::shared_ptr<FoxObject> gFox, std::shared_ptr<ScoreObject> gScore);
	GameManagerCodes manage();
	void generate(SDL_Texture* coinTexture, SDL_Texture* dogTexture, SDL_Texture* cloudTexture, SDL_Renderer *renderer);
	int cleanup();
	int getSpeed();
	void doAction(const KeyAction &action);
};