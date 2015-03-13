#pragma once
#ifndef LOG_H
#define  LOG_H
#include "Enemy.h"
#include "LogSprite.h"
class Log :
	public Enemy
{
private:
	bool rolling;
	long framesRolling;
public:
	Log();
	Log(GLint startX, GLint start, bool rolling);
	void draw();
	void roll();
	void animate();
	bool isRolling();
};
#endif
