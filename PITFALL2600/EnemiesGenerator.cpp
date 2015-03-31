#include "EnemiesGenerator.h"

EnemiesGenerator::EnemiesGenerator(vector<ScenarioEnemies>& positiveScenarios, vector<ScenarioEnemies>& negativeScenarios, int& scenarioNumber, World* world)
	: positiveScenarios(positiveScenarios),
	negativeScenarios(negativeScenarios),
	scenarioNumber(scenarioNumber)	
{
	this->world = world;
}
void EnemiesGenerator::generateNewEnemies()
{
	ScenarioEnemies currentScenario;

	if (world->hasATreasure() == false)
	{
		int n = rand() % 6;
		switch (n)
		{
		case(0) :
		{
			currentScenario.nLogs = 1;
			currentScenario.movingLogs = (((rand() % 5) == 0) ? true : false);

		}break;
		case(1) :
		{
			currentScenario.nLogs = 2;
			currentScenario.movingLogs = true;
		}break;
		case(2) :
		{
			currentScenario.nLogs = 3;
			currentScenario.movingLogs = (((rand() % 5) == 0) ? false : true);
		}break;
		case(3) :
		{

			currentScenario.nCrocodiles = 3;

		}break;
		case(4) :
		{
			if (world->hasABonfire() == false)
			{
				currentScenario.nSnakes = 1;
			}
			else
			{
				generateNewEnemies();
			}
		}break;
		case(5) :
		{
			world->createABonfire();
		}break;
		default:
		{
		}break;
		}
	}

	if (scenarioNumber > 0)
	{
		if (scenarioNumber > (int)positiveScenarios.size() - 1)
		{
			positiveScenarios.push_back(currentScenario);
		}
	}
	else if (scenarioNumber < 0)
	{
		if (abs(scenarioNumber) >(int)negativeScenarios.size() - 1)
		{
			negativeScenarios.push_back(currentScenario);
		}
	}
	else
	{
		positiveScenarios.push_back(currentScenario);
		negativeScenarios.push_back(currentScenario);
	}

	if (world->hasABrickWall() == false && world->hasStairs() == false)
	{
		thisScenario().nScorpions = 1;
	}

	if ((world->hasABlackHole() && world->hasMovingHoles() == false)
		|| world->hasWater() && thisScenario().nCrocodiles == 0 && world->hasMovingHoles() == false && world->hasAVine() == false)
	{
		world->createAVine();
	}

	if (thisScenario().movingLogs == false && world->hasABonfire())
	{
		world->denyBonfires();
	}

	if (thisScenario().nCrocodiles != 0)
	{
		if (rand() % 2 == 0)
		{
			world->createAVine();
		}
		else
		{
			if (thisScenario().nSnakes == 0 && world->hasABonfire() == false && world->hasATreasure() == false)
			{
				if (rand() % 2 == 0)
				{
					world->createATreasure();
				}
			}
		}
		world->createStaticWater();
	}
}

ScenarioEnemies& EnemiesGenerator::thisScenario()
{
	if (scenarioNumber >= 0)
	{
		return positiveScenarios.at(scenarioNumber);
	}
	return negativeScenarios.at(abs(scenarioNumber));
}
