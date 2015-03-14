#include "PitfallGame.h"

void PitfallGame::handleKeyboardInput(int key, int keyState)
{
	if (key == GLUT_KEY_RIGHT)
	{
		if (player->isClimbing() == false) // Prevents the player sprite from changing the animation if the right key is pressed
		{
			if (keyState == DOWN)
			{
				if (player->isJumping() == false && player->isFalling() == false)	// Prevents the player sprite from changing direction while jumping
				{
					player->look(RIGHT);
					player->walking(true);
				}				
			}			
			else // If the user releases the key
			{
				player->walking(false);
			}
		}
		else // If the player is climbing
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
		if (player->isClimbing() == false) // Prevents the player sprite from changing the animation if the left key is pressed
		{
			if (keyState == DOWN)
			{
				if (player->isJumping() == false && player->isFalling() == false) // Prevents the player sprite from changing direction while jumping
				{
					player->look(LEFT);
					player->walking(true);
				}
			}
			
			else // If the user releases the key
			{
				player->walking(false);
			}
		}
		else // If the player is climbing
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
					// If the player is in contact with the stairs and not about to climb out
					if (checkCollisionX(player, world->stairs) && (player->isAbleToClimbOut(world->stairs->hole) == false))
					{
						player->centerOnStair(world->stairs);
						player->walking(false);
						player->climbing(true);
						player->climb(UP);
					}
				}
			}
			else // If the user releases the key
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
			else // If the user releases the key
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
		// Prevents the user from jumping while climbing or falling
		if ((player->isClimbing() == false) && (player->isFalling() == false))
		{
			player->jumping(true);
		}
		// Allows the player to climb out of the tunnel, when he reaches the top of the stairs and press the SPACE_BAR
		if (player->isClimbing() && player->isAbleToClimbOut(world->stairs->hole))
		{
			player->climbOut(RIGHT);
		}
	}
}

PitfallGame::PitfallGame()
{	
	log = NULL;
	scenarioNumber = 1;
	world = new World(scenarioNumber);
	player = new Player(39,140);		
	spawnEnemies();
}

void PitfallGame::run()
{
	moveAll();
	physics();
	checkCollisionsWithEnemies();
}

void PitfallGame::drawAll()
{
	world->draw(scenarioNumber);
	player->draw();

	if (world->stairs != NULL)
	{		
		world->stairs->drawCover();
	}

	if (world->groundHole.size() != 0)
	{
		for (int i = 0; i < 2; i++)
		{
			world->groundHole.at(i).drawCover();
		}
		
	}


	switch (scenarioNumber)
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
	checkBoundaries();
}

void PitfallGame::physics()
{
	if (world->stairs != NULL)
	{
		// Makes the player fall
		if (player->willFall(world->stairs->hole) && (player->isClimbing() == false))
		{
			if (player->isJumping() == false)
			{
				player->floor = world->tunnelFloor.topY();
				player->falling(true);
			}
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
	// Collision with the brick wall
	if (world->brickWall != NULL)
	{	
		if (player->isUndeground())
		{
			if (world->brickWall->sprite->x() != 0) // Prevents the collision check bug when the brickwall's sprite is being 		
			{										// created and still is at the origin and was not moved to the right position yet
				// If the player is colliding with the brick wall
				if (checkCollisionX(player, world->brickWall))
				{
					// if the player is at the left side of the brick wall
					if (relativePosition(player, world->brickWall) == RIGHT)
					{
						// Moves the player away from the brick wall
						player->setX(world->brickWall->x() - 17);
					}
					else // if the player is at the right side of the brick wall
					{
						// Move the player away from the brick wall
						player->setX(world->brickWall->rightX());
					}
				}
			}
		}
	}


	// Makes the player fall if is in contact with a ground  hole
	if (world->groundHole.size() != 0) // if there is a ground hole
	{
		if (player->y() >= world->ground.y())
		{
			for (int i = 0; i < 2; i++)
			{				
				if (player->willFall(&(world->groundHole.at(i))))
				{
					if (player->isJumping() == false)
					{
						player->floor = world->tunnelFloor.topY();
						player->falling(true);
					}								
				}
			}
		}		
	}
}

void PitfallGame::checkBoundaries()
{
	if (log != NULL)
	{
		if (log->rightX() <= 0)
		{
			log->setX(WORLD_WINDOW_WIDTH);
		}
	}

	if (isOutOfBoundaries(player))
	{
		deleteWorld();

		if (player->rightX() >= WORLD_WINDOW_WIDTH)
		{
			scenarioNumber++;
			player->setX(player->width());
		}
		if (player->x() < 0)
		{
			scenarioNumber--;
			player->setX(WORLD_WINDOW_WIDTH - 32);
		}
		world = new World(scenarioNumber);
		spawnEnemies();
	}

}

void PitfallGame::spawnEnemies()
{
	switch (scenarioNumber)
	{
	case(0) :
	{
		log = new Log(422, 128, false);
	}
	case (1) :
	{

	}break;
	default:
		break;
	}
}

int PitfallGame::relativePosition(Player* player, GameObject* object)
{
	int object_center_x = (object->x() + (object->width() / 2.0));
	if (player->x() < object_center_x)
	{
		return RIGHT;
	}
	else if (player->rightX() > object_center_x)
	{
		return LEFT;
	}
	return NONE;
}

void PitfallGame::checkCollisionsWithEnemies()
{
	// Collision with the Enemy log
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
	if (player->isLooking(RIGHT))
	{
		if (player->x() + 11 > object->x() && player->x() < object->rightX())
		{
			return true;
		}
	}
	else
	{
		if (player->x() + 4 < object->rightX() && player->x() + 11 > object->x())
		{
			return true;
		}
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

bool PitfallGame::isOutOfBoundaries(GameObject* object)
{
	if (object->x() < 0 || object->rightX() >= WORLD_WINDOW_WIDTH)
	{
		return true;
	}
	return false;
}

void PitfallGame::deleteWorld()
{
	delete log;
	log = NULL;

	if (world->stairs != NULL)
	{
		delete world->stairs->hole;
		world->stairs->hole = NULL;
	}

	delete world->stairs;
	world->stairs = NULL;

	delete world->brickWall;
	world->brickWall = NULL;

	if (world->groundHole.size() != 0)
	{
		world->groundHole.empty();
	}

	delete world;
}