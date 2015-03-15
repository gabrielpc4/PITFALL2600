#include "TunnelHole.h"


TunnelHole::TunnelHole()
	:TunnelHole(0, 0)
{
}

TunnelHole::TunnelHole(float startX, float startY)
	: Sprite(startX, startY)
{
	Sprite::push_back(Rect(Point(0, 40), Point(43, 46)), Color(BLACK));	// Black rectangle  : width:stairs.width() height: 6
	Sprite::push_back(Rect(Point(0, 46), Point(43, 52)), Color(67.0, 0.0, 0.0));   // DarkRed rectangle: width:stairs.width() height: 12 - 6 = 6	
	Sprite::push_back(Rect(Point(0, 0), Point(43, 30)), Color(67.0, 0.0, 0.0));   // DarkRed rectangle: width:stairs.width() height: 12 - 6 = 6	
	tunnelHole = Rect(Point(0, 0), Point(this->width(), 30));
	cover.push_back(Rect(Point(startX - 10, startY + 30), Point(startX + this->width() + 10, startY + 40)), Color(187, 147, 0));
}

void TunnelHole::drawCover()
{
	cover.draw();
}
