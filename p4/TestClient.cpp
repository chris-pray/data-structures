/*
AUTHOR:
Chris Pray

DATE:
4/18/13

FILENAME:
TestClient.cpp

PURPOSE:
	This file applies white-box and black-box testing on the methods of the included OrdListClass
	implementation. It is ensured that when the methods are used within their context, they will meet
	their preconditions and postconditions and perform as they are meant to. In most cases, the user of
	this class is responsible for their own actions but exceptions have been implemented to help catch
	user mistakes. Exceptions that can be caught are described in detail in the EXCEPTION HANDLING
	section of this heading.

INPUT:
	None

PROCESSING:
	The methods of this implementation of OrdListClass are integrated in order to test each executable
	path to ensure proper function. The default constructor is called enough times to instantiate an
	appropriate number of OrdListClass objects. The copy constructor is called three times, once with an
	empty list argument, once with a single item list argument, and once with a multiple item list
	argument. IsEmpty is called on an empty list and a non-empty list. IsFull is called before every
	insert. FirstPosition is used to intialize an LCV for a while loop which calls EndOfList in its test
	and calls NextPosition to modify the LCV. LastPosition is called to initiallize an LCV for a while
	loop which calls BeginningOfList in its test and calls PrevPosition to modify the LCV. Retrieve is
	also called on an empty list and the RetrieveOnEmptyException is caught. Insert is called to insert
	items into an empty list, into the middle of a list, directly before the last position in the list,
	and after the last position in the list. Find is called with arguements that equal a key of an item
	pointed to by currPos, a key of an item pointed to by tail, and a key of an item in the middle of 
	the list. Delete is called on an empty list, a list with one item, a list whose current position is
	the last position, and a list whose current position is in the middle of the list. ReturnLength is
	called on an empty list, a list with one item, and a list with multiple items. Clear is called on an
	empty list and a non-empty list. operator= is called, being passed an empty list as an argument, a
	single-itemed list as an argument, and a multiple-itemed list as an argument. operator+ is called
	when both operands are empty, when one of the operands is empty, when the operands are not empty and
	equal, and when the operands are not empty and not equal. operator* is called when both operands are
	empty, when the operands have some of the same items, when the operands, have all of the same items,
	and when the operands have none of the same items. operator== and operator!= are called when the
	operands have different lengths, when the operands have the same lengths but are unequal, and when
	the operands have the same lengths and are equal.

OUTPUT:
	When appropriate, prompts are printed to the console to inform the user when method executions are
	working properly.

ASSUMPTIONS:
	This OrdListClass implementation functions properly when its methods are used within the context for
	which they are meant. However, the user of this OrdListClass implemetation is resposible for any
	actions they may take when they use a method from this class outside of the context for which it is
	meant. This means that a call to FirstPosition is meant to be followed directly with a while loop
	that tests for !EndOfList and modifies the loop control variable by calling NextPosition. Similarly,
	a call to LastPosition is meant to be followed directly with a while loop that tests for
	!BeginningOfList and modifies the loop control variable by calling PrevPosition. Those are the only
	contexts in which EndOfList, NextPosition, BeginningOfList, and PrevPosition are meant to be used
	in. I cannot guarantee that this OrdListClass implementation will function properly if those methods
	are not used within those contexts.

EXCEPTION HANDLING:

	DuplicateKeyException
		When an attempt to insert an item into a list with a key equal to a key already in the list
	RetrieveOnEmptyException
		When an attempt to retrieve an item from an empty list is made
	PastEndOfListException
		When an attempt to move the current position in a list past the last position in the list of
		before the first position in the list is made
	OutOfMemoryException
		When failure to allocate dynamic memory occurs

ERROR CHECKING:
	Before inserting an item into any list, the list is first checked to see if it is full.

SUMMARY OF METHODS:
	None

*/

#include "OrdListClass.h"	// For OrdListClass objects
#include<iostream>			// For input/output
#include<cstdlib>			// For exit
using namespace std;

void main()
{
	ItemType item;	// An item to be inserted into a list

	OrdListClass emptyList,			// An empty list
		oneList,			// A list with 1 item
		multiList,			// A list with >1 items
		unionList,			// Gets the union of 2 lists
		intersectionList;	// Gets the intersection of 2 lists

	try
	{
		try
		{
			item.key = 1;
			// If the list is not full
			if( !oneList.IsFull() )
				oneList.Insert( item );


			item.key = 5;
			// If the list is not full
			if( !multiList.IsFull() )
				multiList.Insert( item );

			item.key = 7;
			// If the list is not full
			if( !multiList.IsFull() )
				multiList.Insert( item );

			item.key = 3;
			// If the list is not full
			if( !multiList.IsFull() )
				multiList.Insert( item );

			item.key = 6;
			// If the list is not full
			if( !multiList.IsFull() )
				multiList.Insert( item );

			item.key = 4;
			// If the list is not full
			if( !multiList.IsFull() )
				multiList.Insert( item );

			// If the list is not full
			if( !multiList.IsFull() )
				multiList.Insert( item );

		} // End try
		catch( DuplicateKeyException e )
		{
			cout << e.GetMessage() << endl;

		} // End catch

		cout << endl;

		// If emptyList is empty and oneList is not empty
		if( emptyList.IsEmpty() && !oneList.IsEmpty() )
		{
			cout << "IsEmpty works correctly" << endl;

		} // End if
		// Else emptyList is not empty or oneList is empty
		else
		{
			cout << "IsEmpty does not work correctly" << endl;

		} // End else

		cout << endl;

		try
		{
			item = emptyList.Retrieve();

		} // End try
		catch( RetrieveOnEmptyException e )
		{
			cout << e.GetMessage() << endl;

		} // End catch

		cout << endl;

		// If the keys are found
		if( multiList.Find( 4 ) && multiList.Find( 7 ) && multiList.Find( 5 ) )
		{
			cout << "Find works correctly" << endl;

		} // End if
		// Else at least one of the keys was not found
		else
		{
			cout << "Find does not work correctly" << endl;

		} // End else

		cout << endl;

		// If the lengths are correct
		if( emptyList.ReturnLength() == 0 && oneList.ReturnLength() == 1 && multiList.ReturnLength() == 5 )
		{
			cout << "ReturnLength works correctly" << endl;

		} // End if
		// Else at least one of the lengths are not correct
		else
		{
			cout << "ReturnLength does not work correctly" << endl;

		} // End else

		cout << endl;

		OrdListClass emptyCopy( emptyList );	// An empty list
		OrdListClass oneCopy( oneList );		// A list with 1 item
		OrdListClass multiCopy( multiList );	// A list with >1 items

		// If the list is empty
		if( emptyCopy.IsEmpty() )
		{
			cout << "Empty list copied successfully" << endl;

		} // End if
		// Else the list is not empty
		else
		{
			cout << "Empty list not copied successfully" << endl;

		} // End else

		cout << endl;

		cout << "The key at the current position in oneList is: " << oneList.Retrieve().key << endl;

		cout << endl;

		cout << "oneList:" << endl;
		oneList.FirstPosition();
		// While not at the end of the list
		while( !oneList.EndOfList() )
		{
			cout << oneList.Retrieve().key << endl;
			oneList.NextPosition();

		} // End while

		cout << endl;

		cout << "The key at the current position in oneCopy is: " << oneCopy.Retrieve().key << endl;

		cout << endl;

		cout << "oneCopy:" << endl;
		oneCopy.FirstPosition();
		// While not at the end of the list
		while( !oneCopy.EndOfList() )
		{
			cout << oneCopy.Retrieve().key << endl;
			oneCopy.NextPosition();

		} // End while

		cout << endl;

		cout << "The key at the current position in multiList is: " << multiList.Retrieve().key << endl;

		cout << endl;

		cout << "multiList:" << endl;
		multiList.FirstPosition();
		// While not at the end of the list
		while( !multiList.EndOfList() )
		{
			cout << multiList.Retrieve().key << endl;
			multiList.NextPosition();

		} // End while

		cout << endl;

		cout << "The key at the current position in multiCopy is: " << multiCopy.Retrieve().key << endl;

		cout << endl;

		cout << "multiCopy:" << endl;
		multiCopy.FirstPosition();
		// While not at the end of the list
		while( !multiCopy.EndOfList() )
		{
			cout << multiCopy.Retrieve().key << endl;
			multiCopy.NextPosition();

		} // End while

		cout << endl;

		emptyCopy.Clear();
		oneCopy.Clear();
		multiCopy.Clear();

		// If the lists are empty
		if( emptyCopy.IsEmpty() && oneCopy.IsEmpty() && multiCopy.IsEmpty() )
		{
			cout << "Clear works correctly" << endl;

		} // End if
		// Else at least one of the lists are not empty
		else
		{
			cout << "Clear does not work correctly" << endl;

		} // End else

		cout << endl;

		emptyCopy = emptyList;
		oneCopy = oneList;
		multiCopy = multiList;

		// If the list is empty
		if( emptyCopy.IsEmpty() )
		{
			cout << "Empty list copied successfully" << endl;

		} // End if
		// If the list is not empty
		else
		{
			cout << "Empty list not copied successfully" << endl;

		} // End else

		cout << endl;

		cout << "The key at the current position in oneList is: " << oneList.Retrieve().key << endl;

		cout << endl;

		cout << "oneList:" << endl;
		oneList.LastPosition();
		// While not at the beginning of the list
		while( !oneList.BeginningOfList() )
		{
			cout << oneList.Retrieve().key << endl;
			oneList.PrevPosition();

		} // End while

		cout << endl;

		cout << "The key at the current position in oneCopy is: " << oneCopy.Retrieve().key << endl;

		cout << endl;

		cout << "oneCopy:" << endl;
		oneCopy.LastPosition();
		// While not at the beginning of the list
		while( !oneCopy.BeginningOfList() )
		{
			cout << oneCopy.Retrieve().key << endl;
			oneCopy.PrevPosition();

		} // End while

		cout << endl;

		cout << "The key at the current position in multiList is: " << multiList.Retrieve().key << endl;

		cout << endl;

		cout << "multiList:" << endl;
		multiList.LastPosition();
		// While not at the beginning of the list
		while( !multiList.BeginningOfList() )
		{
			cout << multiList.Retrieve().key << endl;
			multiList.PrevPosition();

		} // End while

		cout << endl;

		cout << "The key at the current position in multiCopy is: " << multiCopy.Retrieve().key << endl;

		cout << endl;

		cout << "multiCopy:" << endl;
		multiCopy.LastPosition();
		// While not at the beginning of the list
		while( !multiCopy.BeginningOfList() )
		{
			cout << multiCopy.Retrieve().key << endl;
			multiCopy.PrevPosition();

		} // End while

		cout << endl;

		emptyCopy.Delete();
		oneCopy.Delete();
		multiCopy.Find( 4 );
		multiCopy.Delete();
		multiCopy.Find( 7 );
		multiCopy.Delete();

		// If the lists are the correct lengths
		if( emptyCopy.IsEmpty() && oneCopy.IsEmpty() && multiCopy.ReturnLength() == 3 )
		{
			cout << "Delete works correctly" << endl;

		} // End if
		// Else at least one of the lists is not the correct length
		else
		{
			cout << "Delete does not work correctly" << endl;

		} // End else

		cout << endl;

		unionList = emptyList + emptyCopy;

		// If the list is empty
		if( unionList.IsEmpty() )
		{
			cout << "The union of 2 empty lists is empty" << endl;

		} // End if
		// Else the list is not empty
		else
		{
			cout << "operator+ does not work correctly" << endl;

		} // End else

		cout << endl;

		intersectionList = emptyList + emptyCopy;

		// If the list is empty
		if( intersectionList.IsEmpty() )
		{
			cout << "The intersection of 2 empty lists is empty" << endl;

		} // End if
		// Else the list is not empty
		else
		{
			cout << "operator* does not work correctly" << endl;

		} // End else

		cout << endl;

		multiList.Find( 5 );
		multiList.Delete();

		cout << "multiList:" << endl;
		multiList.FirstPosition();
		// While not at the end of the list
		while( !multiList.EndOfList() )
		{
			cout << multiList.Retrieve().key << endl;
			multiList.NextPosition();

		} // End while

		cout << endl;

		unionList = emptyList + multiList;

		cout << "unionList = emptyList + multiList:" << endl;
		unionList.FirstPosition();
		// While not at the end of the list
		while( !unionList.EndOfList() )
		{
			cout << unionList.Retrieve().key << endl;
			unionList.NextPosition();

		} // End while

		cout << endl;

		unionList = multiList + emptyList;

		cout << "unionList = multiList + emptyList:" << endl;
		unionList.FirstPosition();
		// While not at the end of the list
		while( !unionList.EndOfList() )
		{
			cout << unionList.Retrieve().key << endl;
			unionList.NextPosition();

		} // End while

		cout << endl;

		cout << "multiCopy:" << endl;
		multiCopy.FirstPosition();
		// While not at the end of the list
		while( !multiCopy.EndOfList() )
		{
			cout << multiCopy.Retrieve().key << endl;
			multiCopy.NextPosition();

		} // End while

		cout << endl;

		unionList = multiList + multiCopy;

		cout << "unionList = multiList + multiCopy:" << endl;
		unionList.FirstPosition();
		// While not at the end of the list
		while( !unionList.EndOfList() )
		{
			cout << unionList.Retrieve().key << endl;
			unionList.NextPosition();

		} // End while

		cout << endl;

		intersectionList = multiList * multiCopy;

		cout << "intersectionList = multiList * multiCopy:" << endl;
		intersectionList.FirstPosition();
		// While not at the end of the list
		while( !intersectionList.EndOfList() )
		{
			cout << intersectionList.Retrieve().key << endl;
			intersectionList.NextPosition();

		} // End while

		cout << endl;

		multiCopy.Find( 3 );
		multiCopy.Delete();
		multiCopy.Find( 6 );
		multiCopy.Delete();

		cout << "multiCopy:" << endl;
		multiCopy.FirstPosition();
		// While not at the end of the list
		while( !multiCopy.EndOfList() )
		{
			cout << multiCopy.Retrieve().key << endl;
			multiCopy.NextPosition();

		} // End while

		cout << endl;

		intersectionList = multiList * multiCopy;

		// If the list is empty
		if( intersectionList.IsEmpty() )
		{
			cout << "The intersection of multiList and multiCopy is empty" << endl;

		} // End if
		// Else the list is not empty
		else
		{
			cout << "operator* does not work correctly" << endl;

		} // End else

		cout << endl;

		multiCopy = multiList;

		cout << "multiCopy:" << endl;
		multiCopy.FirstPosition();
		// While not at the end of the list
		while( !multiCopy.EndOfList() )
		{
			cout << multiCopy.Retrieve().key << endl;
			multiCopy.NextPosition();

		} // End while

		cout << endl;

		intersectionList = multiList * multiCopy;

		cout << "intersectionList = multiList * multiCopy:" << endl;
		intersectionList.FirstPosition();
		// While not at the end of the list
		while( !intersectionList.EndOfList() )
		{
			cout << intersectionList.Retrieve().key << endl;
			intersectionList.NextPosition();

		} // End while

		cout << endl;

		multiList.Clear();
		multiCopy.Clear();

		item.key = 1;
		// If the list is not full
		if( !multiList.IsFull() )
			multiList.Insert( item );

		item.key = 2;
		// If the list is not full
		if( !multiList.IsFull() )
			multiList.Insert( item );

		item.key = 3;
		// If the list is not full
		if( !multiList.IsFull() )
			multiList.Insert( item );

		// If == and != work correctly
		if( !(multiList == oneList) && multiList != oneList )
		{
			cout << "operator== and operator!= work correctly" << endl;

		} // End if
		// Else == or != doesn't work correctly
		else
		{
			cout << "operator== and operator!= do not work correctly" << endl;

		} // End else

		cout << endl;

		item.key = 1;
		// If the list is not full
		if( !multiCopy.IsFull() )
			multiCopy.Insert( item );

		item.key = 2;
		// If the list is not full
		if( !multiCopy.IsFull() )
			multiCopy.Insert( item );

		item.key = 3;
		// If the list is not full
		if( !multiCopy.IsFull() )
			multiCopy.Insert( item );

		// If == and != work correctly
		if( multiList == multiCopy && !(multiList != multiCopy) )
		{
			cout << "operator== and operator!= work correctly" << endl;

		} // End if
		// Else == or != doesn't work correctly
		else
		{
			cout << "operator== and operator!= do not work correctly" << endl;

		} // End else

		cout << endl;

		multiCopy.Clear();

		item.key = 4;
		// If the list is not full
		if( !multiCopy.IsFull() )
			multiCopy.Insert( item );

		item.key = 5;
		// If the list is not full
		if( !multiCopy.IsFull() )
			multiCopy.Insert( item );

		item.key = 6;
		// If the list is not full
		if( !multiCopy.IsFull() )
			multiCopy.Insert( item );

		// If == and != work correctly
		if( !(multiList == multiCopy) && multiList != multiCopy )
		{
			cout << "operator== and operator!= work correctly" << endl;

		} // End if
		// Else == or != doesn't work correctly
		else
		{
			cout << "operator== and operator!= do not work correctly" << endl;

		} // End else


	} // End try
	catch( OutOfMemoryException e )
	{
		cout << e.GetMessage() << endl;

		exit( EXIT_FAILURE );

	} // End catch

} // End main()