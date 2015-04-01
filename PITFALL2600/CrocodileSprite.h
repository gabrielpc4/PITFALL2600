#pragma once
#ifndef CROCODILESPRITE_H_
#define CROCODILESPRITE_H_
#include "AnimatedObject.h"
#define OPEN 1
#define CLOSED  0
class CrocodileSprite :
	public AnimatedObject
{
protected:
	bool mouthState;
public:
	CrocodileSprite();
	CrocodileSprite(float startX, float startY);
	void buildSprite();	
	~CrocodileSprite();
};
#endif

