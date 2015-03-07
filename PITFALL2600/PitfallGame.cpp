#include "PitfallGame.h"
#include <iostream>
using namespace std;
void PitfallGame::handleKeyboardInput(int key, int keyState)
{
	if (key == GLUT_KEY_RIGHT)
	{
		if (keyState == DOWN)
		{
			if (player->isLooking(LEFT))
			{
				player->look(RIGHT);
			}
			player->moving(true);
		}
		else
		{
			player->moving(false);
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (keyState == DOWN)
		{
			if (player->isLooking(RIGHT))
			{
				player->look(LEFT);
			}
			player->moving(true);
		}
		else
		{
			player->moving(false);
		}
	}
	if (!player->isFalling())
	{
		if (key == GLUT_KEY_UP)
		{
			if (keyState == DOWN)
			{
				if (world->stairs != NULL)
				{
					if (checkColisionX(player, world->stairs) && player->y() + CLIMBING_SPEED <= world->stairs->hole->y())
					{
						player->climbing(true);
						player->climb(UP);
					}
				}
			}
			else
			{
				player->climb(NONE);
			}

		}
		if (key == GLUT_KEY_DOWN)
		{
			if (keyState == DOWN)
			{
				if (player->isClimbing())
				{
					player->climb(DOWN);
				}
			}
			else
			{
				player->climb(NONE);
			}
		}
	}
}

void PitfallGame::handleKeyboardInput(unsigned char c)
{
	if (c == SPACE_BAR)
	{	
		player->jumping(true);
	}
}

PitfallGame::PitfallGame()
{
	world = new World(0);
	player = new Player(39, 140);	
}


void PitfallGame::drawAll()
{		
	world->draw();
	player->draw();

	if (world->stairs != NULL)
	{
		world->drawStairHoleCover();
	}
}

void PitfallGame::moveAll()
{	
	player->move();

	if (world->stairs != NULL)
	{	
		if (player->willFall(world->stairs->hole) && !player->isClimbing() && !player->isJumping())
		{		
			if (player->y() >= world->ground.y())
			{
				if (!player->isJumping())
				{
					player->ground_y = world->tunnelFloor.topY();
					player->falling(true);
				}
			}
		}
		if (player->isClimbing())
		{
			if (player->climbingDirection() == DOWN)
			{
				if (player->y() - CLIMBING_SPEED <= world->tunnelFloor.topY())
				{
					player->climbing(false);
					player->setSpeedY(0);
					player->setY(world->tunnelFloor.topY());
				}
			}
			else if (player->climbingDirection() == UP)
			{
				if (player->y() + CLIMBING_SPEED >= world->stairs->hole->y())
				{										
					player->setY(140);
					player->setSpeedX(+PLAYER_SPEED);
					player->jumping(true);	
					player->climbing(false);
				}
			}
		}
	}	
}

bool PitfallGame::checkColisionX(Player* player, GameObject* object)
{	
	if (player->rightX() >= object->x() && player->x() <= object->rightX())
	{		
		return true;
	}
	return false;
}


bool PitfallGame::checkColisionY(Player* player, GameObject* object)
{
	if (player->y() <= object->topY() && player->topY() >= object->y())
	{
		return true;
	}
	return false;
}



