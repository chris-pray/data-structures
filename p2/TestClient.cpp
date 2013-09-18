/*
AUTHOR:
	Chris Pray

DATE:
	3/19/13

FILENAME:
	TestClient.cpp

PURPOSE:
	This file applies unit testing and integration testing on the methods of OrdListClass. Each method
	is extensively tested to ensure that they meet their postconditions, assuming all preconditions are
	met. OrdListClass is derived from ListClass. This file also makes use of the exceptions,
	DuplicateKeyException and OutOfMemoryException. A DuplicateKeyException is thrown when attempting to
	insert an item into the list that has the same key as an item that is already in the list. An
	OutOfMemoryException is thrown when an attempt to allocate dynamic memory in the OrdListClass fails.

INPUT:
	None.

PROCESSING:
	Three OrdListClass objects are instantiated using the default constructor. Items are inserted into
	list1 in a manner that allows the list to be printed just before and immediately after Expand is
	called. A duplicate key is attempted to be inserted into the list as well. While iterating
	MAX_INSERTS times, Find is called on list3 while inserting a random number into the list in its
	correct position. To test NextPosition, a loop is iterated as many times as the length of list3. 
	On each iteration, NextPosition is called, and the key at that position is retrieved and printed.
	Then the list is printed to verify the results. list1 is assigned to list2 by using operator=. A 
	deep copy of list3 is instantiated, called list4. Items are then deleted from list1 in a manner that
	allows the list to be printed just before and immediately after Contract is called from within
	Delete. Delete is then called on an empty list. list2 is cleared. list1 is compared for equallity
	against list2 when they are both empty as well as when they are not empty using operator== and
	operator!=. list1 is also compared for equallity against list3 when list1 is empty and when it is
	not empty using operator== and operator!=. list1 gets assigned the values 0-5 and list2 gets
	assigned the values 3-8 and the intersection of those lists is assigned to list3. Finally, using
	the same values for list1 and list2, the union is now assigned to list3.

OUTPUT:
	A prompt notifying the client when a test is starting and when the test has finished is printed to
	the screen for each test. When testing Insert, list1 and its PDMs are printed to the screen just
	before and immediately after each call to Expand from within Insert. When a duplicate key is
	attempted to be inserted into the list, an error message is printed when the DuplicateKeyException
	is caught. When testing Find, a message is printed on each call to Find, saying whether or not the
	item was found in the list. When testing NextPosition, each key in the list is printed as 
	NextPosition is called, then the entire list is printed along with its PDMs. list2 is printed before
	and after being assigned to list1. list3 and list4 are printed to show that a deep copy was made.
	When testing Delete, list1 and its PDMs are printed to the screen just before and immediately after
	several calls to Contract from within Delete. list2 is printed before and after being cleared. The
	results of the comparisons when testing operator== and operator!= are printed to the screen. list1
	and list2 as well as the intersection and the union are printed to the screen during their 
	respective tests.

ASSUMPTIONS:
	None.

EXCEPTION HANDLING:
	DuplicateKeyException is caught whenever an item is attempted to be inserted into a list when the
		key of the item is already in the list.
	OutOfMemoryException is caught whenever an attempt to allocate dynamic memory fails.

SUMMARY OF METHODS:
	None.
*/

// Libraries and Header Files
#include<iostream>		// For input/output
#include<string>		// For string datatype
#include<cstdlib>		// For exit
#include "OrdList.h"	// For OrdListClass objects
using namespace std;

// Constants
const int MAX_INSERTS = 20;	// Maximum # of inserts to test
const int SEED = 123456789;	// Seed value for random # generator
const int RANGE = 10;		// # of unique keys that can be inserted into a list

//BE SURE TO DOCUMENT THE TEST CLIENT FULLY, Design tests for each method independently , then integration test
void main()
{
	// Variables
	ItemType item;	// An item in a list
	int index;		// LCV; represents a position in a list

	try
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing OrdListClass()

		cout << "Testing OrdListClass()..." << endl << endl;

		OrdListClass list1, list2, list3;	// OrdListClass objects

		cout << "List1, List2, and List3 are instantiated." << endl << endl;

		cout << "OrdListClass() tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing Insert(ItemType)

		cout << "Testing Insert(ItemType)..." << endl << endl;

		cout << "Original list:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		index = 0;

		try
		{
			// While index is < 4
			while(index < 4)
			{
				// Assign the index to item.key
				item.key = (KeyType)index;

				// Insert item into list1
				list1.Insert(item);

				// Increment index by one
				index++;

			} // End while

			cout << endl << "List before expanding:" << endl << endl;

			// Print list1 and its PDMs
			list1.Print();

			// Assign the index to item.key
			item.key = (KeyType)index;

			// Insert item into list1
			list1.Insert(item);

			cout << endl << "List after expanding:" << endl << endl;

			// Print list1 and its PDMs
			list1.Print();

			// Increment index by one
			index++;

			// While index is < 8
			while(index < 8)
			{
				// Assign index to item.key
				item.key = (KeyType)index;

				// Insert item into list1
				list1.Insert(item);

				// Increment index by one
				index++;

			} // End while

			cout << endl << "List before expanding:" << endl << endl;

			// Print list1 and its PDMs
			list1.Print();

			// Assign index to item.key
			item.key = (KeyType)index;

			// Insert item into list1
			list1.Insert(item);

			cout << endl << "List after expanding:" << endl << endl;

			// Print list1 and its PDMs
			list1.Print();

			cout << endl << "Trying to insert a duplicate key:" << endl << endl;

			// Insert item into list1
			list1.Insert(item);

		} // End try
		catch(DuplicateKeyException e)	// Attempt to insert a duplicate key into the list failed
		{
			cout << e.GetMessage() << endl
				<< e.GetKey() << " was not inserted into the list." << endl;

		} // End catch(DuplicateKeyException e)

		cout << endl << "Insert(ItemType) testing successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing Find(KeyType)

		cout << "Testing Find(KeyType)..." << endl << endl;

		// Seed the random number generator
		srand(SEED);

		// Iterate MAX_INSERTS times
		for(int i = 0; i < MAX_INSERTS;i++)
		{
			// Assign a random value to item.key
			item.key = rand() % RANGE;

			// If the key was found in list3
			if(list3.Find(item.key))
			{
				cout << item.key << " was found in the list." << endl;

			} // End if
			// Else the key was not found in list3
			else
			{
				cout << item.key << " was not found in the list." << endl;

				try
				{
					// Insert the item into list3
					list3.Insert(item);

					cout << item.key << " was inserted into the list." << endl;

				} // End try
				catch(DuplicateKeyException e) // Attempt to insert a duplicate key into the list failed
				{
					cout << e.GetMessage() << endl
						<< e.GetKey() << " was not inserted into the list." << endl;

				} // End catch(DuplicateKeyException e)

			} // End else

		} // End for

		cout << endl << "The list:" << endl << endl;

		// Print list3 and its PDMs
		list3.Print();

		cout << endl << "Find(KeyType) tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing NextPosition()

		cout << "Testing NextPosition()..." << endl << endl;

		// If list3 is not empty
		if(!list3.IsEmpty())
		{
			cout << "The list:" << endl << endl;

			// Print list3 and its PDMs
			list3.Print();

			index = 0;

			// Set the current position in list3 to its first position
			list3.FirstPosition();

			cout << endl << "FirstPosition (" << index << "): " << list3.Retrieve().key << endl;

			// For each item in list3
			while(index <= list3.GetLength())
			{
				// Increment the current position in list3 by one
				list3.NextPosition();

				// Increment the index by one
				index++;

				// If the index is >= the length of list3
				if(index >= list3.GetLength())
				{
					// If the current position in list3 equals its length
					if(list3.EndOfList())
					{
						cout << "NextPosition: The current position in the list is at the position after the" << endl
							<< "last element in the list and cannot go to the next position." << endl;

					} // End if
					// Else the current position in list3 is > than its length
					else
					{
						cout << "NextPosition() does not work correctly." << endl;

					} // End else

				} // End if
				// Else the current position in list3 is < its length
				else
				{
					cout << "NextPosition (" << index << "): " << list3.Retrieve().key << endl;

				} // End else

			} // End while

		} // End if
		// Else list3 is empty
		else
		{
			cout << "The list is empty." << endl;

		} // End else

		cout << endl << "NextPosition() tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing operator=(const OrdListClass&)

		cout << "Testing operator=(const OrdListClass&)..." << endl << endl;

		cout << "List1:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		cout << endl << "List2: before calling list2.operator=(list1)" << endl << endl;

		// Print list2 and its PDMs
		list2.Print();

		cout << endl << "List2: after calling list2.operator=(list1)" << endl << endl;

		// Assign list1 to list2
		list2 = list1;

		// Print list2 and its PDMs
		list2.Print();

		cout << endl << "operator=(const OrdListClass&) tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing OrdListClass(const OrdListClass&)

		cout << "Testing OrdListClass(const OrdListClass&)..." << endl << endl;

		// Instantiate a deep copy of list3
		OrdListClass list4(list3);

		cout << "Original list:" << endl << endl;

		// Print list3 and its PDMs
		list3.Print();

		cout << endl << "New list:" << endl << endl;

		// Print list4 and its PDMs
		list4.Print();

		cout << endl << "OrdListClass(const OrdListClass&) tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing Delete()

		cout << "Testing Delete()..." << endl << endl;

		cout << "Original list:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		// Set the current position of list1 to its first position
		list1.FirstPosition();

		// While the length of list1 is > 4
		while(list1.GetLength() > 4)
		{
			// Delete the item at the current position in list11
			list1.Delete();

		} // End while

		cout << endl << "Before contracting:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		// Delete the item at the current position in list11
		list1.Delete();

		cout << endl << "After contracting:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		// Delete the item at the current position in list11
		list1.Delete();

		cout << endl << "Before contracting:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		// Delete the item at the current position in list11
		list1.Delete();

		cout << endl << "After contracting:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		// Delete the item at the current position in list11
		list1.Delete();

		cout << endl << "Empty list:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		// Delete the item at the current position in list11
		list1.Delete();

		cout << endl << "After deleting on empty list:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		cout << endl << "Delete() tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing Clear()

		cout << "Testing Clear()..." << endl << endl;

		cout << "List before calling Clear():" << endl << endl;

		// Print list2 and its PDMs
		list2.Print();

		// Clear list2
		list2.Clear();

		cout << endl << "List after calling Clear():" << endl << endl;

		// Print list2 and its PDMs
		list2.Print();

		cout << endl << "Clear() tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing operator==(const OrdListClass&)const

		cout << "Testing operator==(const OrdListClass&)const..." << endl << endl;

		cout << "List1:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		cout << endl << "List2:" << endl << endl;

		// Print list2 and its PDMs
		list2.Print();

		cout << endl << "List3:" << endl << endl;

		// Print list3 and its PDMs
		list3.Print();

		// If list1 equals list2
		if(list1 == list2)
		{
			cout << endl << "List1 equals List2." << endl << endl;

		} // End if
		// Else list1 does not equal list2
		else
		{
			cout << endl << "operator==(const OrdListClass&)const does not work correctly." << endl << endl;

		} // End else

		// If list1 equals list3
		if(list1 == list3)
		{
			cout << "operator==(const OrdListClass&)const does not work correctly." << endl << endl;

		} // End if
		// Else list1 does not equal list3
		else
		{
			cout << "List1 does not equal List3." << endl << endl;

		} // End else

		// Insert an item into list1 and list2
		list1.Insert(item);
		list2.Insert(item);

		cout << "List1 after inserting " << item.key << ":" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		cout << endl << "List2 after inserting " << item.key << ":" << endl << endl;

		// Print list2 and its PDMs
		list2.Print();

		// If list1 equals list2
		if(list1 == list2)
		{
			cout << endl << "List1 equals List2." << endl << endl;

		} // End if
		// Else list1 does not equal list2
		else
		{
			cout << endl << "operator==(const OrdListClass&)const does not work correctly." << endl << endl;

		} // End else

		// If list1 equals list3
		if(list1 == list3)
		{
			cout << "operator==(const OrdListClass&)const does not work correctly." << endl << endl;

		} // End if
		// Else list1 does not equal list3
		else
		{
			cout << "List1 does not equal List3." << endl << endl;

		} // End else

		cout << "operator==(const OrdListClass&)const tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing operator!=(const OrdListClass&)const

		cout << "Testing operator!=(const OrdListClass&)const..." << endl << endl;

		// Clear list1 and list2
		list1.Clear();
		list2.Clear();

		cout << "List1:" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		cout << endl << "List2:" << endl << endl;

		// Print list2 and its PDMs
		list2.Print();

		cout << endl << "List3:" << endl << endl;

		// Print list3 and its PDMs
		list3.Print();

		// If list1 does not equal list2
		if(list1 != list2)
		{
			cout << endl << "operator!=(const OrdListClass&)const does not work correctly." << endl << endl;

		} // End if
		// Else list1 equals list2
		else
		{
			cout << endl << "List1 equals List2." << endl << endl;

		} // End else

		// If list1 does not equal list3
		if(list1 != list3)
		{
			cout << "List1 does not equal List3." << endl << endl;

		} // End if
		// Else list1 equals list3
		else
		{
			cout << "operator!=(const OrdListClass&)const does not work correctly." << endl << endl;

		} // End else

		// Insert an item into list1 and list2
		list1.Insert(item);
		list2.Insert(item);

		cout << "List1 after inserting " << item.key << ":" << endl << endl;

		// Print list1 and its PDMs
		list1.Print();

		cout << endl << "List2 after inserting " << item.key << ":" << endl << endl;

		// Print list2 and its PDMs
		list2.Print();

		// If list1 does not equal list2
		if(list1 != list2)
		{
			cout << endl << "operator!=(const OrdListClass&)const does not work correctly." << endl << endl;

		} // End if
		// Else list1 equals list2
		else
		{
			cout << endl << "List1 equals List2." << endl << endl;

		} // End else

		// If list1 does not equal list3
		if(list1 != list3)
		{
			cout << "List1 does not equal List3." << endl << endl;

		} // End if
		// Else list1 equals list3
		else
		{
			cout << "operator!=(const OrdListClass&)const does not work correctly." << endl << endl;

		} // End else

		cout << "operator!=(const OrdListClass&)const tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing operator*(const OrdListClass&)const

		cout << "Testing operator*(const OrdListClass&)const..." << endl << endl;

		// Clear list1 and list2
		list1.Clear();
		list2.Clear();

		try
		{
			// Iterate 6 times
			for(int i = 0; i < 6; i++)
			{
				// Assign LCV to item.key
				item.key = (KeyType)i;

				// Insert item into list1
				list1.Insert(item);

			} // End for

			// Iterate 6 times
			for(int i = 3; i < 9; i++)
			{
				// Assign LCV to item.key
				item.key = (KeyType)i;

				// Insert item into list2
				list2.Insert(item);

			} // End for

			cout << "List1:" << endl << endl;

			// Print list1 and its PDMs
			list1.Print();

			cout << endl << "List2:" << endl << endl;

			// Print list2 and its PDMs
			list2.Print();

			// Assign the intersection of list1 and list2 to list3
			list3 = list1 * list2;

			cout << endl << "The intersection of the lists:" << endl << endl;

			// Print list3 and its PDMs
			list3.Print();

		} // End try
		catch(DuplicateKeyException e)	// Attempt to insert a duplicate key into the list failed
		{
			cout << e.GetMessage() << endl
				<< e.GetKey() << " was not inserted into the list." << endl << endl;

		} // End catch(DuplicateKeyException e)

		cout << endl << "operator*(const OrdListClass&)const tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing operator+(const OrdListClass&)const

		cout << "Testing operator+(const OrdListClass&)const..." << endl << endl;

		try
		{
			cout << "List1:" << endl << endl;

			// Print list1 and its PDMs
			list1.Print();

			cout << endl << "List2:" << endl << endl;

			// Print list2 and its PDMs
			list2.Print();

			// Assign the union of list1 and list2 to list3
			list3 = list1 + list2;

			cout << endl << "The union of the lists:" << endl << endl;

			// Print list3 and its PDMs
			list3.Print();

		} // End try
		catch(DuplicateKeyException e)
		{
			cout << e.GetMessage() << endl
				<< e.GetKey() << " was not inserted into the list." << endl << endl;

		} // End catch(DuplicateKeyException e)

		cout << endl << "operator+(const OrdListClass&)const tested successfully." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//	Integration Test

		cout << "Integration test..." << endl << endl;

		OrdListClass l1, l2, l3;	// OrdListClass objects

		cout << "OrdListClass objects l1, l2, and l3 have been instantiated." << endl << endl;

		cout << "l1:" << endl << endl;

		// Print l1 and its PDMs
		l1.Print();

		cout << endl << "l2:" << endl << endl;

		// Print l2 and its PDMs
		l2.Print();

		cout << endl << "l3:" << endl << endl;

		// Print l3 and its PDMs
		l3.Print();

		// Delete the item at the current location in l1
		l1.Delete();

		cout << endl << "l1 after Delete:" << endl << endl;

		// Print l1 and its PDMs
		l1.Print();

		// Clear l1's list
		l1.Clear();

		cout << endl << "l1 after Clear:" << endl << endl;

		// Print l1 and its PDMs
		l1.Print();

		// Increment the current position in l1
		l1.NextPosition();

		cout << endl << "l1 after NextPosition:" << endl << endl;

		// Print l1 and its PDMs
		l1.Print();

		// If l1 equals l2
		if(l1 == l2)
		{
			cout << endl << "l1 equals l2" << endl << endl;

		} // End if
		// Else l1 does not equal l2
		else
		{
			cout << endl << "operator== does not work correctly" << endl << endl;

		} // End else

		// If l2 does not equal l3
		if(l2 != l3)
		{
			cout << "operator!= does not work correctly" << endl << endl;

		} // End if
		// Else l2 equals l3
		else
		{
			cout << "l2 equals l3" << endl << endl;

		} // End else

		// Assign the intersection of l2 and l3 to l1
		l1 = l2 * l3;

		cout << "The intersection of l2 and l3:" << endl << endl;

		// Print l1 and its PDMs
		l1.Print();

		// Assign the union of l2 and l3 to l1
		l1 = l2 + l3;

		cout << endl << "The union of l2 and l3:" << endl << endl;

		// Print l1 and its PDMs
		l1.Print();

		try
		{
			index = 0;

			// Iterate MAX_INSERTS times
			while(index < MAX_INSERTS)
			{
				// Assign index to item.key
				item.key = index;

				// If item.key is not found in l1
				if(!l1.Find(item.key))
				{
					// Insert item into l1
					l1.Insert(item);

				} // End if

				// Set item.key to a random #
				item.key = rand() % RANGE;

				// If item.key is not found in l2
				if(!l2.Find(item.key))
				{
					// Insert item into l2
					l2.Insert(item);

				} // End if

				// Increment the index by one
				index++;

			} // End while

			cout << endl << "l1:" << endl << endl;

			// Print l1 and its PDMs
			l1.Print();

			cout << endl << "l2:" << endl << endl;

			// Print l2 and its PDMs
			l2.Print();

			// If l1 equals l2
			if(l1 == l2)
			{
				cout << endl << "operator== does not work correctly" << endl << endl;

			} // End if
			// Else l1 does not equal l2
			else
			{
				cout << endl << "l1 does not equal l2" << endl << endl;

			} // End else

			// If l1 does not equal l2
			if(l1 != l2)
			{
				cout << "l1 does not equal l2" << endl << endl;

			} // End if
			// Else l1 is equal to l2
			else
			{
				cout << "operator!= does not work correctly" << endl << endl;

			} // End else

			// Assign the intersection of l1 and l2 to l3
			l3 = l1 * l2;

			cout << "The intersection of l1 and l2:" << endl << endl;

			// Print l3 and its PDMs
			l3.Print();

			// Assign the union of l1 and l2 to l3
			l3 = l1 + l2;

			cout << endl << "The union of l1 and l2:" << endl << endl;

			// Print l3 and its PDMs
			l3.Print();

			// Assign l1 to l3
			l3 = l1;

			cout << endl << "l3 after assigning it l1:" << endl << endl;

			// Print l3 and its PDMs
			l3.Print();

			// Instantiate a new OrdListClass object equal to l2
			OrdListClass l4(l2);

			cout << endl << "l4 as a deep copy of l2:" << endl << endl;

			// Print l4 and its PDMs
			l4.Print();

			// Clear l1's list
			l1.Clear();

			cout << endl << "l1 after Clear:" << endl << endl;

			// Print l1 and its PDMs
			l1.Print();

			// While l2 is not empty
			while(!l2.IsEmpty())
			{
				// Set the current position to the last position in the list
				l2.LastPosition();

				// Delete the item at the current position in l2
				l2.Delete();

			} // End while

			cout << endl << "l2 after Delete:" << endl << endl;

			// Print l2 and its PDMs
			l2.Print();

			// Set the current position in l3 to the first position in l3
			l3.FirstPosition();

			cout << endl << "l3:" << endl << endl;

			// Print l3 and its PDMs
			l3.Print();

			// While l3 is not at the end of the list
			while(!l3.EndOfList())
			{
				// Increment the current position of l3 by one
				l3.NextPosition();

			} // End while

			cout << endl << "l3 after NextPosition:" << endl << endl;

			// Print l3 and its PDMs
			l3.Print();

			// Increment the current position of l3 by one
			l3.NextPosition();

			cout << endl << "l3 after NextPosition:" << endl << endl;

			// Print l3 and its PDMs
			l3.Print();

		} // End try
		catch(DuplicateKeyException e)	// Attempt to insert a duplicate key into the list failed
		{
			cout << e.GetMessage() << endl
				 << e.GetKey() << " was not inserted into the list." << endl;

		} // End catch(DuplicateKeyException e)

		cout << endl << "Integration test successful." << endl;

		system("pause");
		system("cls");

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		cout << "Testing complete." << endl;

	} // End try
	catch(OutOfMemoryException e)	// Failed to allocate dynamic memory
	{
		cout << e.GetMessage() << endl;

		system("pause");

		// Terminate program
		exit(EXIT_FAILURE);

	} // End catch(OutOfMemoryException e)

} // End main()