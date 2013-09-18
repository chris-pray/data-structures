/*
AUTHOR:
	Chris Pray

DATE:
	4/4/13

FILENAME:
	stack.CPP

PURPOSE:
	This file contains the implementation for all of the methods declared in stack.h
*/

#include "stack.H"
 
//***************************************************************************
//*																			*
//*				declare struct from forward declaration						*
//*																			*
//***************************************************************************

struct node
{
	 ItemType data;	// Data
	 node* next;	// Pointer to next node

}; // End node


//***************************************************************************
//*																			*
//*				Constructors, Destructor, and Copy Constructor				*
//*																			*
//***************************************************************************

// Constructor
StackClass::StackClass()
{
	// Initialize PDM stack to NULL
	stack = NULL;

} // End StackClass()

//***************************************************************************

// Copy Constructor
StackClass::StackClass(/* In */ const StackClass& orig)	// StackClass object to be copied
{
	// Initialize PDM stack to NULL
	stack = NULL;

	// Aggregately assign the applying object to a deep copy of orig
	operator=(orig);

} // End StackClass(const StackClass& orig)

//***************************************************************************

// Destructor
StackClass::~StackClass() 
{
	// Return all dynamically allocated memory of the applying object back to the heap
	Clear();

} // End ~StackClass()


//***************************************************************************
//*																			*
//*				Observer / Predicators										*
//*																			*
//***************************************************************************

bool StackClass::IsEmpty() const
{
	// Return true if PDM stack equals NULL, false otherwise
	return ( stack == NULL );

} // End IsEmpty()

//***************************************************************************

bool StackClass::IsFull() const
{
	return false;

} // End IsFull()


//***************************************************************************
//*																			*
//*				Observer / Accessor											*
//*																			*
//***************************************************************************

ItemType StackClass::Retrieve() const
{
	// If the stack is not empty
	if( !IsEmpty() )
	{
		// Return the data member of the node PDM stack is pointing to
		return stack->data;
	
	} // End if
	// Else the stack is empty
	else
	{
		throw RetrieveOnEmptyException
			("RetrieveOnEmptyException: Cannot retrieve from an empty stack.");

	} // End else

} // End Retrieve()


//***************************************************************************
//*																			*
//*							Mutators										*
//*																			*
//***************************************************************************

void StackClass::Push(/* In */ ItemType newItem)	// ItemType to be pushed onto the stack								
{
	node* newNode = Allocate();	// Gets the item to be pushed

	// Set the data member of the node that newNode is pointing to to newItem
	newNode->data = newItem;

	// Set the next member of the node that newNode is pointing to to PDM stack
	newNode->next = stack;

	// Set PDM stack to newNode
	stack = newNode;

} // End Push(ItemType newItem)

//***************************************************************************

void StackClass::Pop()
{
	// If the stack is not empty
	if( !IsEmpty() )
	{
		node* temp = stack;	// Gets the node at the top of the stack

		// Set PDM stack to the next member of the node that its pointing to
		stack = stack->next;

		// Return the memory allocated to the node at the top of the stack back to the heap
		delete temp;

	} // End if

} // End Pop()

//***************************************************************************

void StackClass::Clear() 
{
	node* temp = NULL;	// Gets the node at the top of the ]stack

	// While the stack is not empty
	while( stack != NULL )
	{
		// Set temp to PDM stack
		temp = stack;

		// Set PDM stack to the next member of the node its pointing to
		stack = stack->next;

		// Return the memory allocated to the node at the top of the stack back to the heap
		delete temp;

	} // End while

} // End Clear()

//***************************************************************************

void StackClass::operator=(/* In */ const StackClass& orig)	// StackClass object to make a deep copy of
{
	// Empty the applying object's stack
	Clear();

	// If orig's stack is not empty
	if( !orig.IsEmpty() )
	{
		node* applyingPtr;	// Points to a node in the applying object's stack
		node* origPtr;		// Points to a node in the orig's stack

		// Dynamically allocate memory for a node
		stack = Allocate();

		// Assign values to the members of the top node of the applying object's stack
		stack->next = NULL;
		stack->data = orig.stack->data;

		// Assign values to the internal pointers
		applyingPtr = stack;
		origPtr = orig.stack->next;

		// While not past the bottom of orig's stack
		while( origPtr != NULL )
		{
			// Dynamically allocate memory for a node at the bottom of the applying object's stack
			applyingPtr->next = Allocate();

			// Assign values to the members of the node pointed to by the next member of the node
			//  pointed to by applyingPtr
			applyingPtr->next->next = NULL;
			applyingPtr->next->data = origPtr->data;
			
			// Assign new values to the internal pointers
			applyingPtr = applyingPtr->next;
			origPtr = origPtr->next;

		} // End while

	} // End if

} // End operator=(const StackClass& orig)


//***************************************************************************
//*																			*
//*						Protected Method									*
//*																			*
//***************************************************************************

node* StackClass::Allocate()
{
	try
	{
		node* newNode = new node;	// Gets the memory address of the memory dynamically allocated for a
									//  node from the heap

		return newNode;

	} // End try
	catch(bad_alloc e)
	{
		throw OutOfMemoryException("OutOfMemoryException: The heap has run out of memory.");

	} // End catch(bad_alloc e)

} // End Allocate()