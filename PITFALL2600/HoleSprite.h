#pragma once
#include "Sprite.h"
class HoleSprite :
	public Sprite
{
private:
	Rect r3;
	Rect r4;
	Polygon pol;


public:
	HoleSprite();
	HoleSprite(GLint startX, GLint startY);
	~HoleSprite();
};

