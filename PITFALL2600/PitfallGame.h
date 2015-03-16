#pragma once
#ifndef PITFALLGAME_H_
#define PITFALLGAME_H_
#include <string>
#include "Player.h"
#include "Enemies.h"
#include "World.h"

class PitfallGame
{
private:
	Player* player;	
	World* world;	
	vector<Log> log;
	int scenarioNumber;
	int score;
	bool checkCollisionX(Player* player, Sprite& object);
	bool checkCollisionY(Player* player, Sprite& object);
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
public:
	PitfallGame();
	void run();
	void drawAll();
	void handleKeyboardInput(int key, int keyState);
	void handleKeyboardInput(unsigned char c);
};

#endif