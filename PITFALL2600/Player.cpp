#include "Player.h"


Player::Player() :
	Player(0, 0)
{
}

Player::Player(GLint startX, GLint startY) : GameObject(startX,startY)
{
	animationFrame = 0;
	lookingDirection = RIGHT;
	jumping = false;
	_speed = 0;
	this->sprite = new PlayerSprite(startX, startY, 0, RIGHT);
	loop = 0;
	_width = this->sprite->width();
	_height = this->sprite->height();
	falling = false;
	_moving = false;


}

void Player::draw()
{
	
	if (this->rightX() > WORLD_WINDOW_WIDTH)
	{
		this->setX(1);
	}
	if (this->x() < 0)
	{
		this->setX(WORLD_WINDOW_WIDTH - this->width());
	}
	Point backup(this->x(), this->y());	
	delete sprite;


	sprite = new PlayerSprite(backup.x(), backup.y(), animationFrame, lookingDirection);

	
	int difference_x = backup.x() - (backup.x() + this->sprite->x());
	int difference_y = this->_height - this->sprite->height();
	
	sprite->drawSprite(backup.x() - difference_x, backup.y() + difference_y);
}

void Player::jump()
{
	if (!jumping)
	{
		ground_y = this->y();
		jumping = true;
	}	
}

bool Player::isJumping()
{
	return jumping;
}

void Player::move()
{
	if (this->isMoving() || jumping)
	{
		if (!jumping)
		{
			if (this->isLooking(RIGHT))
			{
				this->setSpeed(+PLAYER_SPEED);
			}
			else
			{
				this->setSpeed(-PLAYER_SPEED);
			}
			loop++;

			if (loop % ANIMATION_REFRESH_INTERVAL == 0)
			{

				if (animationFrame >= 5)
				{
					animationFrame = 1;
				}
				else
				{
					animationFrame++;
				}

				if (loop >= INT_MAX)
				{
					loop = 0;
				}
			}
		}
		else
		{
			animationFrame = 5;

			int currentJumpHeight = (this->y() - ground_y);
			if (currentJumpHeight < 22 && !falling)
			{
				*this += Point(0, JUMP_SPEED);
			}
			else
			{
				falling = true;
			}
			if (falling)
			{
				if (this->y() >= ground_y)
				{
					if ((this->y() - ground_y) <= JUMP_SPEED)
					{
						this->setY(ground_y);
						falling = false;
						jumping = false;

						if (!this->isMoving())
						{
							this->setSpeed(0);
						}
					}
					else
					{
						*this += Point(0, -JUMP_SPEED);
					}
				}
			}
		}
	}
	*this += Point(this->_speed, 0);
	if (!_moving && !jumping)
	{	
		this->setSpeed(0);
		animationFrame = 0;
	}
}
	




void Player::look(int DIRECTION)
{
	lookingDirection = DIRECTION;
}

bool Player::isLooking(int DIRECTION)
{
	return (DIRECTION == lookingDirection);
}

void Player::setSpeed(int speed)
{
	this->_speed = speed;
}

int Player::speed()
{
	return _speed;
}

void Player::moving(bool state)
{
	_moving = state;
}
bool Player::isMoving()
{
	return _moving;
}