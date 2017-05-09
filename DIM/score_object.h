#pragma once

#include "game_object.h"

class ScoreObject : public GameObject {
private:
	int score = 0;
public:
	ScoreObject();
	int getScore();
	void increaseScore();
};