#include "Vine.h"

Vine::Vine()	
	: circle(259, 508, 330),
	origin(259, 322)
{
	i = 0;	
	while(i < circle.points.size())
	{
		if (circle.points[i].y() > 198)
		{
			i++;
		}
		else
		{			
			break;
		}
	}
	int j = i +1;
	while (j < circle.points.size())
	{
		if (circle.points[j].y() <= 198)
		{
			j++;
		}
		else
		{
			max = circle.points[j];			
			break;
		}
	}
	swingDirection = RIGHT;
}

void Vine::swing()
{
	float L = 2;
	int g = 10;

	float co = abs(origin.x() - max.x());
	int ca = abs(origin.y() - max.y());
	float hip = sqrt(pow(co, 2) + pow(ca, 2));

	float sinTheta = co / hip;
	float cosThetaMax = ca / hip;

	float currentX = circle.points[i].x();
	float currentY = circle.points[i].y();

	co = abs(origin.x() - currentX);
	ca = abs(origin.y() - currentY);
	hip = sqrt(pow(co, 2) + pow(ca, 2));

	float cosTheta = ca / hip;

	float velocity = sqrt(2 * g * L * (cosTheta - cosThetaMax));

	if (swingDirection == RIGHT)
	{
		i += abs(int(velocity)) + 1;
		if (circle.points[i].y() > 198)
		{
			swingDirection = LEFT;
		}
	}
	else
	{
		i -= abs(int(velocity)) + 1;
		if (circle.points[i].y() > 198)
		{
			swingDirection = RIGHT;
		}
	}
	_end = circle.points[i];
}

void Vine::draw()
{
	glColor3ub(72, 72, 0);
	glBegin(GL_POLYGON);
	glVertex2i(circle.points[i - 1].x(), circle.points[i - 1].y());
	glVertex2i(circle.points[i + 2].x(), circle.points[i + 2].y());
	glVertex2i(origin.x() + 2, origin.y());
	glVertex2i(origin.x() - 1, origin.y());
	glEnd();
}

void Vine::drawCircleTrack()
{
	circle.draw();
}

Point& Vine::end()
{
	return _end;
}

Vine::~Vine()
{
	circle.~Circle();
}
