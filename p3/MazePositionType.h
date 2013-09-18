/*
AUTHOR:
	Chris Pray

DATE:
	4/4/13

FILENAME:
	MazePositionType.h

PURPOSE:
	A MazePositionType is a struct that represents a location in a maze. It must contain a PositionEnum,
	which is defined in this file. A location can either be a wall or an unvisited or visited travelable
	location. In addition, a MazePositionType contains boolean members - triedEast, triedSouth,
	triedWest, and triedNorth - to allow a client to find a path through the maze.
*/

#ifndef MazePositionType_h
#define MazePositionType_h

enum PositionEnum { UNVISITED, WALL, VISITED };

struct MazePositionType
{
	PositionEnum status;	// The "type" of location (wall, unvisited, or visited)
	bool triedEast;			// True if client has taken an east path from this location, false otherwise
	bool triedSouth;		// True if client has taken a south path from this location, false otherwise
	bool triedWest;			// True if client has taken a west path from this location, false otherwise
	bool triedNorth;		// True if client has taken a north path from this location, false otherwise

}; // End MazePositionType

#endif