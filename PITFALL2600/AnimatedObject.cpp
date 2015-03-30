#include "AnimatedObject.h"


AnimatedObject::AnimatedObject()
	: AnimatedObject(0,0,1)
{
	
}

AnimatedObject::AnimatedObject(float startX, float startY, int maxAnimationFrame)
	: Sprite(startX,startY),
	_speed(0, 0)
{
	animationFrame				= 0;
	frames						= 0;
	this->maxAnimationFrame		= maxAnimationFrame;
	animationRefreshInterval	= DEFAULT_ANIMATION_REFRESH_INTERVAL;
}

void AnimatedObject::move()
{
	*this += _speed;
}

void AnimatedObject::draw()
{
	animate();
	Sprite::draw();
}

void AnimatedObject::shiftSpriteOnly(float x, float y)
{
	for (vector<Polygon>::iterator currentPolygon = this->begin(); currentPolygon != this->end(); ++currentPolygon)
	{
		*currentPolygon += Point(x,y);
	}
}

void AnimatedObject::animate()
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

		clear();
		buildSprite();

		if (frames >= INT_MAX)
		{
			frames = 0;
		}
	}
}

void AnimatedObject::buildSprite()
{

}

void AnimatedObject::drawAllRectanglesOutlines()
{
	for (vector<Polygon>::iterator objectPolygon = this->begin(); objectPolygon != this->end(); objectPolygon++)
	{
		for (vector<Rect>::iterator objectRect = objectPolygon->begin(); objectRect != objectPolygon->end(); objectRect++)
		{
			glColor3ub(255, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(objectRect->x(), objectRect->y());
			glVertex2f(objectRect->x() + objectRect->width(), objectRect->y());
			glVertex2f(objectRect->x() + objectRect->width(), objectRect->y() + objectRect->height());
			glVertex2f(objectRect->x(), objectRect->y() + objectRect->height());
			glEnd();
		}
	}
}

void AnimatedObject::push_back(Rect rect)
{
	Polygon p(Sprite::_x, Sprite::_y);
	if (Sprite::_color.notInformed())
	{
		p.setColor(rect.color());
	}
	else
	{
		p.setColor(Sprite::color());
	}
	
	p.push_back(rect);
	vector<Polygon>::push_back(p);
}

void AnimatedObject::push_back(Polygon pol)
{
	Polygon p(Sprite::_x, Sprite::_y, pol.color());
	p.push_back(pol);
	Sprite::push_back(p);
}

void AnimatedObject::setSpeed(float xSpeed, float ySpeed)
{
	_speed = Point(xSpeed, ySpeed);
}

void AnimatedObject::setSpeedX(float xSpeed)
{
	_speed.setX(xSpeed);
}

void AnimatedObject::setSpeedY(float ySpeed)
{
	_speed.setY(ySpeed);
}

Point AnimatedObject::speed()
{
	return _speed;
}

void AnimatedObject::setAnimationFrame(int number)
{
	animationFrame = number;
}

unsigned AnimatedObject::totalPolygons()
{
	return Sprite::size();
}

AnimatedObject::~AnimatedObject()
{
}
