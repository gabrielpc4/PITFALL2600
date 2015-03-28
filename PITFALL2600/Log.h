#pragma once
#ifndef LOG_H
#define  LOG_H
#include "LogSprite.h"
class Log :
	public LogSprite
{	
public:
	Log();
	Log(int LOG_POSITION, bool rolling);
	Log(GLint startX, GLint start, bool rolling);	
	void roll();
	bool isRolling();
};
#endif
