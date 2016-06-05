//
//  BigInteger.h
//  Data Structures Homework #3
//
//  Created by Andrea Borghi on 5/1/14.
//  Copyright (c) 2014 Andrea Borghi. All rights reserved.
//

#ifndef __Data_Structures_Homework__3__BigInteger__
#define __Data_Structures_Homework__3__BigInteger__

#include <iostream>
#include <regex>
#include <sstream>

using namespace std;

class BigInteger {
private:
    struct ListNode {
        int integer;
        ListNode * next;
        ListNode * previous;
    };
    
    ListNode * head;
    ListNode * tail;
    int count;
    
public:
    BigInteger();
    BigInteger(string bigInteger);
    int size() const;
    void insertDigitAtEnd(int digit);
    void insertDigitInFront(int digit);
    string toString() const;
    int getIntAtIndex(int index) const;
    ~BigInteger();
    
    // Overloaded operators
    BigInteger operator = (string& right);
    BigInteger operator + (BigInteger& right);
    BigInteger operator += (BigInteger& right);
    BigInteger operator * (BigInteger& right);
    friend ostream& operator << (ostream& os, const BigInteger& integer);
    friend istream& operator >> (istream& is, BigInteger& integer);
    
    // Inline definition of overloaded logical operators
    bool operator < (const BigInteger &right){if (this -> count != right.count){return this -> count > right.count;} else {return this -> getIntAtIndex(0) > right.getIntAtIndex(0);}};
    bool operator > (const BigInteger &right){return (* this) < right;};
    bool operator <= (const BigInteger &right){return !((* this) > right);};
    bool operator >= (const BigInteger &right){return !((* this) < right);};
    bool operator == (const BigInteger &right){return this -> toString() == right.toString();};
    bool operator != (const BigInteger &right){return (*this) == right;};
};

#endif /* defined(__Data_Structures_Homework__3__BigInteger__) */
