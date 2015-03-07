#include "Point.h"
/**********************************************************************
* Method: Default Constructor
* Description: Initializes a Point at x = 0 and y = 0
**********************************************************************/
Point::Point()
{
	_x = 0;
	_y = 0;
}

/**********************************************************************
* Method: 2 Params Constructor
* Description: Initializes a Point at the specified x and y position
**********************************************************************/
Point::Point(GLint x, GLint y)
{
	_x = x;
	_y = y;
}

/**********************************************************************
* Method: Overloaded = operator
* Description: Allows to use (Point)p1 =(Point)p2;
**********************************************************************/
Point& Point::operator=(const Point& p)
{
	_x = p._x;
	_y = p._y;
	return *this;
}

/**********************************************************************
* Method: Overloaded += operator
* Description: Allows to use (Point p1 += (Point)p2;
**********************************************************************/
Point& Point::operator+=(const Point& p)
{
	_x += p._x;
	_y += p._y;
	return *this;
}

/**********************************************************************
* Method: Overloaded -= operator
* Description: Allows to use (Point)p1 -= (Point)p2;
**********************************************************************/
Point& Point::operator-=(const Point& p)
{
	_x -= p._x;
	_y -= p._y;
	return *this;
}

/**********************************************************************
* Method: Overloaded + operator
* Description: Allows to use (Point)p1 + (Point)p2;
**********************************************************************/
const Point Point::operator+(const Point& p2) const
{
	Point p1 = *this;
	p1 += p2;
	return p1;
}

/**********************************************************************
* Method: Overloaded + operator
* Description: Allows to use (Point)p1 - (Point)p2;
**********************************************************************/
const Point Point::operator-(const Point& p2) const
{
	Point p1 = *this;
	p1 -= p2;
	return p1;
}

/**********************************************************************
* Method Name: x
* Description: Returns the x value
**********************************************************************/
GLint Point::x() const
{
	return (_x);
}

/**********************************************************************
* Method Name: y
* Description: Returns the y value
**********************************************************************/
GLint Point::y() const
{
	return _y;
}

/**********************************************************************
* Method Name: setX
* Description: Sets the x value
**********************************************************************/
void Point::setX(GLint x)
{
	_x = x;
}

/**********************************************************************
* Method Name: setY
* Description: Sets the y value
**********************************************************************/
void Point::setY(GLint y)
{
	_y = y;
}

void Point::clear()
{
	setX(0);
	setY(0);	
}


