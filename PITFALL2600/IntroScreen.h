#pragma once
#include "Treasure.h"
#include "Enemies.h"
#include "PlayerSprite.h"
#include "ScenarioElements.h"
class IntroScreen
{
private:
	PlayerSprite player;
	LogSprite log;
	ScorpionSprite scorpion;
	Snake snake;
	vector<Crocodile> crocodiles;
	Bonfire bonfire;
	Hole blackhole;
	Hole water;
	vector<Treasure> treasure;
public:
	IntroScreen();
	void show();
	~IntroScreen();
};

