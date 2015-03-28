#include "Log.h"


Log::Log()
	: Log(LOG_POSITION_2, false)
{
}

Log::Log(int LOG_POSITION, bool rolling)
	: Log(LOG_POSITION, 128, rolling)
{

}


Log::Log(GLint startX, GLint startY, bool rolling)
	: LogSprite(startX, startY)
{
	this->rolling = rolling;

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
