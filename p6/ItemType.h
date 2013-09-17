/*
AUTHOR:
	Chris Pray

DATE:
	5/10/13

FILENAME:
	ItemType.h

PURPOSE:
	An ItemType is a struct that represents the type of item in an OrdListClass object. It has at least
	1 data member, called key. key is of type KeyType, which is defined using typedef. key represents a
	unique value in the list.
*/

#ifndef ItemType_h
#define ItemType_h

struct ItemType
{
	KeyType key;	// Unique ID which will be used to order the items in an OrdListClass object

}; // End ItemType

#endif