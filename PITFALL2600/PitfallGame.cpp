#include "PitfallGame.h"

PitfallGame::PitfallGame()
{
	log.clear();
	scenarioNumber = 0;
	score = 2000;
	world = new World();
	player = new Player(39, 140);
	world->buildScenario(scenarioNumber);
	spawnEnemies();
}

void PitfallGame::run()
{
	moveAll();
	checkBoundaries();
	physics();
	checkCollisionsWithEnemies();

	if (player->isTakingHit() && score > 0)
	{
		score--;
	}
}

void PitfallGame::spawnEnemies()
{
	switch (scenarioNumber)
	{
	case(0) :
	{
		log.push_back(Log(422, 128, false));
	}break;
	case (1) :
	{
		log.push_back(Log(417, 128, true));
		log.push_back(Log(475, 128, true));
	}break;
	default:
		break;
	}
}

void PitfallGame::handleKeyboardInput(int key, int keyState)
{
	if (key == GLUT_KEY_RIGHT)
	{
		if (player->isClimbing() == false) // Prevents the player sprite from changing the animation if the right key is pressed
		{
			if (keyState == DOWN)
			{
				if (player->isJumping() == false 
					&& player->isFalling() == false)	// Prevents the player sprite from changing direction while jumping
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
			if (isAbleToClimbOut(player))
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
			if (isAbleToClimbOut(player))
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
					if (checkCollisionX(player, *world->stairs) && (isAbleToClimbOut(player) == false))
					{
						centerOnStair(player);
						player->walking(false);
						player->climbing(true);
						player->climb(UP);
					}
				}

				// Prevents the user from jumping while climbing or falling
				if ((player->isClimbing() == false) && (player->isFalling() == false))
				{
					player->jumping(true);
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
		if (player->isClimbing() && isAbleToClimbOut(player))
		{
			player->look(RIGHT);
			player->climbOut(RIGHT);
		}
	}

}

void PitfallGame::drawAll()
{
	world->draw(scenarioNumber);
	player->draw();

	if (world->stairs != NULL)
	{		
		world->stairs->drawCover();
	}

	for (unsigned i = 0; i < world->tunnelHole.size(); i++)
	{
		world->tunnelHole.at(i).drawCover();
	}


	for (unsigned i = 0; i < log.size(); i++)
	{
		log.at(i).draw();
	}


	string label = "Score: ";
	printText(label + std::to_string(score), Point(10, 360));

	label = "Lives: ";
	for (int i = 0; i < player->livesLeft(); i++)
	{
		label += "l";
	}
	printText(label, Point(10, 340));
}

void PitfallGame::moveAll()
{
	player->move();
	for (unsigned i = 0; i < log.size(); i++)
	{
		if (log.at(i).isRolling())
		{
			log.at(i).roll();
		}
	}
}

void PitfallGame::physics()
{
	if (world->stairs != NULL)
	{
		// Makes the player fall
		if (willFall(player, world->stairs->hole) && (player->isClimbing() == false))
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
				if (isAbleToClimbOut(player))
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
			if (world->brickWall->x() != 0) // Prevents the collision check bug when the brickwall's sprite is being 		
			{										// created and still is at the origin and was not moved to the right position yet
				// If the player is colliding with the brick wall
				if (checkCollisionX(player, *world->brickWall))
				{
					
					// if the player is at the left side of the brick wall
					if (relativePosition(player, world->brickWall) == RIGHT)
					{
						// Moves the player away from the brick wall
						player->setX(world->brickWall->x() - PLAYER_ANIMATION_0_WIDTH);
					}
					else // if the player is at the right side of the brick wall
					{
					
						if (player->isLooking(LEFT)) // Prevents the player getting stuck when changing the look direction
						{
							// Move the player away from the brick wall
							player->setX(world->brickWall->rightX() + PLAYER_ANIMATION_0_LOOKING_LEFT_COMPENSATION);
						}
						else
						{
							player->setX(world->brickWall->rightX());
						}						
					}
				}
			}
		}
	}

	// Makes the player fall if is in contact with a ground  hole		
	for (unsigned i = 0; i < world->tunnelHole.size(); i++)
	{
		if (willFall(player, &(world->tunnelHole.at(i))))
		{
			if (player->isJumping() == false)
			{
				player->floor = world->tunnelFloor.topY();
				player->falling(true);
			}
		}
	}	
}

bool PitfallGame::isAbleToClimbOut(Player* player)
{
	return (player->topY() > (world->stairs->hole->y() + 10));
}

void PitfallGame::centerOnStair(Player* player)
{
	player->setX(world->stairs->x() + 5);
}


bool  PitfallGame::willFall(Player* player, Sprite* hole)
{
	if (player->isUndeground() == false)  // Can only fall if it's on the top floor
	{
		if (player->isLooking(RIGHT))
		{
			if (player->x() >= hole->x() && player->x() + PLAYER_ANIMATION_0_WIDTH <= hole->rightX())
			{
				return true;
			}
		}
		else
		{
			if (player->x() + PLAYER_ANIMATION_0_LOOKING_LEFT_COMPENSATION + 1 < hole->rightX()
				&& player->x() >= hole->x())
			{
				return true;
			}
		}
		return false;
	}
	return false;
}



void PitfallGame::checkBoundaries()
{	
	for (unsigned i = 0; i < log.size(); i++)
	{		
		if (log.at(i).rightX() <= 0)
		{
			log.at(i).setX(WORLD_WINDOW_WIDTH);
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
		world->buildScenario(scenarioNumber);
		spawnEnemies();
	}
}



int PitfallGame::relativePosition(Player* player, Sprite* object)
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
	player->takeHit(false);
	for (unsigned i = 0; i < log.size(); i++)
	{
		if (checkCollisionX(player, log.at(i)) && checkCollisionY(player, (Sprite)log.at(i)))
		{
			player->takeHit(true);
		}
	}
}




bool PitfallGame::checkCollisionX(Player* player, Sprite& object)
{
	if (player->isLooking(RIGHT))
	{
		if (player->x() + PLAYER_ANIMATION_0_WIDTH > object.x() && player->x() < object.rightX())
		{
			return true;
		}
	}
	else
	{
		if (player->x() - PLAYER_ANIMATION_0_LOOKING_LEFT_COMPENSATION < object.rightX() && player->x() + PLAYER_ANIMATION_0_WIDTH > object.x())
		{
			return true;
		}
	}
	return false;
}

bool PitfallGame::checkCollisionY(Player* player, Sprite& object)
{
	if (player->y() <= object.topY() && player->topY() >= object.y())
	{
		return true;
	}
	return false;
}

bool PitfallGame::isOutOfBoundaries(Sprite* object)
{
	if (object->x() < 0 || object->rightX() >= WORLD_WINDOW_WIDTH)
	{
		return true;
	}
	return false;
}


void  PitfallGame::printText(string text, Point p)
{
	glColor3f(1.0, 1.0, 1.0);
	char *c;
	float scale = 0.1;
	float orientation = 0;
	glPushMatrix();
	glTranslatef(p.x(), p.y(), 0); // glTranslatef (dx, dy, dz)
	glScalef(scale, scale, scale);	// glScalef (sx, sy, sz)
	glRotatef(orientation, 0, 0, 1);	// glRotatef (angle, x, y, z)
	for (c = (char*)text.c_str(); *c; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
	}
	glPopMatrix();
}


void PitfallGame::deleteWorld()
{
	log.clear();

	if (world->stairs != NULL)
	{
		delete world->stairs->hole;
		world->stairs->hole = NULL;
	}

	delete world->stairs;
	world->stairs = NULL;

	delete world->brickWall;
	world->brickWall = NULL;

	
	world->tunnelHole.clear();
}