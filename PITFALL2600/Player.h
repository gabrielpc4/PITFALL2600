#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "PlayerSprite.h"
#include "AnimatedObject.h"
#include "Vine.h"

#define FALLING_SPEED 4
#define CLIMBING_SPEED 3
#define JUMP_SPEED 3
#define JUMP_MAX_HEIGHT 22

class Player 
	: public PlayerSprite	  
{
private: 
	
	int _lives;		
	int _floor;
	bool _down;	
	bool _swinging;
	bool _standingOnCrocodile;
	long _framesDead;
	void climb();
	void jump();
	void fall();		
public:		
	Player();
	Player(GLint startX, GLint startY);
	void move();
	bool isJumping();
	void jumping(bool state);
	void look(int DIRECTION);
	int isLooking();	
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
	void incrementFramesDead();
	long framesDead();
	void resetLives();
	void setFloor(float y);
	void holdVine(bool state);
	void swing(Vine* vine);
	bool isSwinging();
	bool isHoldingVine();	
	bool isStandingOnCrocodile();
	void standOnCrocodile(bool state);
	void setLives(int number);
};
#endif
