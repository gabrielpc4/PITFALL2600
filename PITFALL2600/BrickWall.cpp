#include "BrickWall.h"

BrickWall::BrickWall() :
	BrickWall(0, 0)
{

}

BrickWall::BrickWall(int startX, int startY) 
	: GameObject(startX,startY)	// Defines the brickwall sprite initial position
{

	this->sprite = new Sprite();
	// Sprite that will be added the rectangles
	Sprite pattern;

	// Creates the grey concrete division and adds it to the sprite
	Rect concreteDivision(Point(0, 0), Point(25, 2), Color(142, 142, 142));
	pattern.push_back(concreteDivision);

	// Creates the first brick level
	Rect bricks(Point(0, concreteDivision.topY()), Point(concreteDivision.width(), concreteDivision.topY() + 6), Color(167, 26, 26));
	pattern.push_back(bricks);

	// Will contain the tree back brick divisions necessary to make the pattern
	Rect brickDivison[3];

	// Creates the first brick division
	brickDivison[0] = Rect(Point(bricks.x() + 3, bricks.y()), Point(bricks.x() + 7, bricks.topY()), Color(BLACK));
	pattern.push_back(brickDivison[0]);

	// Creates the second brick division
	brickDivison[1] = Rect(Point(brickDivison[0].rightX() + 11, bricks.y()), Point(brickDivison[0].rightX() + 14, bricks.topY()), Color(BLACK));
	pattern.push_back(brickDivison[1]);

	// Second level of the brick wall:
	concreteDivision.setY(pattern.height());	// Moves the concreve division to the top of the current brick wall
	pattern.push_back(concreteDivision);		// Adds the concreteDivision to the top of the brick wall

	bricks.setY(pattern.height());			// Moves the bricks to the top of the current brick wall
	pattern.push_back(bricks);				// Adds the bricks to the top of the brick wall

	// Creates the brick division of the second level of the brick wall
	brickDivison[2] = Rect(Point(bricks.x() + 11, bricks.y()), Point(bricks.x() + 14, bricks.topY()), Color(BLACK));
	pattern.push_back(brickDivison[2]);

	// PATTERN CREATED


	// Do the same pattern 4 times, changing the height
	for (int i = 0; i < 4; i++)
	{
		sprite->push_back(pattern);   // Adds the pattern to the final sprite		
		pattern += Point(0, pattern.height()); // Moves the pattern to to top of the final sprite
	}
}

void BrickWall::draw()
{
	//sprite->drawSprite(this->x(), this->y());
}

