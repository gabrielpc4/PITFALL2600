#include "TunnelHole.h"


TunnelHole::TunnelHole()
	:TunnelHole(LEFT_TUNNEL_HOLE, 96)
{
}

TunnelHole::TunnelHole(int SIDE)
	: TunnelHole(SIDE, 96)
{

}

TunnelHole::TunnelHole(float startX, float startY)
	: Sprite(startX, startY)
{
	Sprite::push_back(Rect(Point(0, 40), Point(43, 46)), Color(BLACK));	// Black rectangle  : width:ladder.width() height: 6
	Sprite::push_back(Rect(Point(0, 46), Point(43, 52)), Color(67.0, 0.0, 0.0));   // DarkRed rectangle: width:ladder.width() height: 12 - 6 = 6	
	Sprite::push_back(Rect(Point(0, 0), Point(43, 30)), Color(67.0, 0.0, 0.0));   // DarkRed rectangle: width:ladder.width() height: 12 - 6 = 6	
	tunnelHole = Rect(Point(0, 0), Point(this->width(), 30));
	overlayer.push_back(Rect(Point(startX - 10, startY + 30), Point(startX + this->width() + 10, startY + 40)), Color(187, 147, 0));
}

void TunnelHole::drawOverlayer()
{
	overlayer.draw();
}

TunnelHole::~TunnelHole()
{
	overlayer.clear();
}
