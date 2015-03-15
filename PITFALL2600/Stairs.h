#pragma once
#ifndef STAIRS_H
#define STAIRS_H

#include "Sprite.h"

class Stairs :
	public Sprite
{
private:
	Rect stairsBorder;
	Rect step;	
	Sprite cover;
public:
	Stairs();
	Stairs(GLint startX, GLint startY);
	void draw();
	Sprite* hole;
	void drawCover();
};

#endif
