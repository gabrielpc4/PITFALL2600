#include "GroundHole.h"


GroundHole::GroundHole()
	:GroundHole(0,0)
{
}

GroundHole::GroundHole(GLint startX, GLint startY)
	: GameObject(startX, startY)
{
	sprite = new Sprite();	// Defines the start position of the sprite stairHole in relation to the stair
	sprite->push_back(Rect(Point(0, 0), Point(43, 6)), Color(BLACK));	// Black rectangle  : width:stairs.width() height: 6
	sprite->push_back(Rect(Point(0, 6), Point(43, 12)), Color(67.0, 0.0, 0.0));   // DarkRed rectangle: width:stairs.width() height: 12 - 6 = 6	
	sprite->push_back(Rect(Point(0, -40), Point(43, -10)), Color(67.0, 0.0, 0.0));   // DarkRed rectangle: width:stairs.width() height: 12 - 6 = 6	
	tunnelHole = Rect(Point(0, 0), Point(sprite->width(), 30));
	cover.push_back(Rect(Point(startX, startY + 30), Point(startX + sprite->width(), startY + 40)), Color(187, 147, 0));
}


void GroundHole::draw()
{
	sprite->draw();
}

void GroundHole::drawCover()
{
	cover.draw();
}
