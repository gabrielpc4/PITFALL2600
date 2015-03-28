#pragma once
#ifndef WORLD_H_
#define WORLD_H_

#include "ScenarioObjects.h"
#include "Shapes.h"
#include "global_constants.h"
#include <vector>
#include "glut.h" // Custom glut.h fixed for using namespace std
#include <gl/gl.h>

using namespace std;

class World
{	
private:
	void drawBasicScenario();				// Draws a basic scenario, with the undeground, the ground, trees and leafs
	void buildTreeBranch(Polygon& branch, int treeNum);		//Draws the branches corresponding to the tree number, given the tree color
	void drawTreeLeafs();
	void buildBasicScenario();
	void buildTreeLeafs();
	Rect sky;
	Rect treeTrunk[4];
	Polygon treeLeafs;
	Rect tunnelWall;
	Polygon branches[4];	

	bool hasStairs;
	bool hasVine;
	bool hasTunnelHoles;
	bool hasBlackHole;
	bool hasWater;
	bool movingHole;
	bool hasBrickWall;	
	int brickWallSide;
	
public:
	// Basic Scenario elements
	Rect tunnelFloor;
	Rect tunnelTop;
	Rect ground;
		
	// Other elements	
	Vine* vine;
	Stairs* stairs;
	BrickWall* brickWall;
	vector<TunnelHole> tunnelHole;
	Hole* blackHole;
	Hole* water;
	World();				
	void buildScenario(int scenarioNumber);
	void draw(int scenarioNumber);	// Calls the function drawBasicScenario and loads the first Scenario
	void drawOverlayers();
	void deleteWorld();
	bool allowsVines();	
	bool allowsBlackHole();
	bool allowsWater();
	
};
#endif

