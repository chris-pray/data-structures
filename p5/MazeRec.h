/*
AUTHOR:
	Chris Pray

DATE:
	4/25/13

FILENAME:
	MazeRec.h

PURPOSE:
	A MazeRec is a struct that represents a location in a maze. It must contain a MazeLocEnum, which is
	defined in this file. A location can either be a wall or an unvisited or visited travelable
	location.
*/

#ifndef MazeRec_h
#define MazeRec_h

enum MazeLocEnum { UNVISITED, WALL, VISITED };

struct MazeRec
{
	MazeLocEnum type;	// WALL if location cannot be traveled. UNVISITED if the location can be
						//  traveled but hasn't been. VISITED if the location can be and has been
						//  traveled.

}; // End MazeRec

#endif