#include "PitfallGame.h"

PitfallGame::PitfallGame()
{
	scenarioNumber		= 0;	
	DEBUG_MODE			= false;
	GOD_MODE			= false;
	score				= 2000;
	world				= new World();
	player				= new Player(39, 140);
	scorpion			= NULL;
	paused				= false;
	allowCrocodiles		= false;
	world->buildScenario(scenarioNumber);
	spawnEnemies();
	crocodiles.push_back(Crocodile(187, 136));
	crocodiles.push_back(Crocodile(245, 136));
	crocodiles.push_back(Crocodile(303, 136));
}

void PitfallGame::spawnEnemies()
{
	switch (scenarioNumber)
	{
		case (-2) :
		{
			nScorpions  = 1;
			nLogs		= 2;
			movingLogs	= true;
			nCrocodiles = 0;
		}break;
		case (-1) :
		{
			nScorpions  = 1;
			nLogs		= 0;
			movingLogs	= false;
			nCrocodiles = 3;
		}break;
		case(0) :
		{
			nScorpions  = 0;
			nLogs	    = 1;
			movingLogs	= false;
			nCrocodiles = 0;
		}break;
		case (1) :
		{
			nScorpions	= 0;
			nLogs		= 2;
			movingLogs	= true;
			nCrocodiles = 0;
		}break;
		case (2) :
		{
			nScorpions  = 1;
			nLogs	    = 2;
			movingLogs	= true;
			nCrocodiles = 0;
		}break;
		case (3) :
		{
			nScorpions	= 1;
			nLogs		= 0;
			movingLogs	= false;
			nCrocodiles = 3;
		}break;
		case(4) :
		{
			nScorpions  = 0;
			nLogs	    = 3;
			movingLogs	= true;
			nCrocodiles = 0;
		}break;
		default:
		{
			nScorpions	= 0;
			nLogs		= 0;
			movingLogs	= false;
			nCrocodiles = 0;
		}break;		
	}

	switch (nLogs)
	{
		case (1) :
		{
			logs.push_back(Log(LOG_POSITION_2, movingLogs));
		}break;
		case(2) :
		{
			logs.push_back(Log(LOG_POSITION_2, movingLogs));
			logs.push_back(Log(LOG_POSITION_3, movingLogs));
		}break;
		case(3):
		{
			logs.push_back(Log(LOG_POSITION_1, movingLogs));
			logs.push_back(Log(LOG_POSITION_2, movingLogs));
			logs.push_back(Log(LOG_POSITION_3, movingLogs));
		}break;
		default:
		{

		}break;
	}

	if (nScorpions != 0)
	{
		scorpion = new Scorpion();
	}

	if (nCrocodiles != 0)
	{
		allowCrocodiles = true;
	}
}

void PitfallGame::run()
{
	if (player->isDead() && player->isFalling() == false)
	{
		paused = true;
	}

	if (isPaused() == false)
	{	
		moveAll();
		checkBoundaries();
		physics();
		checkCollisionsWithEnemies();

		if (world->allowsVines())
		{
			if ((player->isSwinging() == false) && player->isJumping() && canGrabVine(player))
			{
				player->holdVine(true);
			}
			if (player->isHoldingVine())
			{
				player->swing(world->vine);
			}
		}

		if (player->isTakingHit() && player->isDead() == false && score > 0)
		{
			score--;
		}
	}

	if (player->isDead() || player->isDead() && player->isFalling() == false)
	{
		player->incrementFramesDead();

		if (player->framesDead() > RESPAWN_FRAMES && player->livesLeft() > 0)
		{
			player->respawn();
			unFreezeHoles();
			paused = false;			
		}
	}
}



void PitfallGame::drawAll()
{
	world->draw(scenarioNumber);
	player->draw();
	world->drawOverlayers();

	for (unsigned i = 0; i < logs.size(); i++)
	{
		logs.at(i).draw();
	}

	if (allowCrocodiles)
	{
		for (unsigned i = 0; i < crocodiles.size(); i++)
		{
			crocodiles.at(i).draw();
		}
	}
	else
	{
		for (unsigned i = 0; i < crocodiles.size(); i++)
		{
			crocodiles.at(i).animate(1);
		}
	}

	if (scorpion != NULL)
	{
		if (DEBUG_MODE)
		{
			if (scorpion->speed().x() != 0)
			{
				scorpion->animate(1);
			}			
		}
		else
		{
			scorpion->draw();
		}		
	}
	showHUD();

	if (DEBUG_MODE)
	{
		drawCollisionRectangles();
		if (world->allowsVines())
		{
			world->vine->drawCircleTrack();
		}
	}
	
	if ((player->isDead() == false) || (player->isDead()) && player->isFalling()) // Makes the game freeze, when the player dies
	{
		glutSwapBuffers();
	}
	
}

void PitfallGame::showHUD()
{
	string label = "Score: ";
	printText(label + std::to_string(score), Point(10, 360));

	label = "Lives: ";
	printText(label + std::to_string(player->livesLeft()), Point(10, 340));
	
	if (player->isDead() && player->livesLeft() == 0 && player->framesDead() == RESPAWN_FRAMES)
	{		
		printText("Press Space to Restart the Game", Point(10, 5));
		glutSwapBuffers();
	}
	else if (GOD_MODE)
	{		
		printText("God Mode ON", Point(10, 5));
	}
}

void PitfallGame::moveAll()
{
	player->move();

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

	for (unsigned i = 0; i < logs.size(); i++)
	{
		if (logs.at(i).isRolling())
		{
			logs.at(i).roll();
		}
	}

	world->vine->swing();

	if (scorpion != NULL)
	{
		scorpion->move(player->x());
	}
}

void PitfallGame::physics()
{	
	if (world->stairs != NULL)
	{
		// Makes the player fall
		if (willFall(player, world->stairs->exit) && (player->isClimbing() == false))
		{
			if (player->isJumping() == false)
			{				
				player->setFloor(world->tunnelFloor.topY());
				player->falling(true);
			}
		}		
	}
	// Collision with the brick wall
	if (world->brickWall != NULL)
	{	
		if (player->isUndeground())
		{
			if (world->brickWall->x() != 0) // Prevents the collision check bug when the brick wall's sprite is being 		
			{								// created and still is at the origin and was not moved to the right position yet
				// If the player is colliding with the brick wall
				if (areColliding(player, *world->brickWall, BOX_DETECTION))
				{					
					// if the player is at the left side of the brick wall
					if (relativePosition(player, world->brickWall) == RIGHT)
					{
						// Moves the player away from the brick wall
						player->setX(world->brickWall->x() - PLAYER_ANIMATION_0_WIDTH);
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
	for (unsigned i = 0; i < world->tunnelHole.size(); i++)
	{
		if (willFall(player, &(world->tunnelHole.at(i))))
		{
			if (player->isJumping() == false)
			{
				player->setFloor(world->tunnelFloor.topY());
				player->falling(true);
			}
		}
	}	
	// Falling in the Black Hole or in the Water
	
	if (world->allowsBlackHole())
	{
		if (willFall(player, world->blackHole))
		{			
			if (player->isJumping() == false)
			{
				if (GOD_MODE == false)
				{
					freezeHoles();
					player->setFloor(world->tunnelTop.y());
					player->falling(true);
					player->die();
				}
			}
		}
	}

	if (world->allowsWater())
	{
		if (willFall(player, world->water) && player->isStandingOnCrocodile() == false)
		{			
			if (player->isJumping() == false)
			{
				if (GOD_MODE == false)
				{
					freezeHoles();
					player->setFloor(world->tunnelTop.y());
					player->falling(true);
					player->die();
				}
			}
		}
	}
	

}

bool PitfallGame::isAbleToClimbOut(Player* player)
{
	return (player->topY() > (world->stairs->exit->y() + 10));
}

void PitfallGame::centerOnStair(Player* player)
{
	player->setX(world->stairs->x() + 5);
}

bool  PitfallGame::willFall(Player* player, Sprite* hole)
{
	if (hole != NULL)
	{
		if (player->isUndeground() == false)  // Can only fall if it's on the top floor
		{
			if (player->isLooking() == RIGHT)
			{
				if (player->x() >= hole->x() && player->rightX() <= hole->rightX())
				{
					return true;
				}
			}
			else
			{
				if (player->rightX()  < hole->rightX()
					&& player->x() >= hole->x())
				{
					return true;
				}
			}
			return false;
		}
	}	
	return false;
}

void PitfallGame::checkBoundaries()
{	
	for (unsigned i = 0; i < logs.size(); i++)
	{		
		if (logs.at(i).rightX() <= 0)
		{
			logs.at(i).setX(WORLD_WINDOW_WIDTH);
		}
	}

	if (isOutOfBoundaries(player))
	{
		world->deleteWorld();
		deleteEnemies();

		if (player->rightX() >= WORLD_WINDOW_WIDTH)
		{
			scenarioNumber++;
			player->setX(22);
		}
		else
		{
			if (player->x() < 0)
			{
				scenarioNumber--;
				player->setX(WORLD_WINDOW_WIDTH - 32);
			}
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

bool PitfallGame::canGrabVine(Player* player)
{
	return isInside(world->vine->end(), Rect(player->x(), player->y(), player->width(), player->height()));
}


void PitfallGame::checkCollisionsWithEnemies()
{
	// Collision with the Enemy log
	player->takeHit(false);
	for (unsigned i = 0; i < logs.size(); i++)
	{
		if (areColliding(player, (Sprite)logs.at(i), BOX_DETECTION))
		{
			player->takeHit(true);
		}
	}

	player->standOnCrocodile(false);

	if (allowCrocodiles)
	{
		for (unsigned i = 0; i < crocodiles.size(); i++)
		{
			if (areCollidingX(player, &crocodiles[i]))
			{
				player->standOnCrocodile(true);
				player->setFloor(crocodiles[i].topY());
			}
		}
	}
	

	if (scorpion != NULL)
	{
		// If the player is close to the scorpion
		if (areClose(player, scorpion) )
		{			
			// Only then to the pixel by pixel collision detection, because it costs a lot of processing
			if (areColliding(player, (Sprite)(*scorpion), PIXEL_BY_PIXEL_DETECTION))
			{ 
				if (GOD_MODE == false)
				{
					player->die();
				}				
			}
		}					
	}
}

bool PitfallGame::areCollidingX(Player* player, Crocodile* crocodile)
{
	if (player->isUndeground() == false)
	{
		if (player->rightX() > crocodile->x() && player->x() < crocodile->rightX())
		{
			return true;
		}
		return false;
	}	
	return false;
}

bool PitfallGame::areColliding(Player* player, Sprite& object, int detectionType)
{
	if (detectionType == BOX_DETECTION)
	{
		if (player->y() <= object.topY() && player->topY() >= object.y())
		{
			if (player->rightX() > object.x() && player->x() < object.rightX())
			{
				return true;
			}
			return false;				
		}
		return false;
	}
	else
	{		
		for (vector<Polygon>::iterator playerPolygon = player->begin(); playerPolygon != player->end(); playerPolygon++)
		{		
			for (vector<Rect>::iterator playerRect = playerPolygon->begin(); playerRect != playerPolygon->end(); playerRect++)
			{
				for (vector<Polygon>::iterator objectPolygon = object.begin(); objectPolygon != object.end(); objectPolygon++)
				{
					for (vector<Rect>::iterator objectRect = objectPolygon->begin(); objectRect != objectPolygon->end(); objectRect++)
					{
				
						if (isInside(*playerRect, *objectRect))
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}		
	return false;
}

bool PitfallGame::isOutOfBoundaries(Player* player)
{
	if (player->x() <= 0 || player->rightX() >= WORLD_WINDOW_WIDTH)
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
	glTranslatef(p.x(), p.y(), 0); 
	glScalef(scale, scale, scale);
	glRotatef(orientation, 0, 0, 1);	
	for (c = (char*)text.c_str(); *c; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
	}
	glPopMatrix();
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
				if (player->isSwinging())
				{
					player->holdVine(false);
				}
				else // If the player is not swinging
				{
					if (world->stairs != NULL)
					{
						// If the player is in contact with the stairs and not about to climb out
						if (areColliding(player, *world->stairs, BOX_DETECTION) && (isAbleToClimbOut(player) == false))
						{
							centerOnStair(player);
							player->walking(false);
							player->climbing(true);
							player->setAnimationFrame(6);
							player->climb(UP);
						}
					}

					// Prevents the user from jumping while climbing or falling
					if ((player->isClimbing() == false) && (player->isFalling() == false))
					{
						player->jumping(true);
					}
				}				
			}
			else // If the user releases the UP arrow key
			{
				if (player->isClimbing())
				{
					player->stopClimbing();
				}				
			}
		}
		if (key == GLUT_KEY_DOWN)
		{
			if (keyState == DOWN)
			{
				if (player->isSwinging())
				{
					player->holdVine(false);
				}
				else // If the player is not swinging
				{
					if (player->isClimbing())
					{
						player->climb(DOWN);
					}
				}				
			}
			else // If the user releases the DOWN arrow key
			{
				if (player->isClimbing())
				{
					player->stopClimbing();
				}
			}
		}
	}
}

void PitfallGame::handleKeyboardInput(unsigned char c)
{
	if (c == SPACE_BAR)
	{
		// Makes the player release the vine when the space-bar is pressed
		if (player->isSwinging())
		{
			player->holdVine(false);						
		}
		else if (player->isDead() && player->livesLeft() == 0 && player->framesDead() >= RESPAWN_FRAMES)
		{
			PitfallGame::reset();
		}
		else
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
	if (c == 'd' || c == 'D')
	{
		DEBUG_MODE = !DEBUG_MODE;
	}
	if (c == 'g' || c == 'G')
	{
		GOD_MODE = !GOD_MODE;
	}
}

void PitfallGame::deleteEnemies()
{
	logs.clear();
	delete scorpion;
	scorpion = NULL;	
	allowCrocodiles = false;
}

void PitfallGame::reset()
{
	world->deleteWorld();	
	this->deleteEnemies();	
	scenarioNumber = 0;
	score = 2000;

	this->spawnEnemies();
	world->buildScenario(0);

	player->resetLives();
	player->respawn();

	
	player->setY(140);	

	unFreezeHoles();
	paused = false;
}

void PitfallGame::freezeHoles()
{
	if (world->blackHole != NULL)
	{
		world->blackHole->freeze();
	}

	if (world->water != NULL)
	{
		world->water->freeze();
	}
}

void PitfallGame::unFreezeHoles()
{

	if (world->blackHole != NULL)
	{
		if (world->blackHole->canChangeSize())
		{
			world->blackHole->unFreeze();
		}		
	}

	if (world->water != NULL)
	{
		if (world->water->canChangeSize())
		{
			world->water->unFreeze();
		}		
	}
}

bool  PitfallGame::isInside(Point& p, Rect& rect)
{
	if (p.x() < rect.rightX() && p.x() > rect.x() && p.y() > rect.y() && p.y() < rect.topY())
	{
		return true;
	}
	return false;
}

bool PitfallGame::isInside(Rect& rect1, Rect& rect2)
{
	if (rect1.rightX() > rect2.x() + 2		// If the right border of the ball is inside the pin
		&& rect1.x() < rect2.rightX() -2    // If the left border of the ball is inside the pin
		&& rect1.topY() > rect1.y() + 1				// If the top border of the ball is inside the pin
		&& rect1.y() < rect2.topY() - 1)
	{
		return true;
	}
	return false;
}

bool PitfallGame::areClose(Player* player, Scorpion* scorpion)
{
	if (player->rightX() > scorpion->x() - 11 && player->x() < scorpion->rightX() + 11)
	{
		return true;
	}
	return false;
}

bool PitfallGame::isPaused()
{
	return paused;
}

void PitfallGame::drawCollisionRectangles()
{
	drawOutline(player->x(), player->y(), player->width(), player->height());

	if (scorpion != NULL)
	{		
		for (vector<Polygon>::iterator playerPolygon = player->begin(); playerPolygon != player->end(); playerPolygon++)
		{
			for (vector<Rect>::iterator playerRect = playerPolygon->begin(); playerRect != playerPolygon->end(); playerRect++)
			{
				for (vector<Polygon>::iterator objectPolygon = scorpion->begin(); objectPolygon != scorpion->end(); objectPolygon++)
				{
					for (vector<Rect>::iterator objectRect = objectPolygon->begin(); objectRect != objectPolygon->end(); objectRect++)
					{
						drawOutline(objectRect->x(), objectRect->y(), objectRect->width(), objectRect->height());
					}
				}
			}
		}
	}	

	if (allowCrocodiles)
	{
		for (unsigned i = 0; i < crocodiles.size(); i++)
		{
			drawOutline(crocodiles[i].x(), crocodiles[i].y(), crocodiles[i].width(), crocodiles[i].height());
		}
	}

	for (unsigned i = 0; i < logs.size(); i++)
	{
		drawOutline((Sprite)(logs[i]));
	}

	
}

void PitfallGame::drawOutline(Sprite& object)
{
	drawOutline(object.x(), object.y(), object.width(), object.height());
}

void PitfallGame::drawOutline(float x, float y, float width, float height)
{
	glColor3ub(255, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x,y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);	
	glVertex2f(x , y + height);	
	glEnd();
}