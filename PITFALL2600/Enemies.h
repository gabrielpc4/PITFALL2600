#ifndef ENEMIES_H_
#define ENEMIES_H_
#include "Log.h"
#include "Scorpion.h"
#include "Crocodile.h"
#include "Snake.h"

class ScenarioEnemies
{
public:
	int nScorpions;
	int nLogs;
	bool movingLogs;
	int nCrocodiles;
	int nSnakes;
	ScenarioEnemies();
};
#endif