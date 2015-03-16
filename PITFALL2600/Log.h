#pragma once
#ifndef LOG_H
#define  LOG_H
#include "LogSprite.h"
class Log :
	public LogSprite
{
private:
	bool rolling;
public:
	Log();
	Log(GLint startX, GLint start, bool rolling);
	void draw();
	void roll();
	bool isRolling();
};
#endif
