#pragma once
#ifndef CIRCLE_H_
#define CIRCLE_H_
#include <vector>
#include "Point.h"

using namespace std;
class Circle
{
private:
	
	Point center;
	int radius;
public:
	vector<Point> points;
	vector<Point> temp;
	Circle();
	Circle(float centerX, float centerY, int radius);
	void buildCircle();
	void draw();
	void light(Point p);
	void bresenhamCircleScan();
	~Circle();
};
#endif

