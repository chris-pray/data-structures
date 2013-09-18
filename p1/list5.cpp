/*
AUTHOR:
	Chris Pray

DATE:
	2/19/13

FILENAME:
	list5.cpp

Purpose:	
	This file contains the implementation for all of the methods declared in list5.h
*/

#ifndef list5_h
	#define list5_h
	#include "list5.h"	// For class declarations
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ListClass5::ListClass5()
{
	length = 0;
	currPos = 0;

} // End ListClass()
	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

bool ListClass5::IsEmpty() const
{
	return length == 0;

} // End IsEmpty()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ListClass5::IsFull() const
{
	return length == MAX_LENGTH_FIVE;

} // End IsFull()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ListClass5::Insert(/* In */ ItemType item)	// Item to be inserted
{
	// If the list is not full
	if(length < MAX_LENGTH_FIVE)
	{
		// Insert the item into the list
		list[length] = item;
		length++;

	} // End if

} // End Insert(ItemType item)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ListClass5::Find(/* In */ ItemType item)	//Item to be found
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

void ListClass5::Delete()
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

void ListClass5::FirstPosition()
{
	currPos = 0;

} // End FirstPosition()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ListClass5::NextPosition()
{
	currPos++;

} // End NextPosition()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ListClass5::EndOfList() const
{	
	return currPos == length;

} // End EndOfList()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ItemType ListClass5::Retrieve() const
{
	return list[currPos];

} // End Retrieve()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ListClass5 ListClass5:: operator = (/* In */ const ListClass5& orig) // List to be copied
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

char ListClass5::ReturnLength() const
{
	return length;

} // End ReturnLength()
