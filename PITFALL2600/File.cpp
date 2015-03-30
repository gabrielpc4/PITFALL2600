#include "File.h"


File::File()
{
	cout << "No File Detected" << end;
}

File::File(const char* fileName)
	: ifstream(fileName)
{
	if (is_open() == false)
	{
		cout << "File not found: " << fileName << endl;
	}
}

char File::nextChar()
{
	char character;
	get(character);

	// Ignore comments
	while (character == '/')
	{		
		ignore(256, '\n');
		get(character);
	}

	return character;
}

int File::nextCharAsInt()
{
	char readedChar = this->nextChar();
	bool negative = false;
	if (readedChar == '-')
	{
		negative = true;
		readedChar = nextChar();
	}
	

	int num = static_cast<int>(readedChar);
	
	if (negative)
	{
		return ((-1) * (num - '0'));
	}
	return num - '0';
}

bool File::nextCharAsBool()
{
	char readedChar = this->nextChar();
	// Ignore line breaks
	if (readedChar == '\n')
	{
		get(readedChar);
	}
	int num = static_cast<int>(readedChar);
	
	if (num - '0' == 0)
	{
		return false;
	}
	return true;
}

string File::nextLine()
{
	string result;
	char c = nextChar();
	while (c != '\n')
	{		
		result += c;

		c = nextChar();
	}
	return result;
}

int File::nextLineAsInt()
{
	stringstream ss(nextLine());
	int num = 0;
	ss >> num;	
	return num;
}

bool File::seekToScenario(int scenarioNumber)
{	
	
	seekg(0);
	int sn = nextLineAsInt();	
	while (sn != scenarioNumber)
	{	
		ignore(1,'\n');
		ignore(256, '\n');
		sn = nextLineAsInt();

		// If sn == 52, means it reached the end of the file, 
		// this makes the program use the default values
		if (sn == 52)
		{
			return false;
		}		
	}
	return true;
}

list<int> File::getAllScenarioNumbersWithTreasure()
{
	list<int> scenariosWithTreasure;

	seekg(0);
	int currentScenario = nextLineAsInt();	

	while (seekToScenario(currentScenario))	// While it doesn't reach the end of the file
	{		
		// for the next 10 characters
		for (unsigned i = 0; i < 10; i++)
		{
			// Move the file pointer 1 character forward
						
			// If it's the 10th character (0 is the 1st)
			if (i == 9)
			{
				// If the read char is 1
				if (nextCharAsInt() == 1)
				{
					scenariosWithTreasure.push_back(currentScenario);
				}
			}
			else
			{
				nextChar();
			}
		}
		currentScenario++;
	}	

	return scenariosWithTreasure;
}



File::~File()
{
	close();
}
