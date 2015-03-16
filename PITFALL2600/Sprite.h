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
	public vector < Polygon >,
	public Polygon
{
public:
	Sprite();
	Sprite(GLint startX, GLint startY);
	Sprite(Rect rect, Color color);
	Sprite(Polygon pol);
	Sprite& operator+=(const Point& point);
	Sprite& operator -= (const Point& point);
	void setX(GLint x);
	void setY(GLint y);
	void setPos(GLint x, GLint y);
	void update();
	void updateX();
	void push_back(Rect rect);
	void push_back(Rect rect, Color color);
	void push_back(Polygon pol);
	void push_back(Sprite sprite);
	void mirrorX();
	void draw();
	void clear();
	void updateWH();
	void setColor(Color color);
};
#endif

