//
//  main.cpp
//  Data Structures Homework #5
//
//  Created by Andrea Borghi on 6/3/14.
//  Copyright (c) 2014 Andrea Borghi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <regex>
#include "HashTable.h"
#include "Star.h"

using namespace std;

// Constants for the menu choices
const char SEARCH = 'S',
           DISPLAY_LIST_CONTENT = 'D',
           PRINT_LIST = 'P',
           SHOW_STATS = 'T',
           MENU = 'M',
           QUIT = 'Q';

const string REGEX_PATTERN = "[0-9-.A-z ]+";

// Functions prototypes
void menu();
char getChoice();
void findInTable(HashTable<Star> * table);
bool copyDataToHashTable(HashTable<Star> * starHashTable);
void removeLeadingWhiteSpace(string& str);

int main(int argc, const char * argv[])
{
    // Dynamically allocate a new HasTable
    HashTable<Star> * table = new HashTable<Star>;
    
    // Call a function to copy the data from a file to the HashTable
    copyDataToHashTable(table);
    
    char choice = MENU; // To store the user's choice
    
    while (choice != QUIT) {
        cout << "\nWhat do you want to do?" << endl;
        
        if (choice == MENU) menu();
        
        cout << "Enter your choice: ";
        
        choice = getChoice();
        
        switch (choice) {
            case SEARCH:
                findInTable(table);
                break;
                
            case DISPLAY_LIST_CONTENT:
                cout << "\nHere is the content of the Hash Table:\n";
                table->printTableElements(cout);
                break;
                
            case PRINT_LIST:
                cout << "\nHere is the Hash Table structure:\n";
                table->printTableStructure(cout);
                break;
                
            case SHOW_STATS:
                table->printStats(cout);
                break;
        }
    }
    
    delete table;
    
    return 0;
}

/**~*~*
 The menu function displays the main menu
 for the program
 *~**/
void menu()
{
    // Display the menu and get the user's choice.
    cout << "\t"
    << SEARCH
    << " - Search an element in the Hash Table via a key\n\t"
    << DISPLAY_LIST_CONTENT
    << " - Display the content of the table\n\t"
    << PRINT_LIST
    << " - Print the table structure\n\t"
    << SHOW_STATS
    << " - Show the table stats\n\t"
    << MENU
    << " - Display this menu again\n\t"
    << QUIT
    << " - Quit the program\n";
}

/**~*~*
 The getChoice function gets an choice from the
 user and returns it as a char.
 *~**/
char getChoice()
{
    // Variables declaration
    char choice = 'Q';
    bool okChoice = false;
    
    // Validate the user input
    while (!okChoice) {
        // Get user input
        cin.get(choice);
        
        // Convert the user input to uppercase
        choice = toupper(choice);
        
        // Check if the user input matches one of the constant choices
        if (choice == SEARCH ||
            choice == DISPLAY_LIST_CONTENT ||
            choice == PRINT_LIST ||
            choice == SHOW_STATS ||
            choice == MENU ||
            choice == QUIT) {
            // Change the control loo[ variable to true
            okChoice = true;
            
        } else {
            // Notify the user that her choice is invalid and clear input
            cout << "\nInvalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(80, '\n');
        }
    }
    
    // Clear the input for other functions
    cin.clear();
    cin.ignore(80, '\n');
    
    // Return user's choice
    return choice;
}

/**~*~*
 The findInTable function asks the user for an element to search
 in a HashTable (passed as an argument) and calls the
 table's public function to search for that value and display
 the result
 *~**/
void findInTable(HashTable<Star> * table)
{
    cout << "Insert a key to search for an element in the Hash Table." << endl;
    
    string key;
    
    getline(cin, key, '\n');
    
    Star result = table->searchForKey(key);
    
    if (result != NULL) {
        cout << "The following element was found:" << endl;
        cout << result.toString() << endl;
        
    } else {
        cout << "Star not found in the Hash Table." << endl;
    }
}

/**~*~*
 The copyDataToHashTable function opens a file, parses its
 content using regular expressions and adds it to the HashTable
 passed as a parameter. Returns true if copy was successful
 and false if it was not.
 *~**/
bool copyDataToHashTable(HashTable<Star> * starHashTable){
    fstream inputFile;
    string integerFromFile;
    
    // Open specified file
    inputFile.open("/Users/andreaborghi/Documents/DAC - Data Structures/Data Structures Homework #5/Data Structures Homework #5/InputFile.txt");
    
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
                Star temp; // To temporarily store a Star
                string data = (*iter); // To store the iterator's content
                
                temp.setRank(atoi(data.c_str()));
                
                ++iter;
                
                data = (*iter);
                
                temp.setMagnitude(atof(data.c_str()));
                
                ++iter;
                
                data = (*iter);
                
                removeLeadingWhiteSpace(data);
                
                temp.setName(data);
                
                ++iter;
                
                data = (*iter);
                
                removeLeadingWhiteSpace(data);
                
                temp.setType(data);
                
                ++iter;
                
                data = (*iter);
                
                removeLeadingWhiteSpace(data);
                
                temp.setConstellation(data);
                
                starHashTable->insertValue(temp);
            }
        }
    }
    
    // Close the input file
    inputFile.close();
    
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

/*
 What do you want to do?
 S - Search an element in the Hash Table via a key
 D - Display the content of the table
 P - Print the table structure
 T - Show the table stats
 M - Display this menu again
 Q - Quit the program
 Enter your choice: d
 
 Here is the content of the Hash Table:
 Alpha Centauri A
 Vega
 Betelgeuse
 Sirius
 Hadar
 Arcturus
 Capella
 Altair
 Procyon
 Aldebaran
 Spica
 Acrux
 Rigel
 Canopus
 Achernar
 
 What do you want to do?
 Enter your choice: p
 
 Here is the Hash Table structure:
 Now printing the main table:
 0. Alpha Centauri A
 1. Vega
 2. [Empty slot]
 3. [Empty slot]
 4. Betelgeuse
 5. [Empty slot]
 6. Sirius
 7. Hadar
 8. Arcturus
 9. Capella
 10. [Empty slot]
 11. Altair
 12. [Empty slot]
 13. [Empty slot]
 14. Procyon
 15. [Empty slot]
 16. [Empty slot]
 17. [Empty slot]
 18. [Empty slot]
 19. [Empty slot]
 20. Aldebaran
 21. [Empty slot]
 22. [Empty slot]
 23. [Empty slot]
 24. [Empty slot]
 25. [Empty slot]
 26. Spica
 27. [Empty slot]
 28. [Empty slot]
 29. [Empty slot]
 30. Acrux
 
 Now printing the buckets:
 Bucket address: 7. Elements in bucket:
 0. Rigel
 1. [Empty slot]
 2. [Empty slot]
 Bucket address: 14. Elements in bucket:
 0. Canopus
 1. [Empty slot]
 2. [Empty slot]
 Bucket address: 26. Elements in bucket:
 0. Achernar
 1. [Empty slot]
 2. [Empty slot]
 
 What do you want to do?
 Enter your choice: t
 Here are the HashTable stats:
 
 *** List initialized ***
 Inserting Acrux...
 The home address is 30
 Inserting Altair...
 The home address is 11
 Inserting Sirius...
 The home address is 6
 Inserting Betelgeuse...
 The home address is 4
 Inserting Aldebaran...
 The home address is 20
 Inserting Vega...
 The home address is 1
 Inserting Spica...
 The home address is 26
 Inserting Hadar...
 The home address is 7
 Inserting Capella...
 The home address is 9
 Inserting Arcturus...
 The home address is 8
 Inserting Achernar...
 Collision! Home address 26 already exists in the Hash Table
 New bucket will be created with number 26
 Inserting Alpha Centauri A...
 The home address is 0
 Inserting Procyon...
 The home address is 14
 Inserting Rigel...
 Collision! Home address 7 already exists in the Hash Table
 New bucket will be created with number 7
 Inserting Canopus...
 Collision! Home address 14 already exists in the Hash Table
 New bucket will be created with number 14
 
 Total amount of elements: 15
 
 Main HashTable size: 31
 Used elements: 12	(Load factor: 38%)
 
 Number of buckets: 3
 Bucket with address 7 has 1 elements out of 3	(Load factor: 33%)
 Bucket with address 14 has 1 elements out of 3	(Load factor: 33%)
 Bucket with address 26 has 1 elements out of 3	(Load factor: 33%)
 Full buckets: 0
 
 Total collisions while buiding the list: 3
 
 What do you want to do?
 Enter your choice: m
 
 What do you want to do?
 S - Search an element in the Hash Table via a key
 D - Display the content of the table
 P - Print the table structure
 T - Show the table stats
 M - Display this menu again
 Q - Quit the program
 Enter your choice: s
 Insert a key to search for an element in the Hash Table.
 Aldebaran
 The following element was found:
 #14 - Name: Aldebaran, Magnitude: 0.870000, Type: orange giant star, Constellation: Taurus
 
 What do you want to do?
 Enter your choice: s
 Insert a key to search for an element in the Hash Table.
 Sirio
 Star not found in the Hash Table.
 
 What do you want to do?
 Enter your choice: s
 Insert a key to search for an element in the Hash Table.
 Spica
 The following element was found:
 #15 - Name: Spica, Magnitude: 0.980000, Type: blue subgiant star, Constellation: Virgo
 
 What do you want to do?
 Enter your choice: q
*/