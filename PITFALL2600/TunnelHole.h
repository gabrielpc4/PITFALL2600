#pragma once
#ifndef TUNNELHOLE_H
#define TUNNELHOLE_H
#include "Sprite.h"
class TunnelHole :
	public Sprite
{
private:
	Rect tunnelHole;
	Sprite overlayer;
public:
	TunnelHole();
	TunnelHole(int SIDE);
	TunnelHole(float startX, float startY);	
	void drawOverlayer();
	~TunnelHole();
};
#endif
