#include "Player.h"


Player::Player() :
	Player(0, 0)
{
}

Player::Player(GLint startX, GLint startY) 
	: GameObject(startX,startY),
	playerSpeed(0,0)

{		
	this->sprite = new PlayerSprite(startX, startY, 0, RIGHT);

	_jumping = false;		
	_width = this->sprite->width();
	_height = this->sprite->height();
	_falling = false;
	_moving = false;
	_climbing = false;

	animationFrame = 0;
	loop = 0;
	ground_y = startY;
	lookingDirection = RIGHT;
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

void Player::jumping(bool state)
{
	if (state == true)
	{
		if (!_jumping)
		{
			ground_y = this->y();
			_jumping = true;
		}
	}
	else
	{
		_jumping = false;
	}
	
}

void Player::jump()
{
	animationFrame = 5;

	int currentJumpHeight = (this->y() - ground_y);
	if (currentJumpHeight < 22 && !_falling)
	{
		this->setSpeedY(JUMP_SPEED);
	}
	else
	{
		_falling = true;
	}

	if (isFalling())
	{
		if (this->y() >= ground_y)
		{
			if ((this->y() - ground_y) <= FALLING_SPEED)
			{
				this->setY(ground_y);
				this->setSpeedY(0);
				_falling = false;
				_jumping = false;

				if (!this->isMoving())
				{
					this->setSpeedX(0);
				}
			}
			else
			{
				this->setSpeedY(-FALLING_SPEED);
			}
		}
	}
}


bool Player::isJumping()
{
	return _jumping;
}

void Player::fall()
{
	animationFrame = 0;
	setSpeedX(0);
	if (this->y() >= ground_y)
	{
		if ((this->y() - ground_y) <= FALLING_SPEED)
		{
			this->setY(ground_y);
			this->setSpeedY(0);
			_falling = false;
		}
		else
		{
			this->setSpeedY(-FALLING_SPEED);
		}
	}
}

void Player::animate()
{
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


void Player::move()
{
	if (this->isMoving() || isJumping())
	{
		if (isJumping())
		{
			jump();
		}
		else
		{
			if (this->isLooking(RIGHT))
			{
				this->setSpeedX(+PLAYER_SPEED);
			}
			else
			{
				this->setSpeedX(-PLAYER_SPEED);
			}
			animate();
		}
	}

	if (isFalling() && !_jumping)
	{
		fall();
	}

	if (isClimbing())
	{
		climb();
	}

	/*********** MOVES THE PLAYER ***********/
	*this += playerSpeed;

	if (!_moving && !_jumping)
	{	
		this->setSpeedX(0);
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

void Player::setSpeedX(int speed)
{
	playerSpeed.setX(speed);
}

void Player::setSpeedY(int speed)
{
	playerSpeed.setY(speed);
}

Point Player::speed()
{
	return playerSpeed;
}

void Player::moving(bool state)
{
	_moving = state;
}
bool Player::isMoving()
{
	return _moving;
}

void Player::falling(bool state)
{
	_falling = state;
}
bool Player::isFalling()
{
	return _falling;
}

void Player::climbing(bool state)
{
	if (!_climbing)
	{
		_climbing = true;
	}
	else
	{
		_climbing = false;
	}
}
bool Player::isClimbing()
{
	return _climbing;
}

void Player::climb()
{
	setSpeedY(CLIMBING_SPEED);
}