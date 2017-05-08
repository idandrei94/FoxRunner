#include "mySDL_init.h"
#include <stdio.h>
#include <string>
#include <vector>

#include "game_sun.h"
#include "game_object.h"


//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

//The background image
SDL_Surface* gBackground = nullptr;

//The sun sprite sheet
SDL_Surface* gSun = nullptr;

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
std::vector<GameObject*> gameObjects;

// Clear all the objects from memory
void clearGameObjects(std::vector<GameObject*>* list) {
	for (std::vector<GameObject*>::iterator it = list->begin(); it <= list->end(); it++) {
		delete(*it);
	}
	delete list;
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
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load splash image
	gBackground = loadSurface("res/background1.bmp");
	if (gBackground == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "res/background1.bmp", SDL_GetError());
		success = false;
	}

	gSun = loadSurface("res/sun.bmp");
	if (gSun == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "res/sun.bmp", SDL_GetError());
		success = false;
	}
	return success;
}

void close() {//Deallocate surface
	SDL_FreeSurface(gBackground);
	gBackground = nullptr;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

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
	while (!quit) {
		while (SDL_PollEvent(&e) != 0)
		{
			//User pressed the window X
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);
		//loop through objects
		for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			SDL_BlitScaled((*it)->getSurface(), (*it)->getRect(), gScreenSurface, (*it)->getPosition());
		}
		//Update the surface
		SDL_UpdateWindowSurface(gWindow);
	}
	close();
	return 0;
}

SDL_Surface* loadSurface(std::string path) {

	//The final optimized image
	SDL_Surface* optimizedSurface = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			SDL_SetColorKey(optimizedSurface, SDL_TRUE, SDL_MapRGB(optimizedSurface->format, 0,0,0));
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}


void initGameObjects() {
	SunObject* sun = new SunObject(gSun);
	gameObjects.push_back(sun);
}