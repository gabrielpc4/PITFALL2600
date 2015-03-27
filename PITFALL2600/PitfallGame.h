#pragma once
#ifndef PITFALLGAME_H_
#define PITFALLGAME_H_
#include <string>
#include "Player.h"
#include "Enemies.h"
#include "World.h"
#include <vector>

using namespace std;

#define SPACE_BAR 32
#define RESPAWN_FRAMES 70

#define BOX_DETECTION 0
#define PIXEL_BY_PIXEL_DETECTION 1

class PitfallGame
{
private:
	Player* player;	
	World* world;	
	vector<Log> logs;
	Scorpion* scorpion;
	vector<Crocodile> crocodiles;
	int scenarioNumber;
	int score;
	bool areColliding(Player* player, Sprite& object, int detectionType);	
	void checkBoundaries();
	bool isOutOfBoundaries(Sprite* object);
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
	bool isInside(Polygon& rect1, Polygon& rect2);
public:
	PitfallGame();
	void run();
	void drawAll();
	void handleKeyboardInput(int key, int keyState);
	void handleKeyboardInput(unsigned char c);
};

#endif