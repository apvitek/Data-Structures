//
//  BigInteger.cpp
//  Data Structures Homework #3
//
//  Created by Andrea Borghi on 5/1/14.
//  Copyright (c) 2014 Andrea Borghi. All rights reserved.
//

#include "BigInteger.h"

// Constants declaration
const string REGEX_PATTERN = "[0-9]"; // To hold the parsing scheme used by Regex

/**~*~*
 Default constructor
 *~**/
BigInteger::BigInteger()
{
    // Instantiate a new ListNode for the head
    head = new ListNode;
    
    // Instantiate the sentinel ListNode
    ListNode * sentinel = new ListNode;
    
    // Set the content of the sentinel node to -1
    sentinel -> integer = -1;
    
    // Set the next pointer in sentinel node to itself
    sentinel -> next = sentinel;
    
    // Set the previous pointer in sentinel node to itself
    sentinel -> previous = sentinel;
    
    // Set the next pointer in head to sentinel node
    head -> next = sentinel;
    
    // Set the tail to the sentinel node
    tail = sentinel;
    
    // Initialize the counter variable
    count = 0;
}

/**~*~*
 Constructor with string which
 calls the default constructor
 *~**/
BigInteger::BigInteger(string bigInteger) : BigInteger()
{
    // Declare an iterator the end of a Regex
    sregex_token_iterator end;
    
    // Set the pattern for a Regex
	regex pattern(REGEX_PATTERN);
    
    // For loop which iterates thorugh a Regex
	for (sregex_token_iterator iter(bigInteger.begin(), bigInteger.end(), pattern); iter != end; ++iter){
		if ((* iter).length() > 0){
            // Extract the element pointed by the iterator to a string
            string iteratorElement = (* iter);
            
            // Cast the result of the iterator to an int and insert it
            // at the end of the new BigInteger
            insertDigitAtEnd(atoi(iteratorElement.c_str()));
		}
	}
}

/**~*~*
 Member function size returns
 the number of elements in the BigInteger
 *~**/
int BigInteger::size() const
{
    return count;
}

/**~*~*
 Member function insertDigitAtEnd inserts
 a new node at the beginning of the BigInteger
 with the int passed in the argument
 *~**/
void BigInteger::insertDigitAtEnd(int digit)
{
    ListNode *newNode;
    
    // Allocate a new node and store digit there
    newNode = new ListNode;
    newNode -> integer = digit;
    
    tail -> next = newNode;
    
    newNode -> next = head -> next;
    
    newNode -> previous = tail;
    
    tail = newNode;
    
    count++;
}

/**~*~*
 Member function insertDigitInFront inserts
 a new node at the end of the BigInteger
 with the int passed as a parameter
 *~**/
void BigInteger::insertDigitInFront(int digit)
{
    ListNode *newNode;
    
    // Allocate a new node and store digit there
    newNode = new ListNode;
    newNode -> integer = digit;
    
    newNode -> previous = head -> next;
    
    newNode -> next = head -> next -> next;
    
    head -> next -> next = newNode;
    
    ++count;
    
    if (count == 1) {
        tail = newNode;
    }
}

/**~*~*
 Member function toString returns
 the string representation of the BigInteger
 *~**/
string BigInteger::toString() const
{
    ListNode *nodePtr; // To move through the list
    int commaCounter = count; // To control wether a comma will be added
    string bigIntegerString; // To store the string representation of a BigInteger
    int scientificNotationCounter = 0;
    
    // Position nodePtr after the sentinel node
    nodePtr = head -> next -> next;
    
    // While nodePtr points to a node, traverse the list
    while (nodePtr != head -> next) {
        // Append the value in this node to the resulting string
        bigIntegerString.append(to_string(nodePtr -> integer));
        
        // Move to the next node.
        nodePtr = nodePtr -> next;
        
        // Decrease commaCounter
        --commaCounter;
        
        ++scientificNotationCounter;
        
        if (scientificNotationCounter <= 25) {
            if (commaCounter % 3 == 0 && nodePtr != tail -> next) {
                bigIntegerString.append(",");
            }
            
        } else {
            bigIntegerString.append(" * E^");
            
            bigIntegerString.append(to_string(count - scientificNotationCounter));
            
            break;
        }
    }
    
    // Return the result string
    return bigIntegerString;
}

/**~*~*
 Member function toString returns
 the int stored in the node at the
 position specified as a parameter
 *~**/
int BigInteger::getIntAtIndex(int index) const
{
    // If the index is beyond the count, return -1
    if (index > count) {
        return -1;
    }
    
    // Declare a pointer to a ListNode
    ListNode * nodePtr;
    
    // If the index is less than half the count, traverse the list forward
    if (index < (count / 2)) {
        // Position nodePtr after the sentinel node
        nodePtr = head -> next -> next;
        
        // While nodePtr points to a node, traverse the list
        while (nodePtr != head -> next && index != 0) {
            // Skip to the next node
            nodePtr = nodePtr -> next;
            
            // Decrease the index
            --index;
        }
    
    // If the index is more than half the count, traverse the list backwards
    } else {
        // Position nodePtr on the tail
        nodePtr = tail;
        
        // Decrease index by the count
        index -= count;
        
        // While nodePtr points to a node, traverse the list
        while (nodePtr != head -> next && index != -1) {
            // Skip to the next node
            nodePtr = nodePtr -> previous;
            
            // Increase the index
            ++index;
        }
    }
    
    return nodePtr -> integer;
}

/**~*~*
 Default destructor
 *~**/
BigInteger::~BigInteger()
{
    ListNode *nodePtr; // To traverse the list
    ListNode *nextNode; // To point to the next node
    
    // Position nodePtr at the sentinel node.
    nodePtr = head -> next -> next;
    
    // While nodePtr is not at the end of the list...
    while (nodePtr -> next != head -> next)
    {
        // Save a pointer to the next node.
        nextNode = nodePtr -> next;
        
        // Delete the current node.
        delete nodePtr;
        
        // Position nodePtr at the next node.
        nodePtr = nextNode;
    }
    
    // Delete teh sentinel node
    delete head -> next;
    
    // Delete the head
    delete head;
}

/**~*~*
 Overloaded = operator
 *~**/
BigInteger BigInteger::operator = (string &right)
{
    return BigInteger(right);
}

/**~*~*
 Overloaded + operator
 *~**/
BigInteger BigInteger::operator + (BigInteger &right)
{
    // Variables declaration
    BigInteger sum; // To store the final sum
    BigInteger * bigger = this; // To store the longest BigInteger
    BigInteger * smaller = &right; // To store the shorter BigInteger
    int elementsSum = 0; // To store the partial elements sum
    int i = 1; // To control the while loop
    int carry = 0; // To store wether a digit is being carried to the next addition
    
    if (this -> count < right.size()) {
        bigger = &right;
        smaller = this;
    }
    
    // Loop that iterates through the elements in the longer BigInteger in reverse order
    while (bigger -> getIntAtIndex(bigger -> size() - i) != -1) {
        // Set the sum equal to the current element of the long BigInteger
        elementsSum = bigger -> getIntAtIndex(bigger -> size() - i);
        
        // If there is an element at the same position in the smaller BigInteger, add it to elementsSum
        if (smaller -> getIntAtIndex(smaller -> size() - i) != -1) elementsSum += smaller -> getIntAtIndex(smaller -> size() - i);
        
        // If there is a digit to carry, add it to elementsSum
        if (carry > 0){
            elementsSum += carry;
            
            // Reset the original variable
            carry = 0;
        }
        
        // If the sum is less or equal than 9, insert it at the beginning of the
        // BigInteger containing the final sum
        if (elementsSum <= 9) {
            sum.insertDigitInFront(elementsSum);
            
            // Reset elementsSum
            elementsSum = 0;
            
        } else {
            // Increase the carry variable
            ++carry;
            
            // Insert the last digit of elementsSum
            sum.insertDigitInFront(elementsSum % 10);
            
            // Reset elementsSum to 1
            elementsSum = 1;
        }
        
        // Increase the counter
        ++i;
    }
    
    // If elementsSum is not zero, insert what is left at the beginning of the
    // BigInteger containing the final sum
    if (elementsSum != 0) sum.insertDigitInFront(elementsSum);
    
    // Return the BigInteger representing the final sum
    return sum;
}

/**~*~*
 Overloaded += operator
 *~**/
BigInteger BigInteger::operator += (BigInteger& right)
{
    return (* this) + right;
}

/**~*~*
 Overloaded * operator
 *~**/
BigInteger BigInteger::operator * (BigInteger &right)
{
    // Variables declaration
    BigInteger product; // To store the BigInteger resulting product
    BigInteger * bigger = this; // To store the longest BigInteger
    BigInteger * smaller = &right; // To store the shortest BigInteger
    int elementsProduct = 0; // To store the partial elements product
    int i = 1; // To control the while loop
    int pos = 0; // To control the for loop
    unsigned long multFactorSmaller = 1; // To hold the multiplication factor for the shorter BigInteger
    unsigned long multFactorBigger = 1; // To hold the multiplication factor for the longer BigInteger
    
    if (this -> count < right.size()) {
        bigger = &right;
        smaller = this;
    }
    
    // Loop that iterates through the elements in the smaller BigInteger in reverse order
    while (smaller -> getIntAtIndex(smaller -> size() - i) != -1){
        // Loop that iterates through the elements in the longer BigInteger in reverse order
        for (pos = bigger -> size() - 1; pos >= 0; --pos) {
            // Set the product equal to the current element of the two BigIntegers to be multiplied
            elementsProduct += ((smaller -> getIntAtIndex(smaller -> size() - i) * multFactorSmaller) * (bigger -> getIntAtIndex(pos) * multFactorBigger));
            
            // Multiply the longer BigInteger multiplication factor
            multFactorBigger *= 10;
        }
        
        // Reset the longer BigInteger multiplication factor
        multFactorBigger = 1;
        
        // Multiply the shorter BigInteger multiplication factor
        multFactorSmaller *= 10;
        
        // Increase the counter
        ++i;
    }
    
    return BigInteger(to_string(elementsProduct));
}

/**~*~*
 Friend function that overloads the << operator
 *~**/
ostream& operator << (ostream& os, const BigInteger& integer)
{
    return os << integer.toString();
}

/**~*~*
 Friend function that overloads the >> operator
 *~**/
istream& operator >> (istream& is, BigInteger& integer)
{
    string integerFromStream;
    
    getline(is, integerFromStream, '\n');
    
    integer = BigInteger(integerFromStream);
    
    return is;
}