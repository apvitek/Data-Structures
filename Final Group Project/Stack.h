/**~*~*
   Stack template
*~**/
#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
	// Structure for the stach nodes
	struct StackNode
	{
		T value;          // Value in the node
		StackNode *next;  // Pointer to next node
	};

	StackNode *top;     // Pointer to the stack top
	int count;

public:
	//Constructor
	Stack(){top = NULL; count = 0;}

	// Destructor
	~Stack();

	// Stack operations
	bool push(T);
	bool pop(T &);
	bool isEmpty();
	int getCount();
	bool getTop(T &);
};


#endif

