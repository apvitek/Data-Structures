//Andrea Borghi
/*========================Documentation=============================================
The HashTable, as part of the wider data structure, allows to keep the search of an
 element stored in the database linear in as many cases as possible. To achieve so,
 the HashTable has a function called Hash which calculates a unique position in the
 array for a key, which in this case is the Star class “Name” field; in the occurrence
 that two different keys result in the same index, the Bucket class allows the HashTable
 to have an extended “overflow” array to store the synonyms of that key. In that case,
 the big O notation for the search becomes linear, but limited in size.
 ==================================================================================*/
// Specification file for the HashTable class

#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include "Star.h"
#include "Bucket.h"

const int TABLE_SIZE = 31;

using namespace std;

class HashTable {
private:
	// Private variables
	Star* table[TABLE_SIZE]; // To store the values corresponding to specific keys
	vector<Bucket *> * bucketList; // To store the container for the synonym keys
	int size; // To store the table's total size
	vector<string> * stats; // To store the table's statistics
	int collisions; // To store the amount of collision

	// Private functions
	int getHashKey(string &value);
	int hash(Star * value);
	int hash(string &value);
	bool insertInBucketList(Star * value);
	bool deleteFromBucketList(Star * value);
	void resetStats() { delete stats; stats = new vector<string>; collisions = 0; };
	int usedElements();

public:
	// Constructor and destructor
	HashTable() : bucketList(new vector<Bucket *>), stats(new vector<string>), size(0), collisions(0) {
		stats->push_back("*** List initialized ***");

		for (int i = 0; i < TABLE_SIZE; ++i) table[i] = NULL;
	}
    
	~HashTable() { delete bucketList; delete stats; }

	// Public functions
	bool insertValue(Star * value);
	bool deleteValue(Star * value);
	Star * searchForKey(string &key);
	void printTableElements(ostream& os);
	void printTableStructure(ostream& os);
	int getSize() { return size; }
	void printStats(ostream& os);
	int getCollisions() { return collisions; }
};