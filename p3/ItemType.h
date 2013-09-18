/*
AUTHOR:
	Chris Pray

DATE:
	4/4/13

FILENAME:
	ItemType.h

PURPOSE:
	An ItemType is a struct that represents an item in a stack. The user of the stack will define the
	type of data in the stack here inside the ItemType definition. When using a stack to keep track of
	a path through a maze, a DirectionEnum must be defined, which can contain the values: NORTH, SOUTH,
	EAST, or WEST.
*/

#ifndef ItemType_h
#define ItemType_h

enum DirectionEnum { NORTH, SOUTH, EAST, WEST };

struct ItemType
{
	DirectionEnum direction;	// A direction (north, south, east, or west)

}; // End ItemType

#endif