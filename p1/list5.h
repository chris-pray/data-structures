/*
AUTHOR:
	Chris Pray

DATE:
	2/19/13

FILENAME:
	list5.h

PURPOSE:
	This file contains the specification for an unsorted ListClass5 of a maximum of 5 elements,
	currently.  It contains 1 default constructor, 10 public methods, 1 operator overload, and 3 private
	data members.  The functionality provided to the user by the public methods is described in the
	Summary of Methods section of this heading.  location.h is included to provide for the use of a
	LocationRec.  Private data members are list, a 1D array of LocationRecs, length, an int determining
	the # of usable items in the list, and currPos, an int that references the current position of the
	list.

ASSUMPTIONS:
	A ListClass object can contain a maximum of 5 elements

ERROR HANDLING:
	None

SUMMARY OF METHODS:
	ListClass()
		Initializes list object

	IsEmpty()
		Indicates whether or not the list is empty

	IsFull()
		Indicates whether or not the list is full

	Insert(ItemType item)
		Inserts the speicifed item at the end of the list

	Find(ItemType item)
		Finds specified item (sets currPos) returns true if found false otherwise

	Delete()
		Deletes the item specified by currPos

	FirstPosition()
		Moves currpos to the beginning of the list

	NextPosition()
		Moves currPos to the next postion in the list

	EndOfList()
		Determines if currPos == length

	Retrieve()
		Returns the list element specified by currPos

	operator =
		Allows aggregate assignment of list objects

	ReturnLength()
		Provides the number of items in the list
*/

#ifndef location_h
	#define location_h
	#include "location.h"	// For LocationRec
#endif

const char MAX_LENGTH_FIVE = 5;	// Maximum # of elements in the list

typedef LocationRec ItemType;	// Type of item stored in the list	

class ListClass5
{

	public:

	ListClass5();
	//Purpose:  Default constructor.  Initializes a list object to an empty list
	//Pre:		List has been instantiated
	//Post:		list's length is 0
	
	bool IsEmpty() const;			
	//Purpose:	Indicates whether or not the list is empty
	//Pre:		List has been instantiated
	//Post:		Returns true if list is empty and false, otherwise
	

	bool IsFull() const;			
	//Purpose:	Indicates whether or not the list is full
	//Pre:		List has been instantiated
	//Post:		Returns true if list is full and false, otherwise
					
	void Insert(ItemType item);	// Item to be added
	//Purpose:	Inserts item into the list
	//Pre:		List is not full
	//Post:		item has been inserted at the end of the current list

	bool Find(ItemType item);	// Item to be found
	//Purpose:	Determines whether or not item is in the list
	//Pre:		item is assigned a value
	//Post:		If item is in the list then true is returned  and currPos contains
	//				the index of the 1st occurence of item in the list, otherwise, 
	//				false is returned and currPos is at length.

	void  Delete();
	//Purpose:  Deletes an item from the list
	//Pre:		Method Find has been called to find the item to delete, and the 
	//				that item is in the list.CurrPos now points at the item to be deleted
	//Post:		The 1st occurrence of item has been deleted from the list

	void FirstPosition();
	//Purpose:  Moves to the beginning of the list
	//Pre:		List has been instantiated
	//Post:		currPos is 0

	void NextPosition();
	//Purpose:	Moves to the next element in the list
	//Pre:		List has been instantiated
	//Post:		currPos has been incremented by 1

	bool EndOfList() const;
	//Purpose:	Determines if the current position of the list is == to the length of the list
	//Pre:		List has been instantiated
	//Post:		Returns true if the current position of the list is == to the length of the list, and
	//				false, otherwise

	ItemType Retrieve() const;
	//Purpose:	Returns the current item in the list
	//Pre:		EndOfList is false
	//Post:		Returns the item at currPos

	virtual ListClass5 operator = (const ListClass5& orig);	// List to be copied
	//Purpose:	Overloads the = operator so that aggregate assignment is possible
	//Pre:		Orig contain the list to be copied
	//Post:		The applying operator contains a copy of the original list 

	char ReturnLength() const;
	//Purpose:	Provides the number of items in the list
	//Pre:		List has been instantiates
	//Post:		The number of items in the list has been returned


  private:

 	ItemType list[MAX_LENGTH_FIVE];	// Stores the items in the list
	char length;					// # of values currently in the list
	char currPos;					// Position of current element

};
