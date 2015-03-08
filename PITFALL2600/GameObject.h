#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Sprite.h"
#include "PlayerSprite.h"
#include<typeinfo.h>

#include "echo.h"
class GameObject : public Point
{
public:
	Sprite* sprite;
	GameObject() {}
	GameObject(int startX, int startY);
	~GameObject();
	GameObject& operator=(const GameObject& g2);
	GameObject& operator+=(const Point& p2);
	const GameObject operator+(const Point& p2) const;
	GLint width() const;
	GLint height() const;
	int rightX();
	int topY();
	void drawSprite(int x, int y);

};

#endif
