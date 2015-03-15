#include "Player.h"


Player::Player() :
	Player(0, 0)
{
}

Player::Player(GLint startX, GLint startY) 
	: PlayerSprite(startX,startY),
	playerSpeed(0,0)
{		
	_down = false;
	_jumping = false;		
	_takingHit = false;
	_falling = false;
	_walking = false;
	_climbing = false;
	_climbingDirection = UP;

	lives = 3;
	animationFrame = 0;
	framesWalking = 0;
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

	
	if (isFalling() && (isJumping() == false) && (isClimbing() == false))
	{
		animationFrame = 0;
	}

	if ((isJumping()) 
		|| (isTakingHit() && isFalling() == false) && (isClimbing() == false) 
		|| (isFalling()) && (this->y() + (this->height() / 2.0) < 96)) // Makes the player open the legs, when there's room for it, when falling
	{
		animationFrame = 5;
	}

	if (isClimbing())
	{
		animate(0, 1);
	}
	

	Point::PRINT(startX, startY);
	PlayerSprite::buildSprite(animationFrame, lookingDirection, isClimbing());

	int difference_x = this->x() - (this->x() + this->x());;
	int difference_y = PLAYER_ANIMATION_0_HEIGHT - this->height();;

	if (isTakingHit() && isJumping() == false && isClimbing() == false)
	{
		difference_y = 0;
	}

	PlayerSprite::draw();
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
	int currentJumpHeight = (this->topY() - (floor + 42));

	if (currentJumpHeight < JUMP_MAX_HEIGHT && _down == false)
	{
		_down = false;
		setSpeedY(JUMP_SPEED);
	}
	else
	{
		_down = true;
	}


	if (_down)
	{
		if (this->y() > floor)
		{
			setSpeedY(-JUMP_SPEED);
		}
		else
		{
			setY(floor);
			setSpeedY(0);
			_falling = false;
			_jumping = false;
			_down = false;

			if (isWalking() == false)
			{
				setSpeedX(0);
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
	framesWalking++;
	int refreshInterval = ANIMATION_REFRESH_INTERVAL;

	if (isClimbing())
	{
		refreshInterval = CLIMBING_ANIMATION_REFRESH_INTERVAL;
	}
	if (framesWalking % refreshInterval == 0)
	{
		if (isWalking() || (isClimbing() && climbingDirection() != NONE))
		{
			//animationFrame++;
		}
		if (animationFrame > maxFramenum)
		{
			animationFrame = minFrameNum;
		}

		if (framesWalking >= INT_MAX)
		{
			framesWalking = 0;
		}
	}	
}


void Player::move()
{
	// If the player is walking or jumping but not climbing
	if ((isWalking() || isJumping()) 
		&& (isClimbing() == false))
	{
		if (isJumping())
		{
			jump();
		}
		else
		{			
			// Changes the player X speed
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

	// If the player is just falling
	if (isFalling() && (isClimbing() == false))
	{
		if (isJumping())
		{
			jumping(false);
		}
		fall();
	}
	
	if (isClimbing())
	{
		// Prevents the player from false jumping, when getting off the stairs, when he initially got on the stairs while jumping
		if (isJumping())
		{
			jumping(false);
		}
		climb();
	}

	// The (isJumping() == false) condition prevents the player from stopping the x position in the middle of a jump
	if ((isWalking() == false) && (isJumping() == false))
	{	
		setSpeedX(0);
	}

	/*********** MOVES THE PLAYER ***********/
	*this += playerSpeed;
}
	


void Player::climb()
{
	// Doesn't allow the player from moving horizontally when climbing
	setSpeedX(0);

	if (_climbingDirection == NONE)
	{
		// Stops the player climbing
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


bool Player::willFall(Sprite* hole)
{		
	if (this->isUndeground() == false)  // Can only fall if it's on the top floor
	{
		if (lookingDirection == RIGHT)
		{
			if (this->x() >= hole->x() && this->x() + PLAYER_ANIMATION_0_WIDTH <= hole->rightX())
			{
				return true;
			}
		}
		else
		{
			if (this->x() + (PLAYER_ANIMATION_0_WIDTH + PLAYER_ANIMATION_0_LOOKING_LEFT_COMPENSATION) <= hole->rightX() 
			&& this->x() + PLAYER_ANIMATION_0_LOOKING_LEFT_COMPENSATION >= hole->x())
			{
				return true;
			}
		}
		return false;
	}	
	return false;
}

bool Player::isAbleToClimbOut(Sprite* hole)
{
	return (((this->y() + this->height() / 2.0) + CLIMBING_SPEED) > hole->y());
}

void Player::climbOut(int direction)
{
	// Moves the floor to the top floor again
	this->floor = GROUND_Y;

	// Teleports the player to a position above the ground ( prevents player stucking)
	setY(GROUND_Y + 5);
	

	if (direction == RIGHT)
	{
		setSpeedX(+PLAYER_SPEED);		
	}	
	else
	{
		setSpeedX(-PLAYER_SPEED);
	}

	// Makes the player jump in the next loop, with the x direction specified by he's speed
	this->jumping(true);

	this->climbing(false);
	
}

void Player::climb(int direction)
{
	_climbingDirection = direction;
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

void Player::setSpeedX(float speed)
{
	playerSpeed.setX(speed);
}

void Player::setSpeedY(float speed)
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

void Player::centerOnStair(Sprite* stairs)
{
	setX(stairs->x() + 5);
}

bool Player::isUndeground()
{
	return (this->y() < 132);
}

int Player::livesLeft()
{
	return lives;
}

void Player::takeHit(bool state)
{
	_takingHit = state;
}

bool Player::isTakingHit()
{
	return _takingHit;
}
