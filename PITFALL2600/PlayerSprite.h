#pragma once
#ifndef PLAYERSPRITE_H_
#define PLAYERSPRITE_H_
#include "Sprite.h"
class PlayerSprite :
	public Sprite
{
private:
	long frames;
protected:
	int lookingDirection;
	bool _climbing;
	bool _walking;
	int _climbingDirection;
public:
	PlayerSprite();
	PlayerSprite(float startX, float startY);
	void buildBasicShape();
	void buildSprite(int animationFrame);
	void buildClimbingSprite();
	void push_back(Rect rect);
	void push_back(Polygon pol);
	void animate(int& animationFrame, int min, int max);
	void mirrorX();
};
#endif
