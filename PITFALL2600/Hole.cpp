#include "Hole.h"

Hole::Hole()
	: Hole(144,132, Color(BLACK), false)
{
}

Hole::Hole(Color color, bool changesSize)
	: Hole(144, 132, color, changesSize)
{
}


Hole::Hole(float startX, float startY, Color color, bool changesSize)
	: AnimatedObject(startX, startY),
	topOverlayer(0,0),
	bottomOverlayer(0, 0)
{	
	this->_color = color;
	this->changesSize = changesSize;
	moving = true;
	topOverlayer.setColor(this->color());	

	movingHolePoints.push_back(Point(101, 0)); movingHolePoints.push_back(Point(129, 20));

	movingHolePoints.push_back(Point(57, 2)); movingHolePoints.push_back(Point(173, 18));

	movingHolePoints.push_back(Point(29, 4)); movingHolePoints.push_back(Point(201, 16));

	movingHolePoints.push_back(Point(14, 6)); movingHolePoints.push_back(Point(216, 14));

	movingHolePoints.push_back(Point(0, 8)); movingHolePoints.push_back(Point(230, 12));

	for (unsigned i = 0; i < movingHolePoints.size(); i++)
	{
		staticHolePoints.push_back(movingHolePoints[i]);
	}

	buildSprite();
}

void Hole::draw()
{
	if (canChangeSize())
	{
		if (animationFrame == 9)
		{
			animationRefreshInterval = 50;
		}
		else if (animationFrame == 4)
		{
			animationRefreshInterval = 150;
		}
		else
		{
			animationRefreshInterval = 2;
		}		
	}
	

	if (moving)
	{
		animate(9);
	}

	

	Sprite::draw();
}

void Hole::buildSprite()
{		
	Sprite::clear();
	topOverlayer.clear();
	bottomOverlayer.clear();

	vector<Point>& pointsToDraw = movingHolePoints;

	if (canChangeSize())
	{
		if (animationFrame < 5)
		{
			for (unsigned i = 0; i < movingHolePoints.size(); i++)
			{
				if (i % 2 == 0)
				{
					if (movingHolePoints[i].y() + 2 <= 10)
					{
						movingHolePoints[i].setY(movingHolePoints[i].y() + 2);
					}
				}
				else
				{
					if (movingHolePoints[i].y() - 2 >= 10)
					{
						movingHolePoints[i].setY(movingHolePoints[i].y() - 2);
					}
				}
			}
			if (animationFrame == 4)
			{
				_width = 0;
			}
		}
		else
		{
			int max = animationFrame - 4;
			int interaction = 0;
			int i = 0;
			while (interaction < max)
			{
				movingHolePoints[i].setY(movingHolePoints[i].y() - 2);
				movingHolePoints[i + 1].setY(movingHolePoints[i + 1].y() + 2);

				interaction++;
				i += 2;
			}
		}

		pointsToDraw = movingHolePoints;
	}
	else
	{
		pointsToDraw = staticHolePoints;
	}

	

	for (unsigned i = 0; i < pointsToDraw.size(); i += 2)
	{
		if (pointsToDraw[i].y() != pointsToDraw[i + 1].y())
		{
			Sprite::push_back(Rect(pointsToDraw[i], pointsToDraw[i + 1]));

			int x1 = pointsToDraw[i].x() + 144;
			int y1 = pointsToDraw[i].y() + 132;

			int x2 = pointsToDraw[i + 1].x() + 144;
			int y2 = 142;
			topOverlayer.push_back(Rect(Point(x1,y1), Point(x2,y2)));
		}		
	}

	bottomOverlayer.push_back(Rect(Point(this->x() - 10, 132 - 36), Point(this->x() + this->width() + 10, 132 - 6), Color(148, 91, 0)));
	bottomOverlayer.push_back(Rect(Point(this->x() - 10, 132 - 6), Point(this->x() + this->width() + 10, 132 + 8), Color(187, 147, 0)));
}

void Hole::drawOverlayer()
{
	bottomOverlayer.draw();
	topOverlayer.draw();
}

void Hole::freeze()
{
	moving = false;	
}

void Hole::unFreeze()
{
	moving = true;
}

bool Hole::canChangeSize()
{
	return changesSize;
}

void Hole::setMoving(bool state)
{	
	changesSize = state;
}

bool Hole::canMove()
{
	return moving;
}

Hole::~Hole()
{
	bottomOverlayer.clear();
	topOverlayer.clear();
}