#pragma once
#ifndef WORLD_H_
#define WORLD_H_

#include "ScenarioObjects.h"
#include "Shapes.h"
#include "global_constants.h"
#include "File.h"
#include <vector>
#include "glut.h" // Custom glut.h fixed for using namespace std
#include <gl/gl.h>

using namespace std;

class ScenarioElements
{
public:
	bool allowStairs;
	bool allowVines;
	bool allowTunnelHoles;
	bool allowBlackHoles;
	bool allowWater;
	bool allowMovingHoles;
	bool allowBrickWalls;
	bool allowBonfires;
	bool allowGoldBars;
	int brickWallSide;
	ScenarioElements()
	{
		allowStairs = false;
		allowVines = false;
		allowTunnelHoles = false;
		allowBlackHoles = false;
		allowWater = false;
		allowMovingHoles = false;
		allowBrickWalls = false;
		allowBonfires = false;
		allowGoldBars = false;
		brickWallSide = NONE;
	}
};

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
	File worldElementsFile;
	list<int> scenariosWithTreasure;
	int scenarioNumber;

public:

	vector<ScenarioElements> positiveScenarios;
	vector<ScenarioElements> negativeScenarios;


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
	GoldBar* goldBar;

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
	void forceStaticHoles();
	void raffleScenarioElements();
	ScenarioElements& thisScenario();
};
#endif

