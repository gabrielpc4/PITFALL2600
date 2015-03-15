#pragma once
#ifndef PLAYERSPRITE_H_
#define PLAYERSPRITE_H_
#include "Sprite.h"
class PlayerSprite :
	public Sprite
{
public:
	PlayerSprite();
	PlayerSprite(float startX, float startY);
	void buildBasicShape();
	void buildSprite(int animationFrame, int direction, bool climbing);
	void buildClimbingSprite();
};
#endif
