#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "GameObject.h"
#include <typeinfo.h>

class Player 
	: public GameObject
{
private: 
	long loop;
	int _height;
	int _width;
	int lookingDirection;
	bool jumping;
	int _speed;
	int animationFrame;
	int ground_y;
	bool falling;
	bool _moving;
public:
	Player();
	Player(GLint startX, GLint startY);
	void draw();
	void drawBasicShape();
	bool isJumping();
	void move();
	void jump();
	void look(int DIRECTION);
	bool isLooking(int DIRECTION);
	void setSpeed(int speed);
	int speed();
	void moving(bool state);
	bool isMoving();
};
#endif
