#include "Rect.h"

Rect::Rect()
	: Rect(0, 0, 1, 1)
{

}

Rect::Rect(float x, float y, float w, float h)
{
	Point::_x = x;
	Point::_y = y;
	this->_width = w;
	this->_height = h;
}

Rect::Rect(Point p1, Point p2)
	: Rect(p1.x(), p1.y(), fabs(p2.x() - p1.x()), fabs(p2.y() - p1.y()))
{

}

Rect::Rect(float x, float y, float w, float h, Color color)
	: Rect(x, y, w, h)
{
	this->_color = color;
}

Rect::Rect(Point p1, Point p2, Color color)
	: Rect(p1, p2)
{
	this->_color = color;
}

Rect& Rect::operator=(const Rect& r2)
{
	Point::_x = r2._x;
	Point::_y = r2._y;
	this->_width = r2._width;
	this->_height = r2._height;
	this->_color = r2.color();
	return *this;
}

const Rect Rect::operator+(const Point& point) const
{
	Rect r1 = *this;
	r1 += point;
	return r1;
}

const Rect Rect::operator-(const Point& point) const
{
	Rect r1 = *this;
	r1 -= point;
	return r1;
}

float Rect::width() const
{
	return (this->_width);
}

float Rect::height() const
{
	return (this->_height);
}

int Rect::rightX() const
{
	return (Point::_x + this->_width);
}

int Rect::topY() const
{
	return (Point::y() + this->_height);
}

void Rect::draw() const
{
	glColor3ub(color().r(), color().g(), color().b());
	glRecti(_x, _y, rightX(), topY());
}

void Rect::draw(Color color) const
{
	glColor3ub(color.r(), color.g(), color.b());
	glRecti(_x, _y, rightX(), topY());
}

void Rect::setColor(Color color)
{
	this->_color = color;
}

Color Rect::color() const
{
	return (_color);
}