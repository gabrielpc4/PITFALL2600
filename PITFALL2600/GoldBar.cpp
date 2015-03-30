#include "GoldBar.h"


GoldBar::GoldBar()
	: GoldBar(413, 132)
{
}

GoldBar::GoldBar(float startX, float startY)
	: AnimatedObject(startX, startY, 1),
	sparkles(startX, startY)
{
	animationRefreshInterval = 3;
	setColor(Color(YELLOW));
	Point p1(0,0);
	Point p2(18,8);
	for (int i = 0; i < 3; i++)
	{
		push_back(Rect(p1, p2));
		p1 += Point(4, 2);
		p2 += Point(4, 2);
	}		
	update();
	buildSprite();
	sparkles.setColor(Color(WHITE));	
}

void GoldBar::buildSprite()
{	
	if (animationFrame == 0)
	{
		Point p1(11, 14);
		Point p2(15, 16);

		for (int i = 0; i < 4; i++)
		{
			sparkles.push_back(Rect(p1, p2));
			p1 += Point(0, 4);
			p2 += Point(0, 4);

			Rect r = Rect(p1, p2);
			if (i < 2)
			{
				sparkles.push_back(r + Point(7 * (i + 1), 0));
				sparkles.push_back(r + Point(-7 * (i + 1), 0));
			}
		}
	}
	else
	{
		Point p1(8, 16);
		Point p2(11, 18);

		sparkles.push_back(Rect(p1, p2));

		p1 += Point(7, 0);
		p2 += Point(7, 0);

		sparkles.push_back(Rect(p1, p2));

		p1 = Point(11, 20);
		p2 = Point(15, 22);

		sparkles.push_back(Rect(p1, p2));

		p1 += Point(-7, 0);
		p2 += Point(-7, 0);

		sparkles.push_back(Rect(p1, p2));


		p1 += Point(14, 0);
		p2 += Point(14, 0);

		sparkles.push_back(Rect(p1, p2));

		p1 += Point(-7, 4);
		p2 += Point(-7, 4);

		sparkles.push_back(Rect(p1, p2));
	}
	
}

void GoldBar::animate()
{
	frames++;

	if (frames % animationRefreshInterval == 0)
	{

		if (animationFrame >= maxAnimationFrame)
		{
			animationFrame = 0;
		}
		else
		{
			animationFrame++;
		}

		sparkles.clear();
		buildSprite();

		if (frames >= INT_MAX)
		{
			frames = 0;
		}
	}
}

void GoldBar::draw()
{
	this->animate();
	sparkles.draw();
	Sprite::draw();
}

GoldBar::~GoldBar()
{
	sparkles.clear();
}
