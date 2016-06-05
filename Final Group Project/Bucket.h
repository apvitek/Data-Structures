//Andrea Borghi
//Declaration file for the Bucket class

#include <iostream>
#include <sstream>
#include "Star.h"

using namespace std;

const int BUCKET_SIZE = 4;

class Bucket {
private:
	Star * duplicateList[BUCKET_SIZE]; // To store the synonym keys
	int bucketKey; // To store the key of the bucket
	int numElements; // To store the amount of elements in the bucket
	bool full; // To store wether the bucket is full

public:
	// Constructor
	Bucket(int bucketK) : bucketKey(bucketK), numElements(0), full(false){
        for (int i = 0; i < BUCKET_SIZE; ++i) duplicateList[i] = NULL;
    };

	// Public methods
	bool insertValue(Star * value);
	bool eraseValue(Star * value);
	int size() { return BUCKET_SIZE; }
	bool isFull() { return full; }
	int getNumElements() const { return numElements; }
	int getBucketKey() const { return bucketKey; }
	bool containsValue(string& value, int& index);
	Star * getValueAtIndex(int i);
	void printBucketElements(ostream& os);
	void printBucketStructure(ostream& os);
};