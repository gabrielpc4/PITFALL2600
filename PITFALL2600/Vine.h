#pragma once
#ifndef VINE_H_
#define VINHE_H_
#include "constants.h"
#include "Circle.h"
#include "Rect.h"

class Vine
	: public Rect
{
private:
	float m = 0.5;
	unsigned i;
	Circle circle;	
	int swingDirection;
	Point origin;
	int minX;
	Point max;
	float differenceToCenter;
	float maxDifferenceToCenter;
	
public:
	Point end;
	Vine();
	void drawCircleTrack();
	void draw();
	void swing();
	~Vine();
};
#endif

