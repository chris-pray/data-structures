/*
AUTHOR:
	Chris Pray

DATE:
	4/18/13

FILENAME:
	ItemType.h

PURPOSE:
	An ItemType is a struct that represents the type of item in an OrdListClass object. It has at least
	1 data member, called key. key is of type KeyType, which is defined using typedef. key represents a
	unique value in the list.
*/

#ifndef ItemType_h
#define ItemType_h

typedef int KeyType;

struct ItemType
{
	KeyType key;	// Unique ID which will be used to order the class
	//other stuff	// Other elements in the list record will subsequently appear here

}; // End ItemType

#endif