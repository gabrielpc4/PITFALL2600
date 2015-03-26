#include "AnimatedObject.h"


AnimatedObject::AnimatedObject()
	: AnimatedObject(0,0)
{
	
}

AnimatedObject::AnimatedObject(float startX, float startY)
	: Sprite(startX,startY),
	_speed(0, 0)
{
	animationFrame  = 0;
	frames			= 0;
	animationRefreshInterval = DEFAULT_ANIMATION_REFRESH_INTERVAL;
}

void AnimatedObject::move()
{
	*this += _speed;
}

void AnimatedObject::draw()
{
	animate(1);
	Sprite::draw();
}

void AnimatedObject::animate(int maxAnimationFrame)
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

		Sprite::clear();
		buildSprite(animationFrame);

		if (frames >= INT_MAX)
		{
			frames = 0;
		}
	}
}

void AnimatedObject::buildSprite(int animationFrame)
{

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

AnimatedObject::~AnimatedObject()
{
}
