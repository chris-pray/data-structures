//FileName:			OrdList.h 
//Author:			Luke Musto 
//Modifications:	Chris Pray
//Date:				2/22/13
//Project:			OrdList 
//
//				BE SURE TO DOCUMENT THIS CLASS FULLY!!! 
//Purpose: This file contains the specification for an expandable/contractable ordered list(descending)
//   class. It inherits basic properties and actions from the abstract base ListClass. Duplicates are
//	 not allowed to be inserted into the list.
//
//                         SUMMARY OF METHODS
//
//The following constructors/destructors are utilized to perform basic functions for a class which uses
//dynamic memory allocation:
//
//	OrdListClass();
//		Instantiates an OrdListClass object. Sets length and currPos to zero. Sets size to MAX_ENTRIES.
//		Sets list to the address of the list.
//	~OrdListClass();
//		Deallocates memory from an OrdListClass object
//	OrdListClass(const OrdListClass& orig);
//		Instantiates a deep copy of orig.
//
//To provide the ability to order the list, the following functions must be OVERIDDEN:
//  
//	bool Find(KeyType key);
//		Finds position of key within the OrdList. 
//	void Insert(ItemType target);
//		Inserts target into OrdList at position specified by PDM currPos. 
//	void Delete();
//		Deletes list element specified by currPos.
//
//The following public methods have been added to the class to provide additional functionality:
//
//	void NextPosition();
//		Sets currPos to next element in list
//	void Clear();
//		Clears the list returning it to its original state. Sets size equal to MAX_ENTRIES. Sets length
//		to EMPTY. Sets currPos to FIRST_POSITION.
//
//The following methods are also implemented as required by the Abstract Base Class:
//
//	void Print();
//		Allows users to print the contents of their struct in an appropriate manner.
//
//The following operators have been overloaded to provided added functionality:
//
//	virtual bool operator==(const OrdListClass& rtOp) const;
//		Tests the contents of rtOp with that of applying ListClass for equality. Returns true if keys
//		are equal, false otherwise.
//	virtual bool operator!=(const OrdListClass& rtOp) const;
//		Tests the contents of rtOp with that of applying ListClass for equality. Returns true if keys
//		are not equal, false otherwise.
//	virtual OrdListClass operator*(const OrdListClass& rtOp) const;
//		Joins/intersects the contents of rtOp with that ListClass (only keys appearing in both will
//		appear in the resultant class)
//	virtual OrdListClass operator+(const OrdListClass& rtOp) const;
//		Merges lists (if duplicates encountered, only 1 ends up in list)
//	virtual void operator=(const OrdListClass& orig);
//		Assigns orig to applying class object.
//
//The following private methods have been added to allow expansion and contraction:
//
//	virtual void Expand();
//		Creates a new list twice the size of the original and copies the info from the smaller list to
//		the larger one.
//	virtual void Contract();
//		Creates a new list half the size of the original and copies the info from the old list to the
//		new one.
//	virtual bool NoRoom();
//		Returns true if list has no empty locations, false otherwise.
//
//ASSUMPTIONS: 
// (1): The definition of the struct ItemType will be supplied by the client in a file called ItemType.h
// (2): Struct ItemType will contain as its first field a component named key which will be of KeyType.
//       KeyType should be a typedef found in ItemType.H The component field key will be used to search
//		 the list.
//
// TO ENSURE PROPER CLASS FUNCTION:
// (3): On an INSERTION, method Find() must be called immediately before using Insert().
// (4): On a DELETION, method Find() must be called before using Delete().
//
//Exception Handling:
//	bad_alloc is caught in methods operator=, Expand, and Contract if an attempt to allocate dynamic
//		memory fails 
//


#ifndef ordList_h
#define ordList_h

#include<iostream>			// For cout in Print()
#include<cstddef>			// For NULL
#include "ABCListClass.h"	// For base class, ListClass
#include "Exceptions.h"		// For custom exceptions, DuplicateKeyException and OutOfMemoryException
using namespace std;
using namespace nmspcExceptions;

// Class Declarations 
class OrdListClass : public ListClass	// Uses ListClass as template for further derivations
{
	public: 
		
		OrdListClass(); 
		//Purpose:				Instantiates an OrdListClass object. Sets length and currPos to zero.
		//						Sets size to MAX_ENTRIES. Sets list to the address of the list.
		//Pre:					None
		//Post:					An OrdListClass object has been instantiated. length and currPos equal
		//						zero. size equals MAX_ENTRIES. list points to the list
		//Classification:		Default Constructor
		//Order of Magnitude:	O(1)


		~OrdListClass();
		//Purpose:				Deallocates memory from an OrdListClass object
		//Pre:					An OrdListClass object exists
		//Post:					The OrdListClass object has been destroyed
		//Classification:		Destructor
		//Order of Magnitude:	O(1)
		

		OrdListClass(const OrdListClass& orig);	// The original OrdListClass object
		//Purpose:				Instantiates a deep copy of orig.
		//Pre:					orig exists
		//Post:					A deep copy of orig has been instantiated
		//Classification:		Copy Constructor
		//Order of Magnitude:	O(1), operator= is called, which is O(1)


		void NextPosition(); 
		//Purpose:				Sets currPos to next element in list
		//Pre:					List has been instantiated 
		//Post:					currPos is set to next element in list. currPos is bound between 0 and
		//						length
		//Classification:		Mutator
		//Order of Magnitude:	O(1)


		bool Find(/* in */ KeyType key);	// The key to search for
		//Purpose:				Finds position of key within the OrdList. 
		//Pre:					key contains a keyType value to search OrdList for. 
		//Post:					If key is found within the OrdList, true is returned and currPos is
		//						set to the element's location in the list. If target is not found, false
		//						is returned and currPos is set to the location where the record would
		//						have appeared had it been in the list. 
		//Classification:		Mutator / Observer / Predicator
		//Order of Magnitude:	O(logN)


		void Insert(/* in */ ItemType target);	// The target to insert
		//Purpose:				Inserts target into OrdList at position specified by PDM currPos. 
		//Pre:					currPos contains location at which to insert new element, where
		//						(0 <= currPos <= length).
		//Post:					target has been inserted into the OrdList at the location specified by
		//						currPos. If list was full prior to insertion, list can now contain twice
		//						as many elements
		//Classification:		Mutator
		//Order of Magnitude:	O(1)
		//Exceptions Thrown:	DuplicateKeyException, OutOfMemoryException


		void Delete(); 
		//Purpose:				Deletes list element specified by currPos.
		//Pre:					currPos contains the location of the element to be deleted, where
		//						(O <= position < length).
	    //Post:					The list element specified by currPos has been deleted from list. If
		//						deletion results in a percentage of ocuupancy less than 25%, list has
		//						been contracted to half the original size.
		//Classification:		Mutator
		//Order of Magnitude:	O(1)


		void Clear(); 
		//Purpose:				Clears the list returning it to its original state. Sets size equal to
		//						MAX_ENTRIES. Sets length to EMPTY. Sets currPos to FIRST_POSITION.
		//Pre:					List has been instantiated.
		//Post:					List has been cleared(returned to its original empty state). size equals
		//						MAX_ENTRIES. length equals EMPTY. currPos equals FIRST_POSITION.
		//Classification:		Mutator
		//Order of Magnitude:	O(1)


		//NOTE: This is the implementation of the PVF in the Base ListCLass
		void Print();
		//Purpose:				Allows users to print the contents of their struct in an appropriate
		//						manner.
		//Pre:					List has been instantiated.
		//Post:					The contents of the list(ItemType) have been printed.
		//Classification:		Observer / Accessor
		//Order of Magnitude:	O(N), where N is the length of the applying object's list


		// Overloaded operators
		virtual bool operator==(const OrdListClass& rtOp)const;	// List to test equallity against
		//Purpose:				Tests the contents of rtOp with that of applying ListClass for equality.
		//						Returns true if keys are equal, false otherwise.
		//Pre:					List has been instantiated.
		//Post:					True has been returned if the keys of the applying object are equal to
		//						the keys of rtOp. Otherwise, false has been returned.
		//Classification:		Observer / Summarizer
		//Order of Magnitude:	O(N), where N is the length of the applying object's list.
	

		virtual bool operator!=(const OrdListClass& rtOp)const;	// List to test equallity against
		//Purpose:				Tests the contents of rtOp with that of applying ListClass for equality.
		//						Returns true if keys are not equal, false otherwise.
		//Pre:					List has been instantiated.
		//Post:					True has been returned if the keys of the applying object are not equal
		//						to the keys of rtOp. Otherwise, false has been returned.
		//Classification:		Observer / Summarizer
		//Order of Magnitude:	O(N), because operator!= calls operator==, which is O(N), where N is
		//						the length of the applying object's list.


		virtual OrdListClass operator*(const OrdListClass& rtOp) const;	// List to intersect with
		//Purpose:				Joins/intersects the contents of rtOp with that ListClass (only keys
		//						appearing in both will appear in the resultant class)
		//Pre:					List has been instantiated.
		//Post:					An OrdListClass object has been returned whose keys are the keys that
		//						appear in both the applying object's list and rtOp's list
		//Classification:		Observer / Accessor / Summarizer
		//Order of Magnitude:	O(N + M), where N is the length of the applying object's list and M is
		//						the length of rtOp's list.


		virtual OrdListClass operator+(const OrdListClass& rtOp) const;	// List to merge with
		//Purpose:				Merges lists (if duplicates encountered, only 1 ends up in list)
		//Pre:					List has been instantiated.
		//Post:					An OrdListClass object has been returned whose keys are the keys found
		//						in both the applying object's list and rtOp's list (there are no
		//						duplicate keys).
		//Classification:		Observer / Accessor / Summarizer
		//Order of Magnitude:	O(N + M), where N is the length of the applying object's list and M is
		//						the length of rtOp's list.


		virtual void operator=(const OrdListClass& orig);	// Object to aggregately assign
		//Purpose:				Assigns orig to applying class object.
		//Pre:					List has been instantiated.
		//Post:					orig has been aggregately assigned to the applying object.
		//Classification:		Mutator
		//Order of Magnitude:	O(1)
		//Exceptions Thrown:	OutOfMemoryException


	protected: 
		
		virtual void Expand();
		//Purpose:				Creates a new list twice the size of the original and copies the info
		//						from the smaller list to the larger one.
		//Pre:					List is full and needs to be enlarged
		//Post:					List size has been doubled.
		//Classification:		Mutator
		//Order of Magnitude:	O(1)
		//Exceptions Thrown:	OutOfMemoryException

		
		virtual void Contract();
		//Purpose:				Creates a new list half the size of the original and copies the info
		//						from the old list to the new one.
		//Pre:					List has less than 25% occupancy
		//Post:					List size has been cut in half
		//Classification:		Mutator
		//Order of Magnitude:	O(1)
		//Exceptions Thrown:	OutOfMemoryException

	
		virtual bool NoRoom();
		//Purpose:				Returns true if list has no empty locations, false otherwise.
		//Pre:					List has been instantiated.
		//Post:					True is returned if list has no available locations, false otherwise.
		//Classification:		Observer / Predicator
		//Order of Magnitude:	O(1)


 	private:
		// maybe we need something here maybe not.. let me know, 
		//BUT you may not add anything unless we agree upon it as a class. 

}; //end OrdListClass 

#endif