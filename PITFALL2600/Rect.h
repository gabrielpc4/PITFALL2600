#pragma once
#ifndef RECT_H_
#define RECT_H_

#include "Point.h"
#include "Color.h"
#include <stdlib.h>
#include <cmath>
#include "glut.h"  // Custom glut.h to work with stdlib.h
/***********************************************************************************************
* Class: Rect
* Description: Stores values for a rectangle like x and y positions as well as width and
height,  as well as most of the basics operations between rectangles and points
************************************************************************************************/
class Rect
{
protected:
	Point _p1;	// Bottom left corner Point
	Point _p2;  // Top right corner Point
	Color _color;
public:
	/***************************************************************************************
	* Method: Default Constructor
	* Description: Initializes a Rectangle at x = 0 and y = 0 with width = 1 and height = 1
	****************************************************************************************/
	Rect();

	/***************************************************************************************
	* Method: 4 Params Constructor
	* Description: Initializes a Rectangle with the specified x , y , width and height
	****************************************************************************************/
	Rect(GLint x, GLint y, GLint w, GLint h);

	Rect(GLint x, GLint y, GLint w, GLint h, Color color);
	Rect(Point p1, Point p2, Color color);

	/***************************************************************************************
	* Method: 2 Params Constructor
	* Description: Initializes a Rectangle given 2 Points
	****************************************************************************************/
	Rect(Point p1, Point p2);

	

	/***************************************************************************************
	* Method: Overloaded = operator
	* Description: Allows (Rect)r1 = (Rect)r2
	****************************************************************************************/
	Rect& operator=(const Rect& r2);

	/***************************************************************************************
	* Method: Overloaded += operator
	* Description: Adds the coordinates of the given Point to the Rectangle
	****************************************************************************************/
	Rect& operator+=(const Point& point);

	/***************************************************************************************
	* Method: Overloaded -= operator
	* Description: Subtracts the coordinates of the given Point to the Rectangle
	****************************************************************************************/
	Rect& operator-=(const Point& point);

	/***************************************************************************************
	* Method: Overloaded + operator
	* Description: Adds the coordinates of the Point to the Rectangle coordinates
	****************************************************************************************/
	const Rect operator+(const Point& point) const;

	/***************************************************************************************
	* Method: Overloaded - operator
	* Description: Subtracts the coordinates of the Point to the Rectangle coordinates
	****************************************************************************************/
	const Rect operator-(const Point& point) const;

	/***************************************************************************************
	* Method Name: x
	* Description: Returns the x coordinate of the bottom left corner of the rectangle
	****************************************************************************************/
	GLint x() const;

	/***************************************************************************************
	* Method Name: y
	* Description: Returns the y coordinate of the bottom left corner of the rectangle
	****************************************************************************************/
	GLint y() const;

	/***************************************************************************************
	* Method Name: width
	* Description: Returns the width of the rectangle
	****************************************************************************************/
	GLint width() const;

	/***************************************************************************************
	* Method Name: height
	* Description: Returns the height of the rectangle
	****************************************************************************************/
	GLint height() const;

	/***************************************************************************************
	* Method Name: rightX
	* Description: Returns the x value of the right corner of the Rectangle
	****************************************************************************************/
	int rightX();

	/***************************************************************************************
	* Method Name: topY
	* Description: Returns the y value of the Top corner of the Rectangle
	****************************************************************************************/
	int topY();

	/***************************************************************************************
	* Method Name: setX
	* Description: Sets the x coordinate of the bottom left corner of the rectangle
	****************************************************************************************/
	void setX(GLint x);

	/***************************************************************************************
	* Method Name: setY
	* Description: Sets the y coordinate of the bottom left corner of the rectangle
	****************************************************************************************/
	void setY(GLint y);

	/***************************************************************************************
	* Method Name: setPos
	* Description: Sets the x and y coordinates of the bottom left corner of the rectangle
	****************************************************************************************/
	void setPos(GLint x, GLint y);

	/***************************************************************************************
	* Method Name: setWidth
	* Description: Sets the width of the rectangle
	****************************************************************************************/
	void setWidth(GLint w);

	/***************************************************************************************
	* Method Name: setHeight
	* Description: Sets the height of the rectangle
	****************************************************************************************/
	void setHeight(GLint h);

	/***************************************************************************************
	* Method Name: p1
	* Description: Returns the bottom left corner Point of the Rectangle
	****************************************************************************************/
	Point p1() const;

	/***************************************************************************************
	* Method Name: p2
	* Description: Returns the top right corner Point of the Rectangle
	****************************************************************************************/
	Point p2() const;

	/***************************************************************************************
	* Method Name: draw
	* Description: Draws the rectangle
	****************************************************************************************/	
	void draw();

	/***************************************************************************************
	* Method Name: draw
	* Description: Draws the rectangle with a specific color
	****************************************************************************************/
	void draw(Color color);

	void setColor(GLint r, GLint g, GLint b);
	void setColor(Color color);
	Color color();

	void drawRect(int x, int y, Color color);
};
#endif