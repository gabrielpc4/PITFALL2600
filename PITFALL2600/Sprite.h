#ifndef SPRITE_H_
#define SPRITE_H_

#include "Point.h"
#include "Rect.h"
#include "Polygon.h"
#include "Color.h"
#include <vector>
#include "glut.h" // Custom glut.h fixed for using namespace std

using namespace std;

class Sprite :
	public vector < Polygon >
{
private:
	float _x;
	float _y;
	int _width;
	int _height;
public:
	/***************************************************************************************
	* Method: Default Constructor
	* Description: It does nothing
	****************************************************************************************/
	Sprite() {}

	Sprite(GLint startX, GLint startY) { _x = startX; _y = startY; }

	void update();
	

	/***************************************************************************************
	* Method: Constructor with a Rectangle parameter
	* Description: Initializes a Sprite, with the given Rectangle and a color
	****************************************************************************************/
	Sprite(Rect rect, Color color);

	/***************************************************************************************
	* Method: Constructor with a Polygon parameter
	* Description: Initializes a Sprite, with the given Polygon
	****************************************************************************************/
	Sprite(Polygon pol);

	/***************************************************************************************
	* Method: Overloaded += operator
	* Description: Adds the coordinates of the given Point to the Sprite
	****************************************************************************************/
	Sprite& operator+=(const Point& point);

	/***************************************************************************************
	* Method: Overloaded-+= operator
	* Description: Subtracts the coordinates of the given Point to the Sprite
	****************************************************************************************/
	Sprite& operator -= (const Point& point);

	/***************************************************************************************
	* Method Name: x
	* Description: Returns the x value of the bottom left corner of the Sprite
	****************************************************************************************/
	int x();

	/***************************************************************************************
	* Method Name: y
	* Description: Returns the y value of the bottom left corner of the Sprite
	****************************************************************************************/
	int y();

	/***************************************************************************************
	* Method Name: width
	* Description: Returns the width of the Rectangle that contains the Sprite
	****************************************************************************************/
	int width();

	/***************************************************************************************
	* Method Name: height
	* Description: Returns the height of the Rectangle that contains the Sprite
	****************************************************************************************/
	int height();

	/***************************************************************************************
	* Method Name: rightX
	* Description: Returns the x value of the right corner of the Sprite
	****************************************************************************************/
	int rightX();

	/***************************************************************************************
	* Method Name: topY
	* Description: Returns the y value of the Top corner of the Sprite
	****************************************************************************************/
	int topY();


	/***************************************************************************************
	* Method Name: setX
	* Description: Sets the x coordinate of the bottom left corner of the Sprite
	****************************************************************************************/
	void setX(GLint x);

	/***************************************************************************************
	* Method Name: setY
	* Description: Sets the y coordinate of the bottom left corner of the Sprite
	****************************************************************************************/
	void setY(GLint y);	

	/***************************************************************************************
	* Method Name: setPos
	* Description: Sets the x and y coordinates of the bottom left corner of the Sprite
	****************************************************************************************/
	void setPos(GLint x, GLint y);	

	/***************************************************************************************
	* Method Name: draw
	* Description: Draws the Sprite
	****************************************************************************************/
	void draw();

	/***************************************************************************************
	* Method Name: push_back
	* Description: Adds a rectangle to the sprite
	****************************************************************************************/
	void push_back(Rect rect);



	/***************************************************************************************
	* Method Name: push_back
	* Description: Adds a rectangle to the sprite with a specific color
	****************************************************************************************/
	void push_back(Rect rect, Color color);

	void push_back(Polygon pol);

	/***************************************************************************************
	* Method Name: push_back(Sprite)
	* Description: Adds a given sprite to the current sprite
	****************************************************************************************/
	void push_back(Sprite sprite);

	void mirrorX();

	void drawSprite(int x, int y);
};

#endif

