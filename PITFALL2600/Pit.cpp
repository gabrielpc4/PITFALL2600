#include "Pit.h"

Pit::Pit()
	: Pit(144,132, Color(BLACK))
{
}

Pit::Pit(float startX, float startY, Color color)
	: Sprite(startX, startY),
	topOverlayer(startX, startY),
	bottomOverlayer(startX, startY)
{	
	this->_color = color;
	topOverlayer.setColor(this->color());
	animationFrame = 0;
	frames = 0;
	buildPit();
}

void Pit::buildPit()
{	
	Sprite::clear();
	topOverlayer.clear();
	bottomOverlayer.clear();

	switch (animationFrame)
	{
		case (0) :
		{
			Sprite::push_back(Rect(Point(101, 0), Point(129, 20)));
			Sprite::push_back(Rect(Point(57, 2), Point(173, 18)));
			Sprite::push_back(Rect(Point(29, 4), Point(201, 16)));
			Sprite::push_back(Rect(Point(14, 6), Point(216, 14)));
			Sprite::push_back(Rect(Point(0, 8), Point(230, 12)));
			
			topOverlayer.push_back(Rect(Point(101, 0), Point(129, 10)));
			topOverlayer.push_back(Rect(Point(57, 2), Point(173, 10)));
			topOverlayer.push_back(Rect(Point(29, 4), Point(201, 10)));
			topOverlayer.push_back(Rect(Point(14, 6), Point(216, 10)));
			topOverlayer.push_back(Rect(Point(0, 8), Point(230, 10)));
		}break;
		default: break;
	}

	bottomOverlayer.push_back(Rect(Point(0, -36), Point(this->width(), -6), Color(148, 91, 0)));
	bottomOverlayer.push_back(Rect(Point(0, -6), Point(this->width(), 10), Color(187, 147, 0)));
}

void Pit::drawOverlayer()
{
	bottomOverlayer.draw();
	topOverlayer.draw();
}

Pit::~Pit()
{
	bottomOverlayer.clear();
	topOverlayer.clear();
}