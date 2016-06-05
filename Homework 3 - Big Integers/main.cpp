//
//  main.cpp
//  Data Structures Homework #3
//
//  Created by Andrea Borghi on 5/1/14.
//  Copyright (c) 2014 Andrea Borghi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <iomanip>
#include "BigInteger.h"

using namespace std;

// Constants declaration
const string REGEX_PATTERN = "[0-9]+"; // To hold the parsing scheme used by Regex

// Function prototypes
bool copyDataToList(vector<BigInteger *> * bigIntegersList);
void printOperations(ostream& os, BigInteger &first, BigInteger &second, BigInteger &sum, BigInteger &product);

int main(int argc, const char * argv[])
{
    // Variables declaration
    fstream outputFile("/Users/andreaborghi/Documents/DAC - Data Structures/Data Structures Homework #3/Data Structures Homework #3/big_ints_out.txt");
    vector<BigInteger *> * bigIntegersList = new vector<BigInteger *>();
    
    // Call a function to copy data from file to bigIntegersList and check its successful completion
    if(!(copyDataToList(bigIntegersList))){
        cout << "The program will terminate now." << endl;
        
        // Terminate the program if file could not be open
        return -1;
    }
    
    // Print the BigIntegers copied from file
    cout << "The big integers imported from the file are:" << endl;
    
    // Iterate thorugh bigIntegerList and print its content
    for (auto it = bigIntegersList -> begin(); it != bigIntegersList -> end(); ++it) {
        cout << "\t" << *(* it) << endl;
    }
    
    cout << endl;
    
    // Loop to traverse bigIntegersList and perform operations on pairs of BigIntegers
    for (auto it = bigIntegersList -> begin(); it != bigIntegersList -> end(); ++it) {
        // Get the first element
        BigInteger first = *(* it);
        
        // Increase the iterator to point at the next element in the vector
        ++it;
        
        // Get the second element
        BigInteger second = *(* it);
        
        // Compute sum of two elements
        BigInteger sum = first + second;
        
        // Computer product of two elements
        BigInteger product = first * second;
        
        // Call a function to print the results on screen
        printOperations(cout, first, second, sum, product);
        
        // If the output file was open successfully, call a function
        // to print the results on file
        if (outputFile.is_open()) {
            printOperations(outputFile, first, second, sum, product);
        }
    }
    
    // Close the input file
    outputFile.close();
    
    // Deallocate dynamic memory
    delete bigIntegersList;
    
    return 0;
}

/**~*~*
 copyDataToList opens a file, parses its content using
 regular expressions and adds it to the vector passed
 as a parameters. Returns true if copy was successful and
 false if it was not.
 *~**/
bool copyDataToList(vector<BigInteger *> * bigIntegersList){
    fstream inputFile;
    string integerFromFile;
    
    // Open specified file
    inputFile.open("/Users/andreaborghi/Documents/DAC - Data Structures/Data Structures Homework #3/Data Structures Homework #3/big_ints.txt");
    
    // If inputFile was open successfully, change success to 1
    if (!inputFile) {
        cout << "The input file could not be open!" << endl;
        
        return false;
    };
    
    // Loop to copy input data as long as the file can be read
    while (getline(inputFile, integerFromFile, '\n')) {
        sregex_token_iterator end;
        
        regex pattern(REGEX_PATTERN);
        
        for (sregex_token_iterator iter(integerFromFile.begin(), integerFromFile.end(), pattern);iter != end; ++iter){
            if ((*iter).length() > 0){
                string number = (*iter);
                
                bigIntegersList -> push_back(new BigInteger(number));
            }
        }
    }
    
    // Close the input file
    inputFile.close();
    
    return true;
}

/**~*~*
 printOperations prints on the parameter output stream
 two BigIntegers and their sum in an orderly fashion.
 *~**/
void printOperations(ostream& os, BigInteger &first, BigInteger &second, BigInteger &sum, BigInteger &product)
{
    BigInteger * bigger = &first;
    BigInteger * smaller = &second;
    
    if (second > first) {
        bigger = &second;
        
        smaller = &first;
    }
    
    // Code for formatting output
    int spacing = (int)bigger -> toString().length();
    os.setf(ios::fixed);
    right(os);
    
    for (int i = 0; i < 60; ++i) os << "=";
    
    os << endl << endl;
    
    os << "First number" << setw(4) << ":" << setw(spacing + 2) << first << setw(2) << " (" << first.size() << " digits)" << endl;
    os << "Second number" << setw(3) << ":" << setw(spacing + 2) << second << setw(2) << " (" << second.size() << " digits)" << endl;
    os << "Bigger number" << setw(3) << ":" << setw(spacing + 2) << * bigger << setw(2) << " (" << bigger -> size() << " digits)" << endl;
    os << "Sum" << setw(13) << ":" << setw(spacing + 2) << sum << setw(2) << " (" << sum.size() << " digits)" << endl;
    os << "Product" << setw(9) << ":" << setw(spacing + 2) << product << setw(2) << " (" << product.size() << " digits)" << endl << endl;
    
    os << setw(spacing + 5) << first << endl;
    os << "+" << setw(spacing + 4) << second << endl;
    
    for (int i = 0; i < spacing + 5; ++i) os << "-";
    
    os << "\n=" << setw(spacing + 4) << sum << endl << endl;
}