#include "Enemy.h"


Enemy::Enemy()
	: Enemy(442, 126)
{
}

Enemy::Enemy(GLint startX, GLint startY)
	: GameObject(startX, startY)
{

}


Enemy::~Enemy()
{
}
