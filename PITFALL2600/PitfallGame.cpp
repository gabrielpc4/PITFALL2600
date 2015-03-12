#include "PitfallGame.h"
#include <iostream>
using namespace std;
void PitfallGame::handleKeyboardInput(int key, int keyState)
{
	if (key == GLUT_KEY_RIGHT)
	{
		if (player->isClimbing() == false)
		{
			if (keyState == DOWN)
			{
				player->look(RIGHT);
				player->walking(true);
			}
			else
			{
				player->walking(false);
			}
		}
		else
		{
			if (player->isAbleToClimbOut(world->stairs->hole))
			{
				player->look(RIGHT);
				player->climbOut(RIGHT);
			}			
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (player->isClimbing() == false)
		{
			if (keyState == DOWN)
			{

				player->look(LEFT);
				player->walking(true);
			}
			else
			{
				player->walking(false);
			}
		}
		else
		{
			if (player->isAbleToClimbOut(world->stairs->hole))
			{
				player->look(LEFT);
				player->climbOut(LEFT);
			}
		}
	}
	if (player->isFalling() == false)
	{
		if (key == GLUT_KEY_UP)
		{				
			if (keyState == DOWN)
			{
				if (world->stairs != NULL)
				{					
					if (checkColisionX(player, world->stairs) && (player->isAbleToClimbOut(world->stairs->hole) == false))
					{
						player->centerOnStair(world->stairs);
						player->walking(false);
						player->climbing(true);
						player->climb(UP);
					}
				}
			}
			else
			{
				player->stopClimbing();
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
				player->stopClimbing();
			}
		}
	}
}

void PitfallGame::handleKeyboardInput(unsigned char c)
{
	if (c == SPACE_BAR)
	{	
		if ((player->isClimbing() == false) && (player->isFalling() == false))
		{
			player->jumping(true);
		}
		if (player->isClimbing() && player->isAbleToClimbOut(world->stairs->hole))
		{
			player->climbOut(RIGHT);
		}
	}
}

PitfallGame::PitfallGame()
{
	world = new World(0);
	player = new Player(39, 140);	
	switch (world->getScenarioNumber())
	{
	case(0) :
	{
		log = new Log(422, GROUND_Y, false);
	}
	default:
		break;
	}
}


void PitfallGame::drawAll()
{		
	world->draw();
	player->draw();

	switch (world->getScenarioNumber())
	{
	case (0) :
	{		
		log->draw();
		world->drawStairHoleCover();
	}break;
	default:break;
	}	
}

void PitfallGame::moveAll()
{	
	player->move();

	if (world->stairs != NULL)
	{	
		if (player->willFall(world->stairs->hole) && (player->isClimbing() == false) && (player->isJumping() == false))
		{						
			player->floor = world->tunnelFloor.topY();
			player->falling(true);

		}
		if (player->isClimbing())
		{
			if (player->climbingDirection() == DOWN)
			{
				if (player->y() - CLIMBING_SPEED < world->tunnelFloor.topY())
				{
					player->climbing(false);
					player->setSpeedY(0);					
					player->setY(world->tunnelFloor.topY());
				}
			}
			else if (player->climbingDirection() == UP)
			{
				if (player->isAbleToClimbOut(world->stairs->hole))
				{				
					player->stopClimbing();					
				}
			}
		}
	}	
	if (world->brickWall != NULL)
	{
		if (player->isUndeground())
		{
			if (checkColisionX(player,world->brickWall))
			{
				if (player->rightX() < world->brickWall->rightX())
				{
					player->setX(world->brickWall->x() - player->width());
				}
				else
				{
					player->setX(world->brickWall->rightX());
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



