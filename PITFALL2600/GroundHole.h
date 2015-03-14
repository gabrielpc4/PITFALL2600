#pragma once
#ifndef GROUNDHOLE_H
#define GROUNDHOLE_H
#include "GameObject.h"
class GroundHole :
	public GameObject
{
private:
	Rect tunnelHole;
	Sprite cover;
public:
	GroundHole();
	GroundHole(GLint startX, GLint startY);	
	void draw();
	void drawCover();
};
#endif
