//Author:			Luke Musto
//Date:				4/7/2013
//Modifications:	Chris Pray
//Purpose:			This specification contains the basis for an ordered list class. 
//					It allows for list insertions, deletions, and looks ups. It contains ?? public
//					methods and ?? private data members. A summary of the public methods appears below.
// 
//Assumptions:
//	1. struct Item Type must contain a field of KeyType key to allow for list look up.
//	2. NextPosition and PrevPosition are iterator functions designed to be used in conjuction with
//		FirstPosition and LastPosition, respectively, and EndOfList and BeginningOfList, respectively,
//		to ensure proper class function.
//
//Error Handling: 
//	None
//
//Exceptions thrown:
//	DuplicateKeyException
//		When an attempt to insert an item into a list with a key equal to a key already in the list
//	RetrieveOnEmptyException
//		When an attempt to retrieve an item from an empty list is made
//  PastEndOfListException
//		When an attempt to move the current position in a list past the last position in the list of
//		before the first position in the list is made
//  OutOfMemoryException
//		When failure to allocate dynamic memory occurs

//Summary of Methods
// OrdListClass() -- initializes list object
//~OrdListClass() -- returns memory to the system
// OrdListClass(const OrdListClass& orig)
// IsEmpty()   -- indicates whether or not the list is empty
// IsFull()    -- indicates whether or not the list is full
// Insert(ItemType item)  -- Inserts the item at position specified by currPos
// Find(KeyType searchKey) -- Finds searchkey (sets currPos) returns true if, found false otherwise
//						      if item does not exist currPos is set to where the element would appear 
// Delete()    --Deletes the item specified by currPos
// FirstPosition() -- moves currpos to the beginning of the list
// LastPosition() -- moves currPos to end of the list
// NextPosition()  -- moves currPos to the next postion in the list
// EndOfList()     -- determines if currPos is at the end of the list
// PrevPosition() -- moves currPos to the previous position in the list
// BeginningOfList() -- determinse if currPos is at the beginning of the list
// Retrieve()      -- returns the list element specified by currPos
// operator =      -- allows aggregate assignment of list objects
// ReturnLength()  -- provides the number of items in the list
// Clear		   -- clears the list
// OrdListClass operator +(const OrdListClass& rtOp) const;
//	--merges two lists, eliminating duplicate keys
// OrdListClass operator*(const OrdListClass& rtOp) const;
//	--Union of two lists OrdListClass rtOp is compared to applying OrdListClass,
//	--resultant contains all elements that appear in both classes
// bool operator==(const OrdListClass& rtOp) const;
//	--Determines if lists are equal - contain equivalent keys
// bool operator!=(const OrdListClass& rtOp) const;
//	--Determines if lists are not equal  
	

//Note Assumptions :struct Item Type must contain a field of KeyType key to allow for list look up.
#include "Itemtype.h"					// For data
#include "OrdListClassExceptions.h"		// For custom exceptions
using namespace OrdListClassExceptions;

//forward declaration
struct node;

class OrdListClass
{
	public:

		// Constructor
		OrdListClass();			
		//Purpose:  Initializes a list object to an empty list
		//Pre:		List has been instantiated
		//Post:		List has been initialized
			
		// Destructor
		~OrdListClass();
		//Purpose:	To return memory assigned to a list object to the system
		//Pre:		List has been instantiated
		//Post:		Memory allocated to list haas been returned to the system

		// Copy Constructor
		OrdListClass(const OrdListClass& orig);
		//Purpose:	To perform a deep copy of a list object
		//Pre:		Object to be copied has been instantiated
		//Post:		An identical deep copy of the object has been made.


		bool IsEmpty() const;			
		//Purpose:	Indicates whether or not the list is empty
		//Pre:		List has been instantiated
		//Post:		Returns true if list is empty and false, otherwise

		bool IsFull() const;			
		//Purpose:	Indicates whether or not the list is full
		//Pre:		List has been instantiated
		//Post:		Returns true if list is full and false, otherwise
	
		void FirstPosition();
		//Purpose:  Moves currPos to the beginning of the list
		//Pre:		List has been instantiated
		//Post:		currPos is at the beginning of the list

		void LastPosition();
		//Purpose:  Moves currPos to the end of the list
		//Pre:		List has been instantiated
		//Post:		currPos is at the end of the list

		void NextPosition();
		//Purpose:	Moves currPos to the next element in the list
		//Pre:		List has been instantiated
		//Post:		currPos moves to the next element

		void PrevPosition();
		//Purpose:	Moves currPos to the previous element in the list
		//Pre:		List has been instantiated
		//Post:		currPos moves to the previous element

		bool BeginningOfList() const;
		//Purpose:	Determines if currPos is at the beginning of the list
		//Pre:		List has been instantiated
		//Post:		Returns true if at the beginning of the list, and false, otherwise

		bool EndOfList() const;
		//Purpose:	Determines if at the end of the list
		//Pre:		List has been instantiated
		//Post:		Returns true if at the end of the list, and false, otherwise

		ItemType Retrieve() const;
		//Purpose:	Returns the current item in the list
		//Pre:		EndOfList is false
		//Post:		Returns the item at currPos

		void Insert(/* In */ ItemType item);	// Item to be added
		//Purpose:	Inserts item into the list in order(descending)
		//Pre:		List is not full
		//Post:		item has been inserted

	
		bool Find(/* In */ KeyType searchKey);	// Item to be found
		//Purpose:	Determines whether or not item is in the list
		//Pre:		searchKey is assigned a value
		//Post:		If item is in the list then true is returned  and currPos 
		//			points to the element, otherwise currpos will be at the end of the list.

		void  Delete();
		//Purpose:  Deletes an item from the list
		//Pre:		Find has been called to find the item to delete, so that currPos now points at the item to be deleted
		//Post:		The item which currPos refers to has been deleted from the list

		int ReturnLength();
		//Purpose:	Provides the number of items in the list
		//Pre:		List has been instantiated
		//Post:		The number of items in the list has been returned

		void Clear();
		//Purpose:	To clear the object
		//Pre:		Object has been instantiated
		//Post:		Object has been cleared and reset to its original state

		void operator=( /* In */ const OrdListClass& orig );	// Object to be copied
		//Purpose:	Overloads the = operator so that aggregate assignment is possible
		//Pre:		orig contain the list to be copied
		//Post:		The applying operator contains a copy of the original list 

		OrdListClass operator+( /* In */ const OrdListClass& rtOp )const;	// The object to merge with
																			//  the applying object
		//Purpose:	Merges two lists, eliminating duplicate keys
		//Pre:		rtOp contains an OrdListClass
		//Post:		A new OrdList has been created that contains the merged items of rtOp and the applying
		//			list
	
		OrdListClass operator*( /* In */ const OrdListClass& rtOp )const;	// The object to intersect
																			//  with the applying object
		//Purpose:	Performs a intersection of the two lists, OrdListClass rtOp and the applying
		//			OrdListClass
		//Pre:		rtOp contains an OrdListClass
		//Post:		A new OrdList nas been created that contains all elements that appear in both classes

	
		bool operator==( /* In */ const OrdListClass& rtOp )const;	// The object to test equallity
																	//  against the applying object
		//Purpose:	Determines if lists are equal - contain equivalent keys
		//Pre:		rtOp contains an OrdListClass
		//Post:		True is returned if the lists contains the same elements, false otherwise
		
		bool operator!=( /* In */ const OrdListClass& rtOp )const;	// The object to test inequallity
																	//  against the applying object
		//Purpose:	Determines if lists are not equal 
		//Pre:		rtOp contains an OrdListClass
		//Post:		True is returned if the lists do not contains the same elements, false otherwise
	

	private:

 		node* currPos;	// Position of current element
		node* tail;		// Last element in the list

}; // End OrdListClass
