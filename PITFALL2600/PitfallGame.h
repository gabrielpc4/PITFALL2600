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
	bool checkCollisionX(Player* player, GameObject* object);
	bool checkCollisionY(Player* player, GameObject* object);
	void checkBoundaries();
	bool isOutOfBoundaries(GameObject* object);
	void spawnEnemies();
	void deleteWorld();
	void checkCollisionsWithEnemies();
	void moveAll();
	void physics();
	int relativePosition(Player* player, GameObject* object);
	void static printText(string text, Point p);
public:
	PitfallGame();
	void run();
	void drawAll();
	void handleKeyboardInput(int key, int keyState);
	void handleKeyboardInput(unsigned char c);
};

#endif