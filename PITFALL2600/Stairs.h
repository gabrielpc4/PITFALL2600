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
	Sprite overlayer;
public:
	Stairs();
	Stairs(GLint startX, GLint startY);
	void draw();
	Sprite* exit;
	void drawOverlayer();
	~Stairs();
};

#endif
