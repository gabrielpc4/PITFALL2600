#pragma once
#ifndef PITFALLGAME_H_
#define PITFALLGAME_H_
#include "Player.h"
#include "Enemies.h"
#include "World.h"

class PitfallGame
{
private:
	Player* player;	
	World* world;	
	Log* log;
public:
	PitfallGame();
	void drawAll();
	void moveAll();
	void handleKeyboardInput(int key, int keyState);
	void handleKeyboardInput(unsigned char c);
	bool checkColisionX(Player* player, GameObject* object);
	bool checkColisionY(Player* player, GameObject* object);
};

#endif