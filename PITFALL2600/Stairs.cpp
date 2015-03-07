#include "Stairs.h"


Stairs::Stairs() :
	Stairs(0,0)// Creates the stairs on the point (0,0)
{

}
Stairs::Stairs(GLint startX, GLint startY) : 
	GameObject(startX, startY)
{
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
	stairsHole = new GameObject(this->x(), this->topY() + 10);	// Defines the start position of the sprite stairHole in relation to the stair
	stairsHole->sprite->push_back(Rect(Point(0, 0), Point(this->width(), 6)), Color(BLACK));	// Black rectangle  : width:stairs.width() height: 6
	stairsHole->sprite->push_back(Rect(Point(0, 6), Point(this->width(), 12)), Color(67.0, 0.0, 0.0));   // DarkRed rectangle: width:stairs.width() height: 12 - 6 = 6	
}


void Stairs::draw()
{	
	this->sprite->drawSprite(this->x(),this->y());		// Draws the stair
    stairsHole->drawSprite(stairsHole->x(), stairsHole->y());	// Draws the stairHole
}

GameObject* Stairs::hole()
{
	return stairsHole;
}