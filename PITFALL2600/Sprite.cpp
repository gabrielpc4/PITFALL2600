#include "Sprite.h"
#include <iostream>
using namespace std;

/***************************************************************************************
* Method: Constructor with a Rectangle parameter
* Description: Initializes a Sprite, with the given Rectangle and a color
****************************************************************************************/
Sprite::Sprite(Rect rect, Color color)
{
	vector<Polygon>::push_back(Polygon(rect, color));
}

/***************************************************************************************
* Method: Constructor with a Sprite parameter
* Description: Initializes a Sprite, with the given Sprite
****************************************************************************************/
Sprite::Sprite(Polygon pol)
{
	vector<Polygon>::push_back(pol);
}


/***************************************************************************************
* Method: Overloaded += operator
* Description: Adds the coordinates of the given Point to the Sprite
****************************************************************************************/
Sprite& Sprite::operator += (const Point& point)
{
	for (vector<Polygon>::iterator it = this->begin(); it != this->end(); ++it)
	{
		*it += point;
	}
	return *this;
}

/***************************************************************************************
* Method: Overloaded-+= operator
* Description: Subtracts the coordinates of the given Point to the Sprite
****************************************************************************************/
Sprite& Sprite::operator -= (const Point& point)
{
	for (vector<Polygon>::iterator it = this->begin(); it != this->end(); ++it)
	{
		*it -= point;
	}
	return *this;
}

/***************************************************************************************
* Method Name: x
* Description: Returns the x value of the bottom left corner of the Sprite
****************************************************************************************/
int Sprite::x()
{
	// Goes through all the rectangles that makes the Sprite and get the smallest x value
	int smallerX = WORLD_WINDOW_WIDTH;
	for (vector<Polygon>::iterator it = this->begin(); it != this->end(); ++it)
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
* Description: Returns the y value of the bottom left corner of the Sprite
****************************************************************************************/
int Sprite::y()
{
	// Goes through all the rectangles that makes the Sprite and get the smallest y value
	int smallerY = WORLD_WINDOW_HEIGHT;
	for (vector<Polygon>::iterator it = this->begin(); it != this->end(); ++it)
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
* Description: Returns the width of the Rectangle that contains the Sprite
****************************************************************************************/
int Sprite::width()
{
	// Goes through all the rectangles that makes the Sprite and get 
	// and smallest x value and calculates the difference, returning the width
	int smallerX = WORLD_WINDOW_WIDTH;
	int biggerX = 0;
	for (vector<Polygon>::iterator it = this->begin(); it != this->end(); ++it)
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
* Description: Returns the height of the Rectangle that contains the Sprite
****************************************************************************************/
int Sprite::height()
{
	// Goes through all the rectangles that makes the Sprite and get 
	// and smallest y value and calculates the difference, returning the height
	int smallerY = WORLD_WINDOW_HEIGHT;
	int biggerY = 0;
	for (vector<Polygon>::iterator it = this->begin(); it != this->end(); ++it)
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
* Description: Returns the x value of the right corner of the Sprite
****************************************************************************************/
int Sprite::rightX()
{
	return (this->x() + this->width());
}

/***************************************************************************************
* Method Name: topY
* Description: Returns the y value of the Top corner of the Sprite
****************************************************************************************/
int Sprite::topY()
{
	return (this->y() + this->height());
}

/***************************************************************************************
* Method Name: setX
* Description: Sets the x coordinate of the bottom left corner of the Sprite
****************************************************************************************/
void Sprite::setX(GLint x)
{
	*this -= Point(this->x(), 0);
	*this += Point(x,0);
}

/***************************************************************************************
* Method Name: setY
* Description: Sets the y coordinate of the bottom left corner of the Sprite
****************************************************************************************/
void Sprite::setY(GLint y)
{
	*this -= Point(0, this->y());
	*this += Point(0, y);
	
}


/***************************************************************************************
* Method Name: setPos
* Description: Sets the x and y coordinates of the bottom left corner of the Sprite
****************************************************************************************/
void Sprite::setPos(GLint x, GLint y)
{
	this->setX(x);
	this->setY(y);
}


/***************************************************************************************
* Method Name: draw
* Description: Draws the Sprite
****************************************************************************************/
void Sprite::draw()
{	
	for (vector<Polygon>::iterator it = this->begin(); it != this->end(); ++it)
	{			
		it->draw();
	}
}

/***************************************************************************************
* Method Name: push_back(Rectangle)
* Description: Adds a rectangle to the sprite
****************************************************************************************/
void Sprite::push_back(Rect rect)
{
	vector<Polygon>::push_back(Polygon(rect));
}


/***************************************************************************************
* Method Name: push_back(Rectangle)
* Description: Adds a rectangle to the sprite with a specific color
****************************************************************************************/
void Sprite::push_back(Rect rect, Color color)
{
	vector<Polygon>::push_back(Polygon(rect, color));
}
/***************************************************************************************
* Method Name: push_back(Polygon)
* Description: Adds a Polygon to the sprite 
****************************************************************************************/
void Sprite::push_back(Polygon pol)
{
	vector<Polygon>::push_back(pol);
}

/***************************************************************************************
* Method Name: push_back(Sprite)
* Description: Adds a given sprite to the current sprite 
****************************************************************************************/
void Sprite::push_back(Sprite sprite)
{
	for (vector<Polygon>::iterator it = sprite.begin(); it != sprite.end(); ++it)
	{
		vector<Polygon>::push_back(*it);
	}
}

void Sprite::mirrorX()
{
	int spriteX = this->x();
	for (vector<Polygon>::iterator it = this->begin(); it != this->end(); ++it)
	{		
		it->mirrorX(spriteX);
	}
	*this += Point((this->width()), 0);	
}


void Sprite::drawSprite(int x, int y)
{

	*this += Point(-(this->x()), -(this->y()));
	for (vector<Polygon>::iterator it = this->begin(); it != this->end(); ++it)
	{
		it->drawPolygon(x, y);
	}
}