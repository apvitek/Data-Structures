#include "Stack.h"


/**~*~*
Member function push pushes the argument onto
the stack.
*~**/
template <class T>
bool Stack<T>::push(T item)
{
	StackNode *newNode; // Pointer to a new node

	// Allocate a new node and store num there.
	newNode = new StackNode;
	if (!newNode)
		return false;
	newNode->value = item;

	// Update links and counter
	newNode->next = top;
	top = newNode;
	count++;

	return true;
}

/**~*~*
Member function pop pops the value at the top
of the stack off, and copies it into the variable
passed as an argument.
*~**/
template <class T>
bool Stack<T>::pop(T &item)
{
	StackNode *temp; // Temporary pointer

	// empty stack
	if (count == 0)
		return false;

	// pop value off top of stack
	item = top->value;
	temp = top->next;
	delete top;
	top = temp;
	count--;

	return true;
}

/**~*~*
Member function isEmpty returns true if the stack
is empty, or false otherwise.
*~**/
template <class T>
bool Stack<T>::isEmpty()
{
	return count == 0;
}

/**~*~*
Member function that returns the number of elements in the stack
*~**/
template <class T>
int Stack<T>::getCount()
{
	return count;
}

/**~*~*
Returns a copy top of the stack without removing it from the stack
*~**/
template <class T>
bool Stack<T>::getTop(T &item)
{
	StackNode *temp; // Temporary pointer

	// empty stack
	if (count == 0)
		return false;

	// peeks at the value at the top of the stack
	item = top->value;
	return true;
}