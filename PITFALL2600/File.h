#pragma once
#ifndef FILE_H_
#define FILE_H_
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
	void seekToScenario(int scenarioNumber);
};
#endif
