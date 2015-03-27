#include "Point.h"

Point::Point()
{
	_x = 0;
	_y = 0;
}

Point::Point(float x, float y)
{
	_x = x;
	_y = y;
}

Point& Point::operator=(const Point& p)
{
	_x = p._x;
	_y = p._y;
	return *this;
}

Point& Point::operator+=(const Point& p)
{
	_x += p._x;
	_y += p._y;
	return *this;
}

Point& Point::operator-=(const Point& p)
{
	_x -= p._x;
	_y -= p._y;
	return *this;
}

const Point Point::operator+(const Point& p2) const
{
	Point p1 = *this;
	p1 += p2;
	return p1;
}

const Point Point::operator-(const Point& p2) const
{
	Point p1 = *this;
	p1 -= p2;
	return p1;
}

float Point::x() const
{
	return _x;
}

float Point::y() const
{
	return _y;
}

void Point::setX(float x)
{
	_x = x;
}

void Point::setY(float y)
{
	_y = y;
}

void Point::print(float x, float y)
{
	cout << x << " " << y << endl;
}
