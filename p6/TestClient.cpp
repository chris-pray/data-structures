/*
AUTHOR:
	Chris Pray

DATE:
	5/10/13

FILENAME:
	TestClient.cpp

PURPOSE:
	This file applies white-box, black-box, unit, and integration testing on the methods of the included
	OrdListClass implementation. It is ensured that when the methods are used within their context, they
	will meet their preconditions and postconditions and perform as they are meant to. In most cases,
	the user of this class is responsible for their own actions but exceptions have been implemented to
	help catch user mistakes. Exceptions that can be caught are described in detail in the EXCEPTION
	HANDLING section of this heading.

INPUT:
	Item keys are read in from the input file defined as FILE_NAME and are used to reconstruct an
	identicle OrdListClass object as the one which printed the keys to the file.

PROCESSING:
	The methods of this implementation of OrdListClass are integrated in order to test each executable
	path to ensure proper function:
	
		The default constructor is called enough times to instantiate an appropriate number of
		OrdListClass objects. 

		Initially, two lists are built (list1 and list2) while testing the methods Find, IsFull, and
		Insert.

		IsEmpty is tested by calling it from an empty list and a non-empty list.

		Find is tested further by determining if the correct result is returned when called from a list
		that contains the key being passed and from a list that does not contain the key being passed.

		ReturnLength is tested by calling it from an empty list and a non-empty list and comparing the
		values returned against the values that should be returned.

		FirstPosition, Retrieve, NextPosition, and EndOfList are tested together because that is the
		only context they should be used in. They are tested by setting up a loop that iterates through
		each location in a list, starting at the first in-order location, while printing the key at each
		location.

		Retrieve is further tested to verify that a InvalidRetrieveException is thrown when trying to
		retrieve from an empty list or a non-empty list whose current position is NULL.

		The Copy Constructor is tested by instantiated deep copies of an empty list and two non-empty
		lists.

		PrintScreen and PrintReverse are called to verify that the copy constructor works correctly
		while also verifying that they themselves also work.

		Clear is called on an empty list and a non-empty list and then IsEmpty is called to verify that
		the lists are empty.

		operator= assigns an empty list to an object and non-empty lists to objects and PrintScreen is
		then called to verify that operator= worked correctly. Retrieve is called on both the object
		that called operator= and the object that the applying object was assigned to to verify that
		their current positions are both respectively pointing to the same item.

		Delete is tested with Find and nodes which were leaves, nodes which had only one subtree, and
		nodes which had two subtrees are deleted. PrintScreen is then called to verify that Delete
		worked correctly.

		operator== and operator!= are tested to verify they return the correct values when the applying
		object is empty and the parameter is empty, when the applying object is empty and the parameter
		is not empty, when the applying object is not empty and the parameter is empty, when both the
		applying object and the parameter are not empty but are not equal, and when both the applying
		object and the parameter are not empty but are equal.

		PrintFile and PrintAsExists are tested together to verify that PrintAsExists prints a visual
		representation of a tree and PrintFile prints keys to the file defined with FILE_NAME so that an
		exact replica of the object which called PrintFile can be created when the keys are read back
		in. Find, IsFull, and Insert are called when reading in the keys from the file to rebuild the
		object that called PrintFile.

		operator+ is tested with PrintScreen and PrintAsExists. PrintScreen is called on the two lists
		which are merged and PrintAsExists is called on the resulting object after operator+ is called
		to verify each key from both lists appears once and only once in the object and that the object
		is a complete tree.

OUTPUT:
	When appropriate, prompts are printed to the console to inform the user when method executions are
	working properly. PrintScreen, PrintReverse, and PrintAsExists each print data stored in an object.
	PrintFile prints keys to an output file defined in FILE_NAME.

ASSUMPTIONS:
	This OrdListClass implementation functions properly when its methods are used within the context for
	which they are meant. However, the user of this OrdListClass implemetation is resposible for any
	actions they may take when they use a method from this class outside of the context for which it is
	meant:

		A call to FirstPosition is meant to be followed directly with a while loop that tests for
		!EndOfList and modifies the loop control variable by calling NextPosition.
		
		Unless Retrieve is used to access each item as that loop iterates, it must be preceeded with a
		call to Find and only be called if Find returned true.
		
		A call to Find should preceed a call to Insert, and Insert should only be called if Find
		returned false. 
		
		A call to Find should preceed a call to Delete and Delete should only be called if Find returned
		true. The same key should be passed with Delete as was passed with Find.

EXCEPTION HANDLING:

	DuplicateKeyException
		When an attempt to insert an item into a list with a key equal to a key already in the list

	InvalidRetrieveException
		When an attempt to retrieve an item from an empty list or from an invalid location is made. An
		invalid location is one where the current position in a list is NULL. This can happen after Find
		is called on an object that doesn't contain an item with the key passed to Find or after
		NextPosition is called when the current position was at the last in-order node in the list.

	OutOfMemoryException
		When failure to allocate dynamic memory occurs

ERROR CHECKING:
	Before inserting an item into any list, the list is first checked to see if it is full.

SUMMARY OF METHODS:
	None

*/

#pragma once

typedef int KeyType;

// Libraries / Header Files:
#include "ItemType.h"	// For data
#include "OrdList.h"	// For OrdListClass objects
#include <iostream>		// For input/output
#include <fstream>		// For file input/output
#include <string>		// For string data type
#include <cstdlib>		// For exit
using namespace std;

// Prototypes:
void PrintToScreen( ItemType& );
	// Prints the key of item to the console, centered in a width of five. If the key is more than four
	//  characters long, "#### " is printed.
void PrintToFile( ItemType&, ofstream& );
	// Prints the key of item to an output file, followed by a space.

// Constants:
const string FILE_NAME = "data.out";	// Name of file to print keys of an OrdListClass object to that
										//  can be used to rebuild an OrdListClass object of the same
										//  shape

void main()
{
	ItemType item;	// An item used with the testing of OrdListClass objects
	ifstream din;	// Input file stream variable
	ofstream dout;	// Output file stream variable

	try
	{
		// Instantiate OrdListClass objects
		OrdListClass<ItemType> emptyList, list1, list2, list2Rebuild, unionList;

		//***************************************************************
		// Building list1
		// Testing Find, IsFull, and Insert

		item.key = 10;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		item.key = 9;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		item.key = 15;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		item.key = 6;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		item.key = 12;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		item.key = 17;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		item.key = 1;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		item.key = 7;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		item.key = 2;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		item.key = 8;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		item.key = 3;
		// If the key is not in list1 and list1 is not full
		if( !list1.Find( item.key ) && !list1.IsFull() )
			// Insert the item into list1
			list1.Insert( item );

		//***************************************************************
		// Building list2
		// Testing Find, IsFull, and Insert

		item.key = 12;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 8;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 15;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 5;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 11;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 20;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 3;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 9;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 18;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 1;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 4;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 10;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		item.key = 19;
		// If the key is not in list2 and list2 is not full
		if( !list2.Find( item.key ) && !list2.IsFull() )
			// Insert the item into list2
			list2.Insert( item );

		//***************************************************************
		// Testing IsEmpty
		
		// If emptyList is empty
		if( emptyList.IsEmpty() )
			cout << "emptyList is empty" << endl;
		// Else emptyList is not empty
		else
			cout << "IsEmpty does not work" << endl;

		// If list1 is not empty
		if( !list1.IsEmpty() )
			cout << "list1 is not empty" << endl;
		// Else list1 is empty
		else
			cout << "IsEmpty does not work" << endl;

		cout << endl;

		//***************************************************************
		// Testing Find

		// If the item's key is not in list1
		if( !list1.Find( item.key ) )
			cout << item.key << " is not in list1" << endl;
		// Else the item's key is in list1
		else
			cout << "Find does not work" << endl;

		// If the item's key is in list2
		if( list2.Find( item.key ) )
			cout << item.key << " is in list2" << endl;
		// Else the item's key is not in list2
		else
			cout << "Find does not work" << endl;

		cout << endl;

		//***************************************************************
		// Testing ReturnLength

		// If the length of emptyList is 0 and the length of list1 is 11
		if( emptyList.ReturnLength() == 0 && list1.ReturnLength() == 11 )
			cout << "emptyList has 0 items" << endl
				 << "list1 has 12 items" << endl;
		// Else the length of emptyList is not 0 or the length of list1 is not 11
		else
			cout << "ReturnLength does not work" << endl;

		cout << endl;

		//***************************************************************
		// Testing FirstPosition, Retrieve, NextPosition, and EndOfList

		cout << "list1: ";
		// Iterate through each item in the list
		list1.FirstPosition();
		while( !list1.EndOfList() )
		{
			cout << list1.Retrieve().key << " ";
			list1.NextPosition();

		} // End while

		cout << endl;

		cout << "list2: ";
		// Iterate through each item in the list
		list2.FirstPosition();
		while( !list2.EndOfList() )
		{
			cout << list2.Retrieve().key << " ";
			list2.NextPosition();

		} // End while

		cout << endl << endl;

		//***************************************************************
		// Testing InvalidRetrieveException

		try
		{
			// Try to retrieve an item from an empty list
			cout << emptyList.Retrieve().key << endl;

		} // End try
		catch( InvalidRetrieveException e )
		{
			cout << e.GetMessage() << endl;

		} // End catch

		try
		{
			// Try to retrieve an item that's not in the list
			list1.Find( item.key );
			cout << list1.Retrieve().key << endl;

		} // End try
		catch( InvalidRetrieveException e )
		{
			cout << e.GetMessage() << endl;

		} // End catch

		cout << endl;

		//***************************************************************
		// Testing Copy Constructor

		// Instantiate deep copies of emptyList, list1, and list2
		OrdListClass<ItemType> emptyListCopy( emptyList );
		OrdListClass<ItemType> list1Copy( list1 );
		OrdListClass<ItemType> list2Copy( list2 );

		//***************************************************************
		// Testing PrintScreen and PrintReverse

		cout << "emptyList forwards: ";
		emptyList.PrintScreen( PrintToScreen );
		cout << endl;
		cout << "emptyList backwards: ";
		emptyList.PrintReverse( PrintToScreen );
		cout << endl;
		cout << "emptyListCopy forwards: ";
		emptyListCopy.PrintScreen( PrintToScreen );
		cout << endl;

		cout << "list1 forwards: ";
		list1.PrintScreen( PrintToScreen );
		cout << endl;
		cout << "list1 backwards: ";
		list1.PrintReverse( PrintToScreen );
		cout << endl;
		cout << "list1Copy forwards: ";
		list1Copy.PrintScreen( PrintToScreen );
		cout << endl;

		cout << "list2 forwards: ";
		list2.PrintScreen( PrintToScreen );
		cout << endl;
		cout << "list2 backwards: ";
		list2.PrintReverse( PrintToScreen );
		cout << endl;
		cout << "list2Copy forwards: ";
		list2Copy.PrintScreen( PrintToScreen );
		cout << endl << endl;

		//***************************************************************
		// Testing Clear

		emptyListCopy.Clear();
		cout << "emptyListCopy is Cleared" << endl;
		// If the list is empty
		if( emptyListCopy.IsEmpty() )
			cout << "emptyListCopy is empty" << endl;
		// Else the list is not empty
		else
			cout << "Clear does not work" << endl;

		list1Copy.Clear();
		cout << "list1Copy is Cleared" << endl;
		// If the list is empty
		if( list1Copy.IsEmpty() )
			cout << "list1Copy is empty" << endl;
		// Else the list is not empty
		else
			cout << "Clear does not work" << endl;

		cout << endl;

		//***************************************************************
		// Testing operator=

		emptyListCopy = emptyList;
		cout << "emptyList has been assigned to emptyListCopy" << endl;
		cout << "emptyList: ";
		emptyList.PrintScreen( PrintToScreen );
		cout << endl;
		cout << "emptyListCopy: ";
		emptyListCopy.PrintScreen( PrintToScreen );
		cout << endl;

		list1.Find( 9 );
		list1Copy = list1;
		cout << "list1 has been assigned to list1Copy" << endl;
		cout << "list1: ";
		list1.PrintScreen( PrintToScreen );
		cout << endl;
		cout << "The key of the item at the current position is: " << list1.Retrieve().key << endl;
		cout << "list1Copy: ";
		list1Copy.PrintScreen( PrintToScreen );
		cout << endl;
		cout << "The key of the item at the current position is: " << list1Copy.Retrieve().key << endl;
		cout << endl;

		//***************************************************************
		// Testing Delete

		cout << "list1Copy: ";
		list1Copy.PrintScreen( PrintToScreen );
		cout << endl;

		item.key = 3;
		// If the item was found in the list
		if( list1Copy.Find( item.key ) )
			list1Copy.Delete( item.key );
		cout << item.key << " has been Deleted" << endl;

		item.key = 7;
		// If the item was found in the list
		if( list1Copy.Find( item.key ) )
			list1Copy.Delete( item.key );
		cout << item.key << " has been Deleted" << endl;

		item.key = 15;
		// If the item was found in the list
		if( list1Copy.Find( item.key ) )
			list1Copy.Delete( item.key );
		cout << item.key << " has been Deleted" << endl;

		cout << "list1Copy: ";
		list1Copy.PrintScreen( PrintToScreen );
		cout << endl << endl;

		//***************************************************************
		// Testing operator== and operator!=

		// If emptyList equals emptyListCopy, emptyList does not equal list1,
		//  list1 does not equal empty list, list1 does not equal list2,
		//  and list2 equals list2Copy
		if( emptyList == emptyListCopy && 
			!( emptyList == list1 ) &&
			!( list1 == emptyList ) &&
			!( list1 == list2 ) &&
			list2 == list2Copy )
			cout << "operator== works" << endl;
		// Else emptyList does not equal emptyListCopy, emptyList equals list1,
		//  list1 equals empty list, list1 equals list2, or list2 does not equal list2Copy
		else
			cout << "operator== does not work" << endl;

		// If emptyList equals emptyListCopy, emptyList does not equal list1,
		//  list1 does not equal empty list, list1 does not equal list2,
		//  and list2 equals list2Copy
		if( !( emptyList != emptyListCopy ) &&
			emptyList != list1 &&
			list1 != emptyList &&
			list1 != list2 &&
			!( list2 != list2Copy ) )
			cout << "operator!= works" << endl;
		// Else emptyList does not equal emptyListCopy, emptyList equals list1,
		//  list1 equals empty list, list1 equals list2, or list2 does not equal list2Copy
		else
			cout << "operator!= does not work" << endl;

		//***************************************************************
		// Testing PrintFile and PrintAsExists

		dout.open( FILE_NAME.c_str() );

		cout << "list2:" << endl;
		list2.PrintAsExists( PrintToScreen );

		list2.PrintFile( PrintToFile, dout );

		dout.close();

		din.open( FILE_NAME.c_str() );

		din >> item.key;

		// While the end of the file has not been reached
		while( din )
		{
			// If the item was not found in the list and the list is not full
			if( !list2Rebuild.Find( item.key ) && !list2Rebuild.IsFull() )
				// Insert the item into the list
				list2Rebuild.Insert( item );

			din >> item.key;

		} // End while

		din.close();

		cout << "list2Rebuild:" << endl;
		list2Rebuild.PrintAsExists( PrintToScreen );

		//***************************************************************
		// Testing operator+ and PrintAsExists

		cout << "list1: ";
		list1.PrintScreen( PrintToScreen );
		cout << endl;
		cout << "list2: ";
		list2.PrintScreen( PrintToScreen );
		cout << endl;

		unionList = list1 + list2;

		cout << "unionList: ";
		unionList.PrintScreen( PrintToScreen );
		cout << endl << endl;

		unionList.PrintAsExists( PrintToScreen );

	} // End try
	catch( OutOfMemoryException e )
	{
		cout << e.GetMessage() << endl;

		exit( EXIT_FAILURE );

	} // End catch

} // End main()

//******************************************************************************************************

// Purpose:	Prints the key of item to the console, centered in a width of five. If the key is more than
//			four characters long, "#### " is printed.
// Pre:		item.key has been defined
// Post:	If the key is less than five characters, it has been printed to the console, centered in a
//			width of five. Otherwise "#### " has been printed to the console.
void PrintToScreen( /* In */ ItemType& item )	// The item whose key to print to the console
{
	// If the key is greater than 9,999
	if( item.key > 9999 )
		cout << "#### ";
	// Else if the key is greater than 999 and less than or equal to 9,999
	else if( item.key > 999 )
		cout << item.key << " ";
	// Else if the key is greater than 99 and less than or equal to 999
	else if( item.key > 99 )
		cout << " " << item.key << " ";
	// Else if the key is greater than 9 and less than or equal to 99
	else if( item.key > 9 )
		cout << " " << item.key << "  ";
	// Else if the key is greater than or equal to 0 and less than or equal to 9
	else if( item.key >= 0 )
		cout << "  " << item.key << "  ";
	// Else if the key is less than -999
	else if( item.key < -999 )
		cout << "#### ";
	// Else if the key is less than -99 and greater than or equal to -999
	else if( item.key < -99 )
		cout << item.key << " ";
	// Else if the key is less than -9 and greater than or equal to -99
	else if( item.key < -9 )
		cout << " " << item.key << " ";
	// Else if the key is less than 0 and greater than or equal to -9
	else
		cout << " " << item.key << "  ";

} // End PrintToScreen( ItemType& item )

//******************************************************************************************************

// Purpose:	Prints the key of item to an output file, followed by a space.
// Pre:		item.key has been defined. dout has been associated with an output file.
// Post:	The key, followed by a space, has been printed to the output file.
void PrintToFile( /* In */ ItemType& item,	// The item whose key to print to the output file
				  /* In */ ofstream& dout )	// Output file stream variable
{
	dout << item.key << " ";

} // End PrintToFile( ItemType& item, ofstream& dout )