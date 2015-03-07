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
}

void PitfallGame::handleKeyboardInput(unsigned char c)
{
	if (c == SPACE_BAR)
	{	
		player->jump();
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

}



