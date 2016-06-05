//
//  main.cpp
//  Data Structures Homework #4
//
//  Created by Andrea Borghi on 5/17/14.
//  Copyright (c) 2014 Andrea Borghi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <regex>
#include "BinarySearchTree.h"
#include "Star.h"

using namespace std;

// Constants for the menu choices
const char SEARCH = 'S',
           DEPTH_FIRST = 'D',
           BREADTH_FIRST = 'B',
           PRINT_INDENTED = 'T',
           PRINT_RANGE = 'R',
           ITERATIVE = 'I',
           MENU = 'M',
           QUIT = 'Q';

const string REGEX_PATTERN = "[0-9-.A-z ]+";

// Functions prototypes
void menu();
char getChoice();
double getElementToSearch();
void findInTree(BinarySearchTree<Star> * starTree);
void printRangeInTree(BinarySearchTree<Star> * starTree);
bool copyDataToTree(BinarySearchTree<Star> * starTree);
void removeLeadingWhiteSpace(string& str);

int main(int argc, const char * argv[])
{
    // Variables declaration
    BinarySearchTree<Star> * starTree = new BinarySearchTree<Star>(); // To store the BinarySearchTree
    char choice = MENU; // To store the user's choice
    
    // Call a function to copy the data from the input file to the BinarySearchTree
    copyDataToTree(starTree);

    // Loop that controls the main menu
    while (choice != QUIT) {
        cout << "What do you want to do?" << endl;
        
        if (choice == MENU) menu();
        
        cout << "Enter your choice: ";
        
        choice = getChoice();
        
        switch (choice) {
            case SEARCH:
                findInTree(starTree);
                cout << endl;
                break;
                
            case DEPTH_FIRST:
                cout << "\nHere is the recursive Preorder traversal:\n";
                starTree->printPreorder(cout);
                
                cout << "\nHere is the recursive Inorder traversal:\n";
                starTree->printInorder(cout);
                
                cout << "\nHere is the recursive Postorder traversal:\n";
                starTree->printPostorder(cout);
                cout << endl;
                break;
                
            case BREADTH_FIRST:
                cout << "\nHere is the iterative Breadth First traversal:\n";
                starTree->printBreadthFirst(cout);
                cout << endl;
                break;
                
            case PRINT_INDENTED:
                cout << "Here is the tree in indented form:\n" << endl;
                starTree->displayTree(cout);
                cout << endl;
                
                cout << "Here is the same tree printed vertically:\n" << endl;
                starTree->displayTreeVertically(cout);
                break;
                
            case PRINT_RANGE:
                printRangeInTree(starTree);
                cout << endl;
                break;
                
            case ITERATIVE:
                cout << "\nHere is the iterative Preorder traversal:\n";
                starTree->iterativePreorder(cout);
                
                cout << "\nHere is the iterative Inorder traversal:\n";
                starTree->iterativeInorder(cout);
                
                cout << "\nHere is the iterative Postorder traversal:\n";
                starTree->iterativePostorder(cout);
                cout << endl;
                break;
        }
    }
    
    // Deallocate memory
    delete starTree;
    
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
    << " - Search an element in the tree\n\t"
    << DEPTH_FIRST
    << " - Traverse the tree depth first\n\t"
    << BREADTH_FIRST
    << " - Traverse the tree breadth first\n\t"
    << PRINT_INDENTED
    << " - Print the tree in indented form\n\t"
    << PRINT_RANGE
    << " - Display the tree elements within a certain range\n\t"
    << ITERATIVE
    << " - Display the tree iteratively\n\t"
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
            choice == DEPTH_FIRST ||
            choice == BREADTH_FIRST ||
            choice == PRINT_INDENTED ||
            choice == PRINT_RANGE ||
            choice == ITERATIVE ||
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
 The function getElementToSearch gets the user input
 to be searched in the BinarySearchTree
 *~**/
double getElementToSearch()
{
    // Variables declaration
    double dataToSearch = 0;
    bool okChoice = false;
    
    // Validate the user input
    while (!okChoice) {
        // Check if the user input matches one of the constant choices
        if (cin >> dataToSearch
            ) {
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
    return dataToSearch;
}

/**~*~*
 The findInTree function asks the user for an element to search
 in a BinarySearchTree (passed as an argument) and calls the
 tree's public function to search for that value and display
 the result
 *~**/
void findInTree(BinarySearchTree<Star> * starTree)
{
    // Variables declaration
    bool okVal = false; // To store wether the value was found or not
    double data = 0.0; // To store the result of the search
    
    // Continue to search for the value until the user input is within a range
    while (!okVal) {
        cout << "\nEnter an element to search in the tree between " << starTree->getSmallest().getMagnitude() << " and " << starTree->getLargest().getMagnitude() << "." << endl;
        
        // Get the user input for the data to find
        data = getElementToSearch();
        
        // If the data is within the tree range, break the loop
        if (data < starTree->getSmallest().getMagnitude() || data > starTree->getLargest().getMagnitude()) {
            cout << data << " is outside the specified range. Please try again." << endl;
            
        } else {
            okVal = true;
        }
    }
    
    // Create a new star with the value to be found
    Star toSearch(data);
    
    // Call a memeber function to search for the user's input in the BST and return wether it was found or not
    starTree->searchNode(toSearch) ? cout << data << " was found in the tree." << endl : cout << data << " was not found in the tree." << endl;
}

/**~*~*
 The printRangeInTree function asks the user for a range of
 elements to search in a BinarySearchTree (passed as an argument)
 and calls the tree's public function to search for the values
 and display the result
 *~**/
void printRangeInTree(BinarySearchTree<Star> * starTree)
{
    double min, max; // To store the minimum and the maxim value to search in the BST
    
    cout << "\nEnter an element to search in the tree between " << starTree->getSmallest().getMagnitude() << " and " << starTree->getLargest().getMagnitude() << "." << endl;
    
    // Get the minimum element to search
    cout << "Enter a minimum value for the range." << endl;
    
    min = getElementToSearch();
    
    // Get the maximum element to search
    cout << "Now enter a maximum value for the range." << endl;

    max = getElementToSearch();
    
    // Create two new Stars with the minimum and maximum value input by the user
    Star starMin(min);
    Star starMax(max);
    
    // Call the BST member function to print the values within the user selected range
    cout << "The elements matching the selected range in the tree are:" << endl;
    
    starTree->printRange(starMin, starMax, cout);
}

/**~*~*
 The copyDataToTree function opens a file, parses its
 content using regular expressions and adds it to the vector
 passed as a parameter. Returns true if copy was successful
 and false if it was not.
 *~**/
bool copyDataToTree(BinarySearchTree<Star> * starTree){
    fstream inputFile;
    string integerFromFile;
    
    // Open specified file
    inputFile.open("/Users/andreaborghi/Documents/DAC - Data Structures/Data Structures Homework #4/Data Structures Homework #4/InputFile.txt");
    
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
                
                starTree->addNode(temp);
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
 S - Search an element in the tree
 D - Traverse the tree depth first
 B - Traverse the tree breadth first
 T - Print the tree in indented form
 R - Display the tree elements within a certain range
 I - Display the tree iteratively
 M - Display this menu again
 Q - Quit the program
 Enter your choice: d
 
 Here is the recursive Preorder traversal:
 Acrux (0.77)
 Altair (0.76)
 Sirius (-1.44)
 Betelgeuse (0.45)
 Vega (0.03)
 Arcturus (-0.05)
 Canopus (-0.62)
 Alpha Centauri A (-0.01)
 Capella (0.08)
 Procyon (0.4)
 Rigel (0.18)
 Hadar (0.61)
 Achernar (0.45)
 Aldebaran (0.87)
 Spica (0.98)
 
 Here is the recursive Inorder traversal:
 Sirius (-1.44)
 Canopus (-0.62)
 Arcturus (-0.05)
 Alpha Centauri A (-0.01)
 Vega (0.03)
 Capella (0.08)
 Rigel (0.18)
 Procyon (0.4)
 Betelgeuse (0.45)
 Achernar (0.45)
 Hadar (0.61)
 Altair (0.76)
 Acrux (0.77)
 Aldebaran (0.87)
 Spica (0.98)
 
 Here is the recursive Postorder traversal:
 Canopus (-0.62)
 Alpha Centauri A (-0.01)
 Arcturus (-0.05)
 Rigel (0.18)
 Procyon (0.4)
 Capella (0.08)
 Vega (0.03)
 Achernar (0.45)
 Hadar (0.61)
 Betelgeuse (0.45)
 Sirius (-1.44)
 Altair (0.76)
 Spica (0.98)
 Aldebaran (0.87)
 Acrux (0.77)
 
 What do you want to do?
 Enter your choice: b
 
 Here is the iterative Breadth First traversal:
 Acrux (0.77)
 Altair (0.76)
 Aldebaran (0.87)
 Sirius (-1.44)
 Spica (0.98)
 Betelgeuse (0.45)
 Vega (0.03)
 Hadar (0.61)
 Arcturus (-0.05)
 Capella (0.08)
 Achernar (0.45)
 Canopus (-0.62)
 Alpha Centauri A (-0.01)
 Procyon (0.4)
 Rigel (0.18)
 
 What do you want to do?
 Enter your choice: t
 Here is the tree in indented form:
 
 3. Spica (0.98)
 2. Aldebaran (0.87)
 1. Acrux (0.77)
 2. Altair (0.76)
 5. Hadar (0.61)
 6. Achernar (0.45)
 4. Betelgeuse (0.45)
 7. Procyon (0.4)
 8. Rigel (0.18)
 6. Capella (0.08)
 5. Vega (0.03)
 7. Alpha Centauri A (-0.01)
 6. Arcturus (-0.05)
 7. Canopus (-0.62)
 3. Sirius (-1.44)
 
 Here is the same tree printed vertically:
 
 1. Acrux (0.77)
 2. Altair (0.76)	             2. Aldebaran (0.87)
 3. Sirius (-1.44)	         3. Spica (0.98)
 4. Betelgeuse (0.45)
 5. Vega (0.03)	   5. Hadar (0.61)
 6. Arcturus (-0.05)	 6. Capella (0.08)	 6. Achernar (0.45)
 7. Canopus (-0.62)	7. Alpha Centauri A (-0.01)	7. Procyon (0.4)
 8. Rigel (0.18)
 
 What do you want to do?
 Enter your choice: r
 
 Enter an element to search in the tree between -1.44 and 0.98.
 Enter a minimum value for the range.
 -1
 Now enter a maximum value for the range.
 0
 The elements matching the selected range in the tree are:
 Canopus (-0.62)
 Arcturus (-0.05)
 Alpha Centauri A (-0.01)
 
 What do you want to do?
 Enter your choice: r
 
 Enter an element to search in the tree between -1.44 and 0.98.
 Enter a minimum value for the range.
 0
 Now enter a maximum value for the range.
 1
 The elements matching the selected range in the tree are:
 Vega (0.03)
 Capella (0.08)
 Rigel (0.18)
 Procyon (0.4)
 Betelgeuse (0.45)
 Achernar (0.45)
 Hadar (0.61)
 Altair (0.76)
 Acrux (0.77)
 Aldebaran (0.87)
 Spica (0.98)
 
 What do you want to do?
 Enter your choice: s
 
 Enter an element to search in the tree between -1.44 and 0.98.
 0.87
 0.87 was found in the tree.
 
 What do you want to do?
 Enter your choice: s
 
 Enter an element to search in the tree between -1.44 and 0.98.
 0.01
 0.01 was not found in the tree.
 
 What do you want to do?
 Enter your choice: s
 
 Enter an element to search in the tree between -1.44 and 0.98.
 1
 1 is outside the specified range. Please try again.
 
 Enter an element to search in the tree between -1.44 and 0.98.
 s
 
 Invalid choice. Please try again.
 0.04
 0.04 was not found in the tree.
 
 What do you want to do?
 Enter your choice: m
 What do you want to do?
 S - Search an element in the tree
 D - Traverse the tree depth first
 B - Traverse the tree breadth first
 T - Print the tree in indented form
 R - Display the tree elements within a certain range
 I - Display the tree iteratively
 M - Display this menu again
 Q - Quit the program
 Enter your choice: i
 
 Here is the iterative Preorder traversal:
 Acrux (0.77)
 Altair (0.76)
 Sirius (-1.44)
 Betelgeuse (0.45)
 Vega (0.03)
 Arcturus (-0.05)
 Canopus (-0.62)
 Alpha Centauri A (-0.01)
 Capella (0.08)
 Procyon (0.4)
 Rigel (0.18)
 Hadar (0.61)
 Achernar (0.45)
 Aldebaran (0.87)
 Spica (0.98)
 
 Here is the iterative Inorder traversal:
 Sirius (-1.44)
 Canopus (-0.62)
 Arcturus (-0.05)
 Alpha Centauri A (-0.01)
 Vega (0.03)
 Capella (0.08)
 Rigel (0.18)
 Procyon (0.4)
 Betelgeuse (0.45)
 Achernar (0.45)
 Hadar (0.61)
 Altair (0.76)
 Acrux (0.77)
 Aldebaran (0.87)
 Spica (0.98)
 Acrux (0.77)
 Aldebaran (0.87)
 Spica (0.98)
 
 Here is the iterative Postorder traversal:
 Canopus (-0.62)
 Alpha Centauri A (-0.01)
 Arcturus (-0.05)
 Rigel (0.18)
 Procyon (0.4)
 Capella (0.08)
 Vega (0.03)
 Achernar (0.45)
 Hadar (0.61)
 Betelgeuse (0.45)
 Sirius (-1.44)
 Altair (0.76)
 Spica (0.98)
 Aldebaran (0.87)
 Acrux (0.77)
 
 What do you want to do?
 Enter your choice: q
 Program ended with exit code: 0
*/