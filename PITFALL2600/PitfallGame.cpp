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
					if (checkCollisionX(player, world->stairs) && (player->isAbleToClimbOut(world->stairs->hole) == false))
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
		log = new Log(422, 128, false);
	}
	default:
		break;
	}
}


void PitfallGame::drawAll()
{		
	world->draw();
	player->draw();
	
	if (world->stairs != NULL)
	{
		world->drawStairHoleCover();
	}

	switch (world->getScenarioNumber())
	{
	case (0) :
	{		
		log->draw();			
	}break;
	default:break;
	}	


	
}

void PitfallGame::moveAll()
{	
	player->move();
	if (log != NULL)
	{
		if (log->isRolling())
		{
			log->roll();
		}
	}	
}

void PitfallGame::physics()
{
	if (world->stairs != NULL)
	{
		// Makes the player fall
		if (player->willFall(world->stairs->hole) && (player->isClimbing() == false) && (player->isJumping() == false))
		{
			player->floor = world->tunnelFloor.topY();
			player->falling(true);
		}

		// Makes the player be able to climb
		if (player->isClimbing())
		{
			if (player->climbingDirection() == DOWN)
			{
				// If the player has climbed all the way down the stairs
				if (player->y() - CLIMBING_SPEED < world->tunnelFloor.topY())
				{
					// Prevent him from going below the floor
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
			if (checkCollisionX(player, world->brickWall))
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

	if (log != NULL)
	{		
		if (checkCollisionX(player, log) && checkCollisionY(player, log))
		{
			player->takeHit(true);
		}
		else
		{
			player->takeHit(false);
		}
	}
}

bool PitfallGame::checkCollisionX(Player* player, GameObject* object)
{	
	if (player->sprite->rightX() >= object->sprite->x() && player->sprite->x() <= object->sprite->rightX())
	{		
		return true;
	}
	return false;
}


bool PitfallGame::checkCollisionY(Player* player, GameObject* object)
{
	
	if (player->sprite->y() <= object->sprite->topY() && player->sprite->topY() >= object->sprite->y())
	{
		return true;
	}
	return false;
}



