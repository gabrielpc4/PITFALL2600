#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "GameObject.h"
#include <typeinfo.h>

class Player 
	: public GameObject
{
private: 
	int lives;
	long framesWalking;
	int _height;
	int _width;
	int lookingDirection;

	Point playerSpeed;
	int animationFrame;

	bool _jumping;
	bool _falling;
	bool _walking;
	bool _climbing;
	int _climbingDirection;
public:
	Player();
	Player(GLint startX, GLint startY);
	void draw();
	void drawBasicShape();
	void animate(int minFrameNum, int maxFramenum);
	bool isJumping();
	void move();
	void jumping(bool state);
	void jump();
	void look(int DIRECTION);
	bool isLooking(int DIRECTION);
	void setSpeedX(int speed);
	void setSpeedY(int speed);
	Point speed();
	void walking(bool state);
	bool isWalking();
	int floor;
	void falling(bool state);
	bool isFalling();
	void fall();	
	void climbing(bool state);
	bool isClimbing();
	void climb(int direction);
	void climb();
	int climbingDirection();
	void stopClimbing();
	bool willFall(GameObject* hole);
	bool isAbleToClimbOut(GameObject* hole);
	void climbOut(int direction);
	void centerOnStair(GameObject* stairs);
	bool isUndeground();
	int livesLeft();
};
#endif
