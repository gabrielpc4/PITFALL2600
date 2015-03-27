#pragma once
#ifndef PLAYERSPRITE_H_
#define PLAYERSPRITE_H_
#include "Sprite.h"
#include "AnimatedObject.h"

#define CLIMBING_ANIMATION_REFRESH_INTERVAL 4
#define PLAYER_ANIMATION_0_WIDTH 11
#define PLAYER_ANIMATION_0_HEIGHT 42
#define PLAYER_ANIMATION_0_LOOKING_LEFT_COMPENSATION 4

class PlayerSprite :
	public AnimatedObject
{
protected:
	int _lookingDirection;
	bool _climbing;
	bool _walking;
	int _climbingDirection;
	bool _takingHit;
	bool _jumping;
	bool _falling;
	bool _dead;
	bool _holdingVine;

// Variables
private:
	float _realY;
	float _realX;
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
	void draw();
	void animate(int minFrameNum, int maxFramenum);
	void buildSprite();
	float x();
	float rightX();
	float width();
	float y();
	float topY();
};
#endif
