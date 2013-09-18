/*
AUTHOR:
	Chris Pray

DATE:
	3/19/13

FILENAME:
	ItemType.h

PURPOSE:
	An ItemType is a struct that represents the type of item in a list. It has at least 1 data member,
	called key. key is of type KeyType, which is defined using typedef. key represents a unique value in
	the list.
*/


#ifndef ItemType_h
#define ItemType_h

#include <string>		// For string data type
using namespace std;

//DEFINE KEYTYPE : necessary for ordering of class
typedef int KeyType;

struct ItemType		
{					
	KeyType key;		// ID which will be used to order the class.
  //string stuff		// Other elements in the list record will subsequently appear here. \

}; // End ItemType

#endif
