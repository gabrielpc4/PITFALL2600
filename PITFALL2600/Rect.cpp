#include "Rect.h"

/***************************************************************************************
* Method: Default Constructor
* Description: Initializes a Rectangle at x = 0 and y = 0 with width = 1 and height = 1
****************************************************************************************/
Rect::Rect()
{
	this->_p1.setX(0);
	this->_p1.setY(0);
	this->_p2.setX(1);
	this->_p2.setY(1);
}

/***************************************************************************************
* Method: 4 Params Constructor
* Description: Initializes a Rectangle with the specified x , y , width and height
****************************************************************************************/
Rect::Rect(GLint x, GLint y, GLint w, GLint h)
{
	this->_p1.setX(x);
	this->_p1.setY(y);
	this->_p2.setX(x + w);
	this->_p2.setY(y + h);
}

/***************************************************************************************
* Method: 2 Params Constructor
* Description: Initializes a Rectangle given 2 Points
****************************************************************************************/
Rect::Rect(Point p1, Point p2)
{
	this->_p1 = p1;
	this->_p2 = p2;
}

Rect::Rect(GLint x, GLint y, GLint w, GLint h, Color color) : Rect(x, y, w, h)
{
	this->_color = color;
}


Rect::Rect(Point p1, Point p2, Color color) : Rect(p1,p2)
{
	this->_color = color;
}

/***************************************************************************************
* Method: Overloaded = operator
* Description: Allows (Rect)r1 = (Rect)r2
****************************************************************************************/
Rect& Rect::operator=(const Rect& r2)
{
	this->_p1 = r2._p1;
	this->_p2 = r2._p2;
	return *this;
}

/***************************************************************************************
* Method: Overloaded += operator
* Description: Adds the coordinates of the given Point to the Rectangle
****************************************************************************************/
Rect& Rect::operator+=(const Point& point)
{
	this->_p1 += point;
	this->_p2 += point;
	return *this;
}

/***************************************************************************************
* Method: Overloaded -= operator
* Description: Allows (Rect)r1 -= (Rect)r2
****************************************************************************************/
Rect& Rect::operator-=(const Point& point)
{
	this->_p1 -= point;
	this->_p2 -= point;
	return *this;
}

/***************************************************************************************
* Method: Overloaded + operator
* Description: Adds the coordinates of the Point to the Rectangle coordinates
****************************************************************************************/
const Rect Rect::operator+(const Point& point) const
{
	Rect r1 = *this;
	r1 += point;
	return r1;
}

/***************************************************************************************
* Method: Overloaded - operator
* Description: Subtracts the coordinates of the Point to the Rectangle coordinates
****************************************************************************************/
const Rect Rect::operator-(const Point& point) const
{
	Rect r1 = *this;
	r1 -= point;
	return r1;
}

/***************************************************************************************
* Method Name: x
* Description: Returns the x coordinate of the bottom left corner of the rectangle
****************************************************************************************/
GLint Rect::x() const
{
	return _p1.x();
}

/***************************************************************************************
* Method Name: y
* Description: Returns the y coordinate of the bottom left corner of the rectangle
****************************************************************************************/
GLint Rect::y() const
{
	return _p1.y();
}

/***************************************************************************************
* Method Name: width
* Description: Returns the width of the rectangle
****************************************************************************************/
GLint Rect::width() const
{
	return (abs(_p1.x() - _p2.x()));
}

/***************************************************************************************
* Method Name: height
* Description: Returns the height of the rectangle
****************************************************************************************/
GLint Rect::height() const
{
	return (abs(_p1.y() - _p2.y()));
}

/***************************************************************************************
* Method Name: rightX
* Description: Returns the x value of the right corner of the Rectangle
****************************************************************************************/
int Rect::rightX()
{
	return (this->x() + this->width());
}

/***************************************************************************************
* Method Name: topY
* Description: Returns the y value of the Top corner of the Rectangle
****************************************************************************************/
int Rect::topY()
{
	return (this->y() + this->height());
}


/***************************************************************************************
* Method Name: setX
* Description: Sets the x coordinate of the bottom left corner of the rectangle
****************************************************************************************/
void Rect::setX(GLint x)
{
	int widthBackup = width();	
	_p1.setX(x);
	_p2.setX(x + widthBackup);
}

/***************************************************************************************
* Method Name: setY
* Description: Sets the y coordinate of the bottom left corner of the rectangle
****************************************************************************************/
void Rect::setY(GLint y)
{
	int heightBackup = height();
	_p1.setY(y);
	_p2.setY(y + heightBackup);
}


/***************************************************************************************
* Method Name: setPos
* Description: Sets the x and y coordinates of the bottom left corner of the rectangle
****************************************************************************************/
void Rect::setPos(GLint x, GLint y)
{
	this->setX(x);
	this->setX(y);
}

/***************************************************************************************
* Method Name: setWidth
* Description: Sets the width of the rectangle
****************************************************************************************/
void Rect::setWidth(GLint w)
{
	_p2.setX(_p1.x() + w);
}


/***************************************************************************************
* Method Name: setHeight

* Description: Sets the height of the rectangle
****************************************************************************************/
void Rect::setHeight(GLint h)
{
	_p2.setX(_p1.x() + h);
}

/***************************************************************************************
* Method Name: p1
* Description: Returns the bottom left corner Point of the Rectangle
****************************************************************************************/
Point Rect::p1() const
{
	return _p1;
}

/***************************************************************************************
* Method Name: p2
* Description: Returns the top right corner Point of the Rectangle
****************************************************************************************/
Point Rect::p2() const
{
	return _p2;
}


/***************************************************************************************
* Method Name: draw
* Description: Draws the rectangle
****************************************************************************************/
void Rect::draw()
{
	glColor3ub(this->_color.r(), this->_color.g(), this->_color.b());
	glRecti(_p1.x(),_p1.y(),_p2.x(),_p2.y());
}

/***************************************************************************************
* Method Name: draw
* Description: Draws the rectangle witha  specific color
****************************************************************************************/
void Rect::draw(Color color)
{
	glColor3ub(color.r(), color.g(), color.b());
	glRecti(_p1.x(), _p1.y(), _p2.x(), _p2.y());
}

void Rect::setColor(GLint r, GLint g, GLint b)
{
	this->_color = Color(r, g, b);
}

void Rect::setColor(Color color)
{
	this->_color = color;
}


Color Rect::color()
{
	return (_color);
}
#include "echo.h"
void Rect::drawRect(int x, int y, Color color)
{
		glColor3ub(color.r(), color.g(), color.b());
		*this += Point(x, y);
		glRecti(this->x(), this->y(), this->x() + this->width(), this->y() + this->height());

	
}
