#pragma once
#ifndef POLYGONS_H_
#define POLYGONS_H_

#include "Point.h"
#include "Rect.h"
#include "Color.h"
#include "global_constants.h"
#include <vector>

using namespace std;

class Polygons
	: public vector<Rect>,
	public Rect
{
protected:
	float startX;
	float startY;

public:
	Polygons();
	Polygons(float startX, float startY);
	Polygons(float startX, float startY, Color color);
	Polygons(Rect rect, Color color);
	Polygons(Rect rect);
	Polygons(Color color);
	Polygons& operator=(const Polygons& p2);
	Polygons& operator+=(const Point& point);
	Polygons& operator-=(const Point& point);
	void setX(GLint x);
	void setY(GLint y);
	void setPos(GLint x, GLint y);
	void update();
	void updateX();
	void push_back(Rect rect);
	void push_back(Polygons pol);
	void mirrorX();
	void mirrorX(int spriteX);
	void  draw() ;
};
#endif