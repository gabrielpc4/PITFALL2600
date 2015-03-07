#pragma once
#ifndef PITFALLGAME_H_
#define PITFALLGAME_H_
#include "Player.h"
#include "World.h"

class PitfallGame
{
private:
	Player* player;
	World* world;	
public:
	PitfallGame();
	void drawAll();
	void moveAll();
	void handleKeyboardInput(int key, int keyState);
	void handleKeyboardInput(unsigned char c);
	bool checkColisionX(Player* player, GameObject* object);
};

#endif