#pragma once
#ifndef SCENARIOGENERATOR_H_
#define SCENARIOGENERATOR_H_
#include "global_constants.h"
#include "ScenarioElements.h"
#include <vector>
using namespace std;
class ScenarioGenerator
{
private:
	vector<ScenarioElements>& positiveScenarios;
	vector<ScenarioElements>& negativeScenarios;
	int& scenarioNumber;
	ScenarioElements& getScenario(int scenarioNumber);
	ScenarioElements& thisScenario();
	void preventSimilarScenarios();
	void randomizeStairs();
	void randomizeHole();
public:
	ScenarioGenerator(vector<ScenarioElements>& positiveScenarios, vector<ScenarioElements>& negativeScenarios, int& scenarioNumber);
	void generateNewScenario();
};
#endif
