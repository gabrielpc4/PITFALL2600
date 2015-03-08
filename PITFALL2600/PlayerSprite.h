#pragma once
#ifndef PLAYERSPRITE_H_
#define PLAYERSPRITE_H_
#include "Sprite.h"
class PlayerSprite :
	public Sprite
{
public:
	PlayerSprite();
	PlayerSprite(int startX, int startY, int animationFrame, int direction, bool climbing);
	void buildBasicShape();
	void buildClimbingSprite();
};
#endif
