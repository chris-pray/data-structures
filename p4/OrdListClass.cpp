/*
AUTHOR:
	Chris Pray

DATE:
	4/18/13

FILENAME:
	OrdListClass.cpp

PURPOSE:
	This file contains the implementation for all of the methods declared in OrdListClass.h
*/

#include "OrdListClass.h"	// For class declarations

struct node
{  
	node* prev;		// Pointer to previous node in the list
	ItemType data;	// Contains the data defined in ItemType
	node* next;		// Pointer to next node in the list

}; // End node

//***************************************************************************************
//*																						*
//*                Constructor / Destructor / Copy Constructor							*
//*																						*
//***************************************************************************************

OrdListClass::OrdListClass()
{
	currPos = nullptr;
	tail = nullptr;

} // End OrdListClass()

//***************************************************************************************

OrdListClass::~OrdListClass()
{
	// Return all dynamically allocated memory to heap
	Clear();

} // End ~OrdListClass()

//***************************************************************************************

OrdListClass::OrdListClass( /* In */ const OrdListClass& orig )	// The list object to be copied
{
	currPos = nullptr;
	tail = nullptr;

	// Assign the applying object to a deep copy of orig
	operator=(orig);

} // End OrdListClass(const OrdListClass& orig)

//***************************************************************************************
//***************************************************************************************

bool OrdListClass::IsEmpty()const
{
	return tail == nullptr;

} // End IsEmpty()const

//***************************************************************************************

bool OrdListClass::IsFull()const
{
	return false;

} // End IsFull()const

//***************************************************************************************

void OrdListClass::FirstPosition()
{
	// If the list is not empty
	if( !IsEmpty() )
		currPos = tail->next;

} // End FirstPosition()

void OrdListClass::LastPosition()
{
	currPos = tail;

} // End LastPosition()

//***************************************************************************************

void OrdListClass::NextPosition()
{
	// If the list is not empty
	if( !IsEmpty() )
	{
		// If the current position in the list is at the last position in the list
		if( currPos == tail )
		{
			// If the current position in the list is at the last position in the list and an exception
			//  should be thrown
			if( EndOfList() )
			{
				throw PastEndOfListException
					("PastEndOfListException: The next position does not exist");

			} // End if

		} // End if
		// Else the current position in the list is not at the last position in the list
		else
		{
			currPos = currPos->next;

		} // End else

	} // End if
	// Else the list is empty
	else
	{
		throw PastEndOfListException("PastEndOfListException: The next position does not exist");

	} // End else

} // End NextPosition()

//***************************************************************************************

void OrdListClass::PrevPosition()
{
	// If the list is not empty
	if( !IsEmpty() )
	{
		// If the current position in the list is at the first position in the list
		if( currPos == tail->next )
		{
			// If the current position in the list is at the first position in the list and an exception
			//  should be thrown
			if( BeginningOfList() )
			{
				throw PastEndOfListException
					("PastEndOfListException: The previous position does not exist");

			} // End if

		} // End if
		// Else the current position in the list is not at the first position in the list
		else
		{
			currPos = currPos->prev;

		} // End else

	} // End if
	// Else the list is empty
	else
	{
		throw PastEndOfListException("PastEndOfListException: The previous position does not exist");

	} // End else

} // End PrevPosition()

//***************************************************************************************

bool OrdListClass::BeginningOfList()const
{
	static bool bol1 = false;	// 1st flag that must be true in order to return true
	static bool bol2 = false;	// 2nd flag that must be true in order to return true

	// If the list is not empty
	if( !IsEmpty() )
	{
		// If the current position in the list is at the first position in the list
		if( currPos == tail->next )
		{
			// If the 1st flag is not true
			if( !bol1 )
			{
				bol1 = true;
				return false;

			} // End if
			// Else if the 2nd flag is not true
			else if( !bol2 )
			{
				bol2 = true;
				return false;

			} // End else if
			// Else both flags are true
			else
			{
				bol1 = false;
				bol2 = false;
				return true;

			} // End else

		} // End if
		// Else the current position in the list is not at the first position in the list
		else
		{
			return false;

		} // End else

	} // End if
	// Else the list is empty
	else
	{
		return true;

	} // End else

} // End BeginningOfList()const

//***************************************************************************************

bool OrdListClass::EndOfList()const
{
	static bool eol1 = false;	// 1st flag that must be true in order to return true
	static bool eol2 = false;	// 2nd flag that must be true in order to return true

	// If the list is not empty
	if( !IsEmpty() )
	{
		// If the current position in the list is at the last position in the list
		if( currPos == tail )
		{
			// If the 1st flag is not true
			if( !eol1 )
			{
				eol1 = true;
				return false;

			} // End if
			// Else if the 2nd flag is not true
			else if( !eol2 )
			{
				eol2 = true;
				return false;

			} // End else if
			// Else both flags are true
			else
			{
				eol1 = false;
				eol2 = false;
				return true;

			} // End else

		} // End if
		// Else the current position in the list is not at the last position in the list
		else
		{
			return false;

		} // End else

	} // End if
	// Else the list is empty
	else
	{
		return true;

	} // End else

} // End EndOfList()const

//***************************************************************************************

ItemType OrdListClass::Retrieve()const
{
	// If the list is not empty
	if( !IsEmpty() )
		return currPos->data;
	// Else the list is empty
	else
		throw RetrieveOnEmptyException("RetrieveOnEmptyException: Cannot retrieve from empty list");

} // End Retrieve()const

//***************************************************************************************

void OrdListClass::Insert( /* In */ ItemType item )	// Item to be added
{
	try
	{
		node* temp = new node;	// Points to the node to be inserted
		temp->prev = nullptr;
		temp->next = nullptr;

		// Assign item to the data field of the node to be inserted
		temp->data = item;

		// If the key of the item to be inserted is not in the list
		if( !Find( item.key ) )
		{
			// If the list is not empty
			if( !IsEmpty() )
			{
				// If currPos is not at the end of the list
				if( currPos != tail )
				{
					// Set pointers so item gets inserted into the list at the position pointed to by
					//  currPos
					temp->prev = currPos->prev;
					temp->next = currPos;
					currPos->prev->next = temp;
					currPos->prev = temp;

				} // End if
				// Else currPos is at the end of the list
				else
				{
					// If the key of the item to be inserted is greater than the key of the last item in
					//  the list
					if( item.key > currPos->data.key )
					{
						// Set pointers so item gets inserted into the list at the position pointed to
						//  by currPos
						temp->prev = currPos->prev;
						temp->next = currPos;
						currPos->prev->next = temp;
						currPos->prev = temp;

					} // End if
					// Else the key of the item to be inserted is less than the key of the last item in
					//  the list
					else
					{
						// Set pointers so item gets inserted into the list at the position pointed to
						//  by currPos
						temp->prev = tail;
						temp->next = tail->next;
						tail->next->prev = temp;
						tail->next = temp;

						// Point tail to the inserted node
						tail = temp;

					} // End else if

				} // End else

			} // End if
			// Else the list is empty
			else
			{
				// Point tail to the inserted node
				tail = temp;

				// Point tail's prev and next pointers to itself
				tail->prev = tail;
				tail->next = tail;

			} // End else

			// Point currPos to the item just inserted
			currPos = temp;

		} // End if
		// Else the key of the item to be inserted is already in the list
		else
			throw DuplicateKeyException("DuplicateKeyException: Key already exists in list");

	} // End try
	catch( bad_alloc e )	// Could not dynamically assign memory for a node
	{
		throw OutOfMemoryException("OutOfMemoryException: Could not allocate memory from heap");

	} // End catch

} // End Insert(ItemType item)

//***************************************************************************************

bool OrdListClass::Find( /* In */ KeyType searchKey )	// Key to be found
{
	bool found = false;	// True if key was found, false otherwise

	// If the list is not empty
	if( !IsEmpty() )
	{
		// If the key to be found is equal to the key of the item at the current position in the list
		if( searchKey == currPos->data.key )
		{
			return true;

		} // End if
		// Else if the key to be found is equal to the key of the item at the last position in the list
		else if( searchKey == tail->data.key )
		{
			currPos = tail;

			return true;

		} // End else if
		// Else if the key to be found is less than the key of the item at the last position in the list
		else if( searchKey < tail->data.key )
		{
			currPos = tail;

			return false;

		} // End else if
		// Else the list must be iterated to search for the key
		else
		{
			// Set the current position in the list to the first position in the list
			FirstPosition();

			do
			{
				// If searchKey equals the key at the current position in the list
				if( searchKey == currPos->data.key )
				{
					found = true;

				} // End if
				// Else the key to be found does not equal the key at the current position in the list
				else
				{
					// Set the current position in the list to the next position in the list
					currPos = currPos->next;

				} // End else

			}while( currPos != tail->next && searchKey <= currPos->data.key && !found );
			// While the end of the list has not been reached, searchKey is <= to the key of the item at
			//  the current position of the list, and searchKey has not yet been found

		} // End else

	} // End if

	return found;

} // End Find(KeyType searchKey)

//***************************************************************************************

void OrdListClass::Delete()
{
	// If the list is not empty
	if( !IsEmpty() )
	{
		// If there is only 1 item in the list
		if( tail == tail->next )
		{
			tail = nullptr;

		} // End if
		// Else there are more than 1 items in the list
		else
		{
			// If the current position in the list is not the last item in the list
			if( currPos == tail )
				tail = tail->prev;

			// Set pointers to not include the node at the current position in the list in the list
			currPos->prev->next = currPos->next;
			currPos->next->prev = currPos->prev;

		} // End else

		// Return the dynamically allocated memory of the node pointed to by currPos to the heap
		delete currPos;

		// If the list is not empty
		if( !IsEmpty() )
			// Set the current position in the list to the first position in the list
			FirstPosition();
		// Else the list is empty
		else
			currPos = nullptr;

	} // End if

} // End Delete()

//***************************************************************************************

int OrdListClass::ReturnLength()
{
	int length = 0;	// The length of the list

	// If the list is not empty
	if( !IsEmpty() )
	{
		OrdListClass temp;	// A shallow copy of the applying object

		temp.tail = tail;

		// Set the current position in temp's list to its first position
		temp.FirstPosition();

		do
		{
			length++;

			temp.currPos = temp.currPos->next;

		}while( temp.currPos != temp.tail->next );
		// While the end of temp's list has not been reached

		temp.tail = nullptr;

	} // End if

	return length;

} // End ReturnLength()

//***************************************************************************************

void OrdListClass::Clear()
{
	// Set the current position in the list to the first position in the list
	FirstPosition();

	// While the list is not empty
	while( !IsEmpty() )
		// Remove the item at the current position in the list from the list
		Delete();

} // End Clear()

//***************************************************************************************

void OrdListClass::operator=( /* In */ const OrdListClass& orig )	// Object to be copied
{
	// Empty the applying object's list
	Clear();

	// If orig's list is not empty
	if( !orig.IsEmpty() )
	{
		OrdListClass origCopy;			// Gets a shallow copy of orig
		node* applyingPtr = nullptr;	// Points to a node in the applying object's list

		origCopy.tail = orig.tail;

		// Set the current position in origCopy's list to the first position in its list
		origCopy.FirstPosition();

		try
		{
			do
			{
				// Insert an item equal to the item at the current position in origCopy's list into the
				//  applying object
				Insert( origCopy.Retrieve() );

				origCopy.currPos = origCopy.currPos->next;

			}while( origCopy.currPos != origCopy.tail->next );
			// While the end of origCopy's list has not been reached

			// Set the current position in the applying object's list to the respective item in orig's
			//  list
			Find( orig.currPos->data.key );

			origCopy.tail = nullptr;

		} // End try
		catch( bad_alloc e )	// Could not dynamically assign memory for a node
		{
			throw OutOfMemoryException("OutOfMemoryException: Could not allocate memory from heap");

		} // End catch

	} // End if	

} // End operator=(const OrdListClass& orig)

//***************************************************************************************

OrdListClass OrdListClass::operator+( /* In */ const OrdListClass& rtOp)const	// The object to merge
																				//  with the applying
																				//  object
{
	OrdListClass ordUnion;	// An OrdListClass object to store the union of the applying object's list
							//  and rtOp's list
	
	try
	{
		// If the applying object's list is not empty and rtOp's list is not empty
		if( !IsEmpty() && !rtOp.IsEmpty() )
		{
			OrdListClass rightCopy;	// Gets a shallow copy of rtOp

			ordUnion = *this;

			rightCopy.tail = rtOp.tail;

			// Set the current position in rightCopy's list to its first position
			rightCopy.FirstPosition();

			do
			{
				// If the key of the item at the current position in rightCopy's list is not already in
				//  ordUnion's list
				if( !ordUnion.Find( rightCopy.currPos->data.key ) )
				{
					// Insert the item at the current position of rightCopy's list into ordUnion's list
					ordUnion.Insert( rightCopy.currPos->data );

				} // End if

				rightCopy.currPos = rightCopy.currPos->next;

			}while( rightCopy.currPos != rightCopy.tail->next );
			// While the end of rightCopy's list has not been reached

			rightCopy.tail = nullptr;

		} // End if
		// Else if the applying object's list is not empty
		else if( !IsEmpty() )
			ordUnion = *this;
		// Else if rtOp's list is not empty
		else if( !rtOp.IsEmpty() )
			ordUnion = rtOp;

		return ordUnion;

	} // End try
	catch( bad_alloc e )	// Could not dynamically assign memory for a node
	{
		throw OutOfMemoryException("OutOfMemoryException: Could not allocate memory from heap");

	} // End catch

} // End operator+(const OrdListClass& rtOp)const

//***************************************************************************************

OrdListClass OrdListClass::operator*( /* In */ const OrdListClass& rtOp)const	// The object to
																				//  intersect with the
																				//  applying object
{
	OrdListClass ordIntersection;	// An OrdListClass object to store the intersection of the applying
									//  object's list and rtOp's list

	try
	{
		// If the applying object's list is not empty and rtOp's list is not empty
		if( !IsEmpty() && !rtOp.IsEmpty() )
		{
			OrdListClass rightCopy;	// Gets a shallow copy of rtOp
			OrdListClass leftCopy;	// Gets a shallow copy of the applying object

			rightCopy.tail = rtOp.tail;
			leftCopy.tail = tail;

			// Set the current positions of rightCopy's list and leftCopy's list to their first
			//  positions
			rightCopy.FirstPosition();
			leftCopy.FirstPosition();

			do
			{
				// If the key of the item at the current position of rightCopy's list is found within an
				//  item in leftCopy's list
				if( leftCopy.Find( rightCopy.currPos->data.key ) )
				{
					// Insert an item equal to the item at the current position in rightCopy's list into
					//  ordIntersection's list
					ordIntersection.Insert( rightCopy.currPos->data );

				} // End if

				rightCopy.currPos = rightCopy.currPos->next;

			}while( rightCopy.currPos != rightCopy.tail->next );
			// While the end of rightCopy's list has not been reached

			rightCopy.tail = nullptr;
			leftCopy.tail = nullptr;

		} // End if

		return ordIntersection;

	} // End try
	catch( bad_alloc e )	// Could not dynamically assign memory for a node
	{
		throw OutOfMemoryException("OutOfMemoryException: Could not allocate memory from heap");

	} // End catch

} // End operator*(const OrdListClass& rtOp)const

//***************************************************************************************

bool OrdListClass::operator==( /* In */ const OrdListClass& rtOp)const	// The object to test equallity
																		//  against the applying object
{
	OrdListClass leftCopy;	// Gets a shallow copy of the applying object
	OrdListClass rightCopy;	// Gets a shallow copy of rtOp
	bool equal = true;		// Gets true if leftCopy's list is equal to rightCopy's list, otherwise gets
							//  false

	leftCopy.tail = tail;
	rightCopy.tail = rtOp.tail;

	// If the length of leftCopy's list does not equal the length of rightCopy's list
	if( leftCopy.ReturnLength() != rightCopy.ReturnLength() )
	{
		equal = false;

	} // End if
	// Else the length of leftCopy's list equals the length of rightCopy's list
	else
	{
		// Set the current positions in rightCopy's and leftCopy's lists to their first positions
		rightCopy.FirstPosition();
		leftCopy.FirstPosition();

		do
		{
			// If the key of the item at the current position in rightCopy's list is found in an item in
			//  leftCopy's list
			if( !leftCopy.Find( rightCopy.currPos->data.key ) )
			{
				equal = false;

			} // End if
			// If the key of the item at the current position in rightCopy's list is not found in an
			//  item in leftCopy's list
			else
			{
				rightCopy.currPos = rightCopy.currPos->next;

			} // End else

		}while( equal && rightCopy.currPos != rightCopy.tail->next );
		// While rightCopy's list still equals leftCopy's list and the end of rightCopy's list has not
		//  been reached

	} // End else

	leftCopy.tail = nullptr;
	rightCopy.tail = nullptr;

	return equal;

} // End operator==(const OrdListClass& rtOp)constS

//***************************************************************************************

bool OrdListClass::operator!=( /* In */ const OrdListClass& rtOp)const	// The object to test
																		//  inequallity against the
																		//  applying object
{
	return !operator==( rtOp );

} // End operator!=(const OrdListClass& rtOp)const