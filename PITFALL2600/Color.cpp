#include "Color.h"

/**********************************************************************
* Method: Default Constructor
* Class: Color
* Description: Initializes a Color with black
**********************************************************************/
Color::Color()
{
	glColor3ub(0, 0, 0);
	this->_r = 0;
	this->_g = 0;
	this->_b = 0;
	informed = false;
}


/**********************************************************************
* Method: Constant Constructor
* Description: Initializes a Color with black or white
**********************************************************************/
Color::Color(const int COLOR_CONSTANT)
{
	informed = true;
	switch (COLOR_CONSTANT)
	{
		case(BLACK)  : { *this = Color(); }break;
		case(WHITE)  : { *this =  Color(255, 255, 255); }break;
		case(RED)    : { *this = Color(255, 0, 0); }break;
		case(GREEN)  : { *this = Color(0, 255, 0); }break;
		case(BLUE)   : { *this = Color(0, 0, 200); }break;
		case(YELLOW) : { *this = Color(255, 255, 0); }break;
		default:{*this = Color(); };
	}
}
/*******************************************************************************
* Method: Default Constructor
* Class: Color
* Description: Initializes a Color with the given red green blue values (0-255)
********************************************************************************/
Color::Color(GLint r, GLint g, GLint b)
{
	informed = true;
	glColor3ub(r, g, b);
	this->_r = r;
	this->_g = g;
	this->_b = b;
}

/**********************************************************************
* Method: setColor
* Class: Color
* Description: changes the color red green blue values (0-255)
**********************************************************************/
void Color::setColor(GLint r, GLint g, GLint b)
{
	informed = true;
	glColor3ub(r, g, b);
	this->_r = r;
	this->_g = g;
	this->_b = b;
}

/********************************************************************
* Method: Overloaded = operator
* Class: Color
* Description: Allows to use (Color)p1 =(Color)c2;
********************************************************************/
void Color::operator=(Color& c2)
{
	informed = true;
	this->setColor(c2.r(), c2.g(), c2.b());
}

/**********************************************************************
* Method: r()
* Class: Color
* Description: Returns the red ammount in the color (0-255)
**********************************************************************/
GLint Color::r()
{
	return _r;
}

/**********************************************************************
* Method: g()
* Class: Color
* Description: Returns the green ammount in the color (0-255)
**********************************************************************/
GLint Color::g()
{
	return _g;
}

/**********************************************************************
* Method: b()
* Class: Color
* Description: Returns the blue ammount in the color (0-255)
**********************************************************************/
GLint Color::b()
{
	return _b;
}

bool Color::notInformed()
{
	return(!informed);
}