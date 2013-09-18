/*
AUTHOR:
	Chris Pray

DATE:
	4/25/13

FILENAME:
	MazeClass.cpp

PURPOSE:
	This file contains the implementation for all of the methods declared in MazeClass.h
*/

#include "MazeClass.h"	// For class declarations

MazeClass::MazeClass( /* In */ const int& setRows,	// # of rows to instantiate MazeClass object with
					  /* In */ const int& setCols )	// # of columns to instantiate MazeClass object with
{
	// Assign values to PDMs numRows and numCols
	numRows = setRows;
	numCols = setCols;

	try
	{
		// Dynamically allocate memory for a maze with numRows rows and numCols cols
		maze = new MazeRec[ numRows * numCols ];

		// For each location in the maze
		for( int i = 0; i < numRows; i++ )
		{
			for( int j = 0; j < numCols; j++ )
			{
				// Initiallize the location as UNVISITED
				maze[ i * numCols + j ].type = UNVISITED;

			} // End for

		} // End for

	} // End try
	catch( bad_alloc e )	// Failed to allocate dynamic memory
	{
		throw OutOfMemoryException("OutOfMemoryException: Failed to dynamically allocate memory.");

	} // End catch

} // End MazeClass( const int setRows, const int setCols )

MazeClass::~MazeClass()
{
	// Return the dynamically allocated memory for the maze back to the heap
	delete [] maze;

} // End ~MazeClass()

MazeClass::MazeClass( /* In */ const MazeClass& orig ) // MazeClass object to instantiate a deep copy of
{
	// Assign values to PDMs numRows and numCols
	numRows = orig.numRows;
	numCols = orig.numCols;

	try
	{
		// Dynamically allocate memory for a maze with numRows rows and numCols cols
		maze = new MazeRec[ numRows * numCols ];

		// For each location in the maze
		for( int i = 0; i < numRows; i++ )
		{
			for( int j = 0; j < numCols; j++ )
			{
				// Initiallize the location as the same type as the respective location in orig
				maze[ i * numCols + j ] = orig.maze[ i * numCols + j ];

			} // End for

		} // End for

	} // End try
	catch( bad_alloc e )	// Failed to allocate dynamic memory
	{
		throw OutOfMemoryException("OutOfMemoryException: Failed to dynamically allocate memory.");

	} // End catch

} // End MazeClass( const MazeClass& orig )

void MazeClass::SetMazeRec( /* In */ const int&		row,	  // Row # of MazeRec to assign to newType
							/* In */ const int&		col,	  // Column # of MazeRec to assign to
															  //  newType
							/* In */ const MazeRec& newType ) // The MazeRec to assign to the MazeRec at
															  //  location (row, col)
{
	// If location (row, col) is within the bounds of the maze
	if( InBounds( row, col ) )
	{
		// Assign the MazeRec struct at position (row, col) to newType
		maze[ row * numCols + col ] = newType;

	} // End if
	// Else location (row, col) is not within the bounds of the maze
	else
	{
		throw OutOfBoundsException("OutOfBoundsException: Location is outside the bounds of the maze.");

	} // End else

} // End SetMazeRec( const int row, const int col, const MazeRec newType )

MazeRec MazeClass::GetMazeRec( /* In */ const int& row,		// Row # of MazeRec to access
							   /* In */ const int& col )	// Column # of MazeRec to access
{
	// If location (row, col) is within the bounds of the maze
	if( InBounds( row, col ) )
	{
		// Return the MazeRec struct at location (row, col) in the maze
		return maze[ row * numCols + col ];

	} // End if
	// Else location (row, col) is not within the bounds of the maze
	else
	{
		throw OutOfBoundsException("OutOfBoundsException: Location is outside the bounds of the maze.");

	} // End else

} // End GetMazeRec( const int row, const int col )

int MazeClass::GetNumRows()
{
	return numRows;

} // End GetNumRows()

int MazeClass::GetNumCols()
{
	return numCols;

} // End GetNumCols()

bool MazeClass::InBounds( /* In */ const int& row,  // Row # of the location to determine if in bounds
						  /* In */ const int& col ) // Column # of the location to determine if in
													//  bounds
{
	return row >= 0 && row < numRows && col >= 0 && col < numCols;

} // End InBounds( const int row, const int col )