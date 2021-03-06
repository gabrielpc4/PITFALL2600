#include "Player.h"


Player::Player() :
	Player(0, 0)	
{
}

Player::Player(GLint startX, GLint startY) 
	: PlayerSprite(startX,startY)	  
{		
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
	_swinging				= false;
	_holdingVine			= false;
	_standingOnCrocodile	= false;
	_climbingDirection		= NONE;
	_lookingDirection		= RIGHT;
	
}


void Player::jumping(bool state)
{
	_jumping = state;

	// Resets the _down jumping variable
	// (Prevents the bug when you grab the ladder while falling down on a jump, 
	//  and when you want to climb out, the player falls back again into the tunnel)
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
			_swinging = false;

			if (isWalking() == false)	// Prevents the player from stopping after landing of a jump,				
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
	if (isHoldingVine() == false)
	{
		// Not swinging but climbing
		if (isClimbing())
		{
			// Prevents the player from false jumping, when getting off the ladder, when he initially got on the ladder while jumping
			if (isJumping())
			{
				jumping(false);
			}
			climb();
		}
		else
		{
			// Not swinging, not climbing but falling
			if (isFalling())
			{
				if (isJumping())
				{
					jumping(false);
				}
				fall();
			}

			// Not swinging, not climbing but walking or jumping			
			if (isWalking() || isJumping())
			{
				if (isJumping())
				{
					jump();
				}
				// Not swinging, not climbing and not jumping
				else
				{
					// Not swinging, not climbing, not jumping and not falling
					if (isFalling() == false)
					{
						// Changes the walking speed of the player
						if (_lookingDirection == RIGHT)
						{
							setSpeedX(+PLAYER_SPEED);
						}
						else
						{
							setSpeedX(-PLAYER_SPEED);
						}
					}
					// Not swinging, not climbing, not jumping but falling
					else
					{
						// Makes the player not be able to move, if it's falling
						setSpeedX(0);
					}
				}
			}
			// Not swinging, not climbing, not walking and not jumping
			else 
			{
				// Makes the player stop moving, if the user releases the arrow key
				setSpeedX(0);
			}
		}

		/*********** MOVES THE PLAYER ***********/
		if (this->isDead() == false || isFalling())	// Prevents the animation to change when the player is dead, 			
		{											// but allows him to fall, in the case the player falls into the pit
			AnimatedObject::move();
		}		
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

	// Teleports the player to a position above the ground ( prevents player stuck)
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
	setX(vine->end().x() - 12);	
	setY(vine->end().y() - this->height() - 8);
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
	setSpeedX(0);
	setSpeedY(0);	
	setX(39);
	setY(206);
	_lookingDirection = RIGHT;
	_floor			  = 140;
	_framesDead		  = 0;
	_jumping		  = true;	
	_down			  = true;
	_dead			  = false;	
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

void Player::holdVine(bool state)
{
	_holdingVine = state;

	if (state == true)
	{
		_swinging = true;
	}

	// Makes the player, when he releases the vine, be able to jump forwards
	else
	{
		if (this->x() > (WORLD_WINDOW_WIDTH / 2.0))
		{			
			look(RIGHT);
			setSpeedX(+PLAYER_SPEED);
		}
		else
		{
			look(LEFT);
			setSpeedX(-PLAYER_SPEED);
		}

		// Makes the player jump, when releasing the vine
		jumping(true);
	}	
}

bool Player::isSwinging()
{
	return _swinging;
}

bool Player::isHoldingVine()
{
	return _holdingVine;
}

void Player::incrementFramesDead()
{
	_framesDead++;
}

bool Player::isStandingOnCrocodile()
{
	return _standingOnCrocodile;
}
void Player::standOnCrocodile(bool state)
{
	_standingOnCrocodile = state;
}

void Player::setLives(int number)
{
	_lives = number;
}