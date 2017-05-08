#include "mySDL_init.h"
#include <stdio.h>
#include <string>
#include <deque>

#include "game_sun.h"
#include "game_object.h"
#include <SDL_image.h>
#include "background_object.h"
#include "game_coin.h"


// The game speed
const int gSpeed = 4;

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

//The background image
SDL_Surface* gBackground1 = nullptr;
SDL_Surface* gBackground2 = nullptr;

//The sun sprite sheet
SDL_Surface* gSun = nullptr;

//The coin sprite sheet
SDL_Surface* gCoin = nullptr;

//Game renderer
SDL_Renderer* gRenderer = nullptr;


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

// List containing all game objects
std::deque<GameObject*> gameObjects;

// Background slider object
BackgroundObject *backgroundObject = nullptr;

// Clear all the objects from memory
void clearGameObjects() {
	for (std::deque<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++) {
		delete(*it);
	}
	delete backgroundObject;
}


bool init() {
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	gSun = loadSurface("res/sun.png");
	if (gSun == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "res/sun.png", SDL_GetError());
		success = false;
	}

	gCoin = loadSurface("res/coin.png");
	if (gCoin == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "res/sun.png", SDL_GetError());
		success = false;
	}

	return success;
}

void close() {
	//Deallocate surface
	SDL_FreeSurface(gBackground1);
	SDL_FreeSurface(gSun);
	gBackground1 = nullptr;
	gSun = nullptr;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	clearGameObjects();
	//Quit SDL subsystems
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
	int frame = 0;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0)
		{
			//User pressed the window X
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		//SDL_RenderCopy(gRenderer, SDL_CreateTextureFromSurface(gRenderer, gBackground1), NULL, NULL);

		backgroundObject->advance();
		SDL_RenderCopy(gRenderer, backgroundObject->getLeftTexture(), NULL, backgroundObject->getLeftOffset());
		SDL_RenderCopy(gRenderer, backgroundObject->getRightTexture(), NULL, backgroundObject->getRightOffset());

		//loop through objects
		for (std::deque<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->advance(frame);
			const SDL_Rect* rec = (*it)->getRect();
			printf("{ %d, %d, %d, %d }\n", rec->x, rec->y, rec->w, rec->x);
			SDL_RenderCopy(gRenderer, (*it)->getTexture(), (*it)->getRect(), (*it)->getPosition());
		}
		//Update the surface
		SDL_UpdateWindowSurface(gWindow);


		SDL_RenderPresent(gRenderer);
		++frame;
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

	SunObject* sun = new SunObject(gSun, gRenderer);
	gameObjects.push_back(sun);

	CoinObject* coin = new CoinObject(gSpeed, gCoin, gRenderer);
	gameObjects.push_back(coin);
}