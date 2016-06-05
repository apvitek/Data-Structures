//Joseph Dollahon
/*========================Documentation=============================================
The purpose of the Input class in respects to the rest of the project is to it 
read in input from the user and validate that it is the correct kind of input that was requested.
==================================================================================*/
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class UserInput
{
private:
	int inputInt;
	double inputDouble;
	string inputString;
	char inputChar;

public:

	//Constructor
	UserInput()
	{
		inputInt = 0;
		inputDouble = 0.0;
		inputChar = ' ';
	}

	//Destructor
	~UserInput()
	{

	}

	//Getter functions
	int getInputInt() { return inputInt; }
	double getInputDouble(){ return inputDouble; }
	string getInputString(){ return inputString; }
	char getInputChar(){ return inputChar; }

	//Function prototypes
	bool readInInt(int &outPut);
	bool readInDouble(double &outPut);
	bool readInString(string &outPut);
	bool readInChar(char &outPut);

};

//***********************************
//Function definitions
//***********************************


/*=====================================
Pre: A int by reference
Returns: true if UserInput is valid, and an int by reference
Purpose: Read in and validate integer data from the user
=====================================*/
bool UserInput::readInInt(int &outPut)
{
	int i = 0;
	bool isValidInput = true;
	string userInput;
	getline(cin, userInput);
	while (i < userInput.length() && isValidInput == true)
	{
		if (!isdigit(userInput[i]))
		{
			isValidInput = false;
		}
		i++;
	}
	if (isValidInput)
	{
		inputInt = atoi(userInput.c_str());
		outPut = inputInt;
	}
	return isValidInput;
}

/*=====================================
Pre: A double by reference
Returns: true if UserInput is valid, and an double by reference
Purpose: Read in and validate floating point data from the user
=====================================*/
bool UserInput::readInDouble(double &outPut)
{
	int i = 0;
	bool decimalPointAlreadyFound = false;
	bool isValidInput = true;
	string userInput;
	getline(cin, userInput);
	while (i < userInput.length() && isValidInput == true)
	{
		if (!isdigit(userInput[i]))
		{
			if (userInput[i] == '.')
			{
				if (decimalPointAlreadyFound == true)
				{
					isValidInput = false;
				}
				else
				{
					decimalPointAlreadyFound = true;
				}
			}
			else
			{
				isValidInput = false;
			}
		}
		i++;
	}
	if (isValidInput)
	{
		inputDouble = atof(userInput.c_str());
		outPut = inputDouble;
	}
	return isValidInput;
}

/*=====================================
Pre: A string by reference
Returns: true if UserInput is valid, and an string by reference
Purpose: Read in and validate string data from the user
=====================================*/
bool UserInput::readInString(string &outPut)
{
	bool isValidInput = true;
	string userInput;
	getline(cin, userInput);
	inputString = userInput;
	outPut = inputString;
	return isValidInput;
}

/*=====================================
Pre: A string by reference
Returns: true if UserInput is valid, and an string by reference
Purpose: Read in and validate string data from the user
=====================================*/
bool UserInput::readInChar(char &outPut)
{
	bool isValidInput = true;
	string userInput;
	getline(cin, userInput);
	if (userInput.length() == 1)
	{
		if (isalpha(userInput[0]))
		{
			inputChar = toupper(userInput[0]);
			outPut = inputChar;
		}
		else
		{
			isValidInput = false;
		}
	}
	else
	{
		isValidInput = false;
	}
	cout << "        [" << outPut << "]" << " was entered" << endl << endl;
	return isValidInput;
}
