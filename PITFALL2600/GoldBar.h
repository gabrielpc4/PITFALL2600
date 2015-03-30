#pragma once
#ifndef GOLDBAR_H_
#define GOLDBAR_H_
#include "AnimatedObject.h"
class GoldBar :
	public AnimatedObject
{
private:
	Sprite sparkles;
public:
	GoldBar();
	GoldBar(float startX, float startY);
	void buildSprite();
	void draw();
	void animate();
	~GoldBar();
};
#endif

