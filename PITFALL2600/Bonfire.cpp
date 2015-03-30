#include "Bonfire.h"


Bonfire::Bonfire()
	: Bonfire(413, 128)
{
}

Bonfire::Bonfire(float startX, float startY)
	: AnimatedObject(startX, startY, 1),
	basicShape(startX, startY)
{
	buildSprite();
	Sprite::update();
}

void Bonfire::buildSprite()
{
	setColor(Color(80, 32, 0));
	push_back(Rect(Point(0, 0), Point(8, 4)));
	push_back(Rect(Point(4, 2), Point(11, 6)));
	push_back(Rect(Point(8, 4), Point(22, 8)));
	push_back(Rect(Point(19, 2), Point(26, 6)));
	push_back(Rect(Point(22, 0), Point(30, 4)));

	setColor(Color(236, 200, 96));
	push_back(Rect(Point(11, 8), Point(19, 10)));
	push_back(Rect(Point(8, 10), Point(22, 12)));


	Sprite::setColor(Color(236, 200, 96));
	push_back(Rect(Point(4, 12), Point(22, 16)));
	push_back(Rect(Point(4, 16), Point(18, 18)));
	push_back(Rect(Point(8, 18), Point(18, 22)));
	push_back(Rect(Point(8, 22), Point(15, 26)));
	push_back(Rect(Point(11, 26), Point(15, 28)));	
}


void Bonfire::draw()
{	
	this->animate();
	Sprite::draw();
}

void Bonfire::DRAW_ON_DEBUG_MODE()
{
	drawAllRectanglesOutlines();
}

void Bonfire::mirrorX()
{
	for (unsigned i = 0; i < this->size(); i++)
	{
		Polygon& currentPolygon = this->at(i);

		this->updateX();
		for (vector<Rect>::iterator currentRect = currentPolygon.begin(); currentRect != currentPolygon.end(); ++currentRect)
		{
			*currentRect -= Point((2 * (currentRect->x() - this->x()) + currentRect->width()), 0);
		}		
	}
	shiftSpriteOnly(_width, 0);
}

void Bonfire::animate()
{
	frames++;	

	if (frames % DEFAULT_ANIMATION_REFRESH_INTERVAL == 0)
	{
		mirrorX();

		if (frames >= INT_MAX)
		{
			frames = 0;
		}
	}
}


Bonfire::~Bonfire()
{
}
