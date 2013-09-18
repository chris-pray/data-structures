/*
AUTHOR:
	Chris Pray

DATE:
	2/19/13

FILENAME:
	list.cpp

Purpose:	
	This file contains the implementation for all of the methods declared in list.h
*/

#ifndef list_h
	#define list_h
	#include "list.h"	// For class declarations
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ListClass::ListClass()
{
	length = 0;
	currPos = 0;

} // End ListClass()
	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

bool ListClass::IsEmpty() const
{
	return length == 0;

} // End IsEmpty()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ListClass::IsFull() const
{
	return length == MAX_LENGTH;

} // End IsFull()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ListClass::Insert(/* In */ ItemType item)	// Item to be inserted
{
	// If the list is not full
	if(length < MAX_LENGTH)
	{
		// Insert the item into the list
		list[length] = item;
		length++;

	} // End if

} // End Insert(ItemType item)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ListClass::Find(/* In */ ItemType item)	//Item to be found
{
	char ind = 0;

	// While there are more items to look at
	while(ind < length)
	{
		// If found
		if(list[ind].row == item.row &&
		   list[ind].col == item.col &&
		   list[ind].dep == item.dep)
		{
			// Set the current position of the list
			currPos = ind;

			return true;

		} // End if

		ind++;

	} // End while

	// Not found
	return false;

} // End Find(ItemType item)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ListClass::Delete()
{
	// Loop through each element in the list
	for(char ind = currPos; ind < length - 1; ind++)
	{
		// Shuffle up to delete
		list[ind] = list[ind+1];

	} // End for
	
	length--;

} // End Delete()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ListClass::FirstPosition()
{
	currPos = 0;

} // End FirstPosition()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ListClass::NextPosition()
{
	currPos++;

} // End NextPosition()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ListClass::EndOfList() const
{	
	return currPos == length;

} // End EndOfList()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ItemType ListClass::Retrieve() const
{
	return list[currPos];

} // End Retrieve()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ListClass ListClass:: operator = (/* In */ const ListClass& orig) // List to be copied
{	
	// Copy length
	length = orig.length;		

	// Iterate through original list
	for(char ind = 0; ind < length; ind++)
	{
		// Copy item
		list[ind] = orig.list[ind];		

	} // End for

	// Copy currPos
	currPos = orig.currPos;

	return *this;

} // End operator = (const ListClass& orig)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char ListClass::ReturnLength() const
{
	return length;

} // End ReturnLength()
