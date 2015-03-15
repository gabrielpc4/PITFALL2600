#pragma once
#ifndef TUNNELHOLE_H
#define TUNNELHOLE_H
#include "Sprite.h"
class TunnelHole :
	public Sprite
{
private:
	Rect tunnelHole;
	Sprite cover;
public:
	TunnelHole();
	TunnelHole(float startX, float startY);	
	void drawCover();
};
#endif
