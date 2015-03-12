#include "World.h"

World::World() : World(0)
{

}

// Defines the Positions of the basic scenario
World::World(int scenarioNumber)
{	
	this->scenarioNumber = scenarioNumber;
	buildBasicScenario();
	buildScenario(scenarioNumber);		
}

void World::buildBasicScenario()
{
	int start_y = 20;			// Defines where the tunnelFloor initial y value should be
	int end_y = start_y + 12;	// Defines where the tunnelFloor final y value should be

	// Instantiates the tunnelFlor Rectangle variable
	tunnelFloor = Rect(Point(0, start_y), Point(WORLD_WINDOW_WIDTH, end_y));
	tunnelFloor.setColor(Color(148, 91, 0));

	start_y = tunnelFloor.topY();
	end_y = start_y + 126;				// Adds the wall height to the start position, to make the final y value
	tunnelWall = Rect(Point(0, start_y), Point(WORLD_WINDOW_WIDTH, end_y));
	tunnelWall.setColor(Color(67, 0, 0));

	start_y = tunnelWall.topY() - 62;
	end_y = start_y + 30;
	tunnelTop = Rect(Point(0, start_y), Point(WORLD_WINDOW_WIDTH, end_y));
	tunnelTop.setColor(tunnelFloor.color());

	start_y = tunnelTop.topY();
	end_y = start_y + 32;
	ground = Rect(Point(0, start_y), Point(WORLD_WINDOW_WIDTH, end_y));
	ground.setColor(Color(187, 147, 0));

	start_y = ground.topY();
	sky = Rect(Point(0, start_y), Point(WORLD_WINDOW_WIDTH, WORLD_WINDOW_HEIGHT));
	sky.setColor(Color(0, 131, 0));

	int start_x = 101;
	int end_x = start_x + 14;
	start_y = ground.topY();
	end_y = ground.topY() + 104;
	treeTrunk[0] = Rect(Point(start_x, start_y), Point(115, end_y));
	

	start_x = treeTrunk[0].rightX() + 101;
	end_x = start_x + 14;
	treeTrunk[1] = Rect(Point(start_x, start_y), Point(end_x, end_y));

	start_x = treeTrunk[1].rightX() + 58;
	end_x = start_x + 14;
	treeTrunk[2] = Rect(Point(start_x, start_y), Point(end_x, end_y));

	start_x = treeTrunk[2].rightX() + 101;
	end_x = start_x + 14;
	treeTrunk[3] = Rect(Point(start_x, start_y), Point(end_x, end_y));
}


void World::buildScenario(int scenarioNumber)
{
	switch (scenarioNumber)
	{
	case(0) :
	{
		stairs = new Stairs(245, tunnelFloor.topY());	
		brickWall = new BrickWall(461, tunnelFloor.topY());
	}break;
	}
}

/*****************************************************************************************
* Method: draw
* Description: Calls the function drawBasicScenario and loads the first Scenario
******************************************************************************************/
void World::draw()
{
	drawBasicScenario();

	switch (scenarioNumber)
	{
	case(0) :
	{
		stairs->draw();
		brickWall->draw();
	}break;
	}

}

/*****************************************************************************************
* Method Name: drawBasicScenario
* Description: Draws a basic scenario, with the undeground, the ground, trees and leafs
******************************************************************************************/
void World::drawBasicScenario()
{	
	
	// Draws the tunnel
	tunnelFloor.draw();
	tunnelWall.draw();
	tunnelTop.draw();

	// Draws the ground
	ground.draw();

	// Draws the sky behind the trees
	sky.draw();	
	
	for (int i = 0; i < 4; i++)
	{
		treeTrunk[i].setColor(Color(83, 43, 0));
		treeTrunk[i].draw();
		drawTreeBranch(i);
	}

	drawTreeLeafs();
}

/*****************************************************************************************
* Method Name: drawTreeBranch
* Description: Draws the branches corresponding to the tree number
******************************************************************************************/
void World::drawTreeBranch(int treeNum)
{
	Polygon branches(treeTrunk[treeNum].color());
	
	// Defines the branches rectangles, acording with the tree that is being drawn
	switch (treeNum)
	{
		case(0) : 
		{
			// Left branch
			branches.push_back(Rect(Point(0,2), Point(8,4)));
			branches.push_back(Rect(Point(4, 0), Point(11,2)));	

			// Middle
			branches.push_back(Rect(Point(11, 0), Point(18, 8)));

			// Right branch
			branches.push_back(Rect(Point(18, 0), Point(26, 2)));
			branches.push_back(Rect(Point(22, 2), Point(26, 4)));
			branches.push_back(Rect(Point(26, 2), Point(29, 12)));

			// Middle
			branches.push_back(Rect(Point(11, 0), Point(18, 8)));			

			// Right branch
			branches.push_back(Rect(Point(18, 0), Point(26, 2)));
			branches.push_back(Rect(Point(22, 2), Point(26, 4)));
			branches.push_back(Rect(Point(26, 2), Point(29, 12)));		
		}break;
		case(1) : 
		{
			branches.push_back(Rect(Point(0, 0), Point(26, 2)));
			branches.push_back(Rect(Point(20, 2), Point(29, 4)));
		}break;
		case(2) : 
		{
			branches.push_back(Rect(Point(0, 2), Point(7, 4)));
			branches.push_back(Rect(Point(2, 0), Point(25, 2)));
		}break;
		case(3) : 
		{
			// Left branch
			branches.push_back(Rect(Point(0, 2), Point(3, 12)));
			branches.push_back(Rect(Point(3, 2), Point(7, 4)));
			branches.push_back(Rect(Point(3, 0), Point(11, 2)));

			// Middle
			branches.push_back(Rect(Point(11, 0), Point(18, 8)));

			// Right branch
			branches.push_back(Rect(Point(18, 0), Point(25, 2)));
			branches.push_back(Rect(Point(21, 2), Point(29, 4)));			
		}break;
		default:;
	}
	// Centers the branches in the middle of the tree trunk
	branches -= Point((int)(branches.width() / 4.0) - 1, 0);
	branches.drawPolygon(treeTrunk[treeNum].x(), treeTrunk[treeNum].topY());
}

/*****************************************************************************************
* Method Name: drawTreeLeafs
* Description: Draws the three leafs
******************************************************************************************/
void World::drawTreeLeafs()
{
	treeLeafs = Polygon(Color(27, 83, 11));
	treeLeafs.push_back(Rect(Point(0,4), Point(14,WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(14, 8), Point(43, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(43, 4), Point(57, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(57, 0), Point(86, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(86, 4), Point(101, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(101, 8), Point(115, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(115, 12), Point(129, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(129, 16), Point(158, WORLD_WINDOW_HEIGHT)));	
	treeLeafs.push_back(Rect(Point(158, 12), Point(173, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(173, 8), Point(187, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(187, 4), Point(201, WORLD_WINDOW_HEIGHT)));	
	treeLeafs.push_back(Rect(Point(201, 0), Point(212, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(201, 0), Point(212, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(212, 2), Point(230, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(230, 4), Point(245, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(245, 8), Point(273, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(273, 4), Point(288, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(288, 2), Point(306, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(306, 0), Point(317, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(317, 4), Point(331, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(331, 8), Point(345, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(345, 12), Point(360, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(360, 16), Point(389, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(389, 12), Point(403, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(403, 8), Point(417, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(417, 4), Point(430, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(430, 0), Point(461, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(461, 4), Point(475, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(475, 8), Point(504, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(504, 4), Point(518, WORLD_WINDOW_HEIGHT)));
	treeLeafs.push_back(Rect(Point(518, 0), Point(WORLD_WINDOW_WIDTH, WORLD_WINDOW_HEIGHT)));
	treeLeafs.drawPolygon(0, 262);
}

void World::drawStairHoleCover()
{
	Rect cover1(Point(stairs->hole->x(), ground.y()), Point(stairs->hole->rightX(), stairs->hole->y()), ground.color());
	Rect cover2(Point(stairs->hole->x(), stairs->hole->y()), Point(stairs->hole->rightX(), stairs->hole->y() + stairs->hole->height() / 2.0), Color(BLACK));
	cover1.draw();
	cover2.draw();
}


int World::getScenarioNumber()
{
	return scenarioNumber;
}
