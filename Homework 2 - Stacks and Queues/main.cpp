/**~*~*
 This program demonstrates the mechanics of Queues and Stacks
 
 Student: Andrea Borghi
 *~**/
#include <iostream>
#include <string>
#include "Queue.h"
#include "Stack.h"
using namespace std;

// Constants for the menu choices
const char INSERT = 'I',
           DELETE = 'D',
           DISPLAY_ALL = 'C',
           DISPLAY_TOP_STACKS = 'T',
           DISPLAY_FRONT_QUEUES = 'F',
           DISPLAY_END_QUEUES = 'R',
           QUIT = 'Q';

// Function prototypes
void printGreetings();
char menu();
char getChoice();
void insertItem(Queue<float> * inQ, Stack<float> * inS);
void deleteItem(Queue<float> * inQ, Queue<float> * outQ, Stack<float> * inS , Stack<float> * outS);
void displayStacksQueues(Queue<float> * inQ, Queue<float> * outQ, Stack<float> * inS , Stack<float> * outS);
void displayTopStacks(Stack<float> * inS , Stack<float> * outS);
void displayFrontQueues(Queue<float> * inQ, Queue<float> * outQ);
void displayEndQueues(Queue<float> * inQ, Queue<float> * outQ);
void printDeletingQueue(Queue<float> * queue);
void printDeletingStack(Stack<float> * stack);

int main()
{
    char choice;    // To hold a menu choice
    
    // Create queues and stacks.
    Queue<float> *inQ = new Queue<float>;
    Queue<float> *outQ = new Queue<float>;
    
    Stack<float> *inS = new Stack<float>;
    Stack<float> *outS = new Stack<float>;
    
    // Call a function to greet the user
    printGreetings();
    
    // Display the menu until QUIT option is entered
    while ((choice = menu())!= QUIT) {
        switch (choice) {
            case INSERT:
                insertItem(inQ, inS);
                break;
                
            case DELETE:
                deleteItem(inQ, outQ, inS, outS);
                break;
                
            case DISPLAY_ALL:
                displayStacksQueues(inQ, outQ, inS, outS);
                break;
                
            case DISPLAY_TOP_STACKS:
                displayTopStacks(inS, outS);
                break;
                
            case DISPLAY_FRONT_QUEUES:
                displayFrontQueues(inQ, outQ);
                break;
                
            case DISPLAY_END_QUEUES:
                displayEndQueues(inQ, outQ);
                break;
        }
    }
    
    // Delete stacks and queues
    cout << "\nDeleting input queue.\n";
    printDeletingQueue(inQ);
    
    cout << "\nDeleting output queue.\n";
    printDeletingQueue(outQ);
    
    cout << "\nDeleting input stack.\n";
    printDeletingStack(inS);
    
    cout << "\nDeleting output stack.\n";
    printDeletingStack(outS);
    
    cout << "\n\t*** THE END ***\n";
    return 0;
}

/**~*~*
 The printGreetings function prints greetings to the
 user on screen.
 *~**/
void printGreetings()
{
    string greetings = "Welcome to the Queues and Stacks practice program!";
    
    // Greet the user
    cout << greetings << endl;
    
    for (int i = 0; i < greetings.length(); ++i) {
        cout << "*";
    }
    
    cout << endl;
}

/**~*~*
 The menu function displays the menu and gets
 the user's choice, which is returned to
 the caller.
 *~**/
char menu()
{
    char choice;
    // Display the menu and get the user's choice.
    cout << "\nWhat do you want to do?\n\t"
    << INSERT
    << " - Insert an item into the queue and stack\n\t"
    << DELETE
    << " - Remove an item from the queue and stack\n\t"
    << DISPLAY_ALL
    << " - Display all items in both queues and stacks\n\t"
    << DISPLAY_TOP_STACKS
    << " - Display elements on top of the stacks\n\t"
    << DISPLAY_FRONT_QUEUES
    << " - Display elements in front of the queues\n\t"
    << DISPLAY_END_QUEUES
    << " - Display elements at the end of the queues\n\t"
    << QUIT
    << " - Quit the program\n"
    << "Enter your choice: ";
    
    choice = getChoice();
    
    return choice;
}

/**~*~*
 The getChoice function gets an choice from the
 user and returns it as a char.
 *~**/
char getChoice()
{
    // Variables declaration
    char choice = 'Q';
    bool okChoice = false;
    
    // Validate the user input
    while (!okChoice) {
        // Get user input
        cin.get(choice);
        
        // Convert the user input to uppercase
        choice = toupper(choice);
        
        // Check if the user input matches one of the constant choices
        if (choice == INSERT ||
            choice == DELETE ||
            choice == DISPLAY_ALL ||
            choice == DISPLAY_TOP_STACKS ||
            choice == DISPLAY_FRONT_QUEUES ||
            choice == DISPLAY_END_QUEUES ||
            choice == QUIT) {
            // Change the control loo[ variable to true
            okChoice = true;
            
        } else {
            // Notify the user that her choice is invalid and clear input
            cout << "\nInvalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(80, '\n');
        }
    }
    
    // Clear the input for other functions
    cin.clear();
    cin.ignore(80, '\n');
    
    // Return user's choice
    return choice;
}

/**~*~*
 The insertItem function gets an item from the
 user and inserts it into the queue.
 *~**/
void insertItem(Queue<float> * queue, Stack<float> * stack)
{
    // Variables declaration
    float item = 0.0;
    bool okInput = false;
    
    while (!okInput) {
        // Get an item to be inserted into the queue
        cout << "\nEnter an item: ";
        
        if (cin >> item) {
            okInput = true;
            
        } else {
            cout << "\nInvalid input. Please enter a floating point number.\n";
            cin.clear();
            cin.ignore(80, '\n');
        }
    }
    
    // Clear the input for other functions
    cin.clear();
    cin.ignore(80, '\n');
    
    // Add item to the input queue
    queue -> enqueue(item) ? cout << "\n\t" << item << " was added to the input queue.\n" : cout << "\t*** " << item << " could not be added to the input queue! ***\n";
    
    // Push item on the input stack
    stack -> push(item) ? cout << "\t" << item << " was added to the input stack.\n" : cout << "\t*** " << item << " could not be added to the input stack! ***\n";
}

/**~*~*
 The deleteItem function removes an item from the queue
 *~**/
void deleteItem(Queue<float> * inQ, Queue<float> * outQ, Stack<float> * inS , Stack<float> * outS)
{
    // Variables declaration
    bool status = false;
    float item = 0.0;
    
    // Remove the item.
    status = inQ -> dequeue(item);
    
    // Display the item.
    if (status){
        cout << "\n\t" << item << " was deleted from the input queue.\n";
        
        outS -> push(item) ? cout << "\t" << item << " was pushed on the output stack.\n" : cout << "\t*** " << item << " could not be pushed on the output stack! ***\n";
        
    } else {
        cout << "\n\t*** Empty queue! ***\n";
    }
    
    // Remove the item.
    status = inS -> pop(item);
    
    // Display the item.
    if (status) {
        cout << "\n\t" << item << " was deleted from the input stack.\n";
        
        outQ -> enqueue(item) ? cout << "\t" << item << " was enqueued on the output queue.\n" : cout << "\t*** " << item << " could not be enqueued on the output queue! ***\n";
        
    } else {
        cout << "\n\t*** Empty stack! ***\n";
    }
}

/**~*~*
 The displayStacksQueues function the number of
 elements in all stacks and queues
 *~**/
void displayStacksQueues(Queue<float> * inQ, Queue<float> * outQ, Stack<float> * inS , Stack<float> * outS)
{
    inQ -> isEmpty() ? cout << "\nThe input queue is empty!\n" : cout << "\nThe input queue contains " << inQ -> getCount() << " elements.";
    
    outQ -> isEmpty() ? cout << "\nThe output queue is empty!\n" : cout << "\nThe output queue contains " << outQ -> getCount() << " elements.";
    
    inS -> isEmpty() ? cout << "\nThe input stack is empty!\n" : cout << "\nThe input stack contains " << inS -> getCount() << " elements.";
    
    outS -> isEmpty() ? cout << "\nThe output stack is empty!\n" : cout << "\nThe output stack contains " << outS -> getCount() << " elements.\n";
}

/**~*~*
 The displayTopStacks function prints the top of
 two stacks to screen
 *~**/
void displayTopStacks(Stack<float> * inS , Stack<float> * outS)
{
    // Variables declaration
    float item = 0.0;
    
    if (!(inS -> isEmpty())) {
        inS -> getTop(item);
        
        cout << "\nThe top of the input stack is: " << item << ".\n";
        
    } else {
        cout << "\nThe input stack is empty!\n";
    }
    
    if (!(outS -> isEmpty())) {
        outS -> getTop(item);
        
        cout << "The top of the output stack is: " << item << ".\n";
        
    } else {
        cout << "The output stack is empty!\n";
    }
}

/**~*~*
 The displayFrontQueues function prints the top of
 two queues to screen
 *~**/
void displayFrontQueues(Queue<float> * inQ, Queue<float> * outQ)
{
    // Variables declaration
    float frontQ = 0.0;
    
    inQ -> queueFront(frontQ) ? cout << "\nThe front of the input queue is " << frontQ << ".\n" : cout << "\nThe front of the input queue is empty!\n";
    
    outQ -> queueFront(frontQ) ? cout << "The front of the output queue is " << frontQ << ".\n" : cout << "\nThe front of the output queue is empty!\n";
}

/**~*~*
 The displayEndQueues function prints the rear of
 two queues to screen
 *~**/
void displayEndQueues(Queue<float> * inQ, Queue<float> * outQ)
{
    // Variables declaration
    float endQ = 0.0;
    
    inQ -> queueRear(endQ) ? cout << "\nThe end of the input queue is " << endQ << ".\n": cout << "\nThe end of the input queue is empty!\n";
    
    outQ -> queueRear(endQ) ? cout << "The end of the output queue is " << endQ << ".\n" : cout << "\nThe end of the output queue is empty!\n";
}

/**~*~*
 The printDeletingQueue function prints the elements
 of a queue as it is being deleted
 *~**/
void printDeletingQueue(Queue<float> * queue)
{
    // Variables declaration
    float item = 0.0;
    
    if (queue -> isEmpty()) {
        cout << "\tThe queue is empty.\n";
        
    } else {
        while (!(queue -> isEmpty())) {
            queue -> dequeue(item);
            
            cout << "\tDeleting item " << item << ".\n";
        }
    }
    
    delete queue;
    
    cout << "Deleted.\n";
}

/**~*~*
 The printDeletingStack function prints the elements
 of a stack as it is being deleted
 *~**/
void printDeletingStack(Stack<float> * stack)
{
    // Variables declaration
    float item = 0.0;
    
    if (stack -> isEmpty()) {
        cout << "\tThe stack is empty.\n";
        
    } else {
        while (!(stack -> isEmpty())) {
            stack -> pop(item);
            
            cout << "\tDeleting item " << item << ".\n";
        }
    }
    
    delete stack;
    
    cout << "Deleted.\n";
}

/*
 Welcome to the Queues and Stacks practice program!
 **************************************************
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: d
 
 *** Empty queue! ***
 
 *** Empty stack! ***
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: i
 
 Enter an item: 10.5
 
 10.5 was added to the input queue.
 10.5 was added to the input stack.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: i
 
 Enter an item: 20.1
 
 20.1 was added to the input queue.
 20.1 was added to the input stack.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: d
 
 10.5 was deleted from the input queue.
 10.5 was pushed on the output stack.
 
 20.1 was deleted from the input stack.
 20.1 was enqueued on the output queue.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: i
 
 Enter an item: 30.2
 
 30.2 was added to the input queue.
 30.2 was added to the input stack.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: d
 
 20.1 was deleted from the input queue.
 20.1 was pushed on the output stack.
 
 30.2 was deleted from the input stack.
 30.2 was enqueued on the output queue.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: i
 
 Enter an item: 40.1
 
 40.1 was added to the input queue.
 40.1 was added to the input stack.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: i
 
 Enter an item: 50.5
 
 50.5 was added to the input queue.
 50.5 was added to the input stack.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: c
 
 The input queue contains 3 elements.
 The output queue contains 2 elements.
 The input stack contains 1 elements.
 The output stack contains 1 elements.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: t
 
 The top of the input stack is: 50.5.
 The top of the output stack is: 20.1.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: f
 
 The front of the input queue is 30.2.
 The front of the output queue is 20.1.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: r
 
 The end of the input queue is 50.5.
 The end of the output queue is 30.2.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: d
 
 30.2 was deleted from the input queue.
 30.2 was pushed on the output stack.
 
 50.5 was deleted from the input stack.
 50.5 was enqueued on the output queue.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: i
 
 Enter an item: 60.5
 
 60.5 was added to the input queue.
 60.5 was added to the input stack.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: d
 
 40.1 was deleted from the input queue.
 40.1 was pushed on the output stack.
 
 60.5 was deleted from the input stack.
 60.5 was enqueued on the output queue.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: i
 
 Enter an item: 70.9
 
 70.9 was added to the input queue.
 70.9 was added to the input stack.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: d
 
 50.5 was deleted from the input queue.
 50.5 was pushed on the output stack.
 
 70.9 was deleted from the input stack.
 70.9 was enqueued on the output queue.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: i
 
 Enter an item: 80.2
 
 80.2 was added to the input queue.
 80.2 was added to the input stack.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: d
 
 60.5 was deleted from the input queue.
 60.5 was pushed on the output stack.
 
 80.2 was deleted from the input stack.
 80.2 was enqueued on the output queue.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: d
 
 70.9 was deleted from the input queue.
 70.9 was pushed on the output stack.
 
 40.1 was deleted from the input stack.
 40.1 was enqueued on the output queue.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: d
 
 80.2 was deleted from the input queue.
 80.2 was pushed on the output stack.
 
 10.5 was deleted from the input stack.
 10.5 was enqueued on the output queue.
 
 What do you want to do?
 I - Insert an item into the queue and stack
 D - Remove an item from the queue and stack
 C - Display all items in both queues and stacks
 T - Display elements on top of the stacks
 F - Display elements in front of the queues
 R - Display elements at the end of the queues
 Q - Quit the program
 Enter your choice: q
 
 Deleting input queue.
 The queue is empty.
 Deleted.
 
 Deleting output queue.
 Deleting item 20.1.
 Deleting item 30.2.
 Deleting item 50.5.
 Deleting item 60.5.
 Deleting item 70.9.
 Deleting item 80.2.
 Deleting item 40.1.
 Deleting item 10.5.
 Deleted.
 
 Deleting input stack.
 The stack is empty.
 Deleted.
 
 Deleting output stack.
 Deleting item 80.2.
 Deleting item 70.9.
 Deleting item 60.5.
 Deleting item 50.5.
 Deleting item 40.1.
 Deleting item 30.2.
 Deleting item 20.1.
 Deleting item 10.5.
 Deleted.
 
 *** THE END ***
 Program ended with exit code: 0
 */
