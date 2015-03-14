#include "HoleSprite.h"


HoleSprite::HoleSprite()
	: HoleSprite(150,132)
{
}

HoleSprite::HoleSprite(GLint startX, GLint startY)
	: Sprite(startX, startY)
{
	Polygon log(Color(80, 32, 0));

	log.push_back(Rect(Point(7, 0), Point(14, 2)));
	log.push_back(Rect(Point(4, 2), Point(7, 4)));
	log.push_back(Rect(Point(14, 2), Point(18, 4)));
	log.push_back(Rect(Point(0, 4), Point(4, 24)));
	log.push_back(Rect(Point(7, 4), Point(14, 10)));
	log.push_back(Rect(Point(18, 4), Point(22, 24)));
	log.push_back(Rect(Point(4, 10), Point(7, 14)));
	log.push_back(Rect(Point(14, 10), Point(18, 26)));
	log.push_back(Rect(Point(4, 16), Point(11, 20)));
	log.push_back(Rect(Point(4, 22), Point(11, 26)));
	log.push_back(Rect(Point(7, 12), Point(14, 16)));
	log.push_back(Rect(Point(11, 18), Point(14, 20)));
	log.push_back(Rect(Point(7, 20), Point(14, 22)));
	log.push_back(Rect(Point(11, 24), Point(14, 26)));
	log.push_back(Rect(Point(7, 26), Point(14, 28)));

	Sprite::push_back(log);
}


HoleSprite::~HoleSprite()
{
}
