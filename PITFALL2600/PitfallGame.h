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
	bool checkCollisionX(Player* player, GameObject* object);
	bool checkCollisionY(Player* player, GameObject* object);
public:
	PitfallGame();
	void drawAll();
	void moveAll();
	void physics();
	void handleKeyboardInput(int key, int keyState);
	void handleKeyboardInput(unsigned char c);
};

#endif