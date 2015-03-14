#include "LogSprite.h"
#include "echo.h"

LogSprite::LogSprite()
	: LogSprite(442,128)
{
}

LogSprite::LogSprite(GLint startX, GLint startY)	
	: Sprite(startX, startY)
{
	frames = 0;
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

void LogSprite::animate()
{
	frames++;

	if (frames % ANIMATION_REFRESH_INTERVAL  == 0)
	{
		Sprite::mirrorX();

		if (frames >= INT_MAX)
		{
			frames = 0;
		}
	}
}


LogSprite::~LogSprite()
{
}
