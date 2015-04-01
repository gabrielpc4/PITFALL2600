#pragma once
#ifndef INTROSCREEN_H_
#define INTROSCREEN_H_
#include "global_constants.h"
#include "Treasure.h"
#include "Enemies.h"
#include "Player.h"
#include "ScenarioElements.h"
#include "Rect.h"
#include <iostream>
#include <string>

class IntroScreen
{
private:
	vector<Crocodile> crocodiles;
	vector<Treasure> treasures;
	Rect background;
	Rect tunnelTop;
	Rect ground;
	Rect sky;
	Rect treeTrunk1;
	Rect treeTrunk2;
	PlayerSprite playerSprite;
	Hole water;
	vector<Crocodile> staticCrocodiles;
	int frames;
	void output1(int x, int y, char *string);
	void static printText(string text, Point p, float size);
public:
	IntroScreen();
	void show();	
	~IntroScreen();
};
#endif
