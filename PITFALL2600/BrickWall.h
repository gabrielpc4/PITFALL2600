#pragma once
#ifndef BRICKWALL_H
#define BRICKWALL_H
#include "Sprite.h"

class BrickWall :
	public Sprite
{
public:
	BrickWall();
	BrickWall(int SIDE);
	BrickWall(int startX, int startY);
};

#endif
