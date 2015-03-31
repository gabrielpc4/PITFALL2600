#pragma once
#ifndef WORLD_H_
#define WORLD_H_

#include "Shapes.h"
#include "File.h"
#include "ScenarioGenerator.h"
#include <vector>
#include <stdlib.h> 
#include <time.h> 
#include "glut.h" // Custom glut.h fixed for using namespace std
#include <gl/gl.h>

using namespace std;

class World
{	
private:
	void drawBasicScenario();				// Draws a basic scenario, with the underground, the ground, trees and leafs
	void buildTreeBranch(Polygons& branch, int treeNum);		//Draws the branches corresponding to the tree number, given the tree color
	void drawTreeLeafs();
	void buildBasicScenario();
	void buildTreeLeafs();
	Rect sky;
	Rect treeTrunk[4];
	Polygons treeLeafs;
	Rect tunnelWall;
	Polygons branches[4];		
	File worldElementsFile;
	int scenarioNumber;
	vector<ScenarioElements> positiveScenarios;
	vector<ScenarioElements> negativeScenarios;
	ScenarioGenerator* scenarioGenerator;


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
	Bonfire* bonfire;
	Treasure* treasure;

	World();				
	void buildScenario(int scenarioNumber);
	void draw(int scenarioNumber);	// Calls the function drawBasicScenario and loads the first Scenario
	void drawOverlayers();
	void deleteWorld();
	bool hasAVine();	
	bool hasABlackHole();
	bool hasWater();
	bool hasABonfire();
	bool hasATreasure();
	bool hasABrickWall();
	bool hasStairs();
	bool hasMovingHoles();
	void createABonfire();
	void createAVine();
	void deleteTreasure();
	void createStaticWater();
	void createATreasure();		
	ScenarioElements& thisScenario();
	void denyBonfires();
};
#endif

