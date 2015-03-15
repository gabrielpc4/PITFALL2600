#pragma once
#ifndef RECT_H_
#define RECT_H_

#include "Point.h"
#include "Color.h"
#include <cmath>
#include "glut.h"
class Rect
	: public Point
{
protected:
	float _width;
	float _height;
	Color _color;
public:
	Rect();
	Rect(float x, float y, float w, float h);
	Rect(float x, float y, float w, float h, Color color);
	Rect(Point p1, Point p2, Color color);
	Rect(Point p1, Point p2);
	Rect& operator=(const Rect& r2);
	const Rect virtual operator+(const Point& point) const;
	const Rect virtual operator-(const Point& point) const;
	float width() const;
	float height() const;
	int rightX() const;
	int topY() const;
	void virtual draw() const;
	void draw(Color color) const;
	void setColor(Color color);
	Color color() const;
};
#endif