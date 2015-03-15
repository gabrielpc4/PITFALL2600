#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include "PlayerSprite.h"

class Player 
	: public PlayerSprite
{
private: 
	int lives;
	

	Point playerSpeed;
	int animationFrame;

	bool _jumping;
	bool _falling;

	
	bool _down;
	
	bool _takingHit;
public:
	Player();
	Player(GLint startX, GLint startY);
	void draw();
	void drawBasicShape();
	bool isJumping();
	void move();
	void jumping(bool state);
	void jump();
	void look(int DIRECTION);
	bool isLooking(int DIRECTION);
	void setSpeedX(float speed);
	void setSpeedY(float speed);
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
	bool willFall(Sprite* hole);
	bool isAbleToClimbOut(Sprite* hole);
	void climbOut(int direction);
	void centerOnStair(Sprite* stairs);
	bool isUndeground();
	int livesLeft();
	void takeHit(bool state);
	bool isTakingHit();
};
#endif
