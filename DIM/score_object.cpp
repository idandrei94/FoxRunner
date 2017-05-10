#include "score_object.h"
#include <stdio.h>
#include "game_manager.h"
#include <string>

ScoreObject::ScoreObject(SDL_Rect &pos, TTF_Font* font) : GameObject(NULL, pos), gFont(font) {}

int ScoreObject::getScore() { return score; }
void ScoreObject::increaseScore() { 
	++score;
	printf("Score >>> %d\n", score);
}

void ScoreObject::reset() { score = 0; }

SDL_Texture* ScoreObject::getTexture() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	std::string s = "Score: " + std::to_string(score);
	SDL_Surface* srf = TTF_RenderText_Solid(gFont, s.c_str(), { 0,0,0 });
	texture = SDL_CreateTextureFromSurface(gRenderer, srf);
	return texture;
}