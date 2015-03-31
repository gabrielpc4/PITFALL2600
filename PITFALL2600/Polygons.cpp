#include "Polygons.h"

Polygons::Polygons()
	: Polygons(0, 0)
{

}

Polygons::Polygons(float startX, float startY)
{
	Point::_x = startX;
	Point::_y = startY;
	this->startX = startX;
	this->startY = startY;
}

Polygons::Polygons(float startX, float startY, Color color)
	: Polygons(startX, startY)	
{
	this->_color = color;
}

Polygons::Polygons(Rect rect, Color color)
	: Polygons(rect)
{
	rect.setColor(color);

}
Polygons::Polygons(Rect rect)
{
	vector<Rect>::push_back(rect);
}

Polygons::Polygons(Color color)
	: Polygons(0,0)
{
	this->_color = color;
}

Polygons& Polygons::operator=(const Polygons& pol2)
{
	Point::_x = pol2._x;
	Point::_y = pol2._y;
	this->_width = pol2._width;
	this->_height = pol2._height;
	this->_color = pol2.color();
	this->startX = pol2.startX;
	this->startY = pol2.startY;
	return *this;
}


Polygons& Polygons::operator+=(const Point& point)
{
	for (vector<Rect>::iterator currentRect = vector<Rect>::begin(); currentRect != vector<Rect>::end(); ++currentRect)
	{
		*currentRect += point;
	}
	return *this;
}

Polygons& Polygons::operator-=(const Point& point)
{
	for (vector<Rect>::iterator currentRect = vector<Rect>::begin(); currentRect != vector<Rect>::end(); ++currentRect)
	{
		*currentRect -= point;
	}
	return *this;
}

void Polygons::setX(GLint x)
{
	*this -= Point(Point::x(), 0);
	*this += Point(x, 0);
}

void Polygons::setY(GLint y)
{
	*this -= Point(0, Point::y());
	*this += Point(0, y);
}

void Polygons::setPos(GLint x, GLint y)
{
	this->setX(x);
	this->setY(y);
}

void Polygons::updateX()
{
	int smallerX = WORLD_WINDOW_WIDTH;

	for (vector<Rect>::iterator currentRect = vector<Rect>::begin(); currentRect != vector<Rect>::end(); ++currentRect)
	{
		if (currentRect->x() < smallerX)
		{
			smallerX = currentRect->x();
		}
	}
	Point::_x = smallerX;
}

void Polygons::update()
{
	int smallerX = WORLD_WINDOW_WIDTH;
	int smallerY = WORLD_WINDOW_HEIGHT;

	int biggerX = 0;
	int biggerY = 0;

	for (vector<Rect>::iterator currentRect = vector<Rect>::begin(); currentRect != vector<Rect>::end(); ++currentRect)
	{
		if (currentRect->x() < smallerX)
		{
			smallerX = currentRect->x();
		}
		if (currentRect->y() < smallerY)
		{
			smallerY = currentRect->y();
		}
		if (currentRect->x() + currentRect->width() > biggerX)
		{
			biggerX = currentRect->x() + currentRect->width();
		}
		if (currentRect->y() + currentRect->height() > biggerY)
		{
			biggerY = currentRect->y() + currentRect->height();
		}
	}
	Point::_x = smallerX;
	Point::_y = smallerY;
	Rect::_width = (biggerX - smallerX);
	Rect::_height = (biggerY - smallerY);
}

void Polygons::push_back(Rect rect)
{

	if (rect.color().notInformed())
	{
		rect.setColor(this->_color);
	}
	rect += Point(startX, startY);
	vector<Rect>::push_back(rect);
	update();
}



void Polygons::push_back(Polygons pol)
{
	for (vector<Rect>::iterator currentRect = pol.begin(); currentRect != pol.end(); ++currentRect)
	{				
		this->push_back(*currentRect);
	}
}

void Polygons::mirrorX()
{
	updateX();
	for (vector<Rect>::iterator currentRect = vector<Rect>::begin(); currentRect != vector<Rect>::end(); ++currentRect)
	{
		*currentRect -= Point((2 * (currentRect->x() - this->x()) + currentRect->width()), 0);
	}
	*this += Point(this->width(), 0);
}

void Polygons::mirrorX(int currentX)
{

	for (vector<Rect>::iterator it = vector<Rect>::begin(); it != vector<Rect>::end(); ++it)
	{		
		*it -= Point((2 * (it->x() - currentX) + it->width()), 0);
	}
}

void Polygons::draw() 
{
	for (vector<Rect>::const_iterator currentRect = vector<Rect>::begin(); currentRect != vector<Rect>::end(); ++currentRect)
	{	
		currentRect->draw();
	}	
}
