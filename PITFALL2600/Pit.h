#pragma once
#ifndef PIT_H
#define PIT_H
#include "Sprite.h"
class Pit :
	public Sprite
{
private:
	long frames;
	int animationFrame;	
	Sprite topOverlayer;
	Sprite bottomOverlayer;
public:
	Pit();
	Pit(float startX, float startY, Color color);
	void buildPit();
	void drawOverlayer();
	~Pit();
};
#endif
