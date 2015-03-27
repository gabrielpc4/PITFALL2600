#pragma once
#ifndef HOLE_H_
#define HOLE_H_
#include "Sprite.h"
class Hole :
	public Sprite
{
private:
	long frames;
	int animationFrame;	
	Sprite topOverlayer;
	Sprite bottomOverlayer;
public:
	Hole();
	Hole(float startX, float startY, Color color);
	void buildHole();
	void drawOverlayer();
	~Hole();
};
#endif
