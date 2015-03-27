#pragma once
#include "CrocodileSprite.h"
class Crocodile :
	public CrocodileSprite
{
public:
	Crocodile();
	Crocodile(float startX, float startY);	
	bool mouthIsOpen();
	~Crocodile();
};

