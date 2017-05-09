#include "score_object.h"
#include <stdio.h>

ScoreObject::ScoreObject() : GameObject(NULL, { 0,0,0,0 }) {}

int ScoreObject::getScore() { return score; }
void ScoreObject::increaseScore() { 
	++score;
	printf("Score >>> %d\n", score);
}