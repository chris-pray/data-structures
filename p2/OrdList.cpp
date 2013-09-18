/*
AUTHOR:
	Chris Pray

DATE:
	3/19/13

FILENAME:
	OrdList.cpp

PURPOSE:
	This file contains the implementation for all of the methods declared in OrdList.h
*/

#include "OrdList.h"	// For class declarations

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Implementation of Constructors/Destructors

OrdListClass::OrdListClass()
{
	// Initialize size to MAX_ENTRIES
	SetSize(MAX_ENTRIES);

} // End OrdListClass()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OrdListClass::~OrdListClass()
{
	ItemType* list = GetListPtr();	// Points to the list

	// Return the dynamic memory allocated to the list back to the heap
	delete [] list;

} // End ~OrdListClass()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OrdListClass::OrdListClass(/* In */ const OrdListClass& orig)	// The original OrdListClass object
{
	// Make a deep copy of orig
	operator=(orig);

} // End OrdListClass(const OrdListClass& orig)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Implementation of Methods that were Overridden

void OrdListClass::NextPosition()
{
	// If the current position in the list is less than the length of the list
	if(GetCurrPos() < GetLength())
	{
		// Increment the current position in the list by one
		SetCurrPos(GetCurrPos() + 1);

	} // End if

} // End NextPosition()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool OrdListClass::Find(/* in */ KeyType key)	// The key to search for
{
	ItemType* list = GetListPtr();			// Points to the list
	int mid;								// The position of the item in the list whose key is
											//  compared with key
	int first = 0;							// The position of the first item in the section of the list
											//  being searched
	int last = GetLength() - 1;				// The position of the last item in the section of the list
											//  being searched
	bool found = false;						// Gets true if an item in the list whose key equals key has
											//  been found, false otherwise
	bool moreToSearch = (first <= last);	// Gets true if there are more items in the list to search,
											//  false otherwise
	
	// While there are more items in the list to search and there has not been an item in the list whose
	//  key equals key found
	while(moreToSearch & !found)
	{
		// Calculate mid
		mid = (first + last) / 2;

		// If key is less than the key of the item in the list at position mid
		if(key < list[mid].key)
		{
			// Calculate first
			first = mid + 1;

			// Determine if there are more items in the list to search
			moreToSearch = (first <= last);

			// If there are not more items in the list to search
			if(!moreToSearch)
			{
				// Set the current position in the list
				SetCurrPos(mid + 1);

			} // End if

		} // End if
		// Else if key is greater than the key of the item in the list at position mid
		else if(key > list[mid].key)
		{
			// Calculate last
			last = mid - 1;

			// Determine if there are more items in the list to search
			moreToSearch = (first <= last);

			// If there are not more items in the list to search
			if(!moreToSearch)
			{
				// Set the current position in the list
				SetCurrPos(mid);

			} // End if

		} // End else if
		// Else key is equal to the key of the item in the list at position mid
		else
		{
			// The key was found
			found = true;

			// Set the current position in the list to mid
			SetCurrPos(mid);

		} // End else

	} // End while

	return found;

} // End Find(KeyType key)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::Insert(/* in */ ItemType target)	// The target to insert
{
	ItemType* list = NULL;	// Gets pointed to the list

	// If the list is empty
	if(IsEmpty())
	{
		// Point list to the list
		list = GetListPtr();

		// Insert target into the current position in the list
		list[GetCurrPos()] = target;

		// Increment the length of the list by one
		SetLength(GetLength() + 1);

	} // End if
	// Else the list is not empty
	else
	{
		// If there's no room in the list
		if(NoRoom())
		{
			// If the current position in the list is set to the length of the list
			if(GetCurrPos() == GetLength())
			{
				// Expand the size of the array
				Expand();

				// Point list to the list
				list = GetListPtr();

				// Copy each item in the list from currPos to the end of the list up one position
				memcpy(&list[GetCurrPos() + 1],											  // Destination
					   &list[GetCurrPos()],												  // Source
					   GetLength() * sizeof(ItemType) - GetCurrPos() * sizeof(ItemType)); // # of bytes
																						  //  to copy
			
				// Insert target into the current position in the list
				list[GetCurrPos()] = target;

				// Increment the length of the list by one
				SetLength(GetLength() + 1);

			} // End if
			// Else if target is not already in the list
			else if(Retrieve().key != target.key)
			{
				// Expand the size of the array
				Expand();

				// Point list to the list
				list = GetListPtr();
				
				// Copy each item in the list from currPos to the end of the list up one position
				memcpy(&list[GetCurrPos() + 1],											  // Destination
					   &list[GetCurrPos()],												  // Source
					   GetLength() * sizeof(ItemType) - GetCurrPos() * sizeof(ItemType)); // # of bytes
																						  //  to copy
				
				// Insert target into the current position in the list
				list[GetCurrPos()] = target;

				// Increment the length of the list by one
				SetLength(GetLength() + 1);

			} // End if
			// Else target is alreay in the list
			else
			{
				throw DuplicateKeyException(target.key,
					"DuplicateKeyException: Attempt to insert a duplicate key failed.");

			} // End else

		} // End if
		// Else there is no room in the list
		else
		{
			// If target is not already in the list
			if(Retrieve().key != target.key)
			{
				// Point list to the list
				list = GetListPtr();

				// Copy each item in the list from currPos to the end of the list up one position
				memcpy(&list[GetCurrPos() + 1],											  // Destination
					   &list[GetCurrPos()],												  // Source
					   GetLength() * sizeof(ItemType) - GetCurrPos() * sizeof(ItemType)); // # of bytes
																						  //  to copy
			
				// Insert target into the current position in the list
				list[GetCurrPos()] = target;

				// Increment the length of the list by one
				SetLength(GetLength() + 1);

			} // End if
			// Else target is alreay in the list
			else
			{
				throw DuplicateKeyException(target.key,
					"DuplicateKeyException: Attempt to insert a duplicate key failed.");

			} // End else

		} // End else

	} // End else

} // End Insert(ItemType target)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::Delete()
{
	// If the list is not empty
	if(!IsEmpty())
	{
		ItemType* list = GetListPtr();	// Points to the list

		// Decrement the length of the list by one
		SetLength(GetLength() - 1);

		// If currPos != length
		if(!EndOfList())
		{
			// Copy each item in the list from currPos + 1 to the end of the list down one position
			memcpy(&list[GetCurrPos()],											   // Destination
				&list[GetCurrPos() + 1],										   // Source
				GetLength() * sizeof(ItemType) - GetCurrPos() * sizeof(ItemType)); // # of bytes to copy

		} // End if
		
		// If the size of the list is greater than MAX_ENTRIES and the length of the list is less than
		//  OCCUPANCY_TRIGGER times the size of the list
		if(GetSize() > MAX_ENTRIES && GetLength() < OCCUPANCY_TRIGGER * GetSize())
		{
			// Contract the size of the list
			Contract();

		} // End if

	} // End if

} // End Delete()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::Clear()
{
	ItemType* list = GetListPtr();	// Points to the list

	// Return the dynamic memory allocated to the list back to the heap
	delete [] list;

	// Allocate enough memory for an array of MAX_ENTRIES items from the heap
	list = new ItemType[MAX_ENTRIES];

	// Set the pointer to the list to the new dynamic array
	SetListPtr(list);

	// Set the size of the list to MAX_ENTRIES
	SetSize(MAX_ENTRIES);

	// Set the current position in the list to FIRST_POSITION
	SetCurrPos(FIRST_POSITION);

	// Set the length of the list to EMPTY
	SetLength(EMPTY);

} // End Clear()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Implementation of Operators that were Overloaded

bool OrdListClass::operator==(const OrdListClass& rtOp)const	// List to test equallity against
{
	bool isEqual = false;	// Gets true if the calling object is equal to rtOp, otherwise false

	// If the length of the applying object's list is equal to the length of rtOp's list
	if(GetLength() == rtOp.GetLength())
	{
		ItemType* left = GetListPtr();			// Points to the applying object's list
		ItemType* right = rtOp.GetListPtr();	// Points to rtOp's list
		int index = FIRST_POSITION;				// The position in the list

		isEqual = true;

		// While the position in the list is within the bounds of the array and each key compared so far
		//  is equal
		while(index < GetLength() && isEqual)
		{
			// If the keys are not equal
			if(!(left[index].key == right[index].key))
			{
				isEqual = false;

			} // End if

			index++;

		} // End while

	} // End if

	return isEqual;

} // End operator== (const OrdListClass& rtOp)const

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool OrdListClass::operator!=(const OrdListClass& rtOp)const	// List to test equallity against
{
	return !operator==(rtOp);

} // End operator!= (const OrdListClass& rtOp)const

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OrdListClass OrdListClass::operator*(const OrdListClass& rtOp)const	// List to intersect with
{
	OrdListClass left;				// left.list gets pointed to the applying object's list
	OrdListClass right;				// right.list gets pointed to rtOp's list
	OrdListClass ordIntersection;	// Gets the intersection of the applying object's list and rtOp's
									//  list
	bool moreToSearch;				// Determines whether to keep iterating through the loop; Gets true
									//  if the current position in either the applying object's list or
									//  rtOp's list is not equal to the length of their list

	// Return the memory allocated to left's list back to the heap
	delete [] left.GetListPtr();

	// Point left.list to the applying object's list
	left.SetListPtr(GetListPtr());

	// Set left's length to the length of the applying object
	left.SetLength(GetLength());

	// Return the memory allocated to right's list back to the heap
	delete [] right.GetListPtr();

	// Point right.list to rtOp's list
	right.SetListPtr(rtOp.GetListPtr());

	// Set right's length to the length of rtOp
	right.SetLength(rtOp.GetLength());

	moreToSearch = !left.EndOfList() && !right.EndOfList();

	// While left's current position does not equal its length and right's current position does not
	//  equal its length
	while(moreToSearch)
	{
		// If the key at the current position of left is greater than the key at the current position of
		//  right
		if(left.Retrieve().key > right.Retrieve().key)
		{
			// Increment the current position of left by one
			left.NextPosition();

			moreToSearch = !left.EndOfList();

		} // End if
		// Else if the key at the current position of left is less than the key at the current position
		//  of right
		else if(left.Retrieve().key < right.Retrieve().key)
		{
			// Increment the current position of right by one
			right.NextPosition();

			moreToSearch = !right.EndOfList();

		} // End else if
		// Else the key's at the current positions of left and right are equal
		else
		{
			// Insert the item at the current position of left into the current position of
			//  ordIntersection
			ordIntersection.Insert(left.Retrieve());

			// Increment the current position of ordIntersection by one
			ordIntersection.NextPosition();

			// Increment the current position of left by one
			left.NextPosition();

			// Increment the current position of right by one
			right.NextPosition();

			moreToSearch = !left.EndOfList() && !right.EndOfList();

		} // End else

	} // End while

	// Point left.list and right.list to NULL
	left.SetListPtr(NULL);
	right.SetListPtr(NULL);

	return ordIntersection;

} // End operator* (const OrdListClass& rtOp)const

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OrdListClass OrdListClass::operator+(const OrdListClass& rtOp)const
{
	OrdListClass left;		// left.list gets pointed to the applying object's list
	OrdListClass right;		// right.list gets pointed to rtOp's list
	OrdListClass ordUnion;	// Gets the union of the applying object's list and rtOp's list
	bool moreToSearch;		// Determines whether to keep iterating through the loop; Gets true if the
							//  current position in either the applying object's list or rtOp's list is
							//  not equal to the length of their list

	// Return the memory allocated to left's list back to the heap
	delete [] left.GetListPtr();

	// Point left.list to the applying object's list
	left.SetListPtr(GetListPtr());

	// Set left's length to the length of the applying object
	left.SetLength(GetLength());

	// Return the memory allocated to right's list back to the heap
	delete [] right.GetListPtr();

	// Point right.list to rtOp's list
	right.SetListPtr(rtOp.GetListPtr());

	// Set right's length to the length of rtOp
	right.SetLength(rtOp.GetLength());

	moreToSearch = !left.EndOfList() && !right.EndOfList();

	// While left's current position does not equal its length and right's current position does not
	//  equal its length
	while(moreToSearch)
	{
		// If the key at the current position of left is greater than the key at the current position of
		//  right
		if(left.Retrieve().key > right.Retrieve().key)
		{
			// Insert the item at the current position of left into the current position of ordUnion
			ordUnion.Insert(left.Retrieve());

			// Increment the current position of ordUnion by one
			ordUnion.NextPosition();

			// Increment the current position of left by one
			left.NextPosition();

			moreToSearch = !left.EndOfList();

		} // End if
		// Else if the key at the current position of left is less than the key at the current position
		//  of right
		else if(left.Retrieve().key < right.Retrieve().key)
		{
			// Insert the item at the current position of right into the current position of ordUnion
			ordUnion.Insert(right.Retrieve());

			// Increment the current position of ordUnion by one
			ordUnion.NextPosition();

			// Increment the current position of right by one
			right.NextPosition();

			moreToSearch = !right.EndOfList();

		} // End else if
		// Else the key's at the current positions of left and right are equal
		else
		{
			// Insert the item at the current position of left into the current position of ordUnion
			ordUnion.Insert(left.Retrieve());

			// Increment the current position of ordUnion by one
			ordUnion.NextPosition();

			// Increment the current position of left by one
			left.NextPosition();

			// Increment the current position of right by one
			right.NextPosition();

			moreToSearch = !left.EndOfList() && !right.EndOfList();

		} // End else

	} // End while

	// If the current position of left does not equal the length of left
	if(!left.EndOfList())
	{
		// While the current position of left does not equal the length of left
		while(!left.EndOfList())
		{
			// Insert the item at the current position of left into the current position of ordUnion
			ordUnion.Insert(left.Retrieve());

			// Increment the current position of ordUnion by one
			ordUnion.NextPosition();

			// Increment the current position of left by one
			left.NextPosition();

		} // End while

	} // End if
	// Else if the current position of right does not equal the length of right
	else if(!right.EndOfList())
	{
		// While the current position of right does not equal the length of right
		while(!right.EndOfList())
		{
			// Insert the item at the current position of right into the current position of ordUnion
			ordUnion.Insert(right.Retrieve());

			// Increment the current position of ordUnion by one
			ordUnion.NextPosition();

			// Increment the current position of right by one
			right.NextPosition();

		} // End while

	} // End else if

	// Point left.list and right.list to NULL
	left.SetListPtr(NULL);
	right.SetListPtr(NULL);

	return ordUnion;

} // End operator+(const OrdListClass& rtOp) const

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::operator=(const OrdListClass& orig)	// Object to aggregately assign
{
	try
	{
		ItemType* newList = GetListPtr();	// Points to the applying object's list

		// Return the memory allocated to the list back to the heap
		delete [] newList;

		// Allocate memory for a new list the size of orig's list
		newList = new ItemType[orig.GetSize()];

		// Set the applying object's size to orig's size
		SetSize(orig.GetSize());

		// Copy orig's list to the list pointed to by newList
		memcpy(newList,							// Destination
			   orig.GetListPtr(),				// Source
			   GetSize() * sizeof(ItemType));	// # of bytes to copy

		// Set the applying object's list pointer to the list pointed to by newList
		SetListPtr(newList);

		// Set the current position of the applying object to the current position of orig
		SetCurrPos(orig.GetCurrPos());

		// Set the length of the applying object to the length of orig
		SetLength(orig.GetLength());

	} // End try
	catch(bad_alloc e)	// Failed to allocate memory
	{
		throw OutOfMemoryException("OutOfMemoryException : Not enough memory to complete operation.");

	} // End catch(bad_alloc e)

} // End operator=(const OrdListClass& orig)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Implementation of Protected Methods

void OrdListClass::Expand()
{
	try
	{
		// Allocate memory for an array twice the size of the applying object's list
		ItemType* newList = new ItemType[EXPANSION_FACTOR * GetSize()];	// Points to the expanded list

		ItemType* oldList = GetListPtr();	// Points to the applying object's list

		// Copy each item from the applying object's list into the list pointed to by newList
		memcpy(newList,							// Destination
			   oldList,							// Source
			   GetSize() * sizeof(ItemType));	// # of bytes to copy

		// Return the memory allocated to the applying object's list back to the heap
		delete [] oldList;

		// Point oldList to NULL
		oldList = NULL;

		// Set the applying object's list pointer to the list pointed to by newList
		SetListPtr(newList);

		// Set the applying object's size to twice its original size
		SetSize(EXPANSION_FACTOR * GetSize());

	} // End try
	catch(bad_alloc e)	// Failed to allocate memory
	{
		throw OutOfMemoryException("OutOfMemoryException : Not enough memory to complete operation.");

	} // End catch(bad_alloc e)

} // End Expand()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::Contract()
{
	try
	{
		// Allocate memory for an array half the size of the applying object's list
		ItemType* newList = new ItemType[int(GetSize() * CONTRACTION_FACTOR)];	// Points to the
																				//  expanded list

		ItemType* oldList = GetListPtr();	// Points to the applying object's list

		// Set the applying object's size to half its original size
		SetSize(int(GetSize() * CONTRACTION_FACTOR));

		// Copy each item from the applying object's list into the list pointed to by newList
		memcpy(newList,							// Destination
			   oldList,							// Source
			   GetSize() * sizeof(ItemType));	// # of bytes to copy

		// Return the memory allocated to the applying object's list back to the heap
		delete [] oldList;

		// Point oldList to NULL
		oldList = NULL;

		// Set the applying object's list pointer to the list pointed to by newList
		SetListPtr(newList);

	} // End try
	catch(bad_alloc e)	// Failed to allocate memory
	{
		throw OutOfMemoryException("OutOfMemoryException : Not enough memory to complete operation.");

	} // End catch(bad_alloc e)

} // End Contract()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool OrdListClass::NoRoom()
{
	return GetLength() == GetSize();

} // End NoRoom()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Implementation of PVF's

void OrdListClass::Print()
{
	// If the list is not empty
	if(!IsEmpty())
	{
		ItemType* list = GetListPtr();	// Points to the list

		// For each item in the list
		for(int i = 0; i < GetLength(); i++)
		{
			cout << "Index " << i << ": " << list[i].key << endl;

		} // End for

	} // End if
	// Else the list is empty
	else
	{
		cout << "The list is empty." << endl;

	} // End else

	cout << "Current position: " << GetCurrPos() << endl
		 << "Length: " << GetLength() << endl
		 << "Size: " << GetSize() << endl;

} // End Print()
