//FileName : list.h 
//Author:Luke Musto 
//Date 9/28/03 
//Modifications: 10/1/05	-- added setCurrPos functionality 
//				 02/26/07	-- added setLength method
//								removed overloaded operator ==
//				 10/03/07	-- update documentation re: ItemType now in separate file 
//								w/KeyType
//				 2/12/08	-- update return type of Find to bool.
//			 	 09/27/08	-- modify documentation -- correct ambiguities/errata
//				 03/02/09   -- add expansion and contraction factors to constants
//							    update documentation		
//			 	 10/05/09	-- modify documentation -- correct ambiguities/errata
//				 3/09/10	-- modify to add functionality of NoRoom() method. 	
//				 	 	       used to identify criteria for expansion of the list
//				 2/15/11	- added size pdm and accessor method
//				 2/18/12	- added overloaded operators -
//				 9/20/12	- added operator == 
//				 2/22/13	- added additional overloaded operator!= and updated documentation
//				 
//Project List 
//
//Purpose: This file contains the specification for an abstract base unordered list
//   class. The struct definition for the list should be placed in the file 
//   ItemType.h, therefore no code change need be made within the implementation 
//   file to change the basic design of a list item. The maximum number of list 
//   entries it currently handles is 4. It provides the programmer with all 
//   methods necessary to implement a list. It contains 13 public and  10 protected methods. 
//   It also contains 4 private data elements.
//
//
//**NOTE THE CLASS IS USED TO IMPLEMENT AN UNORDERED LIST. 
//       THE CLIENT INSERTS ITEMS AT THE END OF THE LIST BY INVOKING METHOD 
//			LastPosition() followed by NextPosition() before calling Insert().
//
//
//ASSUMPTIONS:  ******IMPORTANT!!!! READ THESE   ******
//(1): The definition of the struct ItemType will be supplied by the client in 
//       a file called ItemType.h 
//(2): Struct ItemType will contain as its first field a component named key
//       which will be of KeyType. KeyType should be a typedef found in 
//       ItemType.H The component field key will be used to search the list.
//
// TO ENSURE PROPER CLASS FUNCTION:
//(3): On an INSERTION, methods LastPosition() and NextPosition must be called 
//		 immediately before using Insert().
//(4): On a DELETION, method Find() must be called before using Delete().
//
//
//ERROR CHECKING:  
//(1): None
//	   
//
//                       SUMMARY OF METHODS: 
//
//PUBLIC METHODS
//
//ListClass();           sets private  data members length & currPos to zero,
//						 allocates memory for MAXENTRIES records and sets 
//						 array size to MAXENTRIES.
//void  FirstPosition(); sets currPos  to beginning of list 
//void  NextPosition();  sets currPos  to next element in list 
//void  LastPosition();  sets currPos  to last element in the list
//bool  IsEmpty();       returns true  if OrdList has no elements.
//bool  IsFull();        returns true  if OrdList is full, false otherwise 
//bool  EndofList();     returns true  if currPos specifies end of List
//						   (1st empty position in the List). 
//ItemType Retrieve(); returns a record (ItemType) specified by currPos. 
//
//bool Find(/*in*/ KeyType target);		finds position of target within the OrdList, 
//										returns true if found, false otherwise 
//
//void Insert(/*in*/ ItemType newItem); 
//   --inserts target into list at position specified by PDM currPos.
//	 -- NOTE: Lastposition and Nextposition MUST be called immediately before insert.
//
//void Delete(); Deletes ListEntry specified by currPos 
//	 -- NOTE  FindPosition should be called before deleting a list entry.	
//
//void Clear();   Clears list and sets length and currPos to zero.
//int GetLength();  returns ths number of items in the list. 
//
//virtual void Print()= 0 ; PVF allowing descendant classes to output a single list element.
//							must be implemented in descendent classes
//
//PROTECTED METHODS:
//
//virtual ItemType* GetListPtr()const;
//	--Allows descendant classes to retrieve the pointer for the list
//virtual void SetListPtr(ItemType* newList, int newSize);
//	-- Allows descendant classes to set the pointer for the list
//virtual void GetSize() const;
//	-- Allows descendant classes access currPos
//virtual void SetSize(int newSize);
//	-- Allows descendant classes to set currPos
//virtual void GetCurrPos() const;
//	-- Allows descendant classes access currPos
//virtual void SetCurrPos(int newCurrPos);
//	-- Allows descendant classes to set currPos
//virtual void SetLength(int newLength); 
//
// Pure Virtual Functions :MUST BE IMPLEMENTED IN DESCENDENT CLASSES
//virtual void Expand()=0;
//	--creates a new list twice the size of the original w/ same elements 
//virtual void Contract()=0;
//	--creates a new list half the size of the original w/ same elements 
//virtual bool NoRoom()=0;
//	--returns true if list has no empty locations, false otherwise
//
//
//PRIVATE MEMBERS: 
//int length;                            //length of list 
//int currPos;                           //current position in the List
//int size;								 //current size of list
//ItemType* list						 //pointer to List

#ifndef ABCListClass_h
#define ABCListClass_h

#include "ItemType.h"  // SUPPLIED BY CLIENT FOR DEFINITION OF CLASS
					   // CONTAINS LAYOUT OF ELEMENT TO BE STORED IN LIST	


//Constant Declarations 
const int MAX_ENTRIES = 4;							//initial size 
const int FIRST_POSITION = 0;						//list minimum 
const int EMPTY = 0;								//list empty 

const int EXPANSION_FACTOR = 2;						//Used to expand list
const float CONTRACTION_FACTOR = 0.5f;				//Used to contract list
const float OCCUPANCY_TRIGGER = 0.25f;				//Used to determine if contraction is needed

// Class Declarations 
class ListClass 
{
	public: 
		ListClass(); //default constructor; 
		//sets private data members length & currPos to zero and initializes the 
		//array with enough memory for MAXENTRIES number of ItemType objects.
		//Pre: None 
		//Post: length & currPos have been initialized to zero and the class has enough 
		//      memory to contain MAXENTRIES objects of ItemType.

		void FirstPosition(); 
		//sets currPos to begining of list 
		//Pre: List exists 
		//Post: currPos has been set to the front of the List.
		
		void NextPosition(); 
		//sets currPos to next element in list
		//Pre: List exists 
		//Post: currPos is set to next element in list 

		void LastPosition(); 
		//sets currPos to last element in list
		//Pre: List exists 
		//Post: currPos is set to last element in list 

		bool IsEmpty() const; 
		//returns true if List has no elements. 
		//Pre : List exists 
		//Post: if List has no elements true is returned, otherwise false. 

		virtual bool IsFull() const; 
		//returns true if List is full
		//Pre: List exists 
		//Post: if List is full, true is returned, otherwise false. 

		bool EndOfList() const; 
		//returns true if currPos specifies end of List. 
		//Pre: List exists. 
		//Post: if currPos = length, true is returned, otherwise false 

		ItemType Retrieve() const; 
		//returns a record of type ItemType specified by currPos. 
		//Pre: currPos contains valid position in list (FindPosition has been called)
		//Post: A copy of the pdm record specified by PDM currPos has been returned to
		//		the caller. 
	
		virtual bool Find(/* in */KeyType target); 
		//finds position of key within the OrdList. 
		//Pre: target contains a keyType value to search List for. 
		//Post: If target is found within the List, true is returned and 
		//      currPos is set to the elements location in the list. If target is 
		//      not found, false is returned.
		
		virtual void Insert(/* in */ ItemType newItem); 
		//inserts target into OrdList at position specified by PDM currPos. 
		//Pre:	1) Space exists within the list 
		//		2) currPos contains location at which to insert new element; 
		//			where (O <= currPos < size) and LastPosition() and NextPosition() 
		//			have been called.
		//Post: target has been inserted at the location specified by currPos. 

		virtual void Delete(); 
		//deletes list entry specified by currPos, 
		//Pre: currPos contains the location of the element to be deleted;
		//     where (O <= position < length)(Findposition has been called.)
	    //Post: element has been deleted from list. 

		virtual void Clear(); 
		//clears the List 
		//Pre: List exists. 
		//Post: List has been cleared and if necessary resized to initial LISTENTRIES size.

		int GetLength() const; 
		//returns the number of entries in the the List 
		//Pre: List exists. 
		//Post: Number of Entries has been returned 

		//Pure virtual function to be defined in Descendent Classes 
		virtual void Print()=0;
		//Allows users to print the contents of their struct in an 
		//appropriate manner
		//Pre: List exists
		//Post: The contents of a list(ItemType) member have been printed.

	protected:
		virtual ItemType* GetListPtr()const;
		// Allows descendant classes to retrieve the pointer for the list
		// Pre: None
		// Post: Pointer to the list has been returned

		virtual void SetListPtr(ItemType* newList);
		// Allows descendant classes to set the pointer for the list
		// Pre: None
		// Post: PDM Pointer to the list has been returned

		virtual int GetSize() const;
		// Allows descendent classes to get currPos
		// Pre:  None
		// Post: PDM currPos has been returned
	
		virtual void SetSize(int newSize);
		// Allows descendent classes to set currPos
		// Pre:  None
		// Post: PDM currPos has been set

		virtual int GetCurrPos() const;
		// Allows descendent classes to get currPos
		// Pre: None
		// Post: PDM currPos has been returned
	
		virtual void SetCurrPos(int newCurrPos);
		// Allows descendent classes to set currPos
		// Pre: None
		// Post: PDM currPos has been set

		virtual void SetLength(int newLength);
		// Allows descendent classes to set length
		// Pre:  None
		// Post PDM length has been set

//**************************************************************************************************
		//Pure virtual function to be defined in Descendant Classes 
		virtual void Expand()=0;
		// creates a new list twice the size of the original and copies the
		//  info from the smaller list to the larger one.
		//Pre : List is full and needs to be enlarged
		//Post: List size has been doubled 
		
		
		virtual void Contract()=0;
		//	--creates a new list half the size of the original w/ same elements 
		//Pre : List occupancy is less than 25%
		//Post: List size has been reduced by half.
		//		List can never shrink to less than original size
		
		virtual bool NoRoom()=0;
		//	--returns true if list has no empty locations, false otherwise
		//Pre : List exists
		//Post: true is returned if list has no available locations, false otherwise
		
	private: 
		int length;          //length(occupied elements) of list 
		int currPos;         //specifies current position in the List 
		ItemType* list;		 //pointer to the list 
		int size;			 //size(total number of elements possible) of list

};//end ListClass 

#endif