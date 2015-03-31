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
	push_back(rect);
}

Sprite::Sprite(Polygons pol)
{
	push_back(pol);
}

Sprite& Sprite::operator += (const Point& point)
{
	for (vector<Polygons>::iterator currentPolygons = this->begin(); currentPolygons != this->end(); ++currentPolygons)
	{
		*currentPolygons += point;
	}
	_x += point.x();
	_y += point.y();
	return *this;
}

Sprite& Sprite::operator -= (const Point& point)
{
	for (vector<Polygons>::iterator currentPolygons = this->begin(); currentPolygons != this->end(); ++currentPolygons)
	{
		*currentPolygons -= point;
	}
	_x -= point.x();
	_y -= point.y();
	return *this;
}

void Sprite::setX(GLint x)
{
	*this -= Point(_x, 0);
	*this += Point(x, 0);
}

void Sprite::setY(GLint y)
{
	*this -= Point(0, _y);
	*this += Point(0, y);

}

void Sprite::setPos(GLint x, GLint y)
{
	this->setX(x);
	this->setY(y);
}

void Sprite::draw()
{
	for (vector<Polygons>::iterator currentPolygons = this->begin(); currentPolygons != this->end(); ++currentPolygons)
	{
		currentPolygons->draw();
	}
}

void Sprite::updateX()
{
	int smallerX = WORLD_WINDOW_WIDTH;

	for (vector<Polygons>::iterator currentPolygons = this->begin(); currentPolygons != this->end(); ++currentPolygons)
	{
		if (currentPolygons->x() < smallerX)
		{
			smallerX = currentPolygons->x();
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

	for (vector<Polygons>::iterator currentPolygons = this->begin(); currentPolygons != this->end(); ++currentPolygons)
	{
		if (currentPolygons->x() < smallerX)
		{
			smallerX = currentPolygons->x();
		}
		if (currentPolygons->y() < smallerY)
		{
			smallerY = currentPolygons->y();
		}
		if (currentPolygons->rightX() > biggerX)
		{
			biggerX = currentPolygons->rightX();
		}
		if (currentPolygons->topY() > biggerY)
		{
			biggerY = currentPolygons->topY();
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
	Polygons p(startX, startY);
	p.push_back(rect);
	vector<Polygons>::push_back(p);
	this->update();
}

void Sprite::push_back(Rect rect, Color color)
{
	rect.setColor(color);
	Sprite::push_back(rect);
}

void Sprite::push_back(Polygons pol)
{
	if (pol.color().notInformed())
	{
		pol.setColor(this->_color);
	}
	Polygons p(startX, startY);
	p.push_back(pol);
	vector<Polygons>::push_back(p);
	this->update();
}

void Sprite::push_back(Sprite sprite)
{
	for (vector<Polygons>::iterator currentPolygons = sprite.begin(); currentPolygons != sprite.end(); ++currentPolygons)
	{
		vector<Polygons>::push_back(*currentPolygons);
	}
	this->update();
	
}

void Sprite::mirrorX()
{		
	for (unsigned i = 0; i < this->size(); i++)
	{
		Polygons& currentPolygons = this->at(i);
		currentPolygons.mirrorX();
	}
}


void Sprite::setColor(Color color)
{
	this->_color = color;
}
