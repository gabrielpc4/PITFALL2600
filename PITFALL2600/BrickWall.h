#pragma once
#ifndef BRICKWALL_H
#define BRICKWALL_H
#include "GameObject.h"

class BrickWall :
	public GameObject
{
public:
	BrickWall();
	BrickWall(int startX, int startY);
	void draw();
};

#endif
