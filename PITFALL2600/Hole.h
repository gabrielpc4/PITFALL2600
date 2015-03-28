#pragma once
#ifndef HOLE_H_
#define HOLE_H_
#include "AnimatedObject.h"
class Hole :
	public AnimatedObject
{
private:
	Sprite topOverlayer;
	Sprite bottomOverlayer;
	vector<Point> movingHolePoints;
	vector<Point> staticHolePoints;
	bool changesSize;
	bool moving;
	
public:	
	Hole();
	Hole(Color color, bool changesSize);
	Hole(float startX, float startY, Color color, bool changesSize);
	void buildSprite();
	void draw();
	void drawOverlayer();
	void freeze();
	void unFreeze();
	bool canChangeSize();
	void setMoving(bool state);
	bool canMove();
	~Hole();
};
#endif
