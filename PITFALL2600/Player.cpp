#include "Player.h"


Player::Player() :
	Player(0, 0)
{
}

Player::Player(GLint startX, GLint startY) 
	: GameObject(startX,startY),
	playerSpeed(0,0)
{		
	this->sprite = new PlayerSprite(startX, startY, 0, RIGHT, false);

	_jumping = false;		
	_width = this->sprite->width();
	_height = this->sprite->height();
	_falling = false;
	_walking = false;
	_climbing = false;
	_climbingDirection = UP;

	animationFrame = 0;
	loop = 0;
	floor = startY;
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
	
	if (isClimbing() == false)
	{
		if (isWalking())
		{
			animate(1, 5);
		}
		else
		{
			animationFrame = 0;
		}		
	}

	if (isJumping() && (isClimbing() == false))
	{
		animationFrame = 5;
	}
	if (isFalling() && (isJumping() == false) && (isClimbing() == false))
	{
		animationFrame = 0;
	}
	if (isClimbing())
	{
		animate(0, 1);
	}
	
	sprite = new PlayerSprite(backup.x(), backup.y(), animationFrame, lookingDirection, isClimbing());
	int difference_x = backup.x() - (backup.x() + this->sprite->x());
	int difference_y = this->_height - this->sprite->height();
	cout << "j:" << _jumping << "  sY:" << playerSpeed.y() << "  f:" << floor <<endl;

	sprite->drawSprite(backup.x() - difference_x, backup.y() + difference_y);
}

void Player::jumping(bool state)
{
	if (state == true)
	{
		if (isJumping() == false)
		{
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
	int currentJumpHeight = (this->y() - floor);

	if (currentJumpHeight < JUMP_MAX_HEIGHT && (isFalling() == false))
	{
		setSpeedY(JUMP_SPEED);
	}
	else
	{
		_falling = true;
	}


	if (isFalling())
	{
		if (this->y() > floor)
		{
			if ((this->y() - floor) > FALLING_SPEED)
			{
				setSpeedY(-FALLING_SPEED);			
			}
			else
			{
				setY(floor);
				setSpeedY(0);
				_falling = false;
				_jumping = false;

				if (isWalking() == false)
				{
					setSpeedX(0);
				}
			}
		}
	}
}

void Player::fall()
{
	animationFrame = 0;
	setSpeedX(0);
	if (this->y() > floor)
	{
		if ((this->y() - floor) > FALLING_SPEED)
		{
			setSpeedY(-FALLING_SPEED);			
		}
		else
		{
			setY(floor);
			setSpeedY(0);
			_falling = false;
		}
	}
}

void Player::animate(int minFrameNum, int maxFramenum)
{
	loop++;
	int refreshInterval = ANIMATION_REFRESH_INTERVAL;

	if (isClimbing())
	{
		refreshInterval = CLIMBING_ANIMATION_REFRESH_INTERVAL;
	}
	if (loop % refreshInterval == 0)
	{
		if (isWalking() || (isClimbing() && climbingDirection() != NONE))
		{
			animationFrame++;
		}
		if (animationFrame > maxFramenum)
		{
			animationFrame = minFrameNum;
		}

		if (loop >= INT_MAX)
		{
			loop = 0;
		}
	}	
}


void Player::move()
{

	if ((isWalking() || isJumping()) && (isClimbing() == false))
	{
		if (isJumping())
		{
			jump();
		}
		else
		{			
			if (this->isLooking(RIGHT))
			{
				setSpeedX(+PLAYER_SPEED);
			}
			else
			{
				setSpeedX(-PLAYER_SPEED);
			}		
		}
	}

	if (isFalling() && (isJumping() == false) && (isClimbing() == false))
	{
		fall();
	}
	
	if (isClimbing())
	{
		climb();
	}
	
	/*********** MOVES THE PLAYER ***********/
	*this += playerSpeed;

	if ((isWalking() == false) && (isJumping() == false))
	{	
		setSpeedX(0);
	}
}
	

void Player::climb(int direction)
{
	_climbingDirection = direction;
}

void Player::climb()
{
	setSpeedX(0);

	if (_climbingDirection == NONE)
	{
		setSpeedY(0);
	}
	else if (_climbingDirection == UP)
	{
		setSpeedY(+CLIMBING_SPEED);
	}
	else
	{
		setSpeedY(-CLIMBING_SPEED);
	}
}


bool Player::willFall(GameObject* hole)
{
		
	if (lookingDirection == RIGHT)
	{
		if (this->x() > hole->x() && this->rightX() <= hole->rightX())
		{
			return true;
		}
	}
	else
	{
		if (this->rightX() < hole->rightX() && this->x() >= hole->x())
		{
			return true;
		}
	}
	
	return false;
}

bool Player::isAbleToClimbOut(GameObject* hole)
{
	this->floor = GROUND_Y;
	return (((this->y() + this->height() / 2.0) + CLIMBING_SPEED) > hole->y());
}

void Player::climbOut(int direction)
{
	setY(GROUND_Y + 5);
	if (direction == RIGHT)
	{
		setSpeedX(+PLAYER_SPEED);		
	}	
	else
	{
		setSpeedX(-PLAYER_SPEED);
	}
	this->jumping(true);
	this->climbing(false);
	
}

int Player::climbingDirection()
{
	return _climbingDirection;
}

void Player::stopClimbing()
{
	_climbingDirection = NONE;
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

void Player::walking(bool state)
{
	_walking = state;
}
bool Player::isWalking()
{
	return _walking;
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
	_climbing = state;
}
bool Player::isClimbing()
{
	return _climbing;
}

bool Player::isJumping()
{
	return _jumping;
}

void Player::centerOnStair(GameObject* stairs)
{
	setX(stairs->x() + 8);
}