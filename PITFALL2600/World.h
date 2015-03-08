#pragma once
#ifndef WORLD_H_
#define WORLD_H_

#include "ScenarioObjects.h"
#include "Shapes.h"
#include "constants.h"
#include <vector>
#include "glut.h" // Custom glut.h fixed for using namespace std
#include <gl/gl.h>


using namespace std;

class World
{	
private:
	int scenarioNumber;
	void drawBasicScenario();				// Draws a basic scenario, with the undeground, the ground, trees and leafs
	void drawTreeBranch(int treeNum);		//Draws the branches corresponding to the tree number, given the tree color
	void drawTreeLeafs();
	void buildBasicScenario();
	void buildScenario(int scenarioNumber);
	Rect sky;
	Rect treeTrunk[4];
	Polygon treeLeafs;
	Rect tunnelWall;
	

public:
	// Basic Scenario elements
	Rect tunnelFloor;
	Rect tunnelTop;
	Rect ground;
		
	// Other elements	
	Stairs* stairs;
	BrickWall* brickWall;
	World();
	World(int scenarioNumber);						// Defines the Positions of the basic scenario
	void draw();	// Calls the function drawBasicScenario and loads the first Scenario
	void drawStairHoleCover();
	
};
#endif

