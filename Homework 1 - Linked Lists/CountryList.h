// Specification file for the CountryList class
#ifndef COUNTRYLIST_H
#define COUNTRYLIST_H

#include <string>
using namespace std;

const int COUNTRY_CODE_SIZE = 3; // 2 + \0

struct Country
{
    char code[COUNTRY_CODE_SIZE];
    string name;
    string capital;
    int population;
};

class CountryList
{
private:
    // Declare a structure for the list
    struct ListNode
    {
        Country country;        // The value in this node
        ListNode *next;         // To point to the next node
    };
    
    ListNode *head;            // List head pointer
    int count;
    
public:
    // Constructor
    CountryList();
    
    // Destructor
    ~CountryList();
    
    // Linked list operations
    void insertNode(Country countryIn);
    bool deleteNode(Country &countryData);
    bool searchNode(Country &countryData);
    void displayList() const;
    
    int size() const;
    bool searchLetterInCapital(char &letter);
    
};
#endif
