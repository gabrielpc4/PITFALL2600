#pragma once
#ifndef POLYGON_H_
#define POLYGON_H_

#include "Point.h"
#include "Rect.h"
#include "Color.h"
#include "constants.h"
#include <vector>
#include "glut.h" // Custom glut.h fixed for using namespace std

using namespace std;

class Polygon : public vector<Rect>
{
private:
	Color _color;

public:
	Polygon(){}
	/***********************************************************************
	* Method: Constructor with Rectangle argument
	* Description: Initializes a Polygon with the given Rectangle and color
	************************************************************************/
	Polygon(Rect rect);

	Polygon(Rect rect, Color color);

	/***********************************************************************
	* Method: Constructor with Color argument
	* Description: Defines the color of the Polygon
	************************************************************************/
	Polygon(Color color);



	/***************************************************************************************
	* Method: Overloaded += operator
	* Description: Adds the coordinates of the given Point to the Polygon
	****************************************************************************************/
	Polygon& operator+=(const Point& point);

	/***************************************************************************************
	* Method: Overloaded -= operator
	* Description: Subtracts the coordinates of the given Point to the Polygon
	****************************************************************************************/
	Polygon& operator-=(const Point& point);

	/***************************************************************************************
	* Method Name: x
	* Description: Returns the x value of the bottom left corner of the polygon
	****************************************************************************************/
	int x();

	/***************************************************************************************
	* Method Name: y
	* Description: Returns the y value of the bottom left corner of the polygon
	****************************************************************************************/
	int y();

	/***************************************************************************************
	* Method Name: width
	* Description: Returns the width of the Rectangle that contains the polygon
	****************************************************************************************/
	int width();

	/***************************************************************************************
	* Method Name: height
	* Description: Returns the height of the Rectangle that contains the polygon
	****************************************************************************************/
	int height();

	/***************************************************************************************
	* Method Name: rightX
	* Description: Returns the x value of the right corner of the Polygon
	****************************************************************************************/
	int Polygon::rightX();

	/***************************************************************************************
	* Method Name: topY
	* Description: Returns the y value of the Top corner of the Polygon
	****************************************************************************************/
	int topY();

	/***************************************************************************************
	* Method Name: setX
	* Description: Sets the x coordinate of the bottom left corner of the Polygon
	****************************************************************************************/
	void setX(GLint x);

	/***************************************************************************************
	* Method Name: setY
	* Description: Sets the y coordinate of the bottom left corner of the Polygon
	****************************************************************************************/
	void setY(GLint y);

	/***************************************************************************************
	* Method Name: setPos
	* Description: Sets the x and y coordinates of the bottom left corner of the Polygon
	****************************************************************************************/
	void setPos(GLint x, GLint y);

	/***************************************************************************************
	* Method Name: draw
	* Description: Draws the polygon
	****************************************************************************************/
	void draw();

	void setColor(GLint r, GLint g, GLint b);
	void setColor(Color color);
	Color color();

	/***************************************************************************************
	* Method Name: push_back(Rect)
	* Description: Adds a given rectangle to the current polygon
	****************************************************************************************/
	void push_back(Rect rect);

	/***************************************************************************************
	* Method Name: push_back(Polygon)
	* Description: Adds a given polygon to the current polygon
	****************************************************************************************/
	void push_back(Polygon pol);

	void mirrorX();
	void mirrorX(int currentX);

	void drawPolygon(int x, int y);
};

#endif