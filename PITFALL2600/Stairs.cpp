#include "Stairs.h"


Stairs::Stairs() :
	Stairs(245,32)// Creates the stairs on the point (0,0)
{

}
Stairs::Stairs(GLint startX, GLint startY) : 
	GameObject(startX, startY)
{
	hole = NULL;
	this->sprite = new Sprite();
	// Defines the stair border
	stairsBorder = Rect(Point(0, 0), Point(28, 94));

	// Defines the position and color of the first step of the stair
	step = Rect(Point(stairsBorder.x() + 7, stairsBorder.y() + 4), Point(stairsBorder.x() + 21, stairsBorder.y() + 8));
	step.setColor(Color(148, 91, 0));

	sprite->push_back(stairsBorder, Color(67.0, 0.0, 0.0));	// Adds the starts border to the stairs sprite

	// Draws 11 steps with a 4 pixel distance between them
	for (int i = 0; i < 11; i++)
	{
		sprite->push_back(step);
		step += Point(0, step.height() + 4);
	}

	// Creates and draws the stair hole	
	hole = new GameObject(this->x(), this->topY() + 10);	// Defines the start position of the sprite stairHole in relation to the stair
	hole->sprite->push_back(Rect(Point(0, 0), Point(this->width(), 6)), Color(BLACK));	// Black rectangle  : width:stairs.width() height: 6
	hole->sprite->push_back(Rect(Point(0, 6), Point(this->width(), 12)), Color(67.0, 0.0, 0.0));   // DarkRed rectangle: width:stairs.width() height: 12 - 6 = 6	

	cover.push_back(Rect(Point(hole->x(), hole->y() - 10), Point(hole->rightX(), hole->y()), Color(187, 147, 0)));
}


void Stairs::draw()
{	
	this->sprite->drawSprite(this->x(),this->y());		// Draws the stair
    hole->drawSprite(hole->x(), hole->y());	// Draws the stairHole
}


void Stairs::drawCover()
{
	cover.drawSprite(cover.x(), cover.y());	
}
