#include "Hole.h"

Hole::Hole()
	: Hole(144,132, Color(BLACK), STATIC_HOLE)
{
}

Hole::Hole(Color color, int type)
	: Hole(144, 132, color, type)
{
}


void Hole::expandOrShrink()
{	
	if (animationFrame <= 5)
	{
		for (unsigned i = 0; i < movingHolePoints.size(); i++)
		{
			if (animationFrame == 5)
			{
				movingHolePoints[i].setY(10);		
			}
			else
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
			
		}		
	}
	else
	{
		int max = animationFrame - 5;
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
	/*cout << "animationFrame: " << animationFrame << endl;
	for (unsigned i = 0; i < movingHolePoints.size(); i+=2)
	{
		Point::print(movingHolePoints[i].x(), movingHolePoints[i].y());
		Point::print(movingHolePoints[i + 1].x(), movingHolePoints[i + 1].y());
		cout << endl;
	}*/
}

Hole::Hole(float startX, float startY, Color color, int type)
	: AnimatedObject(startX, startY, 10),
	topOverlayer(0,0),
	bottomOverlayer(0, 0)
{	
	this->_color = color;	
	this->type = type;

	canChangeSize = true;

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

void Hole::animate()
{
	if (canChangeSize)
	{		
		if (animationFrame == 10)
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

		frames++;

		if (frames % animationRefreshInterval == 0)
		{			

			if (animationFrame >= 10)
			{
				animationFrame = 0;
			}
			else
			{
				animationFrame++;
			}

			expandOrShrink();			

			if (frames >= INT_MAX)
			{
				frames = 0;
			}		
		}				
	}		
}

void Hole::draw()
{
	buildSprite();	

	if (type == STATIC_HOLE)
	{
		_width = 230;
	}
	
	if (type == MOVING_HOLE && animationFrame == 4)
	{
		_width = 0;
	}	

	Sprite::draw();
}

void Hole::buildSprite()
{		
	Sprite::clear();
	topOverlayer.clear();
	bottomOverlayer.clear();

	if (type == STATIC_HOLE)
	{
		for (unsigned i = 0; i < staticHolePoints.size(); i += 2)
		{
			Sprite::push_back(Rect(staticHolePoints[i], staticHolePoints[i + 1]));

			int x1 = staticHolePoints[i].x() + 144;
			int y1 = staticHolePoints[i].y() + 132;

			int x2 = staticHolePoints[i + 1].x() + 144;
			int y2 = 142;
			topOverlayer.push_back(Rect(Point(x1, y1), Point(x2, y2)));
		}
	}
	else
	{
		
		for (unsigned i = 0; i < movingHolePoints.size(); i += 2)
		{
			if (movingHolePoints[i].y() != movingHolePoints[i + 1].y())
			{
				Sprite::push_back(Rect(movingHolePoints[i], movingHolePoints[i + 1]));

				int x1 = movingHolePoints[i].x() + 144;
				int y1 = movingHolePoints[i].y() + 132;

				int x2 = movingHolePoints[i + 1].x() + 144;
				int y2 = 142;
				topOverlayer.push_back(Rect(Point(x1, y1), Point(x2, y2)));
			}
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

void Hole::DRAW_OVERLAYER_ON_DEBUG_MODE()
{
	Color color1(topOverlayer.color().r(), topOverlayer.color().g() + 10, topOverlayer.color().b());
	Color color2(Color(bottomOverlayer.color().r(), bottomOverlayer.color().g() + 10, bottomOverlayer.color().b()));
	topOverlayer.setColor(color1);
	bottomOverlayer.setColor(color2);
	drawOverlayer();
}

void Hole::enableSizeChanging()
{
	canChangeSize = true;
}
void Hole::disableSizeChanging()
{
	canChangeSize = false;
}

void Hole::setType(int type)
{
	this->type = type;
}

Hole::~Hole()
{
	bottomOverlayer.clear();
	topOverlayer.clear();
}