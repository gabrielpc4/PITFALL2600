#include "World.h"

// Defines the Positions of the basic scenario
World::World()
{	
	vine				= NULL;
	stairs				= NULL;
	brickWall			= NULL;
	blackHole			= NULL;
	water				= NULL;
	allowVines			= false;
	vine				= new Vine();
	buildBasicScenario();		
}

void World::buildScenario(int scenarioNumber)
{	
	switch (scenarioNumber)
	{
	case(-1) :
	{
		allowVines = true;
		water = new Hole(144, 132, Color(BLUE));
		
	}break;
	case(0) :
	{
		stairs = new Stairs(245, 32);
		brickWall = new BrickWall(461, 32);
	}break;
	case(1) :
	{
		stairs = new Stairs(245, 32);
		brickWall = new BrickWall(461, 32);
		tunnelHole.push_back(TunnelHole(144, 96));
		tunnelHole.push_back(TunnelHole(331, 96));
	}break;
	case(2) :
	{
		allowVines = true;
		blackHole = new Hole(144, 132, Color(BLACK));
	}break;
	default:{}break;
	}
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
	treeTrunk[0] = Rect(Point(start_x, start_y), Point(115, end_y), Color(Color(83, 43, 0)));
	

	start_x = treeTrunk[0].rightX() + 101;
	end_x = start_x + 14;
	treeTrunk[1] = Rect(Point(start_x, start_y), Point(end_x, end_y), treeTrunk[0].color());

	start_x = treeTrunk[1].rightX() + 58;
	end_x = start_x + 14;
	treeTrunk[2] = Rect(Point(start_x, start_y), Point(end_x, end_y), treeTrunk[0].color());

	start_x = treeTrunk[2].rightX() + 101;
	end_x = start_x + 14;
	treeTrunk[3] = Rect(Point(start_x, start_y), Point(end_x, end_y), treeTrunk[0].color());

	buildTreeLeafs();

	for (unsigned i = 0; i < 4; i++)
	{
		buildTreeBranch(branches[i], i);
	}
}

void World::buildTreeLeafs()
{
	treeLeafs = Polygon(0, 262, Color(27, 83, 11));
	treeLeafs.push_back(Rect(Point(0, 4), Point(14, WORLD_WINDOW_HEIGHT)));
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
}


/*****************************************************************************************
* Method: draw
* Description: Calls the function drawBasicScenario and loads the first Scenario
******************************************************************************************/
void World::draw(int scenarioNumber)
{	
	drawBasicScenario();

	if (stairs != NULL)
	{
		stairs->draw();
	}

	if (brickWall != NULL)
	{
		brickWall->draw();
	}

	if (tunnelHole.size() != 0)
	{
		for (int i = 0; i < 2; i++)
		{
			tunnelHole.at(i).draw();
		}
	}

	if (blackHole != NULL)
	{
		blackHole->draw();
	}

	if (water != NULL)
	{
		water->draw();
	}

	
	if (this->allowVines)
	{
		vine->draw();
	}
	
	treeLeafs.draw();
}

/*****************************************************************************************
* Method Name: drawBasicScenario
* Description: Draws a basic scenario, with the underground, the ground, trees and leafs
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
		treeTrunk[i].draw();
		branches[i].draw();
	}
}

/*****************************************************************************************
* Method Name: drawTreeBranch
* Description: Draws the branches corresponding to the tree number
******************************************************************************************/
void World::buildTreeBranch(Polygon& branch, int treeNum)
{
	branch = Polygon(treeTrunk[treeNum].x(), treeTrunk[treeNum].topY(), Color(83, 43, 0));

	// Defines the branches rectangles, according with the tree that is being drawn
	switch (treeNum)
	{
	case(0) :
	{
		// Left branch
		branch.push_back(Rect(Point(0, 2), Point(8, 4)));
		branch.push_back(Rect(Point(4, 0), Point(11, 2)));

		// Middle
		branch.push_back(Rect(Point(11, 0), Point(18, 8)));

		// Right branch
		branch.push_back(Rect(Point(18, 0), Point(26, 2)));
		branch.push_back(Rect(Point(22, 2), Point(26, 4)));
		branch.push_back(Rect(Point(26, 2), Point(29, 12)));

		// Middle
		branch.push_back(Rect(Point(11, 0), Point(18, 8)));

		// Right branch
		branch.push_back(Rect(Point(18, 0), Point(26, 2)));
		branch.push_back(Rect(Point(22, 2), Point(26, 4)));
		branch.push_back(Rect(Point(26, 2), Point(29, 12)));
	}break;
	case(1) :
	{
		branch.push_back(Rect(Point(0, 0), Point(26, 2)));
		branch.push_back(Rect(Point(20, 2), Point(29, 4)));
	}break;
	case(2) :
	{
		branch.push_back(Rect(Point(0, 2), Point(7, 4)));
		branch.push_back(Rect(Point(2, 0), Point(25, 2)));
	}break;
	case(3) :
	{
		// Left branch
		branch.push_back(Rect(Point(0, 2), Point(3, 12)));
		branch.push_back(Rect(Point(3, 2), Point(7, 4)));
		branch.push_back(Rect(Point(3, 0), Point(11, 2)));

		// Middle
		branch.push_back(Rect(Point(11, 0), Point(18, 8)));

		// Right branch
		branch.push_back(Rect(Point(18, 0), Point(25, 2)));
		branch.push_back(Rect(Point(21, 2), Point(29, 4)));
	}break;
	default:;
	}
	// Centers the branches in the middle of the tree trunk
	branch -= Point((int)(branch.width() / 4.0) - 1, 0);	
}


void World::drawOverlayers()
{
	if (stairs != NULL)
	{
		stairs->drawOverlayer();
	}

	for (unsigned i = 0; i < tunnelHole.size(); i++)
	{
		tunnelHole.at(i).drawOverlayer();
	}

	if (blackHole != NULL)
	{
		blackHole->drawOverlayer();
	}

	if (water != NULL)
	{
		water->drawOverlayer();
	}
}

void World::deleteWorld()
{
	if (stairs != NULL)
	{
		stairs->~Stairs();
		delete stairs;
		stairs = NULL;
	}

	if (brickWall != NULL)
	{
		delete brickWall;
		brickWall = NULL;
	}
	
	if (tunnelHole.empty() == false)
	{
		for (unsigned i = 0; i < tunnelHole.size(); i++)
		{
			tunnelHole.at(i).~TunnelHole();
		}
		tunnelHole.clear();
	}
	
	if (blackHole != NULL)
	{
		blackHole->~Hole();
		delete blackHole;
		blackHole = NULL;
	}	

	if (water != NULL)
	{
		water->~Hole();
		delete water;
		water = NULL;
	}
	
	allowVines		= false;
}

bool World::hasAVine()
{
	return allowVines;
}


