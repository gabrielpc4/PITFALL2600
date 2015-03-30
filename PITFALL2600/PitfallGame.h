#pragma once
#ifndef PITFALLGAME_H_
#define PITFALLGAME_H_
#include <string>
#include "Player.h"
#include "Enemies.h"
#include "World.h"
#include "File.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <vector>

using namespace std;

#define SPACE_BAR 32
#define RESPAWN_FRAMES 70

#define BOX_DETECTION 0
#define PIXEL_BY_PIXEL_DETECTION 1

class ScenarioEnemies
{
public:
	int nScorpions;
	int nLogs;
	bool movingLogs;
	int nCrocodiles;
	int nSnakes;
	ScenarioEnemies()
	{
		nScorpions = 0;
		nLogs = 0;
		movingLogs = false;
		nCrocodiles = 0;
		nSnakes = 0;
	}
};

class PitfallGame
{
private:
	Player* player;	
	World* world;	
	vector<Log> logs;
	Scorpion* scorpion;
	vector<Crocodile> crocodiles;
	Snake* snake;
	File enemiesFile;
	int scenarioNumber;
	int score;
	bool paused;
	bool allowCrocodiles;
	bool DEBUG_MODE;
	bool GOD_MODE;


	vector<ScenarioEnemies> positiveScenarios;
	vector<ScenarioEnemies> negativeScenarios;
	
	bool areCollidingX(Player* player, Crocodile* crocodile);
	bool areColliding(Player* player, Sprite& object, int detectionType);	
	bool areClose(Player* player, Sprite* object);
	void checkBoundaries();
	bool isOutOfBoundaries(Player* player);
	void spawnEnemies();
	void deleteEnemies();
	void checkCollisionsWithEnemies();
	void moveAll();
	void physics();
	int relativePosition(Player* player, Sprite* object);
	void static printText(string text, Point p);
	bool isAbleToClimbOut(Player* player);
	void centerOnStair(Player* player);
	bool willFall(Player* player, Sprite* hole);
	void showHUD();
	void reset();
	bool canGrabVine(Player* player);
	bool isInside(Point& p, Rect& rect);
	bool isInside(Rect& rect1, Rect& rect2);
	bool isPaused();
	void drawOutline(Sprite& object);
	void drawOutline(float x, float y, float width, float height);
	void drawCollisionRectangles();
	void freezeHoles();
	void unFreezeHoles();
	void raffleEnemies();
public:
	PitfallGame();
	void run();
	void drawAll();
	void handleKeyboardInput(int key, int keyState);
	void handleKeyboardInput(unsigned char c);
	ScenarioEnemies& thisScenario();
};

#endif