#pragma once
#ifndef ENEMIESGENERATOR_H_
#define ENEMIESGENERATOR_H_
#include "global_constants.h"
#include "Enemies.h"
#include "World.h"
#include <vector>
using namespace std;
class EnemiesGenerator
{
private:
	vector<ScenarioEnemies>& positiveScenarios;
	vector<ScenarioEnemies>& negativeScenarios;
	int& scenarioNumber;
	World* world;	
	ScenarioEnemies& thisScenario();	
public:
	EnemiesGenerator(vector<ScenarioEnemies>& positiveScenarios, vector<ScenarioEnemies>& negativeScenarios, int& scenarioNumber, World* world);
	void generateNewEnemies();
};
#endif
