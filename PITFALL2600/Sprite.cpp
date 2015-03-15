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
	return *this;
}

Sprite& Sprite::operator -= (const Point& point)
{
	for (vector<Polygon>::iterator currentPolygon = vector<Polygon>::begin(); currentPolygon != vector<Polygon>::end(); ++currentPolygon)
	{
		*currentPolygon -= point;
	}
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

	for (vector<Rect>::iterator currentRect = vector<Rect>::begin(); currentRect != vector<Rect>::end(); ++currentRect)
	{
		if (currentRect->x() < smallerX)
		{
			smallerX = currentRect->x();
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

	for (vector<Polygon>::iterator currentRect = vector<Polygon>::begin(); currentRect != vector<Polygon>::end(); ++currentRect)
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
	this->_x = smallerX;
	this->_y = smallerY;
	this->_width = (biggerX - smallerX);
	this->_height = (biggerY - smallerY);
}


void Sprite::push_back(Rect rect)
{
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
	pol += Point(startX, startY);
	vector<Polygon>::push_back(pol);
}

void Sprite::push_back(Sprite sprite)
{
	for (vector<Polygon>::iterator currentPolygon = sprite.vector<Polygon>::begin(); currentPolygon != sprite.vector<Polygon>::end(); ++currentPolygon)
	{
		vector<Polygon>::push_back(*currentPolygon);
	}
}

void Sprite::mirrorX()
{
	updateX();
	int spriteX = Point::x();
	for (vector<Polygon>::iterator it = vector<Polygon>::begin(); it != vector<Polygon>::end(); ++it)
	{
		it->mirrorX(spriteX);
	}
	*this += Point((Rect::width()), 0);
}