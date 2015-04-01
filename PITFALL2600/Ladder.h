#pragma once
#ifndef LADDER_H
#define LADDER_H
#include "Sprite.h"
class Ladder :
	public Sprite
{
private:
	Rect stairsBorder;
	Rect step;	
	Sprite overlayer;
public:
	Ladder();
	Ladder(GLint startX, GLint startY);
	void draw();
	Sprite* exit;
	void drawOverlayer();
	~Ladder();
};

#endif
