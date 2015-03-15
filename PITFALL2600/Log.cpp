#include "Log.h"


Log::Log()
	: Log(442,128, false)
{
}


Log::Log(GLint startX, GLint startY, bool rolling)
	: LogSprite(startX, startY)
{
	this->rolling = rolling;

}


void Log::draw()
{


	if (isRolling())
	{
		//LogSprite::animate();		
	}

	LogSprite::draw();
}

void Log::roll()
{
	if (this->rightX() > 0)
	{
		*(this) += Point(-PLAYER_SPEED, 0);
	}		
}

bool Log::isRolling()
{
	return rolling;
}
