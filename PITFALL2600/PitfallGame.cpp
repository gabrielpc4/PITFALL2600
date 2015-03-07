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
	if (key == GLUT_KEY_UP)
	{

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
}

void PitfallGame::moveAll()
{	
	player->move();

	if (world->stairs != NULL)
	{
		if (checkColisionX(player, world->stairs))
		{
			if (player->ground_y >= world->ground.y())
			{
				if (!player->isJumping())
				{
					player->ground_y = world->tunnelFloor.topY();
					player->falling(true);
				}
			}
			else
			{
				/*if ((player->topY() / 2.0) < world->stairs->hole->y())
				{
					player->climbing(true);
				}
				else
				{
					player->jump();
					player->climbing(false);
				}*/
			}
		}
	}
	
}

bool PitfallGame::checkColisionX(Player* player, GameObject* object)
{
	int compareX;
	if (player->isLooking(RIGHT))
	{
		compareX = player->x();
	}
	else
	{
		compareX = player->rightX();
	}
	if (compareX >= world->stairs->x() && compareX <= world->stairs->rightX())
	{
		return true;
	}
	return false;
}



