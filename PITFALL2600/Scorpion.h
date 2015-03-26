#pragma once
#ifndef SCORPION_H_
#define SCORPION_H_
#include "ScorpionSprite.h"
#define SCORPION_SPEED 1
class Scorpion :
	public ScorpionSprite
{	
public:
	Scorpion();
	Scorpion(float startX, float startY);	
	void move(float player_x);	
	~Scorpion();
};
#endif

