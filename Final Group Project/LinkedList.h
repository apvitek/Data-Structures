//
//  LinkedList.h
//  Data Structure Final Project
//
//  Created by Andrea Borghi on 5/19/14.
//  Copyright (c) 2014 Andrea Borghi. All rights reserved.
//

#ifndef __Data_Structure_Final_Project__LinkedList__
#define __Data_Structure_Final_Project__LinkedList__

#include <iostream>

using namespace std;

template <class T>
class LinkedList {
private:
    // Declare a structure for the list
    struct ListNode
    {
        T data;
        ListNode * next;
    };
    
    ListNode * head;
    int count;
    
public:
    // Constructor
    LinkedList();
    
    // Destructor
    ~LinkedList();
    
    // Linked list operations
    void insertNode(T dataIn);
    bool deleteNode(T &data);
    bool searchNode(T &data);
    void displayList() const;
    int size() const;
    
};

// Implementation file for the LinkedList class

using namespace std;

//**************************************************
// Constructor                                     *
//**************************************************
template <class T>
LinkedList<T>::LinkedList()
{
    // Instantiate a new ListNode for the head
    head = new ListNode;
    
    // Instantiate the sentinel ListNode
    ListNode * sentinel = new ListNode;
    
    // Set the next pointer in sentinel node to NULL
    sentinel->next = NULL;
    
    // Set the next pointer in head to sentinel node
    head->next = sentinel;
    
    // Initialize the counter variable
    count = 0;
}

//**************************************************
// displayList shows the value                     *
// stored in each node of the linked list          *
// pointed to by head.                             *
//**************************************************
template <class T>
void LinkedList<T>::displayList() const
{
    ListNode * nodePtr;  // To move through the list
    
    // Position nodePtr after the sentinel node.
    nodePtr = head->next->next;
    
    // While nodePtr points to a node, traverse the list.
    while (nodePtr != NULL)
    {
        // Display the value in this node in columns.
        cout << nodePtr->data << endl;
        
        // Move to the next node.
        nodePtr = nodePtr->next;
    }
}

//**************************************************
// The searchNode function searches for a node     *
// with nodeData.code. If the node was found       *
// then true is returned and the T data of   *
// node found is returned in nodeData. If the node *
// was not found, then false is returned and       *
// nodeData reference variable is unchanged.       *
//**************************************************
template <class T>
bool LinkedList<T>::searchNode(T &nodeData)
{
    ListNode * nodePtr;            // To traverse the list
    
    // Position nodePtr at the head of list.
    nodePtr = head;
    
    // Skip all nodes that doesn't matches code of nodeData
    while (nodePtr != NULL && nodePtr->data != nodeData)
    {
        // Move to the next node
        nodePtr = nodePtr->next;
    }
    
    // If nodePtr is NULL (not found)
    if (!nodePtr)
        return false;
    
    // Load nodeData with data from the found node
    nodeData = nodePtr->T;
    return true;
}

//**************************************************
// The insertNode function inserts a node with     *
// TIn copied to its T member.         *
//**************************************************
template <class T>
void LinkedList<T>::insertNode(T dataIn)
{
    ListNode *newNode;             // A new node
    ListNode *nodePtr;             // To traverse the list
    ListNode *previousNode = NULL; // The previous node
    
    // Allocate a new node and store TIn there.
    newNode = new ListNode;
    newNode->data = dataIn;
    
    // Position nodePtr at sentinel node.
    nodePtr = head->next;
    
    // Initialize previousNode to head.
    previousNode = nodePtr;
    
    // Skip all nodes whose value is less than code.
    while (nodePtr != NULL && nodePtr->data < dataIn)
    {
        previousNode = nodePtr;
        nodePtr = nodePtr->next;
    }
    
    newNode->next = previousNode->next;
    
    previousNode->next = newNode;
    
    // Increase counter
    count++;
}

//**************************************************
// The deleteNode function searches for a node     *
// with the same code in nodeData. If node is found*
// it is deleted from the list and from memory. The*
// function returns true if node was deleted & the *
// node to delete T information is returned  *
// in nodeData. If node to delete is not found (or *
// there is nothing to delete) then a false is     *
// returned.                                       *
//**************************************************
template <class T>
bool LinkedList<T>::deleteNode(T &nodeData)
{
    ListNode * nodePtr;       // To traverse the list
    ListNode * previousNode;  // To point to the previous node
    
    // Initialize nodePtr to sentinel node
    nodePtr = head->next;
    previousNode = NULL;
    
    // Skip all nodes whose code is not equal to the code pointed by pDeleteCode.
    while (nodePtr != NULL && nodePtr->T != nodeData)
    {
        previousNode = nodePtr;
        nodePtr = nodePtr->next;
    }
    
    // If node-to-delete not found OR no nodes
    if (!nodePtr)
        return false;
    
    // otherwise (node-to-delete found & not first node)
    nodeData = nodePtr->data;  // return the deleted data
    previousNode->next = nodePtr->next;
    delete nodePtr;
    
    count--;
    return true;
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************
template <class T>
LinkedList<T>::~LinkedList()
{
    ListNode * nodePtr;   // To traverse the list
    ListNode * nextNode;  // To point to the next node
    
    // Position nodePtr at the dummy node.
    nodePtr = head->next;
    
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
    
    delete head;
}

//**************************************************
// The size function return the size of the list.  *
//**************************************************
template <class T>
int LinkedList<T>::size()const
{
    return count;
}

#endif /* defined(__Data_Structure_Final_Project__LinkedList__) */
