//Joseph Dollahon
//Andrea Borghi
//5-11-2014

//Main for Team Project

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "Star.h"
#include "UserInput.h"

using namespace std;

//Constants for menu
const char ADD_DATA = 'A';
const char DELETE = 'D';
const char SEARCH = 'S';
const char LIST_HASH = 'H';
const char LIST_SORTED = 'O';
const char DISPLAY_TREE = 'T';
const char WRITE_TO_FILE = 'W';
const char HASH_STATS = 'I';
const char DISPLAY_MENU = 'M';

const string REGEX_PATTERN = "[0-9-.A-z ]+";

//Function declorations

char getChoice();
void displayBoarder();
bool readFromFile(HashTable *hashTable, BinarySearchTree *bsTree);
char menu(bool display);
bool addTo(HashTable *hashTable, BinarySearchTree *bsTree);
bool deleteData(HashTable *hashTable, BinarySearchTree *bsTree);
bool search(HashTable *hashTable);
void displayByHash(HashTable *hashTable);
void displaySortedList(BinarySearchTree *bsTree);
void displayTree(BinarySearchTree *bsTree);
void writeToFile(HashTable *hashTable);
void hashStats(HashTable *hashTable);
void removeLeadingWhiteSpace(string& str);


struct listHead
{
	HashTable *hashTable;
	BinarySearchTree *bsTree;
};

int main()
{
	listHead list;
	list.bsTree = new BinarySearchTree;
	list.hashTable = new HashTable;
	bool displayMenu = true;
	char choice;
	readFromFile(list.hashTable, list.bsTree);
	while ((choice = menu(displayMenu)) != 'Q')
	{
		displayMenu = false;
		switch (choice)
		{
		case ADD_DATA:
			displayBoarder();
			addTo(list.hashTable, list.bsTree);
			displayBoarder();
			break;
		case DELETE:
			displayBoarder();
			deleteData(list.hashTable, list.bsTree);
			displayBoarder();
			break;
		case SEARCH:
			displayBoarder();
			search(list.hashTable);
			displayBoarder();
			break;
		case LIST_HASH:
			displayBoarder();
			displayByHash(list.hashTable);
			displayBoarder();
			break;
		case LIST_SORTED:
			displayBoarder();
			displaySortedList(list.bsTree);
			displayBoarder();
			break;
		case DISPLAY_TREE:
			displayBoarder();
			displayTree(list.bsTree);
			displayBoarder();
			break;
		case WRITE_TO_FILE:
			displayBoarder();
			writeToFile(list.hashTable);
			cout << "Contents of the Hash Table writtent to file" << endl;
			displayBoarder();
			break;
		case HASH_STATS:
			displayBoarder();
			hashStats(list.hashTable);
			displayBoarder();
			break;
		case DISPLAY_MENU:
			displayMenu = true;
			break;
		default:
			cout << choice << " is invalid input" << endl << endl;
		}
		if (choice != 'M')
		{
			cout << endl << "What would you like to do next? 'M' for menu" << endl;
		}
	}
	writeToFile(list.hashTable);
	list.bsTree->~BinarySearchTree();
	list.hashTable->~HashTable();
	return 0;
}

//Function definitions

/**~*~*
 The getChoice function gets an choice from the
 user and returns it as a char.
 *~**/
char getChoice()
{
	UserInput userInput;
	char choice = ' ';
	userInput.readInChar(choice);
	return choice;
}

void displayBoarder()
{
	cout << "===========================================================================" << endl << endl;
}

bool readFromFile(HashTable *hashTable, BinarySearchTree *bsTree)
{
	fstream inputFile;
	string integerFromFile;
	// Open specified file
	//inputFile.open("C:/Users/Joseph/Documents/Visual Studio 2013/Projects/TeamProjectComplete/TeamProjectComplete/Input.txt");
	inputFile.open("/Users/andreaborghi/Documents/DAC - Data Structures/TeamProject/Input.txt");
	// If inputFile was open successfully, change success to 1
	if (!inputFile) {
		cout << "The input file could not be open!" << endl;
		return false;
	};
	// Loop to copy input data as long as the file can be read
	while (getline(inputFile, integerFromFile, '\n')) {
		sregex_token_iterator end;
		regex pattern(REGEX_PATTERN);
		for (sregex_token_iterator iter(integerFromFile.begin(), integerFromFile.end(), pattern); iter != end; ++iter){
			if ((*iter).length() > 0) {
				Data star;
				Star *temp = new Star; // To temporarily store a Star
				string data = (*iter); // To store the iterator's content
				temp->setRank(atoi(data.c_str()));
				++iter;
				data = (*iter);
				temp->setMagnitude(atof(data.c_str()));
				++iter;
				data = (*iter);
				removeLeadingWhiteSpace(data);
				temp->setName(data);
				++iter;
				data = (*iter);
				removeLeadingWhiteSpace(data);
				temp->setType(data);
				++iter;
				data = (*iter);
				removeLeadingWhiteSpace(data);
				temp->setConstellation(data);
				star.starPtr = temp;
				bsTree->BST_insert(star);
				hashTable->insertValue(temp);
			}
		}
	}
	// Close the Input file
	inputFile.close();
	return true;
}




/*=====================================
 Pre: bool to tell it whether to display the menu.
 Returns: a character converted to upper case.
 Purpose: displays the menu, and reads in the user choice.
 =====================================*/
char menu(bool displayMenu)
{
	if (displayMenu == true)
	{
		displayBoarder();
		cout << "\nEnter the letter for the corresponding choice\n\t"
			<< "A : to add data\n\t"
			<< "D : to delete data\n\t"
			<< "S : to search\n\t"
			<< "H : to display the elements in the hash table\n\t"
			<< "O : to display the elements sorted\n\t"
			<< "T : to display the elements indented tree\n\t"
			<< "W : write data to file\n\t"
			<< "I : statistic of the hash table\n\t"
			<< "M : to display the menu again\n\t"
			<< "Q : to quit\n\n\n";
		displayBoarder();
	}
	return getChoice();
}

/*=====================================
 Pre: The hash table and the BST by reference
 Returns: true if data was added succesfully
 Purpose: Reads in data from the user and adds it
 to the Hash Table and BST
 =====================================*/
bool addTo(HashTable *hashTable, BinarySearchTree *bsTree)
{
	UserInput userInput;
	int rank;
	string name;
	double magnitude;
	string type;
	string constellation;

	cout << endl << "Enter Star" << endl;
	cout << "Rank: ";
	while (!userInput.readInInt(rank))
	{
		cout << "Invalid input enter a integer" << endl;
		cout << "Rank: ";
	}
	cout << "Name: ";
	userInput.readInString(name);
	cout << "Magnitude: ";
	while (!userInput.readInDouble(magnitude))
	{
		cout << "Invalid input enter a floating point number" << endl;
		cout << "Magnitude: ";
	}
	cout << "Description: ";
	userInput.readInString(type);
	cout << "Constellation: ";
	userInput.readInString(constellation);
	Star *newStar = new Star(rank, name, magnitude, type, constellation);
	Data data;
	data.starPtr = newStar;
	//If the key field is already present in the hash table reject it.
	if (!hashTable->searchForKey(name))
	{
		bsTree->BST_insert(data);
		hashTable->insertValue(newStar);
		return true;
	}
	else
	{
		cout << "The element you are trying to add already exists in the database!" << endl;
		return false;
	}
	return true;
}

/**~*~*
 The removeLeadingWhiteSpace function checks if
 the string passed as a referenced parameter
 contains a leading whitespace and erases it
 *~**/
void removeLeadingWhiteSpace(string& str)
{
	if (str[0] == '\t' || str[0] == '\n' || str[0] == ' ' || str[0] == '\r') {
		str.erase(0, 1);
	}
}

/*=====================================
 Pre: The hash table and the BST by reference
 Returns: true if data was deleted succesfully
 Purpose: Deletes data from the Hash Table and BST
 =====================================*/
bool deleteData(HashTable *hashTable, BinarySearchTree *bsTree)
{
	UserInput input;
	string target;
	cout << "Enter value to be deleted ";
	input.readInString(target);
	cout << endl;
	hashTable->deleteValue(hashTable->searchForKey(target));
	if (bsTree->deleteValue(target))
	{
		cout << "[" << target << "]" << " has been deleted" << endl;
	}
	else
	{
		cout << "[" <<  target << "]" << " does not exist in data base." << endl;
	}
	return true;
}

/*=====================================
 Pre: The hash table and the BST by reference
 Returns: True if data was deleted succesfully
 Purpose: Deletes data from the Hash Table and BST
 =====================================*/
bool search(HashTable *hashTable)
{
	UserInput input;
	string target;
	cout << "Enter Star name to search for ";
	input.readInString(target);
	Star * found = hashTable->searchForKey(target);
	if (found) {
		cout << "The following element was retrieved from the table:" << endl;
		cout << found->toString() << endl;
	}
	else {
		cout << target << " not found in the Hash Table." << endl;
	}
	return true;
}


/*=====================================
 Pre: The hash table by reference
 Returns: Nothing
 Purpose: Displays the contents of the hash table
 =====================================*/
void displayByHash(HashTable *hashTable)
{
	hashTable->printTableStructure(cout);
}

/*=====================================
 Pre: The BST by reference
 Returns: Nothing
 Purpose: Displays the contents of the BST
 =====================================*/
void displaySortedList(BinarySearchTree *bsTree)
{
	bsTree->BST_InorderTraverse();
}

/*=====================================
 Pre: The BST by reference
 Returns: Nothing
 Purpose: Displays the contents of the BST indented
 =====================================*/
void displayTree(BinarySearchTree *bsTree)
{
	bsTree->indented();
}

/*=====================================
 Pre: The hash table by reference
 Returns: Nothing
 Purpose: Writes the contents of the hashTable to the file
 =====================================*/
void writeToFile(HashTable *hashTable)
{
	//fstream output("Output.txt");
	fstream output("/Users/andreaborghi/Documents/DAC - Data Structures/TeamProject/Output.txt");
	hashTable->printTableElements(output);
	output.close();
}

/*=====================================
 Pre: The hash table by reference
 Returns: Nothing
 Purpose: Displays the statistics about the hash table
 =====================================*/
void hashStats(HashTable *hashTable)
{
	hashTable->printStats(cout);
}
