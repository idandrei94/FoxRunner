#include "mySDL_init.h"
#include <stdio.h>
#include <string>

#include "game_sun.h"
#include "game_object.h"
#include <SDL_image.h>
#include "background_object.h"
#include "game_coin.h"
#include "game_fox.h"
#include "game_dog.h"
#include <list>
#include "game_manager.h"
#include <memory>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "object_text.h"

// The game speed
const int gSpeed = 8;
int FRAME_COUNT = 0; 

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

//The background image
SDL_Surface* gBackground1 = nullptr;
SDL_Surface* gBackground2 = nullptr;

//The sun sprite sheet
SDL_Texture* gSun = nullptr;

//The coin sprite sheet
SDL_Texture* gCoin = nullptr;

//The player fox spritesheet
SDL_Texture *gFox = nullptr;

//The obstacle dog spritesheet
SDL_Texture* gDog = nullptr;

//The Game Over overlay
SDL_Texture* gOver = nullptr;

//Clouds
SDL_Texture* gCloud = nullptr;

//Game renderer
SDL_Renderer* gRenderer = nullptr;


//Game manager, keeps track of score/collisions
GameManager* gManager;

// Responsible for sound
Mix_Music* gMusic = nullptr;

// Sound assets
Mix_Chunk* gSong1 = nullptr;

//Starts up SDL and creates the window
bool init();

//Loads all the assets
bool loadMedia();

//Frees media and shuts down SDL
void close();

// Loads a surface from an image and optimizes it
SDL_Surface* loadSurface(std::string path);

// Create the game objects
void initGameObjects();

// Background slider object
BackgroundObject *backgroundObject = nullptr;

// True-type font used in the game
TTF_Font *gFont = nullptr;

// Clear all the objects from memory
void clearGameObjects() {
	gameObjects.clear();
	foregroundGameObjects.clear();
	delete backgroundObject;
}


bool init() {
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else 
	{
		//Create window
		gWindow = SDL_CreateWindow("The quick brown fox jumps over the lazy dog.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize!\n");
					//success = false;
				}
				if (Mix_OpenAudio(44100, AUDIO_S16LSB, 2, 2048) < 0) {
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", SDL_GetError());
					success = false;
				} 
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load splash image
	gBackground1 = loadSurface("res/background1.png");
	if (gBackground1 == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "res/background1.png", SDL_GetError());
		success = false;
	}

	gBackground2 = loadSurface("res/background2.png");
	if (gBackground2 == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "res/background2.png", SDL_GetError());
		success = false;
	}

	gSun = SDL_CreateTextureFromSurface(gRenderer, loadSurface("res/sun.png"));
	if (gSun == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "res/sun.png", SDL_GetError());
		success = false;
	}

	gCoin = SDL_CreateTextureFromSurface(gRenderer, loadSurface("res/coin.png"));
	if (gCoin == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "res/coin.png", SDL_GetError());
		success = false;
	}

	gFox = SDL_CreateTextureFromSurface(gRenderer, loadSurface("res/fox.png"));
	if (gCoin == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "res/fox.png", SDL_GetError());
		success = false;
	}

	gDog = SDL_CreateTextureFromSurface(gRenderer, loadSurface("res/dog.png"));
	if (gCoin == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "res/dog.png", SDL_GetError());
		success = false;
	}

	gOver = SDL_CreateTextureFromSurface(gRenderer, loadSurface("res/game_over.png"));
	if (gCoin == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "res/game_over.png", SDL_GetError());
		success = false;
	}

	gCloud = SDL_CreateTextureFromSurface(gRenderer, loadSurface("res/cloud.png"));
	if (gCoin == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "res/cloud.png", SDL_GetError());
		success = false;
	}

	gSong1 = Mix_LoadWAV("res/OST1.wav");
	if (gSong1 == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	
	gFont = TTF_OpenFont("res/font.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	return success;
}

void close() {
	//Deallocate surface
	SDL_FreeSurface(gBackground1);
	SDL_FreeSurface(gBackground2);
	SDL_DestroyTexture(gSun);
	SDL_DestroyTexture(gCoin);
	SDL_DestroyTexture(gFox);
	SDL_DestroyTexture(gDog);
	SDL_DestroyTexture(gOver);
	SDL_DestroyTexture(gCloud);
	gBackground1 = nullptr;
	gSun = nullptr;
	gCoin = nullptr;
	gFox = nullptr;
	gDog = nullptr;
	gOver = nullptr;
	gCloud = nullptr;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	Mix_FreeChunk(gSong1);
	gSong1 = nullptr;

	Mix_FreeMusic(gMusic);
	gMusic = nullptr;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	clearGameObjects();
	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int startGame() {
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
	}
	initGameObjects();
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	Mix_PlayChannel(-1, gSong1, -1);
	while (!quit) {
		while (SDL_PollEvent(&e) != 0)
		{
			//User pressed the window X
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_SPACE:
					gManager->doAction(KeyAction::JUMP);
					break;
				case SDLK_r:
					gManager->doAction(KeyAction::START_GAME);
					break;
				case SDLK_m:
					if (Mix_Volume(-1, -1) == 0)
						Mix_Volume(-1, 128);
					else
						Mix_Volume(-1, 0);
					break;
				}
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		gManager->cleanup();
		gManager->generate(gCoin, gDog, gCloud, gRenderer);
		if (gManager->manage() == GameManagerCodes::GAME_END) {
		}

		backgroundObject->advance();
		SDL_RenderCopy(gRenderer, backgroundObject->getLeftTexture(), NULL, backgroundObject->getLeftOffset());
		SDL_RenderCopy(gRenderer, backgroundObject->getRightTexture(), NULL, backgroundObject->getRightOffset());

		//loop through objects
		for (std::list<std::shared_ptr<GameObject> >::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->advance(FRAME_COUNT);
			SDL_RenderCopy(gRenderer, (*it)->getTexture(), (*it)->getRect(), (*it)->getPosition());
		}
		for (std::list<std::shared_ptr<GameObject> >::iterator it = foregroundGameObjects.begin(); it != foregroundGameObjects.end(); ++it) {
			(*it)->advance(FRAME_COUNT);
			SDL_RenderCopy(gRenderer, (*it)->getTexture(), (*it)->getRect(), (*it)->getPosition());
		}
		//Update the surface
		SDL_UpdateWindowSurface(gWindow);


		SDL_RenderPresent(gRenderer);
		++FRAME_COUNT;
	}
	close();
	return 0;
}

SDL_Surface* loadSurface(std::string path) {

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
		//Get rid of old loaded surface
	}

	return loadedSurface;
}


void initGameObjects() {
	backgroundObject = new BackgroundObject(gSpeed, gBackground1, gRenderer);
	backgroundObject->addBackground(gBackground2, gRenderer);
	backgroundObject->addBackground(gBackground2, gRenderer);
	backgroundObject->addBackground(gBackground2, gRenderer);
	backgroundObject->addBackground(gBackground1, gRenderer);
	backgroundObject->addBackground(gBackground1, gRenderer);
	backgroundObject->addBackground(gBackground2, gRenderer);

	SDL_Rect pos = { 450, 25, 128, 128 };
	std::shared_ptr<SunObject> sun( new SunObject(gSun, pos));
	gameObjects.push_back(sun);
	pos = { 5, 280, 120, 100 };
	std::shared_ptr<FoxObject> fox( new FoxObject(gFox, pos));
	//foregroundGameObjects.push_back(fox);

	pos = { 475,410,140,70 };
	std::shared_ptr<ScoreObject> score(new ScoreObject(pos, gFont));
	//foregroundGameObjects.push_front(score);

	gManager = new GameManager(gSpeed, fox, score);

	pos = { 60,145, 1500, 190 };
	std::shared_ptr<GameObject> menu(new TextObject(pos, gFont, gRenderer));
	foregroundGameObjects.push_front(menu);
}