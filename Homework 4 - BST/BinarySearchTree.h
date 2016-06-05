//
//  BinarySearchTree.h
//  Data Structures Homework #4
//
//  Created by Andrea Borghi on 5/17/14.
//  Copyright (c) 2014 Andrea Borghi. All rights reserved.
//

#ifndef __Data_Structures_Homework__4__BinarySearchTree__
#define __Data_Structures_Homework__4__BinarySearchTree__

#include <iostream>
#include <queue>
#include <stack>
#include <iomanip>
#include <cmath>

using namespace std;

template <class T>
class TreeNode {
public:
    T data; // To store the node's data
    TreeNode<T> * left; // To store the address of the left child
    TreeNode<T> * right; // To store the address of the right child
    
    // Default constructor
    TreeNode(T d) { data = d; left = NULL; right = NULL; }
};

template <class T>
class BinarySearchTree {
private:
    TreeNode<T> * root; // To store the address of the root node
    int elementsNumber; // To store the amount of nodes in the tree
    int height; // To store the height of the tree
    
    // Private member functions
    TreeNode<T> * insertNode (T newNode, TreeNode<T> * startingNode);
    TreeNode<T> * eraseNode (T node, TreeNode<T> * startingNode);
    bool findNode(T node, TreeNode<T> * startingNode);
    void preorder(TreeNode<T> * startingNode, ostream& os);
    void inorder(TreeNode<T> * startingNode, ostream& os);
    void postorder(TreeNode<T> * startingNode, ostream &os);
    void breadthFirst(TreeNode<T> * startingNode, ostream &os);
    void range(T& min, T& max, TreeNode<T> * startingNode, ostream &os);
    void printIndentedSideways(TreeNode<T> * startingNode, int indent, ostream& os);
    int findHeight(TreeNode<T> * startingNode);
    T findMin(TreeNode<T> * startingNode);
    T findMax(TreeNode<T> * startingNode);
    void deleteTree(TreeNode<T> * startingNode);
    
public:
    // Constructor
    BinarySearchTree() : root(NULL), elementsNumber(0) {}
    
    // Destructor
    ~BinarySearchTree() { deleteTree(root); }
    
    // Public member functions
    bool isEmpty(){ return (root); }
    int getElementsNumber() { return elementsNumber; }
    bool addNode(T data) { return (insertNode(data, root)); }
    bool deleteNode (T data) { return (eraseNode(data, root)); }
    bool searchNode (T data) { return (findNode(data, root)); }
    void displayTree(ostream& os) {printIndentedSideways(root, 0, os); }
    
    // Recursive traversals
    void printPreorder(ostream& os) { preorder(root, os); }
    void printInorder(ostream& os) { inorder(root, os); }
    void printPostorder(ostream& os) { postorder(root, os); }
    void printBreadthFirst(ostream& os) { breadthFirst(root, os); }
    void printRange(T& min, T& max, ostream& os) { range(min, max, root, os); }
    void displayTreeVertically(ostream& os);
    
    // Utility functions
    int getHeight() { return height; };
    T getSmallest() { return findMin(root); }
    T getLargest() { return findMax(root); }
    
    // Iterative traversals
    void iterativePreorder(ostream& os);
    void iterativeInorder(ostream& os);
    void iterativePostorder(ostream& os);
};

// Private functions
/**~*~*
 The insertNode private member function recursively inserts
 a new node in the BinarySearchTree.
 *~**/
template <class T>
TreeNode<T> * BinarySearchTree<T>::insertNode(T newNode, TreeNode<T> * startingNode)
{
    // If the argument node is null, create a new TreeNode
    if (!startingNode) {
        startingNode = new TreeNode<T>(newNode);
        
        // If the root is null, the new TreeNode must be the root
        if (!root) root = startingNode;
        
        // Increase the count of nodes in the tree
        ++elementsNumber;
        
        // Calculate height of the tree via private memeber function
        height = findHeight(root);
        
        // If the data in the node is less than the one to be inserted,
        // recursively call itself with the right child as an argument
    } else if (startingNode->data < newNode) {
        startingNode->right = insertNode (newNode, startingNode->right);
       
        // If the data in the node is more than the one to be inserted,
        // recursively call itself with the left child as an argument
    } else {
        startingNode->left = insertNode (newNode, startingNode->left);
    }
    
    return startingNode;
}

/**~*~*
 The eraseNode private member function recursively deletes
 a node from the BinarySearchTree.
 *~**/
template <class T>
TreeNode<T> * BinarySearchTree<T>::eraseNode(T node, TreeNode<T> * startingNode)
{
    // If the current node's data matches the node to delete, delete that node
    if (startingNode->data == node){
        delete startingNode;
        
        // Reduce the count of nodes in the tree
        --elementsNumber;
        
        // Calculate height of the tree via private memeber function
        height = findHeight(root);
        
        // Set the return value as null
        startingNode = NULL;
        
        // If the data in the node is less than the one to be inserted,
        // recursively call itself with the right child as an argument
    } else if (startingNode->data < node) {
        startingNode->left = eraseNode(node, startingNode->right);
        
        // If the data in the node is more than the one to be inserted,
        // recursively call itself with the left child as an argument
    } else if (startingNode->data > node) {
        startingNode->right = eraseNode(node, startingNode->left);
    }
    
    return startingNode;
}

/**~*~*
 The findNode private member function recursively searches
 for a node in the BinarySearchTree and returns wether that
 node was found or not.
 *~**/
template <class T>
bool BinarySearchTree<T>::findNode(T node, TreeNode<T> * startingNode)
{
    bool result; // To store wether the node was found or not
    
    // If the current node is null, change flag variable to false
    if (!startingNode) {
        result = false;
      
        // If the current node matches the parameter node, change
        // the flag variable to false
    } else if (node == startingNode->data){
        result = true;
        
        // If the data in the node is less than the one to be inserted,
        // recursively call itself with the right child as an argument
    } else if (node > startingNode->data) {
        result = findNode(node, startingNode->right);
        
        // If the data in the node is more than the one to be inserted,
        // recursively call itself with the left child as an argument
    } else if (node < startingNode->data) {
        result = findNode(node, startingNode->left);
    }
    
    return result;
}

/**~*~*
 The preorder private member function recursively prints
 the nodes in the BinarySearchTree to the os stream in
 the fashion ROOT - LEFT - RIGHT.
 *~**/
template <class T>
void BinarySearchTree<T>::preorder(TreeNode<T> * startingNode, ostream& os)
{
    // If the current node is null, return
    if (!startingNode) return;
    
    // Print the current node's data to the stream
    os << "\t" << startingNode->data << "\n";
    
    // Recursively call itself with the left child as an argument
    preorder(startingNode->left, os);
    
    // Recursively call itself with the right child as an argument
    preorder(startingNode->right, os);
}

/**~*~*
 The inorder private member function recursively prints
 the nodes in the BinarySearchTree to the os stream in
 the fashion LEFT - ROOT - RIGHT.
 *~**/
template <class T>
void BinarySearchTree<T>::inorder(TreeNode<T> * startingNode, ostream& os)
{
    // If the current node is null, return
    if (!startingNode) return;
    
    // Recursively call itself with the left child as an argument
    inorder(startingNode->left, os);
    
    // Print the current node's data to the stream
    os << "\t" << startingNode->data << "\n";
    
    // Recursively call itself with the right child as an argument
    inorder(startingNode->right, os);
}

/**~*~*
 The postorder private member function recursively prints
 the nodes in the BinarySearchTree to the os stream in
 the fashion LEFT - RIGHT - ROOT.
 *~**/
template <class T>
void BinarySearchTree<T>::postorder(TreeNode<T> * startingNode, ostream& os)
{
    // If the current node is null, return
    if (!startingNode) return;
    
    // Recursively call itself with the left child as an argument
    postorder(startingNode->left, os);
    
    // Recursively call itself with the right child as an argument
    postorder(startingNode->right, os);
    
    // Print the current node's data to the stream
    os << "\t" << startingNode->data << "\n";
}

/**~*~*
 The preorder private member function iteratively prints
 the nodes in the BinarySearchTree to the os stream by
 levels (ROOT - all nodes lever n + 1).
 *~**/
template <class T>
void BinarySearchTree<T>::breadthFirst(TreeNode<T> * startingNode, ostream &os)
{
    // If the current node is null, return
    if (!startingNode) return;
    
    queue<TreeNode<T> *> traversalQueue; // To traverse the BST iteratively
    
    // Push the root of the tree in the traversalQueue
    traversalQueue.push(root);
    
    // Loop that repeats until the traversalQueue is empty
    while (!traversalQueue.empty()) {
        TreeNode<T> * current = traversalQueue.front(); // To store the current node in front of the queue
        
        // Print the current node's data to the stream
        os << "\t" << current->data << "\n";
        
        // If the current node has a left child, push the child node the traversalQueue
        if (current->left) traversalQueue.push(current->left);
        
        // If the current node has a right child, push the child node the traversalQueue
        if (current->right) traversalQueue.push(current->right);
        
        // Remove the fron of the traversalQueue
        traversalQueue.pop();
    }
}

/**~*~*
 The range private member function recursively prints
 the nodes in the BinarySearchTree within a certain range
 specified by the user.
 *~**/
template <class T>
void BinarySearchTree<T>::range(T& min, T& max, TreeNode<T> * startingNode, ostream &os)
{
    // If the current node is null, return
    if (!startingNode) return;
    
    // Recursively call itself with the left child as an argument
    range(min, max, startingNode->left, os);
    
    // If the current node's data is within the correct range, print it to the stream
    if (min <= startingNode->data && max >= startingNode->data) os << "\t" << startingNode->data << "\n";
    
    // Recursively call itself with the right child as an argument
    range(min, max, startingNode->right, os);
}

/**~*~*
 The findMin private member function recursively searches
 for the node in the BinarySearchTree with the least value
 and returns it.
 *~**/
template <class T>
T BinarySearchTree<T>::findMin(TreeNode<T> * startingNode)
{
    T data; // To store the found node
    
    // If the curent node is not null and the its left child is not null,
    // call itself recursively passing the left child as argument
    if (startingNode != NULL) {
        if (startingNode->left != NULL) {
            data = findMin(startingNode->left);
         
            // Otherwise, the current node must contain the smallest data found yet
        } else {
            data = startingNode->data;
        }
    }
    
    // Return the found data, or a default data if not found
    return data;
}

/**~*~*
 The findMin private member function recursively searches
 for the node in the BinarySearchTree with the biggest value
 and returns it.
 *~**/
template <class T>
T BinarySearchTree<T>::findMax(TreeNode<T> * startingNode)
{
    T data; // To store the found node
    
    // If the curent node is not null and the its right child is not null,
    // call itself recursively passing the right child as argument
    if (startingNode != NULL) {
        if (startingNode->right != NULL) {
            data = findMax(startingNode->right);
            
          // Otherwise, the current node must contain the biggest data found yet
        } else {
            data = startingNode->data;
        }
    }
    
    // Return the found data, or a default data if not found
    return data;
}

/**~*~*
 The deleteTree private member function recursively traverses
 the nodes in the BinarySearchTree and deletes them.
 *~**/
template <class T>
void BinarySearchTree<T>::deleteTree(TreeNode<T> * startingNode)
{
    // If the current node is null, return
    if (!startingNode) return;
    
    // Recursively call itself with the current left child as an argument
    deleteTree(startingNode->left);
    
    // Recursively call itself with the current right child as an argument
    deleteTree(startingNode->right);
    
    // Delete the current node
    delete startingNode;
}

/**~*~*
 The findHeight private member function recursively traverses
 the nodes in the BinarySearchTree and calculates the tree's height.
 *~**/
template <class T>
int BinarySearchTree<T>::findHeight(TreeNode<T> * startingNode)
{
    // If the current node is null, return -1
    if (!startingNode) return -1;
    
    // Recursively call itself with the left node as an argument
    // and store the result in the leftHeight variable
    int leftHeight = findHeight(startingNode->left);
    
    // Recursively call itself with the right node as an argument
    // and store the result in the rightHeight variable
    int rightHeight = findHeight(startingNode->right);
    
    // Return the biggest between leftHeight and rightHeight plus one
    return max(leftHeight, rightHeight) + 1;
}

// Public functions
/**~*~*
 The findHeight public member function iteratively traverses
 the nodes in the BinarySearchTree and prints them by level
 in a vertical fashion.
 *~**/
template <class T>
void BinarySearchTree<T>::displayTreeVertically(ostream& os)
{
    // If the current node is null, return
    if (!root) return;
    
    // Variables declaration
    queue<TreeNode<T>*> nodesQueue; // To store the queue to traverse the tree
    int nodesInCurrentLevel = 1; // To store the amount of nodes in the current level
    int nodesInNextLevel = 0; // To store the amount of nodes in the next level
    int level = 1; // To store the current level
    int treeHeight = getHeight(); // To store the tree's height
    
    treeHeight *= sqrt(treeHeight);
    
    // Push the root of the tree on the traversal queue
    nodesQueue.push(root);
    
    // Loop that iterates while the traversal queue is not empty
    while (!nodesQueue.empty()) {
        TreeNode<T> * currNode = nodesQueue.front();
        
        // Dequeue the top of the traversal queue
        nodesQueue.pop();
        
        // Reduce the number of nodes in the current level
        --nodesInCurrentLevel;
        
        // If the current node is not null, print as many blank
        // spaces as the tree's height
        if (currNode) {
            for (int i = 0; i < treeHeight; ++i) {
                os << " ";
            }
            
            // Print the current node to the stream
            os << level << ". " << currNode->data << "\t";
            
            // Enqueue the current node's left child
            nodesQueue.push(currNode->left);
            
            // Enqueue the current node's right child
            nodesQueue.push(currNode->right);
            
            // Insrease the nodes in the next level count by 2
            nodesInNextLevel += 2;
        }
        
        // If there are no nodes in the current level
        if (nodesInCurrentLevel == 0) {
            // Print an end of line to the stred
            os << endl;
            
            // Swap the level in the next level and in the current level
            nodesInCurrentLevel = nodesInNextLevel;
            
            // Reset the count of nodes in the next level
            nodesInNextLevel = 0;
            
            // Increase the current level
            ++level;
            
            // Decrease the current tree height
            treeHeight -= sqrt(treeHeight);
        }
    }
}

/**~*~*
 The findHeight public member function iteratively traverses
 the nodes in the BinarySearchTree and prints them by level
 in a horizontal fashion.
 *~**/
template <class T>
void BinarySearchTree<T>::printIndentedSideways(TreeNode<T> * startingNode, int indent, ostream& os)
{
    // If the current node is not null
    if (startingNode) {
        // Increase the indedn by 2
        indent += 2;
        
        // Recirsively call itself with the right node as argument
        printIndentedSideways(startingNode->right, indent, os);
        
        // Print the current node's data to the output stream
        os << setw(indent * 3) << indent / 2 << ". " << startingNode->data << endl;
        
        // Recirsively call itself with the left node as argument
        printIndentedSideways(startingNode->left, indent, os);
    }
}

// Extra credit
/**~*~*
 The iterativeInorder private member function iteratively
 prints the nodes in the BinarySearchTree to the os stream in
 the fashion LEFT - ROOT - RIGHT.
 *~**/
template <class T>
void BinarySearchTree<T>::iterativeInorder(ostream& os)
{
    // If the root node is null, return
    if (!root) return;
    
    stack<TreeNode<T>*> nodesStack; // To traverse the BST
    
    // Push the root of the tree on the traversal stack
    nodesStack.push(root);
    
    // Set the current node to the root
    TreeNode<T> * currNode = root;
    
    // Loop that iterates while the traversal stack is not empty
    // and the current node is not null
    while (!nodesStack.empty() || currNode) {
        // While the current node is not null,
        // push it to the traversal stack and
        // move the current pointer to its left child
        while (currNode) {
            nodesStack.push(currNode);
            
            currNode = currNode->left;
        }
        
        // If the traversal stack is not empty,
        // set the current node to the top of the
        // traversal stack, remove the top of the
        // stack and print it to the output stream
        if (!nodesStack.empty()) {
            currNode = nodesStack.top();
            
            nodesStack.pop();
            
            os << "\t" << currNode->data << endl;
            
            currNode = currNode->right;
        }
    }
}

/**~*~*
 The iterativePreorder private member function iteratively
 prints the nodes in the BinarySearchTree to the os stream in
 the fashion ROOT - LEFT - RIGHT.
 *~**/
template <class T>
void BinarySearchTree<T>::iterativePreorder(ostream& os)
{
    // If the root node is null, return
    if (!root) return;
    
    stack<TreeNode<T>*> nodesStack; // To traverse the BST
    queue<TreeNode<T>*> nodesQueue;
    
    // Push the root of the tree on the traversal stack
    nodesStack.push(root);
    
    // Set the current node to the root of the tree
    TreeNode<T> * currNode = root;
    
    // Loop that iterates while the traversal stack
    // is not empty
    while (!nodesStack.empty()) {
        // Set the current node to the top of the traversal stack
        currNode = nodesStack.top();
        
        // Push the current node on the traversal stack
        nodesQueue.push(currNode);
        
        // Pop the top node from the traversal stack
        nodesStack.pop();
        
        // If the current node's right child is not null,
        // push in on the traversal stack
        if (currNode->right) {
            nodesStack.push(currNode->right);
        }
        
        // If the current node's left child is not null,
        // push in on the traversal stack
        if (currNode->left) {
            nodesStack.push(currNode->left);
        }
        
        // Loop that iterates while the traversal queue is not empty
        while (!nodesQueue.empty()) {
            // Print the fron of the traversal queue to the output stream
            os << "\t" << nodesQueue.front()->data << endl;
            
            // Dequeue the front of the traversal queue
            nodesQueue.pop();
        }
    }
}

/**~*~*
 The iterativePostorder private member function iteratively
 prints the nodes in the BinarySearchTree to the os stream in
 the fashion LEFT - RIGHT - ROOT.
 *~**/
template <class T>
void BinarySearchTree<T>::iterativePostorder(ostream& os)
{
    // If the root node is null, return
    if (!root) return;
    
    stack<TreeNode<T>*> nodesStack;
    
    nodesStack.push(root);
    
    TreeNode<T> * currNode = root, * prevNode = nullptr;
    
    while (!nodesStack.empty()) {
        currNode = nodesStack.top();
        
        // If the current node is null, pop it from the stack
        if(!currNode) {
            nodesStack.pop();
            
            // If the node is a leaf, print its data and pop it from the stack
        } else if(!currNode->left && !currNode->right) {
            os << "\t" << currNode->data << endl;
            
            nodesStack.pop();
            
            // If the previous pointer is the current node's left child,
            // push the right node on the stack
        } else if(currNode->left == prevNode) {
            nodesStack.push(currNode->right);
            
            // If the previous pointer is the current node's right child,
            // print its data and remove it from the stack
        } else if(currNode->right == prevNode) {
            os << "\t" << currNode->data << endl;
            
            nodesStack.pop();
            
            // If none of the previos conditions is true, push the left child
            // on the stack
        } else {
            nodesStack.push(currNode->left);
        }
        
        // Update previous pointer
        prevNode = currNode;
    }
}

#endif /* defined(__Data_Structures_Homework__4__BinarySearchTree__) */
