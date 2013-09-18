//Author: Luke Musto
//Date 4/28/2010
//
//Modifications:	Chris Pray	- 5/10/13
//
//Purpose:			This specification contains a template class for an ordered list. The parameterized
//					type, ItemType must be defined before the inclusion of this file in the application
//					and it must be a structure with field named, key, which is of type KeyType, which
//					also must be defined in the application including this file. This class template
//					allows for list insertions, deletions, looks ups, and printing. It contains a
//					constructor, a copy constructor, a destructor, 15 public methods, 4 overloaded
//					operators, 14 protected methods, and 3 private data members. A summary of the public
//					methods appears below.
// 
//Assumptions:
//	1. The parameterized type, ItemType, must be defined in the application using this template class
//		and must be a struct with a field called key, which also must be defined in the application
//		using this template class. key must be a unique value to the item which contains it.
//	2. FirstPosition, NextPosition, and EndOfList are designed to be used in the context of iterating
//		through a list.
//	3. Unless Retrieve is being used in conjunction with FirstPosition, NextPosition, and EndOfList to
//		print the contents of the list, Find must be called before a call to Retrieve, and in that case
//		Retrieve should only be called if Find returned true.
//	4. Find must be called immediately before a call to Insert, and Insert should only be called in Find
//		returned false.
//	5. Find must be called immediately before a call to Delete, and Delete should only be called if Find
//		returned true.
//	6. FunctionType and FunctionType2 have been defined in the client so that they print an item in the
//		list in the correct format.
//
//Error Handling: 
//	If the key passed when calling Delete does not match the key of the item at the current position in
//	the list, the item does not get Deleted.
//
//Exception Handling:
//	
//	*Exceptions Caught*
//
//		bad_alloc
//			When an attempt to dynamically allocate memory fails
//
//	*Exceptions Thrown*
//
//		DuplicateKeyException
//			When an attempt to insert an item into a list with a key equal to a key already in the list
//
//		InvalidRetrieveException
//			When an attempt to retrieve an item from an empty list or from an invalid location is made.
//			An invalid location is one where currPos == NULL
//
//		OutOfMemoryException
//			When failure to allocate dynamic memory occurs

//Summary of Public Methods:
//
// OrdListClass()
//	Instantiates an OrdListClass object as an empty list.
//
// ~OrdListClass()
//	Returns all dynamically allocated memory in the object to the heap.
//
// OrdListClass( const OrdListClass<ItemType>& orig )
//	Instantiates an OrdListClass object as a deep copy of orig.
//
// IsEmpty()const
//	Determines if the list is empty.
//
// IsFull()const
//	Determines if the list is full.
//
// EndOfList()
//	Determines if the current position in the list is at the end of the list. (currPos = NULL, prevPos
//	points to the last item in the list)
//
// FirstPosition()
//	Sets the current position in the list to the first in-order item in the list. Sets prevPos to
//	currPos's parent.
//
// NextPosition()
//	Sets the current position in the list to the next in-order item in the list. Sets prevPos to
//	currPos's parent.
//
// Find( KeyType target )
//	Determines if an item with the target KeyType is in the list. If it is, the current position in the
//	list is set to the item with that target KeyType. Otherwise, the current position in the list is set
//	to where that item would be located if it were in the list. prevPos is set to currPos's parent.
//
// Retrieve()const
//	Returns the item at the current position in the list.
//
// Insert( ItemType newItem )
//	Inserts a new item into the list.
//
// Delete( KeyType key )
//	Removes the item at the current position in the list from the list.
//
// Clear()
//	Removes all items from the list.
//
// ReturnLength()const
//	Returns the number of items in the list.
//
// operator=( const OrdListClass<ItemType>& orig )
//	Assigns orig to the applying object.
//
// PrintScreen( FunctionType visit )
//	Prints the list to the console, in order, starting with the item with the lowest key.
//
// PrintFile( FunctionType2 visit, ofstream& dout )
//	Prints the list to an output file, so that when read in an exact replica of the object's tree can be
//	recreated.
//
// PrintReverse( FunctionType visit )
//	Prints the list to the console, in reverse order, so that the first item printed is the one with the
//	largest key and the last item printed is the one with the smallest key.
//
// PrintAsExists( FunctionType visit )
//	Prints a visual representation of the object's tree to the console.
//
// operator==( const OrdListClass<ItemType>& rtOp )const
//	Determines if the keys in the applying object's list are equal to the keys in rtOp's list.
//
// operator!=( const OrdListClass<ItemType>& rtOp )const
//	Determines if there is any inequallity among the keys of the applying object's list and rtOp's list.
//
// operator+( const OrdListClass<ItemType>& rtOp )const
//	Combines two lists together. Any duplicate keys only appear once. The resulting object's tree is
//	complete.

#ifndef ordlisttemplate_h
#define ordlisttemplate_h

#include "OrdListExceptions.h"		// For custom exceptions
#include <cstdlib>					// for NULL
#include <iostream>					// For input/output
#include <cmath>					// For pow
using namespace std;
using namespace OrdListExceptions;

typedef void (*FunctionType)(ItemType&);
	// Function pointer used to return an ItemType record to the client during a traversal
typedef void (*FunctionType2)(ItemType&, ofstream&);
	// Function pointer used to return an ItemType record and an output file stream to the client during
	//  a traversal

const int MAX_ITEMS = 31;	// Maximum number of items that can be printed when PrintAsExists is called

// IMPORTANT: PLEASE NOTE:  THIS IS A CLASS TEMPLATE, THEREFORE: 
//		(1) THE STRUCT ItemType DECLARATION MUST BE SUPPLIED BY CLIENT AND APPEAR ABOVE THE MAIN.
//		(2) IT SHOULD CONTAIN A FIELD OF KeyType CALLED key. This will be used to order the list.
//		(3) KeyType SHOULD APPEAR AS A typedef ABOVE THE ItemType DECLARATION in the client.

template <class ItemType>
struct node;				// Forward declaration of a node

template <class ItemType>
class OrdListClass
{
	public:

		OrdListClass();
		// Purpose:				Instantiates an OrdListClass object as an empty list.
		// Pre:					None.
		// Post:				An OrdListClass object has been instantiated as an empty list.
		// Classification:		Constructor
		// Order of Magnitude:	O( 1 )

		~OrdListClass();
		// Purpose:				Returns all dynamically allocated memory in the object to the heap.
		// Pre:					An OrdListClass object has been instantiated.
		// Post:				All dynamically allocated memory from the object has been returned to
		//						the heap.
		// Classification:		Destructor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list.

		OrdListClass( /* In */ const OrdListClass<ItemType>& orig );	// The object to create a deep copy of
		// Purpose:				Instantiates an OrdListClass object as a deep copy of orig.
		// Pre:					orig exists.
		// Post:				An OrdListClass object has been instantiated as a deep copy of orig.
		// Classification:		Copy Constructor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list.

		bool IsEmpty()const;
		// Purpose:				Determines if the list is empty.
		// Pre:					An OrdListClass object has been instantiated.
		// Post:				If the list is empty, true has been returned. Otherwise, false has been
		//						returned.
		// Classification:		Observer / Predicator
		// Order of Magnitude:	O( 1 )

		bool IsFull()const;
		// Purpose:				Determines if the list is full.
		// Pre:					An OrdListClass object has been instantiated.
		// Post:				If the list is full, true has been returned. Otherwise, false has been
		//						returned.
		// Classification:		Observer / Predicator
		// Order of Magnitude:	O( 1 )

		bool EndOfList();
		// Purpose:				Determines if the current position in the list is at the end of the
		//						list. (currPos = NULL, prevPos points to the last item in the list)
		// Pre:					An OrdListClass object has been instantiated.
		// Post:				If the current position in the list is at the end of the list, true has
		//						been returned. Otherwise, false has been returned.
		// Classification:		Observer / Predicator
		// Order of Magnitude:	O( 1 )
	
		void FirstPosition();
		// Purpose:				Sets the current position in the list to the first in-order item in the
		//						list. Sets prevPos to currPos's parent.
		// Pre:					An OrdListClass object has been instantiated.
		// Post:				currPos points to the first in-order item in the list. prevPos points to
		//						currPos's parent.
		// Classification:		Mutator
		// Order of Magnitude:	O( N ), where N is the height of the object's tree.
		
		void NextPosition();
		// Purpose:				Sets the current position in the list to the next in-order item in the
		//						list. Sets prevPos to currPos's parent.
		// Pre:					An OrdListClass object has been instantiated. currPos != NULL.
		// Post:				currPos points to the next in-order item in the list. prevPos points to
		//						currPos's parent.
		// Classification:		Mutator
		// Order of Magnitude:	O( N ), where N is the height of the object's tree.

		bool Find( /* In */ KeyType target );
		// Purpose:				Determines if an item with the target KeyType is in the list. If it is,
		//						the current position in the list is set to the item with that target
		//						KeyType. Otherwise, the current position in the list is set to where
		//						that item would be located if it were in the list. prevPos is set to
		//						currPos's parent.
		// Pre:					An OrdListClass object has been instantiated. target has been defined.
		// Post:				If an item with the target KeyType was found, true has been returned and
		//						the current position in the list has been set to that item. Otherwise,
		//						false has been returned and the current position in the list has been
		//						set to where that item would be located if it were in the list. prevPos
		//						has been set to currPos's parent.
		// Classification:		Mutator / Observer / Predicator
		// Order of Magnitude:	O( log2 N ), where N is the number of nodes in the list.

		ItemType Retrieve()const;
		// Purpose:				Returns the item at the current position in the list.
		// Pre:					An OrdListClass object has been instantiated. The current position in
		//						the list must be a valid location to retrieve from (currPos != NULL).
		//						See ASSUMPTIONS.
		// Post:				The item at the current position in the list has been returned.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( 1 )

		void Insert( /* In */ ItemType newItem );
		// Purpose:				Inserts a new item into the list.
		// Pre:					An OrdListClass object has been instantiated. The current position in
		//						the list is where the new item should be inserted. An item with the same
		//						key must not already be in the list. See ASSUMPTIONS.
		// Post:				The new item has been inserted into the list in the correct location.
		// Classification:		Mutator
		// Order of Magnitude:	O( 1 )

		void Delete( /* In */ KeyType key );
		// Purpose:				Removes the item at the current position in the list from the list.
		// Pre:					An OrdListClass object has been instantiated. The key of the item at the
		//						current position in the list matches the key specified by the caller.
		//						See ASSUMPTIONS.
		// Post:				The item at the current position of the list has been removed from the
		//						list.
		// Classification:		Mutator
		// Order of Magnitude:	O( N ), where N is the height of the object's tree.
								   
		void Clear();
		// Purpose:				Removes all items from the list.
		// Pre:					An OrdListClass object has been instantiated.
		// Post:				The list is empty.
		// Classification:		Mutator
		// Order of Magnitude:	O( N ), where N is the number of node in the list.

		int ReturnLength()const;
		// Purpose:				Returns the number of items in the list.
		// Pre:					An OrdListClass object has been instantiated.
		// Post:				The number of items in teh list has been returned.
		// Classification:		Observer / Summerizer
		// Order of Magnitude:	O( N ), where N is the number of node in the list.

		virtual void operator=( /* In */ const OrdListClass<ItemType>& orig );	// The object to assign
																				//  to the applying
																				//  object
		// Purpose:				Assigns orig to the applying object.
		// Pre:					An OrdListClass object has been instantiated. orig exists.
		// Post:				The applying object is a deep copy of orig.
		// Classification:		Mutator
		// Order of Magnitude:	O( N * M + log2 M ), where N is the number of nodes initially in the
		//						applying object and M is the number of nodes in orig.

		void PrintScreen( /* In */ FunctionType visit );	// Pointer to client function that specifies
															//  the format in an item is to be printed
		// Purpose:				Prints the list to the console, in order, starting with the item with
		//						the lowest key.
		// Pre:					An OrdListClass object has been instantiated. visit is a pointer to a
		//						function in the client, which specifies the format in which an item is
		//						to be printed.
		// Post:				The list has been printed to the console, in order, starting with the
		//						item with the lowest key.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list.

		void PrintFile( /* In */	 FunctionType2 visit,	// Pointer to client function that specifies
															//  the format in an item is to be printed
						/* In/Out */ ofstream& dout );		// Output file stream variable
		// Purpose:				Prints the list to an output file, so that when read in an exact replica
		//						of the object's tree can be recreated.
		// Pre:					An OrdListClass object has been instantiated. visit is a pointer to a
		//						function in the client, which specifies the format in which an item is
		//						to be printed. dout has been associated with the output file
		// Post:				The list has been printed to an output file in a format so that when
		//						read in, an exact replica of the object's tree can be recreated.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list.

		void PrintReverse( /* In */ FunctionType visit );	// Pointer to client function that specifies
															//  the format in an item is to be printed
		// Purpose:				Prints the list to the console, in reverse order, so that the first item
		//						printed is the one with the largest key and the last item printed is the
		//						one with the smallest key.
		// Pre:					An OrdListClass object has been instantiated. visit is a pointer to a
		//						function in the client, which specifies the format in which an item is
		//						to be printed.
		// Post:				The list has been printed to the console, in reverse order, so that the
		//						first item printed is the one with the largest key and the last item
		//						printed is the one with the smallest key.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list.

		void PrintAsExists( /* In */ FunctionType visit );	// Pointer to client function that specifies
															//  the format in an item is to be printed
		// Purpose:				Prints a visual representation of the object's tree to the console.
		// Pre:					An OrdListClass object has been instantiated. The object's tree's height
		//						is <= 5. visit is a pointer to a function in the client, which specifies
		//						the format in which an item is to be printed.
		// Post:				A visual representation of the object's tree has been printed to the
		//						console.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list.

		virtual bool operator==( /* In */ const OrdListClass<ItemType>& rtOp )const;	// The object to compare the
																			//  applying object's
																			//  eqallity against
		// Purpose:				Determines if the keys in the applying object's list are equal to the
		//						keys in rtOp's list.
		// Pre:					An OrdListClass object has been instantiated. rtOp exists.
		// Post:				If the keys in the applying object's list are equal to the keys in
		//						rtOp's list, true has been returned. Otherwise, false has been returned.
		// Classification:		Observer / Predicator
		// Order of Magnitude:	O( N ), where N is the number of nodes in the applying object's list.

		virtual bool operator!=( /* In */ const OrdListClass<ItemType>& rtOp )const;	// The object to compare the
																			//  applying object's
																			//  ineqallity against
		// Purpose:				Determines if there is any inequallity among the keys of the applying
		//						object's list and rtOp's list.
		// Pre:					An OrdListClass object has been instantiated. rtOp exists.
		// Post:				If there is any inequallity among the keys in the applying object's list
		//						and the keys in rtOp's list, true has been returned. Otherwise, false
		//						has been returned.
		// Classification:		Observer / Predicator
		// Order of Magnitude:	O( N ), where N is the number of nodes in the applying object's list.

		virtual OrdListClass<ItemType> operator+
			( /* In */ const OrdListClass<ItemType>& rtOp )const; // The object to combine with the
																  //  applying object
		// Purpose:				Combines two lists together. Any duplicate keys only appear once. The
		//						resulting object's tree is complete.
		// Pre:					An OrdListClass object has been instantiated. rtOp exists.
		// Post:				The applying object's list has bee combined with rtOp's list and the
		//						resulting list has been returned. Any duplicate keys appear only once.
		//						The tree in the returned object is complete.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( 5 * ( N + M ) ), where N is the number of items in the applying
		//						object and M is the number of items in rtOp.


	private:

		node<ItemType>* root;		// Pointer to the root of the list
		node<ItemType>* currPos;	// Pointer to the current position in the list
		node<ItemType>* prevPos;	// Pointer to the current position's parent in the list


	protected:

		node<ItemType>* Allocate();
		// Purpose:				Dynamically allocates memory for a node and returns a pointer to that
		//						node. The node's left and right subtrees are NULL.
		// Pre:					There is enough memory on the heap to allocate for a node.
		// Post:				A pointer to the newly allocated node has been returned. The node's left
		//						and right subtrees are NULL.
		// Classification:		Mutator
		// Order of Magnitude:	O( 1 )

		bool rFind( /* In */ KeyType key );	// The key to search for
		// Purpose:				Determines if an item with the specified key is within the list.
		// Pre:					An OrdListClass object has been instantiated. The key to be searched for
		//						has been defined.
		// Post:				If an item with the specified key was found, true has been returned and
		//						the current position in the list has been set to that item. Otherwise,
		//						false has been returned and the current position in the list has been
		//						set to where that item would be located if it were in the list. prevPos
		//						has been set to currPos's parent.
		// Classification:		Mutator / Observer / Predicator
		// Order of Magnitude:	O( log2 N ), where N is the number of nodes in the list

		void rClear( /* In */ node<ItemType>* trav );	// A traversal pointer
		// Purpose:				Removes all items from the list.
		// Pre:					An OrdListClass object has been instantiated.
		// Post:				The list is empty.
		// Classification:		Mutator
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list

		bool rIsEqual
			( /* In */ node<ItemType>* applyingTrav,	// Traversal pointer to the applying object's tree
			  /* In */ node<ItemType>* rtOpTrav )const;	// Traversal pointer to to rtOp's tree
		// Purpose:				Determines if the keys in the list pointed to by applyingPtr are equal
		//						to the keys in the list pointed to by rtOpPtr.
		// Pre:					An OrdListClass object has been instantiated. rtOp exists.
		// Post:				If the keys in the applying object's list are equal to the keys in
		//						rtOp's list, true has been returned. Otherwise, false has been returned.
		// Classification:		Observer / Predicator
		// Order of Magnitude:	O( N ), where N is the number of nodes in the applying object's list.

		void rAssign
			( /* In/Out */ node<ItemType>*& applyingTrav,	// Traversal pointer to the applying
															//  object's tree
			  /* In */	   node<ItemType>* origTrav );		// Traversal pointer to orig's tree
		// Purpose:				Creates a deep copy of the list pointed to by origTrav in the list
		//						pointed to by applyingTrav.
		// Pre:					The list pointed to by applyingTrav is empty. The list pointed to by
		//						origTrav exists.
		// Post:				The list pointed to by applyingTrav is a deep copy of the list pointed
		//						to by origTrav.
		// Classification:		Mutator
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list

		int rReturnLength( /* In */ node<ItemType>* trav )const;	// A traversal pointer
		// Purpose:				Determines the number of items in a list.
		// Pre:					trav points to a list that exists.
		// Post:				The number of items in the list pointed to by trav has been returned.
		// Classification:		Observer / Summerizer
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list

		void rPrintScreen( /* In */ FunctionType visit,	// Pointer to client function that specifies the
														//  format in an item is to be printed
						   /* In */ node<ItemType>* trav );		// A traversal pointer
		// Purpose:				Prints the list to the console, in order, starting with the item with
		//						the lowest key.
		// Pre:					An OrdListClass object has been instantiated. visit is a pointer to a
		//						function in the client, which specifies the format in which an item is
		//						to be printed.
		// Post:				The list has been printed to the console, in order, starting with the
		//						item with the lowest key.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list.

		void rPrintReverse
			( /* In */ FunctionType visit,		// Pointer to client function that specifies the format
												//  in an item is to be printed
			  /* In */ node<ItemType>* trav );	// A traversal pointer
		// Purpose:				Prints the list to the console, in reverse order, so that the first item
		//						printed is the one with the largest key and the last item printed is the
		//						one with the smallest key.
		// Pre:					An OrdListClass object has been instantiated. visit is a pointer to a
		//						function in the client, which specifies the format in which an item is
		//						to be printed.
		// Post:				The list has been printed to the console, in reverse order, so that the
		//						first item printed is the one with the largest key and the last item
		//						printed is the one with the smallest key.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list.

		void rPrintFile
			( /* In */	   FunctionType2 visit,	   // Pointer to client function that specifies the
												   //  format in an item is to be printed
			  /* In/Out */ ofstream& dout,		   // Output file stream variable
			  /* In */	   node<ItemType>* trav ); // A traversal pointer
		// Purpose:				Prints the list to an output file, so that when read in an exact replica
		//						of the
		//						object's tree can be recreated.
		// Pre:					An OrdListClass object has been instantiated. visit is a pointer to a
		//						function in the client, which specifies the format in which an item is
		//						to be printed. dout has been associated with the output file
		// Post:				The list has been printed to an output file in a format so that when
		//						read in, an exact replica of the object's tree can be recreated.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list.

		void rFill( /* In */	 node<ItemType>* trav,	// A traversal pointer
					/* In/Out */ ItemType arr[],		// The array to fill
					/* In */	 int index );			// Index of the array to insert into
		// Purpose:				Fills an array in a manner such that each sequential index in the array
		//						holds a copy of the next item in a breadth-first traversal of the
		//						applying object's tree.
		// Pre:					trav must initially point to the applying object's tree's root. arr has
		//						a length of MAX_ITEMS and each element's intitial key is INT_MIN. index
		//						contains the correct index to insert a copy of the item pointed to by
		//						trav into.
		// Post:				The array has been filled using a breadth-first traversal through the
		//						applying object's tree. NULL locations within the tree are represented
		//						in the array as a key of INT_MAX. Locations in the tree that could not
		//						be traversed are represented in the array as INT_MIN.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the list.

		void rFindParent( /* In */ node<ItemType>* trav );	// A traversal pointer
		// Purpose:				Sets prevPos to its parent node.
		// Pre:					prevPos != root && prevPos != NULL
		// Post:				prevPos has been set to its parent node.
		// Classification:		Mutator
		// Order of Magnitude:	O( N ), where N is the height of the applying object's tree

		void rFillUnion( /* In/Out */ OrdListClass<ItemType>& ordUnion,	// The union of the applying
																		//  object and rtOp
						 /* In */	  node<ItemType>* rtOpTrav )const;	// A traversal pointer
		// Purpose:				Combines all the keys from the applying object with all the keys from
		//						the tree pointed to by rtOpTrav into ordUnion. Duplicate keys only
		//						appear once.
		// Pre:					ordUnion has been instantiated as a deep copy of the applying object.
		//						rtOpTrav points to a tree that exists. 
		// Post:				ordUnion contains each key from the applying object and each key from
		//						the tree pointed to by rtOpTrav. Each duplicate only appears once.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the tree pointed to by
		//						rtOpTrav.



		void rCompleteUnion
			( /* In/Out */ OrdListClass<ItemType>& ordUnion,	// List that contains a complete tree
							 /* In/Out */ ItemType arr[],		// Array of items
							 /* In */	  int min,				// Minimum index in range
							 /* In */	  int max )const;		// Maximum index in range
		// Purpose:				Inserts each item from an array into an object, making a complete tree.
		// Pre:					ordUnion has been instantiated and is empty on the initial function
		//						call. arr contains the items to be inserted into ordUnion. min is the
		//						minimum of a range of indexes of the array so that an index can be
		//						calculated which an item will be copied from. max is the maximum of a
		//						range of indexes of the array so that an index can be calculated which
		//						an item will be copied from. numBottom is the number of nodes that will
		//						appear on the bottom level of the tree.
		// Post:				ordUnion contains a complete tree with all the items from arr.
		// Classification:		Mutator
		// Order of Magnitude:	O( N ), where N is the number of items in the array.



		void rFillArr( /* In */ node<ItemType>* trav,		// Pointer to the tree to copy items from
					   /* In/Out */ ItemType arr[],			// Array to be filled
					   /* In */ int& index,					// Index at which to insert an item at
					   /* In */ const int& numVals )const;	// Max number of elements in the array
		// Purpose:				Fills an array with copies of the items from the tree pointed to by trav
		//						in an in-order sequence.
		// Pre:					trav points to the root of the tree to fill the array from. arr has been
		//						dynamically allocated with enough memory for numVals items. index
		//						contains the index of the array at which to insert an item into. numVals
		//						contains the maximum number of items in the array.
		// Post:				arr has been filled with copies of the items from the tree pointed to by
		//						trav in an in-order sequence.
		// Classification:		Observer / Accessor
		// Order of Magnitude:	O( N ), where N is the number of nodes in the tree pointed to by trav.

	
}; // End OrdListClass

#include "OrdList.cpp"

#endif