#include "GameObject.h"

GameObject::GameObject(int startX, int startY)
	: Point(startX, startY)
{
	sprite = new Sprite();
}



void GameObject::drawSprite(int x, int y)
{
	sprite->drawSprite(x, y);
}

GameObject::~GameObject()
{

}

GameObject& GameObject::operator=(const GameObject& g2)
{
	sprite = g2.sprite;
	this->setX(g2.x());
	this->setY(g2.y());
	return *this;
}
GameObject& GameObject::operator+=(const Point& p)
{
	*sprite += p;
	setX(x() + p.x());
	setY(y() + p.y());
	return *this;
}

const GameObject GameObject::operator+(const Point& p) const
{
	GameObject g1 = *this;
	g1 += p;	
	return g1;
}

GLint GameObject::width() const
{
	return sprite->width();
}
GLint GameObject::height() const
{
	return sprite->height();
}
int GameObject::rightX()
{
	return this->x() + this->width();
}
int GameObject::topY()
{
	return (this->y() + this->height());
}

