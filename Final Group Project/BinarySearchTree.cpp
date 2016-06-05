//Joseph Dollahon
// Implementation file for the BST class
#include <iostream>  // For cout and NULL
#include "BinarySearchTree.h"
#include <iomanip>
#include "Star.h"

using namespace std;

/**~*~*
   This function calls a recursive function to traverse the
   tree in inorder
*~**/
void BinarySearchTree::BST_InorderTraverse() const
{
    _BST_InorderTraverse(root);
}

/**~*~*
   Inorder Traversal of the Binary Tree:
   Left-Root-Right
*~**/
void BinarySearchTree::_BST_InorderTraverse(BST_Node *root) const
{
    if (root)
    {
        _BST_InorderTraverse(root->left);
        root->data.starPtr->printStar();
        cout << endl;
        _BST_InorderTraverse(root->right);
    }
}

/**~*~*
   Insert data into a BST
*~**/
void BinarySearchTree::BST_insert(Data dataIn)
{
	BST_Node *newNode;
	BST_Node *pWalk;
	BST_Node *parent = NULL;

	// allocate the new node

	newNode = new BST_Node;
	newNode->data.starPtr = dataIn.starPtr;
	newNode->left = NULL;
	newNode->right = NULL;

	if (!root) // tree is empty
		root = newNode;
	else
	{
		pWalk = root;
		while (pWalk)
		{
			parent = pWalk;
			if (dataIn.starPtr->getName() < pWalk->data.starPtr->getName())
				pWalk = pWalk->left;
			else
				pWalk = pWalk->right;
		}

		// insert the new node
		if (dataIn.starPtr->getName() < parent->data.starPtr->getName()) // no left child
			parent->left = newNode;
		else
			parent->right = newNode;
	}
	count++;
}

/**~*~*
   Destructor
   This function calls a recursive function to delete all nodes in the binary tree
*~**/
BinarySearchTree::~BinarySearchTree()
{
    if (root)
        _BST_Destroy(root);
}

/**~*~*
   This function traverses the binary tree in postorder and deletes every node
*~**/
void BinarySearchTree::_BST_Destroy(BST_Node *root)
{
    if (root)
    {
        _BST_Destroy(root->left);
        _BST_Destroy(root->right);
        delete root;
    }
    return;
}

/**~*~*
Search a BST for a given target to delete: if found and deleted it returns true
otherwise returns false. It calls the private _deleteValue to locate and delete the node.
*~**/
bool BinarySearchTree::deleteValue(string target)
{
	bool deleted = _deleteValue(target);
	if (deleted)
	{
		return true;
	}
	return false;
}



/**~*~*
Locates the node that contains a given target in a BST and deletes it:
- if found returns true and deleted
- if not found returns false.
*~**/
bool BinarySearchTree::_deleteValue(string target)
{
	if (!root) // tree is empty
		return NULL;

	// tree is not empty
	BST_Node *pWalk = root;
	BST_Node *temp = pWalk;
	Star starCopy;
	BST_Node *parent = pWalk;
	while (pWalk)
	{
		if (target != pWalk->data.starPtr->getName())
		{
			parent = pWalk;
		}

		if (target < pWalk->data.starPtr->getName())
		{
			pWalk = pWalk->left;
		}
		else
		{
			if (target > pWalk->data.starPtr->getName())
			{
				pWalk = pWalk->right;
			}
			else
			{
				if (pWalk->data.starPtr->getName() == target)
				{
					//if the node has no children
					if (pWalk->left == NULL && pWalk->right == NULL)
					{
						if (parent->left == pWalk)
						{
							parent->left = NULL;
						}
						else
						{
							parent->right = NULL;
						}
						delete pWalk;
					}
					//if the node has one child
					else if ((pWalk->left != NULL && pWalk->right == NULL) || (pWalk->right != NULL && pWalk->left == NULL))
					{

						if (pWalk->right == NULL)
						{
							if (parent->left == pWalk)
							{
								parent->left = pWalk->left;
							}
							else
							{
								parent->right = pWalk->left;
							}

							delete pWalk;
						}
						else
						{
							if (parent->right == pWalk)
							{
								parent->right = pWalk->right;
							}
							else
							{
								parent->left = pWalk->right;
							}
							delete pWalk;
						}
					}
					//if the node has two children
					else
					{
						parent = pWalk;
						pWalk = pWalk->right;
						while (pWalk->left != NULL)
						{
							temp = pWalk;
							pWalk = pWalk->left;
						}
						//Copy left most node on the right subtree to the node that needs to be deleted.
						parent->data.starPtr->setRank(pWalk->data.starPtr->getRank());
						parent->data.starPtr->setType(pWalk->data.starPtr->getType());
						parent->data.starPtr->setName(pWalk->data.starPtr->getName());
						parent->data.starPtr->setMagnitude(pWalk->data.starPtr->getMagnitude());
						parent->data.starPtr->setConstellation(pWalk->data.starPtr->getConstellation());
						//Delete the node
						delete pWalk;
						//Set its parent to left pointer to null.
						temp->left = NULL;
					}
				}
				return true; // deleted
			}
		}
	}

	return false; // not found
}

void BinarySearchTree::indented()
{
     _indented(root, 0);
}

/*=====================================
Pre: bst node by reference
Returns: bst node by reference
Purpose: prints the tree in an indented form.
=====================================*/
void BinarySearchTree::_indented(BST_Node *current, int indent)
{
    
    if(current != NULL) {
        
        if(current->left)
        {
             
             _indented(current->left, indent+4);
        }
        if (indent) 
        {

           cout << setw(indent) << ' ';
           
        }
        current->data.starPtr->printStar();
        cout << endl;
        if(current->right)
        {
             
             _indented(current->right, indent+4);
        }
        
    }
}