#include "Sprite.h"

Sprite::Sprite()
	: Sprite(0, 0)
{

}

Sprite::Sprite(GLint startX, GLint startY)
{
	_x = startX;
	_y = startY;
	this->startX = startX;
	this->startY = startY;
}

Sprite::Sprite(Rect rect, Color color)
{
	rect.setColor(color);
	vector<Polygon>::push_back(rect);
}

Sprite::Sprite(Polygon pol)
{
	vector<Polygon>::push_back(pol);
}

Sprite& Sprite::operator += (const Point& point)
{
	for (vector<Polygon>::iterator currentPolygon = vector<Polygon>::begin(); currentPolygon != vector<Polygon>::end(); ++currentPolygon)
	{
		*currentPolygon += point;
	}
	_x += point.x();
	_y += point.y();
	return *this;
}

Sprite& Sprite::operator -= (const Point& point)
{
	for (vector<Polygon>::iterator currentPolygon = vector<Polygon>::begin(); currentPolygon != vector<Polygon>::end(); ++currentPolygon)
	{
		*currentPolygon -= point;
	}
	_x -= point.x();
	_y -= point.y();
	return *this;
}

void Sprite::setX(GLint x)
{
	*this -= Point(Point::x(), 0);
	*this += Point(x, 0);
}

void Sprite::setY(GLint y)
{
	*this -= Point(0, Point::y());
	*this += Point(0, y);

}

void Sprite::setPos(GLint x, GLint y)
{
	this->setX(x);
	this->setY(y);
}

void Sprite::draw()
{
	for (vector<Polygon>::iterator currentPolygon = vector<Polygon>::begin(); currentPolygon != vector<Polygon>::end(); ++currentPolygon)
	{
		currentPolygon->draw();
	}
}

void Sprite::updateX()
{
	int smallerX = WORLD_WINDOW_WIDTH;

	for (vector<Polygon>::iterator currentPolygon = vector<Polygon>::begin(); currentPolygon != vector<Polygon>::end(); ++currentPolygon)
	{
		if (currentPolygon->x() < smallerX)
		{
			smallerX = currentPolygon->x();
		}
	}
	Point::_x = smallerX;
}

void Sprite::update()
{
	int smallerX = WORLD_WINDOW_WIDTH;
	int smallerY = WORLD_WINDOW_HEIGHT;

	int biggerX = 0;
	int biggerY = 0;

	for (vector<Polygon>::iterator currentPolygon = vector<Polygon>::begin(); currentPolygon != vector<Polygon>::end(); ++currentPolygon)
	{
		if (currentPolygon->x() < smallerX)
		{
			smallerX = currentPolygon->x();
		}
		if (currentPolygon->y() < smallerY)
		{
			smallerY = currentPolygon->y();
		}
		if (currentPolygon->rightX() > biggerX)
		{
			biggerX = currentPolygon->rightX();
		}
		if (currentPolygon->topY() > biggerY)
		{
			biggerY = currentPolygon->topY();
		}
	}
	_x = smallerX;
	_y = smallerY;
	_width = (biggerX - smallerX);
	_height = (biggerY - smallerY);
}

void Sprite::push_back(Rect rect)
{
	if (rect.color().notInformed())
	{
		rect.setColor(this->_color);
	}
	Polygon p(startX, startY);
	p.push_back(rect);
	vector<Polygon>::push_back(p);
	this->update();
}

void Sprite::push_back(Rect rect, Color color)
{
	rect.setColor(color);
	Sprite::push_back(rect);
}

void Sprite::push_back(Polygon pol)
{
	if (pol.color().notInformed())
	{
		pol.setColor(this->_color);
	}
	Polygon p(startX, startY);
	p.push_back(pol);
	vector<Polygon>::push_back(p);
	this->update();
}

void Sprite::push_back(Sprite sprite)
{
	for (vector<Polygon>::iterator currentPolygon = sprite.vector<Polygon>::begin(); currentPolygon != sprite.vector<Polygon>::end(); ++currentPolygon)
	{
		vector<Polygon>::push_back(*currentPolygon);
	}
	this->update();
	
}

void Sprite::mirrorX()
{		
	for (vector<Polygon>::iterator currentPolygon = vector<Polygon>::begin(); currentPolygon != vector<Polygon>::end(); ++currentPolygon)
	{
		currentPolygon->mirrorX();
	}
}

void Sprite::clear()
{
	this->vector<Polygon>::clear();
}

void Sprite::setColor(Color color)
{
	this->_color = color;
}