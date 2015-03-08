#pragma once
#ifndef STAIRS_H
#define STAIRS_H

#include "GameObject.h"

class Stairs :
	public GameObject
{
private:
	Rect stairsBorder;
	Rect step;	
public:
	Stairs();
	Stairs(GLint startX, GLint startY);
	void draw();
	GameObject* hole;
};

#endif
