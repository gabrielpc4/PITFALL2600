#pragma once
#ifndef COLOR_H_
#define COLOR_H_

#include "glut.h"  //Custom glut.h fixed to work with stdlib.h
#include <gl/gl.h>
/*****************************************************************************************
* Class: Color
* Description: This class sets the openGL current color for drawing, using the constructor
or the method setColor. The color system is rgb with the range 0 - 255
******************************************************************************************/
#define BLACK 0
#define RED 25
#define GREEN 50
#define BLUE 75
#define YELLOW 10
#define WHITE 255

class Color
{
private:
	GLint _r;
	GLint _g;
	GLint _b;
	bool informed;

public:
	/**********************************************************************
	* Method: Default Constructor
	* Description: Initializes a Color with black
	**********************************************************************/
	Color();

	/**********************************************************************
	* Method: Constant Constructor
	* Description: Initializes a Color with black or white
	**********************************************************************/
	Color(const int COLOR_CONSTANT);

	/*******************************************************************************
	* Method: Default Constructor
	* Description: Initializes a Color with the given red green blue values (0-255)
	********************************************************************************/
	Color(GLint r, GLint g, GLint b);

	/**********************************************************************
	* Method: setColor
	* Description: changes the color red green blue values (0-255)
	**********************************************************************/
	void setColor(GLint r, GLint g, GLint b);

	/********************************************************************
	* Method: Overloaded = operator
	* Description: Allows to use (Color)p1 =(Color)c2;
	********************************************************************/
	void Color::operator=(Color& c2);

	/**********************************************************************
	* Method: r()
	* Description: Returns the red ammount in the color (0-255)
	**********************************************************************/
	GLint r();

	/**********************************************************************
	* Method: g()
	* Description: Returns the green ammount in the color (0-255)
	**********************************************************************/
	GLint g();

	/**********************************************************************
	* Method: b()
	* Description: Returns the blue ammount in the color (0-255)
	**********************************************************************/
	GLint b();

	bool notInformed();
};
#endif