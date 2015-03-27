#include "Crocodile.h"

Crocodile::Crocodile()
	: Crocodile(187, 136)
{
}

Crocodile::Crocodile(float startX, float startY)
	: CrocodileSprite(startX, startY)
{

}

bool Crocodile::mouthIsOpen()
{
	return mouthState;
}

float Crocodile::x()
{
	if (mouthIsOpen())
	{
		return _x + 22;
	}
	return _x;
}
float Crocodile::width()
{
	if (mouthIsOpen())
	{
		return 7;
	}
	return _width;
}
float Crocodile::rightX()
{
	return (this->x() + this->width());
}

float Crocodile::height()
{
	return 6;
}

float Crocodile::topY()
{
	return _y + this->height();
}


Crocodile::~Crocodile()
{
}
