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
	bool _jumping;
	Point playerSpeed;
	int animationFrame;
	
	bool _falling;
	bool _moving;
	bool _climbing;
public:
	Player();
	Player(GLint startX, GLint startY);
	void draw();
	void drawBasicShape();
	void animate();
	bool isJumping();
	void move();
	void jumping(bool state);
	void jump();
	void look(int DIRECTION);
	bool isLooking(int DIRECTION);
	void setSpeedX(int speed);
	void setSpeedY(int speed);
	Point speed();
	void moving(bool state);
	bool isMoving();
	int ground_y;
	void falling(bool state);
	bool isFalling();
	void fall();	
	void climbing(bool state);
	bool isClimbing();
	void climb();
};
#endif
