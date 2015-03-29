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
	int type;
	bool canChangeSize;	

	void expandOrShrink();
	void buildSprite();
public:	
	Hole();
	Hole(Color color, int type);
	Hole(float startX, float startY, Color color, int type);
	void animate();
	void draw();
	void DRAW_OVERLAYER_ON_DEBUG_MODE();
	void drawOverlayer();
	void setType(int type);
	void enableSizeChanging();
	void disableSizeChanging();	
	~Hole();
};
#endif
