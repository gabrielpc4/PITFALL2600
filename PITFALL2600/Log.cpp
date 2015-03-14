#include "Log.h"


Log::Log()
	: Log(442,128, false)
{
}


Log::Log(GLint startX, GLint startY, bool rolling)
	: Enemy(startX, startY)
{
	this->rolling = rolling;
	sprite = new LogSprite(startX, startY);		
}

void Log::animate()
{
	framesRolling++;

	if (framesRolling % ANIMATION_REFRESH_INTERVAL == 0)
	{
		//sprite->mirrorX();

		if (framesRolling >= INT_MAX)
		{
			framesRolling = 0;
		}
	}
}

void Log::draw()
{
	
	if (isRolling())
	{
		animate();
		sprite->drawSprite(this->x(), this->y());
	}
	else
	{
		sprite->drawSprite(this->x(), this->y());
	}
}

void Log::roll()
{
	if (this->sprite->rightX() > 0)
	{
		*(this) += Point(-PLAYER_SPEED, 0);
	}		
}

bool Log::isRolling()
{
	return rolling;
}
