/*
AUTHOR:
	Chris Pray

DATE:
	4/4/13

FILENAME:
	stack.H

PURPOSE:
	This file contains the specification for a stack class. Method preconditions, postconditions, and
	purposes will remain consistent for any implementations of the methods.

ASSUMPTIONS:
	(1) The user of this class should not call Push on a full stack
	(2) The user of this class should not call Retrieve on an empty stack

EXCEPTION HANDLING:
	bad_alloc is caught in method Allocate if an attempt to allocate dynamic memory fails 
*/

//********************************************************************************************
// The public methods are: 
//
//    StackClass();  		: Prepares stack for usage.	
//
//	  ~StackClass();    	: Returns all dynamically allocated memory to heap.
//
//	  StackClass(const StackClass& orig);  : Creates a deep copy of the object.
//		
//    bool IsEmpty() const : Returns true if stack has no elements. 
//
//    bool IsFull() const  : Returns true if stack has no empty spaces.
//
//    void Push(ItemType newItem);	  : Adds newItem to top of stack.
//
//    void Pop();		  : Removes top item from stack.
//
//    ItemType Retrieve() const;      : Returns item at top of stack		
//		 DOES NOT REMOVE TOP ELEMENT!!!!  STACK IS UNCHANGED!!!
//	 
//	  void Clear();       : Empties the stack.
//
//	  virtual void operator=(const StackClass& orig);   : Allows for aggregate assignment of
//															StackClass objects.
//
//********************************************************************************************

#ifndef stack_H
#define stack_H

#include "ItemType.h"			// Provides the structure of the type of data to be stored on the stack
#include "StackExceptions.h"	// For custom exceptions
#include <cstdlib>				// For NULL
using namespace nmspcStackExceptions;

// Forward declaration of struct
struct node;

// Class Declaration
class StackClass
{
	public:

		// Constructor(s) and Destructor(s)
			
		StackClass();
		/*
		Purpose:			Instantiates a StackClass object. Initiallizes PDM stack to NULL.
		Pre:				None.
		Post:				A StackClass object has been instantiated. PDM stack has been initiallized
							to NULL.
		Classification:		Default Constructor
		Order of Magnitude:	O(1)
		*/

		~StackClass();
		/*
		Purpose:			Returns all dynamically allocated memory of a StackClass object back to the
							heap
		Pre:				A StackClass object has been instantiated.
		Post:				All dynamically allocated memory of the StackClass object has been returned
							to the heap.
		Classification:		Destructor
		Order of Magnitude:	O(N), ~StackClass() calls Clear(), which is O(N), where N is the # of items
							in the applying object's stack
		*/

		StackClass(/* In */ const StackClass& orig);	// StackClass object to be copied
		/*
		Purpose:			Instantiates a deep copy of orig.
		Pre:				orig exists.
		Post:				A StackClass object has been instatiated with the values of orig.
		Classification:		Copy Constructor
		Order of Magnitude:	O(N + M), StackClass(const StackClass& orig) calls operator=(orig), which is
							O(N + M), where N is the # of items in the applying object's stack and M is
							the # of items in orig's stack
		Exceptions Thrown:	OutOfMemoryException
		*/


		// ADT stack operations:

		bool IsEmpty() const;      
		/*
		Purpose:			Determines whether the stack is empty.
		Pre:				A StackClass object has been instantiated.
		Post:				If the stack is empty, true has been returned. Otherwise false has been
							returned.
		Classification:		Observer / Predicator
		Order of Magnitude:	O(1)
		*/

		bool IsFull() const;	  
		/*
		Purpose:			Determines whether the stack is full.
		Pre:				A StackClass object has been instantiated.
		Post:				If the stack is full, true has been returned. Otherwise false has been
							returned.
		Classification:		Observer / Predicator
		Order of Magnitude:	O(1)
		*/

		void Push(/* In */ ItemType newItem);	// ItemType to be pushed onto the stack
		/*
		Purpose:			Adds newItem to the top of the stack.
		Pre:				A StackClass object has been instantiated. The stack is not full.
		Post:				newItem is at the top of the stack.
		Classification:		Mutator
		Order of Magnitude:	O(1)
		Exceptions Thrown:	OutOfMemoryException
		*/

		void Pop();			
		/*
		Purpose:			Removes the top item from the stack.
		Pre:				A StackClass object has been instantiated. The stack is not empty.
		Post:				The top item has been removed from the stack.
		Classification:		Mutator
		Order of Magnitude:	O(1)
		*/

		ItemType Retrieve() const;	
		/*
		Purpose:			Returns a copy of the top item on the stack.
		Pre:				A StackClass object has been instantiated. The stack is not empty.
		Post:				A copy of the top item on the stack has been returned.
		Classification:		Observer / Accessor
		Order of Magnitude:	O(1)
		Exceptions Thrown:	RetrieveOnEmptyException
		*/
	
		void Clear();
		/*
		Purpose:			Empties the stack.
		Pre:				A StackClass object has been instantiated.
		Post:				The stack is empty.
		Classification:		Mutator
		Order of Magnitude:	O(N), where N is the # of items in the applying object's stack
		*/


		// Overloaded Operators

		virtual void operator=(/* In */ const StackClass& orig);	// StackClass object to make a deep
																	//  copy of
		/*
		Purpose:			Allows for aggregate assignment of StackClass objects.
		Pre:				The applying StackClass object has been instantiated. orig exists.
		Post:				The applying object has been assigned as a deep copy of orig.
		Classification:		Mutator
		Order of Magnitude:	O(N + M), where N is the # of items in the applying object's stack and M is
							the # of items in orig's stack
		Exceptions Thrown:	OutOfMemoryException
		*/


	private:

		// PDM(s)

		node* stack;	// Stack declaration 

    
	protected:
		
		node* Allocate();
		/*
		Purpose:			Dynamically allocates memory for a node.
		Pre:				A StackClass object has been instantiated.
		Post:				The pointer to newly dynamically allocated memory for a node has been
							returned.
		Classification:		Mutator
		Order of Magnitude:	O(1)
		Exceptions Thrown:	OutOfMemoryException
		*/

}; // End StackClass

#endif