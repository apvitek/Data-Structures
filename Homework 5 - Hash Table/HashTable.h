//
//  HashTable.h
//  Data Structures Homework #5
//
//  Created by Andrea Borghi on 6/3/14.
//  Copyright (c) 2014 Andrea Borghi. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include "Star.h"
#include "Bucket.h"

const int TABLE_SIZE = 31;

using namespace std;

template <class T>
class HashTable
{
private:
    // Private variables
    T table[TABLE_SIZE]; // To store the values corresponding to specific keys
    vector<Bucket<T> *> * bucketList; // To store the container for the synonyms
    int size; // To store the table's total size
    vector<string> * stats; // To store the table's statistics
    int collisions; // To store the amount of collision
    
    // Private functions
    int getHomeAddress(string &value);
    int hash(T &value);
    int hash(string &value);
    bool insertInBucketList(T& value);
    bool deleteFromBucketList(T& value);
    void resetStats() { delete stats; stats = new vector<string>; collisions = 0; };
    int usedElements();
    
public:
    // Constructor and destructor
    HashTable(): bucketList(new vector<Bucket<T>*>), stats(new vector<string>), size(0), collisions(0)
    {
        stats->push_back("*** List initialized ***");
        for (int i = 0; i < TABLE_SIZE; ++i) table[i] = NULL;
    }
    
    ~HashTable() { delete bucketList; delete stats; }
    
    // Public functions
    bool insertValue(T &value);
    bool deleteValue(T &value);
    T searchForKey(string &key);
    void printTableElements(ostream& os);
    void printTableStructure(ostream& os);
    int getSize() { return size; }
    void printStats(ostream& os);
    int getCollisions() { return collisions; }
};

// Private member functions
/**~*~*
 The getHomeAddress function contains the logic to
 generate a has value for a string, passed as an argument
 *~**/
template <class T>
int HashTable<T>::getHomeAddress(string &value)
{
    int result = floor(pow((int)value[value.length() - 1] * (int)value[value.length() / 2], 2) / pow((int)value[0], 3));
    
    return result % TABLE_SIZE;
}

/**~*~*
 The hash function is overloaded.
 This version generates a home address
 for the generic object passed as a parameter
 based on its string representation
 *~**/
template <class T>
int HashTable<T>::hash(T &value)
{
    // Convert value to string
    stringstream stream;
    stream << value;
    string objectToString = stream.str();
    
    // Return the computed home address for the string value
    return getHomeAddress(objectToString);
}

/**~*~*
 The hash function is overloaded.
 This version generates a home address
 for the string passed as a parameter
 *~**/
template <class T>
int HashTable<T>::hash(string &value)
{
    // Return the computed home address for the string value
    return getHomeAddress(value);
}

/**~*~*
 The insertInBucketList function is called when
 a collision is detected. It calculates the index for
 a bucket, searches for that bucket in the bucketList
 and adds the value passed as a parameters in that bucket.
 If the bucket exists but it is full, the user is notified
 and the value is not added. If the bucket does not exists,
 it is created.
 *~**/
template <class T>
bool HashTable<T>::insertInBucketList(T& value)
{
    // Compute the value of the bucket's key
    int valueBucketAddress = hash(value) % (TABLE_SIZE);
    
    // Loop to taverse bucketList
    for (auto it = bucketList->begin(); it != bucketList->end(); ++it) {
        // If a bucket is found with the corresponding bucket address, try to insert the value
        // by calling the appropriate bucket's member function
        if ((*it)->getBucketAddress() == valueBucketAddress) {
            // If the insertion operation succeeds, add a new statistic
            if ((*it)->insertValue(value)){
                stringstream ss;
                
                ss << "\t" << value << " is now in bucket " << valueBucketAddress;
                
                stats->push_back(ss.str());
                
                // Increase the Hash Table size
                ++size;
                
                return true;
                
                // If the insertion operation fails, add a new statistic and return false
            } else {
                stats->push_back("\t*** BUCKET FULL! ***");
                
                return false;
            }
        }
    }
    
    // Add a new statistic
    stats->push_back("\tNew bucket will be created with number " + to_string(valueBucketAddress));
    
    // Instantiate a new bucket with the computed bucket address
    Bucket<T> * newBucket = new Bucket<T>(valueBucketAddress);
    
    // Add the parameter value to the new bucket
    newBucket->insertValue(value);
    
    // Insert the new bucket in bucketList
    bucketList->push_back(newBucket);
    
    // Increase the Hash Table size
    ++size;
    
    // Sort bucketList to keep other functions efficient
    sort(bucketList->begin(), bucketList->end(), [](const Bucket<T> * a, const Bucket<T> * b) -> bool
    {
        return a->getBucketAddress() < b->getBucketAddress();
    });
    
    return true;
}

/**~*~*
 The deleteFromBucketList function is called when
 the element that the user desires to delete in not
 found in the main table. The bucket address is computed
 from the value passed as paramenter and searched for
 in the bucketList. If not found, the function returns
 false. Otherwise, the value is deleted from the
 relative bucket.
 *~**/
template <class T>
bool HashTable<T>::deleteFromBucketList(T& value)
{
    // Compute the value of the bucket's key
    int valueBucketAddress = hash(value) % (TABLE_SIZE);
    
    // Loop to taverse bucketList
    for (auto it = bucketList->begin(); it != bucketList->end(); ++it) {
        // If a bucket is found with the corresponding bucket address, try to delete the value
        // by calling the appropriate bucket's member function
        if ((*it)->getBucketAddress() == valueBucketAddress) {
            // If the deletion operation succeeds, add a new statistic
            if ((*it)->deleteValue(value)){
                stringstream ss;
                
                ss << "\t" << value << " was been deleted from bucket " << valueBucketAddress;
                
                stats->push_back(ss.str());
                
                // Decrease the Hash Table size
                --size;
                
                return true;
                
            // If the insertion operation fails, add a new statistic
            } else {
                stats->push_back("\tThe value wasn't found in this bucket");
            }
        }
    }
    
    // If the entire bucket:ist has been traversed with no success, add a new
    // statistic and return false
    stats->push_back("\tThe value could not be found in any of the buckets");
    
    return false;
}

/**~*~*
 The usedElements function calculates
 how many slots contain allocated elements
 in the main Hash Table and returns it
 *~**/
template <class T>
int HashTable<T>::usedElements()
{
    int usedElementsCount = 0;
    
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i] != NULL) ++usedElementsCount;
    }
    
    return usedElementsCount;
}

// Public member functions
/**~*~*
 The insertValue function is called when
 a collision is detected. It calculates the address of
 a bucket, searches for that bucket in the bucketList
 and adds the value passed as a parameters in that bucket.
 If the bucket exists but is full, the user is notified
 and the value is not added. If the bucket does not exists,
 it is created.
 *~**/
template <class T>
bool HashTable<T>::insertValue(T &value)
{
    // Add a new statistic
    stringstream ss;
    ss << "Inserting " << value << "...";
    stats->push_back(ss.str());
    
     // Compute the key value of the paramenter element
    int homeAddress = hash(value);
    
    // If the computer home address is too big for the table size,
    // add a new statistic and return false
    if (homeAddress < 0 || homeAddress > TABLE_SIZE) {
        stats->push_back(to_string(homeAddress) + " is too big");
        
        return false;
    }
    
    // If the value contained at the specified home address in
    // the main table is not set, place the parameter value there
    if (table[homeAddress] == NULL) {
        table[homeAddress] = value;
        
        // Increase the size of the Hash Table
        ++size;
        
        // Add a new statistic
        stats->push_back("\tThe home address is " + to_string(homeAddress));
        
    } else {
        // Add a new statistic informing the user that a collision happened
        stats->push_back("\tCollision! Home address " + to_string(homeAddress) + " already exists in the Hash Table");
        
        // Increase the amount of collision in the list
        ++collisions;
        
        // Return the result of calling the private member function
        // to insert the parameter value in bucketList
        return insertInBucketList(value);
    }
    
    return true;
}

/**~*~*
 The deleteValue function is called when
 the element that the user desires to delete in not
 found in the main table. The bucket address is computed
 from the value passed as paramenter and searched for
 in the bucketList. If not found, the function returns
 false. Otherwise, the value is deallocated from the
 relative bucket.
 *~**/
template <class T>
bool HashTable<T>::deleteValue(T& value)
{
    // Add a new statistic
    stringstream ss;
    ss << "Deleting " << value << "...";
    stats->push_back(ss.str());
    
    // Compute the home address of the paramenter element
    int homeAddress = hash(value);
    
    // If the computed home address is too big for the table size,
    // add a new statistic and return false
    if (homeAddress < 0 || homeAddress > TABLE_SIZE) {
        stats->push_back(to_string(homeAddress) + " is too big");
        
        return false;
    }
    
    // If the value contained at the specified home address index
    // in the main table is identical to the paramenter value,
    // delete it
    if (table[homeAddress] == value) {
        delete table[homeAddress];
        
        // Decrease the size of the Hash Table
        --size;
        
        // Add a new statistic
        stats->push_back("Deleted");
        
    } else {
        // Add a new statistic informing the user that a collision happened
        stats->push_back(value + " is not the main Hash Table. Searching the buckets...");
        
        // Return the result of calling the private member function
        // to delete the parameter value from bucketList
        return insertInBucketList(value);
    }
    
    return true;
}

/**~*~*
 The searchForKey function searches for a value
 in the Hash Table which has a string representation
 identical to the key passed a string parameter and
 returns the object if found, and null if not found
 *~**/
template <class T>
T HashTable<T>::searchForKey(string &key)
{
    // Compute the string representation of the object contained
    // at the index specified by the parameter key
    stringstream stream;
    stream << table[hash(key)];
    string objectToString = stream.str();
    
    // If the string representation of the object at the index
    // key in the main Hash Table is identical to the key, return it
    if (objectToString == key) {
        return table[hash(key)];
        
        // Otherwise, search for the value in the buckets
    } else {
        int valueBucketAddress = hash(key) % (TABLE_SIZE);
        int index = -1;
        
        // Loop that iterates thorugh bucketList
        for (auto it = bucketList->begin(); it != bucketList->end(); ++it) {
            // If the computed bucket address is smaller than the current bucket
            // address, interrupt the search as the bucket sought for does not exist.
            // This is guaranteed because the bucketList is kept sorter in ascending
            // order by each bucket's key
            if (valueBucketAddress < (*it)->getBucketAddress()) break;
            
            // If a bucket is found with the corresponding address, try to search for the value
            // by calling the appropriate bucket's member function
            if (valueBucketAddress == (*it)->getBucketAddress()) {
                if ((*it)->containsValue(key, index)) return (*it)->getValueAtIndex(index);
            }
        }
    }
    
    return NULL;
}

/**~*~*
 The printTableElements function prints the contents
 in the Hash Table in an ordinate fashion to the
 output stream
 *~**/
template <class T>
void HashTable<T>::printTableElements(ostream& os)
{
    // Loop that iterates through the main table and prints its content
    // if it is not NULL
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i] != NULL) os << "\t" << table[i] << endl;
    }
    
    // Loop that iterates thorugh bucketList and calls its element's
    // member function to print their content to the output stream
    for (auto it = bucketList->begin(); it != bucketList->end(); ++it) {
        (*it)->printBucketElements(os);
    }
}

/**~*~*
 The printTableElements function prints the contents
 in the Hash Table to the output stream highlighting
 their position in the table internal organization,
 including elements which are not allocated
 *~**/
template <class T>
void HashTable<T>::printTableStructure(ostream& os)
{
    os << "Now printing the main table:" << endl;
    
    for (int i = 0; i < TABLE_SIZE; ++i) {
        (table[i] != NULL) ? os << "\t" << i <<". " << table[i] << endl : os << "\t" << i <<". [Empty slot]" << endl;
    }
    
    os << endl << "Now printing the buckets:" << endl;
    
    for (auto it = bucketList->begin(); it != bucketList->end(); ++it) {
        (*it)->printBucketStructure(os);
    }
}

/**~*~*
 The printStats function prints the statistics
 in the Hash Table in an ordinate fashion to the
 output stream
 *~**/
template <class T>
void HashTable<T>::printStats(ostream& os)
{
    int usedElems = usedElements();
    double loadFactor = (usedElems * 100) / TABLE_SIZE;

    os << "Here are the HashTable stats:" << endl << endl;
    
    for (auto it = stats->begin(); it != stats->end(); ++it) {
        os << (*it) << endl;
    }
    
    os << "\nTotal amount of elements: " << size << endl;
    
    os << "\nMain HashTable size: " << TABLE_SIZE << endl;
    os << "\tUsed elements: " << usedElems << "\t(Load factor: " << loadFactor << "%)" << endl;
    
    os << "\nNumber of buckets: " << bucketList->size() << endl;
    
    int fullBuckets = 0;

    for (auto it = bucketList->begin(); it != bucketList->end(); ++it) {
        int numElems = (*it)->getNumElements();
        int bucketSize = (*it)->size();
        loadFactor = (numElems * 100) / bucketSize;
        
        os << "\tBucket with address " << (*it)->getBucketAddress() << " has " << numElems << " elements out of " << bucketSize
        << "\t(Load factor: " << loadFactor << "%)" << endl;
        
        if ((*it)->isFull()) ++fullBuckets;
    }
    
    os << "Full buckets: " << fullBuckets << endl;
    
    os << "\nTotal collisions while buiding the list: " << collisions << endl;
}