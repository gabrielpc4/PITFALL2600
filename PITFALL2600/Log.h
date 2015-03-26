#pragma once
#ifndef LOG_H
#define  LOG_H
#include "LogSprite.h"
class Log :
	public LogSprite
{	
public:
	Log();
	Log(GLint startX, GLint start, bool rolling);	
	void roll();
	bool isRolling();
};
#endif
