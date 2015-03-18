#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "PlayerSprite.h"
#include "Vine.h"

class Player 
	: public PlayerSprite
{
private: 
	int _lives;
	Point playerSpeed;
	int animationFrame;	
	int _floor;
	bool _down;
	bool _dead;
	bool _swinging;
	long _framesDead;
	void climb();
	void jump();
	void fall();
	void swing(Vine* vine);
public:
	Player();
	Player(GLint startX, GLint startY);
	void draw();
	void move();
	bool isJumping();
	void jumping(bool state);
	void look(int DIRECTION);
	int isLooking();
	void setSpeedX(float speed);
	void setSpeedY(float speed);
	Point speed();
	void walking(bool state);
	bool isWalking();
	void falling(bool state);
	bool isFalling();
	void climbing(bool state);
	bool isClimbing();
	void climb(int direction);
	int climbingDirection();
	void stopClimbing();
	void climbOut(int direction);
	bool isUndeground();
	int livesLeft();
	void takeHit(bool state);
	bool isTakingHit();
	void die();
	void respawn();
	bool isDead();
	long framesDead();
	void resetLives();
	void setFloor(float y);
	void swinging(bool state);
};
#endif
