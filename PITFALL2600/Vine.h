#pragma once
#ifndef VINE_H_
#define VINHE_H_
#include "global_constants.h"
#include "Circle.h"

class Vine
{
private:
	unsigned i;
	int swingDirection;
	Circle circle;
	Point origin;
	Point max;
	Point _end;
	
public:	
	Vine();
	void drawCircleTrack();
	void draw();
	void swing();
	Point& end();
	~Vine();
};
#endif

