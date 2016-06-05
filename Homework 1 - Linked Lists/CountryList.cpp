// Implementation file for the CountryList class
#include <iostream>  // For cout and NULL
#include <iomanip>   // For setw()
#include <cstring>   // For strcmp()
#include "CountryList.h"

using namespace std;

//**************************************************
// Constructor                                     *
//**************************************************
CountryList::CountryList()
{
    // Instantiate a new ListNode for the head
    head = new ListNode;
    
    // Instantiate the sentinel ListNode
    ListNode * sentinel = new ListNode;
    
    // Set the next pointer in sentinel node to NULL
    sentinel -> next = NULL;
    
    // Set the next pointer in head to sentinel node
    head -> next = sentinel;
    
    // Initialize the counter variable
    count = 0;
}

//**************************************************
// displayList shows the value                     *
// stored in each node of the linked list          *
// pointed to by head.                             *
//**************************************************

void CountryList::displayList() const
{
    //int longestName = 0;
    //int longestCapital = 0;
    ListNode *nodePtr;  // To move through the list
    
    // Display the header
    cout << left << "CODE  " << setw(20)
    << "COUNTRY_NAME" << setw(15)
    << "CAPITAL" << "     POPULATION\n";
    
    // Position nodePtr after the sentinel node.
    nodePtr = head -> next -> next;
    
    // While nodePtr points to a node, traverse the list.
    while (nodePtr != NULL)
    {
        // Display the value in this node in columns.
        cout << left << setw(6)   << nodePtr->country.code
        << setw(20)          << nodePtr->country.name
        << setw(15)          << nodePtr->country.capital
        << right << setw(15) << nodePtr->country.population << endl;
        
        // Move to the next node.
        nodePtr = nodePtr->next;
    }
}

//**************************************************
// The searchNode function searches for a node     *
// with nodeData.code. If the node was found       *
// then true is returned and the Country data of   *
// node found is returned in nodeData. If the node *
// was not found, then false is returned and       *
// nodeData reference variable is unchanged.       *
//**************************************************
bool CountryList::searchNode(Country &nodeData)
{
    ListNode *nodePtr;            // To traverse the list
    
    // Position nodePtr at the head of list.
    nodePtr = head;
    
    // Skip all nodes that doesn't matches code of nodeData
    while (nodePtr != NULL && strcmp(nodePtr->country.code, nodeData.code) != 0)
    {
        // Move to the next node
        nodePtr = nodePtr->next;
    }
    
    // If nodePtr is NULL (not found)
    if (!nodePtr)
        return false;
    
    // Load nodeData with data from the found node
    nodeData = nodePtr->country;
    return true;
}

//**************************************************
// The insertNode function inserts a node with     *
// countryIn copied to its country member.         *
//**************************************************

void CountryList::insertNode(Country countryIn)
{
    ListNode *newNode;             // A new node
    ListNode *nodePtr;             // To traverse the list
    ListNode *previousNode = NULL; // The previous node
    
    // Allocate a new node and store countryIn there.
    newNode = new ListNode;
    newNode->country = countryIn;
    
    // Position nodePtr at sentinel node.
    nodePtr = head -> next;
    
    // Initialize previousNode to head.
    previousNode = nodePtr;
    
    // Skip all nodes whose value is less than code.
    while (nodePtr != NULL && strcmp(nodePtr->country.code, countryIn.code) < 0)
    {
        previousNode = nodePtr;
        nodePtr = nodePtr->next;
    }
    
    newNode -> next = previousNode -> next;
    
    previousNode -> next = newNode;
    
    // Increase counter
    count++;
}

//**************************************************
// The deleteNode function searches for a node     *
// with the same code in nodeData. If node is found*
// it is deleted from the list and from memory. The*
// function returns true if node was deleted & the *
// node to delete country information is returned  *
// in nodeData. If node to delete is not found (or *
// there is nothing to delete) then a false is     *
// returned.                                       *
//**************************************************

bool CountryList::deleteNode(Country &nodeData)
{
    ListNode *nodePtr;       // To traverse the list
    ListNode *previousNode;  // To point to the previous node
    
    // Initialize nodePtr to sentinel node
    nodePtr = head -> next;
    previousNode = NULL;
    
    // Skip all nodes whose code is not equal to the code pointed by pDeleteCode.
    while (nodePtr != NULL && strcmp(nodePtr->country.code, nodeData.code) != 0)
    {
        previousNode = nodePtr;
        nodePtr = nodePtr->next;
    }
    
    // If node-to-delete not found OR no nodes
    if (!nodePtr)
        return false;
    
    // otherwise (node-to-delete found & not first node)
    nodeData = nodePtr->country;  // return the deleted data
    previousNode->next = nodePtr->next;
    delete nodePtr;
    
    count--;
    return true;
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

CountryList::~CountryList()
{
    ListNode *nodePtr;   // To traverse the list
    ListNode *nextNode;  // To point to the next node
    
    // Position nodePtr at the head of the list.
    nodePtr = head;
    
    // While nodePtr is not at the end of the list...
    while (nodePtr != NULL)
    {
        // Save a pointer to the next node.
        nextNode = nodePtr->next;
        
        // Delete the current node.
        delete nodePtr;
        
        // Position nodePtr at the next node.
        nodePtr = nextNode;
    }
}

//**************************************************
// The size function return the size of the list.  *
//**************************************************

int CountryList::size()const
{
    return count;
}

//**************************************************
// The searchLetterInCapital function searches for *
// a node with a nodeData containing a variable    *
// Capital which containes the character specified *
// in the paramenter. Whenever scondition occurs,  *
// the node's Capital field is printed on screen   *
// and the function returns true. If no node satis-*
// fying this condition is  found, the function    *
// returns false.                                  *
//**************************************************

bool CountryList::searchLetterInCapital(char &letter)
{
    // Variable declarations
    ListNode *nodePtr;            // To traverse the list
    char letterOtherCase;         // To store the lowercase or uppcercase version of the char input parameter
    bool found = false;           // To store wether the letter was found or not
    
    // Assign other the other case of the character parameter to letterOtherCase
    isupper(letter) ? letterOtherCase = tolower(letter) : letterOtherCase = toupper(letter);
    
    // Position nodePtr at the head of list.
    nodePtr = head;
    
    // Traverse the entire list
    while (nodePtr != NULL)
    {
        // Store the country capital of the current node in a temporary string
        string capitalName = nodePtr->country.capital;
        
        // Loop to iterate through the characters of the string
        for (int i = 0; i < capitalName.length(); ++i)
        {
            if (capitalName[i] == letter || capitalName[i] == letterOtherCase)
            {
                // Display the string containing the parameter character
                cout << capitalName << endl;
                
                // Set the boolean flag to true
                found = true;
                
                // In case more of the same letters are in the word, break to avoid repetitions
                break;
            }
        }
        
        // Move to the next node
        nodePtr = nodePtr->next;
    }
    
    return found;
}