//Joseph Dollahon
/*========================Documentation=============================================
The purpose of the Binary Search Tree in respects to the rest of the project is to
store pointers to the Stars that have been allocated and display them in sorted
order by name.  It is also responsible for deleting the allocated data when a star is removed.
==================================================================================*/
// Specification file for the BST class
#ifndef BinarySearchTree_H
#define BinarySearchTree_H

#include "Star.h"

using namespace std;

struct Data
{
	Star *starPtr;
	// more fields could be added if needed
};

class BinarySearchTree
{
private:

	struct BST_Node
	{
		Data data;         // The value in this node
		BST_Node *left;    // To point to the left node
		BST_Node *right;   // To point to the right node
	};

	BST_Node *root;       // root of the tree
	int count;            // number of nodes in the tree

public:
	// Constructor
	BinarySearchTree()
	{
		root = NULL;
		count = 0;
	}

	// Destructor
	~BinarySearchTree();

	// Binary Tree operations
	void BST_insert(Data dataIn);
	bool deleteValue(string target);
	void BST_InorderTraverse() const;
	void BST_PreorderTraverse() const;
	void BST_PostorderTraverse() const;
	void postorderTraverseIter();
	void inorderTraverseIter();
	void preorderTraverseIter();
	void levelOrder();
	void indented();
	void _indented(BST_Node *current, int indent);

private:
	bool _deleteValue(string target);
	void _BST_InorderTraverse(BST_Node *root) const;
	void _BST_PreorderTraverse(BST_Node *root) const;
	void _BST_PostorderTraverse(BST_Node *root) const;
	void _BST_Destroy(BST_Node *root);
};

#endif