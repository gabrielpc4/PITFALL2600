#include "Player.h"


Player::Player() :
	Player(0, 0)
{
}

Player::Player(GLint startX, GLint startY) 
	: PlayerSprite(startX,startY),
	playerSpeed(0,0)
{		
	animationFrame			= 0;
	_lives					= 3;
	_framesDead				= 0;
	_floor					= startY;
	_down					= false;
	_jumping				= false;
	_takingHit				= false;
	_falling				= false;
	_walking				= false;
	_climbing				= false;
	_dead					= false;
	_climbingDirection		= NONE;
	_lookingDirection		= RIGHT;
	
}

void Player::draw()
{
	// Waking sprite
	if (isClimbing() == false)
	{
		if (isWalking())
		{
			// Animate the walking
			animate(animationFrame, 1, 5);
		}
		else
		{
			animationFrame = 0;
		}		
	}
	
	// Falling sprite
	if (isFalling() && (isJumping() == false) && (isClimbing() == false))
	{
		animationFrame = 0;
	}

	// Jumping, and taking hit sprite
	if ((isJumping()) 
		|| (isTakingHit() && isFalling() == false) && (isClimbing() == false) 
		|| (isFalling()) && (this->y() + (this->height() / 2.0) < 96)) // Makes the player open the legs, when there's room for it, when falling
	{
		animationFrame = 5;
	}

	// Climbing sprite
	if (isClimbing())
	{
		// Switches between the climbing animations
		animate(animationFrame, 0, 1);
	}

	// UPDATES THE SPRITE (ANIMATION)
	if (this->isDead() == false || isFalling()) // Prevents the animation to change when the player is dead, 												
	{											// but allows to change to the falling sprite, for the case the player falls into the pit
		// Rebuilds the sprite, with the new animation sprite
		PlayerSprite::Sprite::clear();
		PlayerSprite::buildSprite(animationFrame);
	}	

	PlayerSprite::draw();
}

void Player::jumping(bool state)
{
	_jumping = state;

	// Resets the _down jumping variable
	// (Prevents the bug when you grab the stairs while falling down on a jump, 
	//  and when you want to clim out, the player falls back again into the tunnel)
	if (state == false)
	{
		_down = false;
	}
}

void Player::jump()
{

	int currentJumpHeight = (this->topY() - (_floor + PLAYER_ANIMATION_0_HEIGHT));

	if (currentJumpHeight < JUMP_MAX_HEIGHT && _down == false)
	{
		setSpeedY(JUMP_SPEED);
	}
	else
	{
		_down = true;
	}
	// Makes the player go back to the ground (gravity)
	if (_down)
	{
		// If the player has not reached the floor
		if (this->y() - 10 > _floor)
		{
			// Makes the player go down
			setSpeedY(-JUMP_SPEED);
		}
		else
		{
			setY(_floor);	// Forces the sprite to be in the right height
			setSpeedY(0);	// Stops the vertical movement

			// Set flags back to false
			_falling = false;
			_jumping = false;
			_down = false;
			
			if (isWalking() == false)	// Prevents the player from stoping after landing of a jump,				
			{							// and has not released the arrow key

				setSpeedX(0);
			}
		}				
	}
}

void Player::fall()
{	
	animationFrame = 0;
	setSpeedX(0);
	if (this->y() > _floor)
	{
		if ((this->y() - _floor) > FALLING_SPEED)
		{
			setSpeedY(-FALLING_SPEED);
		}
		else
		{
			setY(_floor);
			setSpeedY(0);
			_falling = false;
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
			if (_lookingDirection == RIGHT)
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
	if (this->isDead() == false || isFalling())	// Prevents the animation to change when the player is dead, 			
	{											// but allows him to fall, in the case the player falls into the pit
		*this += playerSpeed;
	}

	if (this->isDead())
	{
		_framesDead++;
	}	
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

void Player::climbOut(int direction)
{
	// Moves the floor to the top floor again
	this->_floor = GROUND_Y;

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

void Player::swing(Vine* vine)
{
	/*setX(vine->end().x());
	setY(vine->end().y());*/
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
	_lookingDirection = DIRECTION;
}

int Player::isLooking()
{
	return _lookingDirection;
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


bool Player::isUndeground()
{
	return (this->y() < 136);
}

int Player::livesLeft()
{
	return _lives;
}

void Player::takeHit(bool state)
{
	_takingHit = state;
}

bool Player::isTakingHit()
{
	return _takingHit;
}

void Player::die()
{
	_dead = true;	
	_walking = false;
	if (_framesDead == 0)
	{
		_lives--;
	}	
}
void Player::respawn()
{
	_dead = false;
	_lookingDirection = RIGHT;
	_floor = 140;
	_framesDead = 0;
	_jumping = true;
	_down = true;
	setX(39);
	setY(206);
}

bool Player::isDead()
{
	return _dead;
}

void Player::resetLives()
{
	this->_lives = 3;
}

void Player::setFloor(float y)
{
	this->_floor = y;
}

long Player::framesDead()
{
	return _framesDead;
}

void Player::swinging(bool state)
{
	_swinging = state;
}

