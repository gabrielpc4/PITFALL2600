#pragma once
#ifndef BONFIRE_H_
#define BONFIRE_H_
#include "AnimatedObject.h"
class Bonfire :
	public AnimatedObject
{
private:
	Sprite basicShape;
public:
	Bonfire();
	Bonfire(float startX, float startY);
	void buildSprite();
	void animate();
	void mirrorX();
	void draw();
	void DRAW_ON_DEBUG_MODE();
	~Bonfire();
};
#endif

