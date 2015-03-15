#pragma once
#ifndef POLYGON_H_
#define POLYGON_H_

#include "Point.h"
#include "Rect.h"
#include "Color.h"
#include "constants.h"
#include <vector>
#include "glut.h" 

using namespace std;

class Polygon
	: public vector<Rect>,
	public Rect
{
protected:
	float startX;
	float startY;

public:
	Polygon();
	Polygon(float startX, float startY);
	Polygon(float startX, float startY, Color color);
	Polygon(Rect rect, Color color);
	Polygon(Rect rect);
	Polygon(Color color);
	Polygon& operator=(const Polygon& p2);
	Polygon& operator+=(const Point& point);
	Polygon& operator-=(const Point& point);
	void setX(GLint x);
	void setY(GLint y);
	void setPos(GLint x, GLint y);
	void update();
	void updateX();
	void push_back(Rect rect);
	void push_back(Polygon pol);
	void mirrorX();
	void mirrorX(int spriteX);
	void  draw() ;
};
#endif