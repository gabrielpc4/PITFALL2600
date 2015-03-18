#pragma once
#ifndef PLAYERSPRITE_H_
#define PLAYERSPRITE_H_
#include "Sprite.h"
class PlayerSprite :
	public Sprite
{
// Variables
protected:
	int _lookingDirection;
	bool _climbing;
	bool _walking;
	int _climbingDirection;
	bool _takingHit;
	bool _jumping;
	bool _falling;

private:
	long frames;
	float _realY;
	Color pantsColor;
	Color shirtColor;
	Color skinColor;
	Color hatColor;

	//Methods
	void buildSwingingSprite();
	void buildBasicShape();
	void buildClimbingSprite();
	void push_back(Rect rect);
	void push_back(Polygon pol);
	void mirrorX();
	void update();
public:
	PlayerSprite();
	PlayerSprite(float startX, float startY);	
	void animate(int& animationFrame, int min, int max);	
	void buildSprite(int animationFrame);
	float y();
	float topY();
};
#endif
