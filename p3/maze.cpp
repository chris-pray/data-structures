/*
AUTHOR:
	Chris Pray

DATE:
	4/4/13

FILENAME:
	maze.cpp

PURPOSE:
	This file contains the implementation for all of the methods declared in maze.h
*/

#include "maze.h"


//***************************************************************************************
//*																						*
//*				Non-default Constructor, Copy Constructor, Destructor					*
//*																						*
//***************************************************************************************

// Non-default Constructor
MazeClass::MazeClass(/* In */ const int setNumRows,	// # of rows to instantiate object with
					 /* In */ const int setNumCols)	// # of columns to instantiate object with
{
	// Assign values to PDMs numRows and numCols
	numRows = setNumRows;
	numCols = setNumCols;
	
	try
	{
		// Dynamically allocate memory for a maze with numRows rows and numCols cols
		maze = new MazePositionType[numRows * numCols];

		// For each location in the maze
		for(int i = 0; i < numRows; i++)
		{
			for(int j = 0; j < numCols; j++)
			{
				// Assign values to each struct member
				maze[i * numCols + j].status = UNVISITED;
				maze[i * numCols + j].triedEast = false;
				maze[i * numCols + j].triedSouth = false;
				maze[i * numCols + j].triedWest = false;
				maze[i * numCols + j].triedNorth = false;

			} // End for

		} // End for

	} // End try
	catch(bad_alloc e)
	{
		throw OutOfMemoryException("OutOfMemoryException: The heap has run out of memory.");

	} // End catch

} // End MazeClass(int setNumRows, int setNumCols)

//***************************************************************************************

// Copy Constructor
MazeClass::MazeClass(/* In */ const MazeClass& orig)	// The MazeClass object to instantiate a deep
														//  copy of
{
	// Assign values to PDMs numRows and numCols
	numRows = orig.numRows;
	numCols = orig.numCols;

	try
	{
		// Dynamically allocate memory for a maze with numRows rows and numCols cols
		maze = new MazePositionType[numRows * numCols];

		// For each location in the maze
		for(int i = 0; i < numRows; i++)
		{
			for(int j = 0; j < numCols; j++)
			{
				// Assign values to each struct member
				maze[i * numCols + j] = orig.maze[i * numCols + j];

			} // End for

		} // End for

	} // End try
	catch(bad_alloc e)
	{
		throw OutOfMemoryException("OutOfMemoryException: The heap has run out of memory.");

	} // End catch

} // End MazeClass(const MazeClass& orig)

//***************************************************************************************

// Destructor
MazeClass::~MazeClass()
{
	delete [] maze;

} // End ~MazeClass()


//***************************************************************************************
//*																						*
//*									Mutator												*
//*																						*
//***************************************************************************************

void MazeClass::SetPosition(/* In */ const int			    row,		 // The row at which to set the
																		 //  MazePositionType struct
							/* In */ const int			    col,		 // The column at which to set
																		 //  the MazePositionType struct
							/* In */ const MazePositionType newPosition) // The MazePositionType struct
																		 //  to assign the
																		 //  MazePositionType struct at
																		 //  location (row, col) to
{
	// If location (row, col) is within the bounds of the maze
	if(row >= 0 && row < numRows && col >= 0 && col < numCols)
	{
		// Assign the MazePositionType struct at position (row, col) to newPosition
		maze[row * numCols + col] = newPosition;

	} // End if

} // End SetPosition(int row, int col, MazePositionType newPosition)


//***************************************************************************************
//*																						*
//*								Observer / Accessor										*
//*																						*
//***************************************************************************************

MazePositionType MazeClass::GetPosition(/* In */ const int row,	// The row at which to retrieve
										/* In */ const int col)	// The column at which to retrieve
{
	// If location (row, col) is within the bounds of the maze
	if(row >= 0 && row < numRows && col >= 0 && col < numCols)
	{
		// Return the MazePositionType struct at location (row, col) in the maze
		return maze[row * numCols + col];

	} // End if
	// Else location (row, col) is not within the bounds of the maze
	else
	{
		throw RetrieveFromOutOfBoundsException("RetrieveFromOutOfBoundsException: Cannot retrieve a "
			"position from a location\n                                  outside the bounds of the "
			"maze.");

	} // End else

} // End GetPosition(int row, int col)

//***************************************************************************************

int MazeClass::GetNumRows()
{
	return numRows;

} // End GetNumRows()

//***************************************************************************************

int MazeClass::GetNumCols()
{
	return numCols;

} // End GetNumCols()