#include "Polygon.h"



/***********************************************************************
* Method: Constructor with Rectangle argument
* Description: Initializes a Polygon with the given Rectangle and color
************************************************************************/
Polygon::Polygon(Rect rect)
{	
	this->_color = rect.color();
	this->push_back(rect);
}

Polygon::Polygon(Rect rect, Color color)
{
	this->_color = color;
	this->push_back(rect);
}


/***********************************************************************
* Method: Constructor with Color argument
* Description: Defines the color of the Polygon
************************************************************************/
Polygon::Polygon(Color color)
{
	this->_color = color;
}


/***************************************************************************************
* Method: Overloaded += operator
* Description: Adds the coordinates of the given Point to the Polygon
****************************************************************************************/
Polygon& Polygon::operator+=(const Point& point)
{
	for (vector<Rect>::iterator it = this->begin(); it != this->end(); ++it)
	{
		*it += point;
	}
	return *this;
}

/***************************************************************************************
* Method: Overloaded -= operator
* Description: Subtracts the coordinates of the given Point to the Polygon
****************************************************************************************/
Polygon& Polygon::operator-=(const Point& point)
{
	for (vector<Rect>::iterator it = this->begin(); it != this->end(); ++it)
	{
		*it -= point;
	}
	return *this;
}

/***************************************************************************************
* Method Name: x
* Description: Returns the x value of the bottom left corner of the polygon
****************************************************************************************/
int Polygon::x()
{
	// Goes through all the rectangles that makes the polygon and get the smallest x value
	int smallerX = WORLD_WINDOW_WIDTH;
	for (vector<Rect>::iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->x() < smallerX)
		{
			smallerX = it->x();
		}		
	}
	return (smallerX);
}


/***************************************************************************************
* Method Name: y
* Description: Returns the y value of the bottom left corner of the polygon
****************************************************************************************/
int Polygon::y()
{
	// Goes through all the rectangles that makes the polygon and get the smallest y value
	int smallerY = WORLD_WINDOW_HEIGHT;
	for (vector<Rect>::iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->y() < smallerY)
		{
			smallerY = it->y();
		}
	}
	return (smallerY);
}

/***************************************************************************************
* Method Name: width
* Description: Returns the width of the Rectangle that contains the polygon
****************************************************************************************/
int Polygon::width()
{
	// Goes through all the rectangles that makes the polygon and get 
	// and smallest x value and calculates the difference, returning the width
	int smallerX = WORLD_WINDOW_WIDTH;
	int biggerX = 0;
	for (vector<Rect>::iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->x() < smallerX)
		{
			smallerX = it->x();
		}
		if (it->x() + it->width() > biggerX)
		{
			biggerX = it->x() + it->width();
		}
	}
	return (biggerX - smallerX);
}

/***************************************************************************************
* Method Name: height
* Description: Returns the height of the Rectangle that contains the polygon
****************************************************************************************/
int Polygon::height()
{
	// Goes through all the rectangles that makes the polygon and get 
	// and smallest y value and calculates the difference, returning the height
	int smallerY = WORLD_WINDOW_HEIGHT;
	int biggerY = 0;
	for (vector<Rect>::iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->y() < smallerY)
		{
			smallerY = it->y();
		}
		if (it->y() + it->height() > biggerY)
		{
			biggerY = it->y() + it->height();
		}
	}
	return (biggerY - smallerY);
}

/***************************************************************************************
* Method Name: rightX
* Description: Returns the x value of the right corner of the Polygon
****************************************************************************************/
int Polygon::rightX()
{
	return (this->x() + this->width());
}

/***************************************************************************************
* Method Name: topY
* Description: Returns the y value of the Top left corner of the Polygon
****************************************************************************************/
int Polygon::topY()
{
	return (this->y() + this->height());
}


/***************************************************************************************
* Method Name: setX
* Description: Sets the x coordinate of the bottom left corner of the Polygon
****************************************************************************************/
void Polygon::setX(GLint x)
{
	*this -= Point(this->x(), 0);
	*this += Point(x, 0);
}

/***************************************************************************************
* Method Name: setY
* Description: Sets the y coordinate of the bottom left corner of the Polygon
****************************************************************************************/
void Polygon::setY(GLint y)
{
	*this -= Point(0, this->y() );
	*this += Point(0, y);
}


/***************************************************************************************
* Method Name: setPos
* Description: Sets the x and y coordinates of the bottom left corner of the Polygon
****************************************************************************************/
void Polygon::setPos(GLint x, GLint y)
{
	this->setX(x);
	this->setY(y);
}


/***************************************************************************************
* Method Name: draw
* Description: Draws the polygon
****************************************************************************************/
void Polygon::draw()
{	
	for (vector<Rect>::iterator it = this->begin(); it != this->end(); ++it)
	{		
		it->draw(_color);
	}
}

void Polygon::setColor(GLint r, GLint g, GLint b)
{
	this->_color = Color(r, g, b);
}

void Polygon::setColor(Color color)
{
	this->_color = color;
}

Color Polygon::color()
{
	return _color;
}

/***************************************************************************************
* Method Name: push_back(Rect)
* Description: Adds a given polygon to the current polygon
****************************************************************************************/
void Polygon::push_back(Rect rect)
{
	if (rect.color().notInformed())
	{
		Rect temp = Rect(rect.p1(), rect.p2(), _color);
		vector<Rect>::push_back(temp);
	}
	else
	{
		vector<Rect>::push_back(rect);
	}
	
}

/***************************************************************************************
* Method Name: push_back(Polygon)
* Description: Adds a given polygon to the current polygon
****************************************************************************************/
void Polygon::push_back(Polygon pol)
{
	for (vector<Rect>::iterator it = pol.begin(); it != pol.end(); ++it)
	{
		vector<Rect>::push_back(*it);
	}
}

void Polygon::mirrorX()
{
	int x = this->x();
	for (vector<Rect>::iterator it = this->begin(); it != this->end(); ++it)
	{
		*it -= Point((2 * (it->x() - x) + it->width()), 0);
	}
	*this += Point(this->width(), 0);
}

void Polygon::mirrorX(int currentX)
{
	for (vector<Rect>::iterator it = this->begin(); it != this->end(); ++it)
	{
		*it -= Point((2 * (it->x() - currentX) + it->width()), 0);
	}
}
#include "echo.h"
void Polygon::drawPolygon(int x, int y)
{
	for (vector<Rect>::iterator it = this->begin(); it != this->end(); ++it)
	{
		it->drawRect(x, y, _color);
	}

}