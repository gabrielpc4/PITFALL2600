#pragma once
#ifndef GROUNDHOLE_H
#define GROUNDHOLE_H
#include "Sprite.h"
class GroundHole :
	public Sprite
{
private:
	Rect tunnelHole;
	Sprite cover;
public:
	GroundHole();
	GroundHole(float startX, float startY);	
	void drawCover();
};
#endif
