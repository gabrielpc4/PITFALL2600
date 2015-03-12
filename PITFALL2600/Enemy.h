#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"
class Enemy :
	public GameObject
{
public:
	Enemy();
	Enemy(GLint startX, GLint startY);
	virtual ~Enemy();
};
#endif

