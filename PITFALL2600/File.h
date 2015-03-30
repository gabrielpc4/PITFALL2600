#pragma once
#ifndef FILE_H_
#define FILE_H_
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;
class File :
	public ifstream
{
public:
	File();
	File(const char* fileName);
	~File();
	char nextChar();
	int nextCharAsInt();
	bool nextCharAsBool();
	bool seekToScenario(int scenarioNumber);
	list<int> getAllScenarioNumbersWithTreasure();
	string nextLine();
	int nextLineAsInt();
};
#endif
