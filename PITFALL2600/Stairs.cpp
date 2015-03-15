#include "Stairs.h"


Stairs::Stairs() :
	Stairs(245,32)// Creates the stairs on the point (0,0)
{

}
Stairs::Stairs(GLint startX, GLint startY) : 
	Sprite(startX, startY)
{

	hole = NULL;

	// Defines the stair border
	stairsBorder = Rect(Point(0, 0), Point(28, 94), Color(67.0, 0.0, 0.0));
	

	// Defines the position and color of the first step of the stair
	step = Rect(Point(stairsBorder.x() + 7, stairsBorder.y() + 4), Point(stairsBorder.x() + 21, stairsBorder.y() + 8), Color(148, 91, 0));
	
	Sprite::push_back(stairsBorder);	// Adds the starts border to the stairs sprite

	
	
	// Draws 11 steps with a 4 pixel distance between them
	for (int i = 0; i < 11; i++)
	{
		Sprite::push_back(step);
		step += Point(0, step.height() + 4);
	}

	// Creates and draws the stair hole	
	hole = new Sprite(this->x(), this->topY() + 10);	// Defines the start position of the sprite stairHole in relation to the stair
	
	hole->push_back(Rect(Point(0, 0), Point(this->width(), 6)), Color(BLACK));	// Black rectangle  : width:stairs.width() height: 6
	hole->push_back(Rect(Point(0, 6), Point(this->width(), 12)), Color(67.0, 0.0, 0.0));   // DarkRed rectangle: width:stairs.width() height: 12 - 6 = 6	

	cover.push_back(Rect(Point(hole->x(), hole->y() - 10), Point(hole->rightX(), hole->y()), Color(287, 147, 0)));
}


void Stairs::draw()
{	
	Sprite::draw();	// Draws the stair
	hole->draw();	// Draws the stairHole
}


void Stairs::drawCover()
{
	cover.draw();
}
