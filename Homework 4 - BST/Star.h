//
//  Star.h
//  Data Structure Final Project
//
//  Created by Andrea Borghi on 5/19/14.
//  Copyright (c) 2014 Andrea Borghi. All rights reserved.
//

#ifndef __Data_Structure_Final_Project__Star__
#define __Data_Structure_Final_Project__Star__

#include <iostream>

using namespace std;

const string DEFAULT = "Unknown";

// Star Class
class Star {
private:
    string name;
    int rank;
    double magnitude;
    string type;
    string constellation;
    
public:
    // Constructors
    Star() : name(DEFAULT), rank(0), magnitude(0.0), type(DEFAULT), constellation(DEFAULT){};
    Star(double m) : name(DEFAULT), rank(0), magnitude(m), type(DEFAULT), constellation(DEFAULT){};
    
    // Setters and getters
    string getName() { return name; }
    void setName(string n) { name = n; }
    int getRank(){ return rank; }
    void setRank(int r) { rank = r; }
    double getMagnitude() { return magnitude; }
    void setMagnitude(double m) { magnitude = m; }
    string getType() { return type; }
    void setType(string t) { type = t; }
    string getConstellation() { return constellation; }
    void setConstellation(string c) { constellation = c; }
    string toString() const { return "#" + to_string(rank) + " - Name: " + name + ", Magnitude: " + to_string(magnitude) + ", Type: " + type + ", Constellation: " + constellation; }
    
    // Overloaded << operator
    friend ostream& operator << (ostream& os, const Star& star) { return os << star.name << " (" << star.magnitude << ")"; }
    
    // Inline definition of overloaded logical operators
    bool operator < (const Star &right){ if (this->magnitude != right.magnitude){ return this->magnitude < right.magnitude;} return this->name > right.name; }
    bool operator > (const Star &right){ return !((* this) < right); }
    bool operator <= (const Star &right){ return !((* this) > right); }
    bool operator >= (const Star &right){ return !((* this) < right); }
    bool operator == (const Star &right){ return this->magnitude == right.magnitude; }
    bool operator != (const Star &right){ return !((*this) == right); }
};

#endif /* defined(__Data_Structure_Final_Project__Star__) */
