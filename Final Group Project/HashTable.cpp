//Andrea Borghi
// Implementation file for the HashTable class

#include "HashTable.h"

// Private member functions
/**~*~*
 The getHashKey function contains the logic to
 generate a Hash Key for a string, passed as an argument
 *~**/
int HashTable::getHashKey(string &value)
{
    int result = floor(pow((int)value[value.length() - 1] * (int)value[value.length() / 2], 2) / pow((int)value[0], 3));
    
    return result % TABLE_SIZE;
}

/**~*~*
 The hash function is overloaded.
 This version generates a Hash Key
 for the generic object passed as a parameter
 based on its string representation
 *~**/
int HashTable::hash(Star * value)
{
    // Convert value to string
    stringstream stream;
    stream << *value;
    string objectToString = stream.str();
    
    // Return the computer key for the string value
    return getHashKey(objectToString);
}

/**~*~*
 The hash function is overloaded.
 This version generates a Hash Key
 for the string passed as a parameter
 *~**/
int HashTable::hash(string &value)
{
    // Return the computer key for the string value
    return getHashKey(value);
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
bool HashTable::insertInBucketList(Star * value)
{
    // Compute the value of the bucket's key
    int valueBucketKey = hash(value) % (TABLE_SIZE);
    
    // Loop to taverse bucketList
    for (auto it = bucketList->begin(); it != bucketList->end(); ++it) {
        // If a bucket is found with the corresponding bucket key, try to insert the value
        // by calling the appropriate bucket's member function
        if ((*it)->getBucketKey() == valueBucketKey) {
            // If the insertion operation succeeds, add a new statistic
            if ((*it)->insertValue(value)){
                stringstream ss;
                
                ss << "\t" << *value << " is now in bucket " << valueBucketKey;
                
                stats->push_back(ss.str());
                
                // Increase the Hash Table size
                ++size;
                
                return true;
                
                // If the insertion operation fails, add a new statistic and return false
            }
            else {
                stats->push_back("\t*** BUCKET FULL! ***");
                
                return false;
            }
        }
    }
    
    // Add a new statistic
    stats->push_back("\tNew bucket will be created with number " + to_string(valueBucketKey));
    
    // Instantiate a new bucket with the computed bucket key
    Bucket * newBucket = new Bucket(valueBucketKey);
    
    // Add the parameter value to the new bucket
    newBucket->insertValue(value);
    
    // Insert the new bucket in bucketList
    bucketList->push_back(newBucket);
    
    // Increase the Hash Table size
    ++size;
    
    // Sort bucketList to keep other functions efficient
    sort(bucketList->begin(), bucketList->end(), [](const Bucket * a, const Bucket * b) -> bool
         {
             return a->getBucketKey() < b->getBucketKey();
         });
    
    return true;
}

/**~*~*
 The deleteFromBucketList function is called when
 the element that the user desires to delete in not
 found in the main table. The bucket key is computed
 from the value passed as paramenter and searched for
 in the bucketList. If not found, the function returns
 false. Otherwise, the value is deallocated from the
 relative bucket.
 *~**/
bool HashTable::deleteFromBucketList(Star * value)
{
    // Compute the value of the bucket's key
    int valueBucketKey = hash(value) % (TABLE_SIZE);
    
    // Loop to taverse bucketList
    for (auto it = bucketList->begin(); it != bucketList->end(); ++it) {
        // If a bucket is found with the corresponding bucket key, try to delete the value
        // by calling the appropriate bucket's member function
        if ((*it)->getBucketKey() == valueBucketKey) {
            // If the deletion operation succeeds, add a new statistic
            if ((*it)->eraseValue(value)){
                stringstream ss;
                
                ss << "\t" << *value << " was been deleted from bucket " << valueBucketKey;
                
                stats->push_back(ss.str());
                
                // Decrease the Hash Table size
                --size;
                
                return true;
                
                // If the insertion operation fails, add a new statistic
            }
            else {
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
int HashTable::usedElements()
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
 a collision is detected. It calculates the index for
 a bucket, searches for that bucket in the bucketList
 and adds the value passed as a parameters in that bucket.
 If the bucket exists but is full, the user is notified
 and the value is not added. If the bucket does not exists,
 it is created.
 *~**/
bool HashTable::insertValue(Star * value)
{
    // Add a new statistic
    stringstream ss;
    ss << "Inserting " << *value << "...";
    stats->push_back(ss.str());
    
    // Compute the key value of the paramenter element
    int key = hash(value);
    
    // If the computer key is too big for the table size, add
    // a new statistic and return false
    if (key < 0 || key > TABLE_SIZE) {
        stats->push_back(to_string(key) + " is too big");
        
        return false;
    }
    
    // If the value contained at the specified key index in
    // the main table is not set, place the parameter value there
    if (table[key] == NULL) {
        table[key] = value;
        
        // Increase the size of the Hash Table
        ++size;
        
        // Add a new statistic
        stats->push_back("\tThe key is " + to_string(key));
        
    }
    else {
        // Add a new statistic informing the user that a collision happened
        stats->push_back("\tCollision! Key " + to_string(key) + " already exists in the Hash Table");
        
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
 found in the main table. The bucket key is computed
 from the value passed as paramenter and searched for
 in the bucketList. If not found, the function returns
 false. Otherwise, the value is deallocated from the
 relative bucket.
 *~**/
bool HashTable::deleteValue(Star * value)
{
    // Add a new statistic
    stringstream ss;
    if (value)
    {
        
        ss << "Deleting " << *value << "...";
        stats->push_back(ss.str());
        
        // Compute the key value of the paramenter element
        int key = hash(value);
        
        // If the computer key is too big for the table size, add
        // a new statistic and return false
        if (key < 0 || key > TABLE_SIZE) {
            stats->push_back(to_string(key) + " is too big");
            
            return false;
        }
        
        // If the value contained at the specified key index in
        // the main table is identical to the paramenter value,
        // delete it
        if (table[key] == value) {
            delete table[key];
            
            table[key] = NULL;
            
            // Decrease the size of the Hash Table
            --size;
            
            // Add a new statistic
            stats->push_back("Deleted");
            
        }
        else {
            // Add a new statistic informing the user that a collision happened
            stats->push_back("The value is not the main Hash Table. Searching the buckets...");
            
            // Return the result of calling the private member function
            // to delete the parameter value from bucketList
            return deleteFromBucketList(value);
        }
        return true;
    }
    else
    {
        return false;
    }
}

/**~*~*
 The searchForKey function searches for a value
 in the Hash Table which has a string representation
 identical to the key passed a string parameter and
 returns the object if found, and null if not found
 *~**/
Star * HashTable::searchForKey(string &key)
{
    // Compute the string representation of the object contained
    // at the index specified by the parameter key
    if (!table[hash(key)]) return NULL;
    
    stringstream stream;
    stream << * table[hash(key)];
    string objectToString = stream.str();
    
    // If the string representation of the object at the index
    // key in the main Hash Table is identical to the key, return it
    if (objectToString == key) {
        return table[hash(key)];
        
        // Otherwise, search for the value in the buckets
    }
    else {
        int valueBucketKey = hash(key) % (TABLE_SIZE);
        int index = -1;
        
        // Loop that iterates thorugh bucketList
        for (auto it = bucketList->begin(); it != bucketList->end(); ++it) {
            // If the computed value key is smaller than the current bucket
            // key, interrupt the search as the bucket sought for does not exist.
            // This is guaranteed because the bucketList is kept sorter in ascending
            // order by each bucket's key
            if (valueBucketKey < (*it)->getBucketKey()) break;
            
            // If a bucket is found with the corresponding bucket key, try to search for the value
            // by calling the appropriate bucket's member function
            if (valueBucketKey == (*it)->getBucketKey()) {
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
void HashTable::printTableElements(ostream& os)
{
    // Loop that iterates through the main table and prints its content
    // if it is not NULL
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i] != NULL) os << "\t" << table[i]->toString() << endl;
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
void HashTable::printTableStructure(ostream& os)
{
    os << "Now printing the main table:" << endl;
    
    for (int i = 0; i < TABLE_SIZE; ++i) {
        (table[i] != NULL) ? os << "\t" << i << ". " << *table[i] << endl : os << "\t" << i << ". [Empty slot]" << endl;
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
void HashTable::printStats(ostream& os)
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
        
        os << "\tBucket with key " << (*it)->getBucketKey() << " has " << numElems << " elements out of " << bucketSize
        << "\t(Load factor: " << loadFactor << "%)" << endl;
        
        if ((*it)->isFull()) ++fullBuckets;
    }
    
    os << "Full buckets: " << fullBuckets << endl;
    
    os << "\nTotal collisions while building the list: " << collisions << endl;
}