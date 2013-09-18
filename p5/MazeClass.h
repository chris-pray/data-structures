/*
AUHTOR:
	Chris Pray

DATE:
	4/25/13

FILENAME:
	MazeClass.h

PURPOSE:
	This file contains the specification for a dynamically allocated two-dimensional maze class. The
	user of this class supplies the dimensions of a maze object at run-time. A maze is instantiated as
	an open two-dimensional plane and it is up to the user to build the maze through the use of this
	class's operations. The data that each location in the maze will contain is defined in MazeRec.h,
	which must be supplied by the user.

ASSUMPTIONS:
	(1) When using the class non-default constructor, the user must pass positive integers as the
		dimensions of the maze
	(2) A valid row # and a valid column # must be passed to methods SetMazeRec and GetMazeRec. Valid
		row #s are between 0 and numRows - 1, inclusive. Valid column #s are between 0 and numCols - 1,
		inclusive.

EXCEPTION HANDLING:
	
	*Exceptions Caught*

		bad_alloc
			caught in the non-default constructor and the copy constructor if an attempt to allocate
			dynamic memory fails

	*Exceptions Thrown*
		
		OutOfBoundsException
			Thrown whenever an attempt to access or modify a MazeRec from a location that's outside the
			bounds of the maze is made

		OutOfMemoryException
			Thrown whenever an attempt to dynamically allocate memory for the instantiation of a
			MazeClass object fails

SUMMARY OF METHODS:

	MazeClass(const int setRows, const int setCols)
		Instantiates a MazeClass object with setRows rows and setCols columns. Assigns setRows to
		numRows and setCols to numCols. For each location in the maze, type gets assigned UNVISITED.

	~MazeClass()
		Returns all dynamically allocated memory of a MazeClass object back to the heap.

	MazeClass(const MazeClass& orig)
		Instantiates a deep copy of orig.

	void SetMazeRec(const int row, const int col, const MazeRec newType)
		Sets the MazeRec struct at a specified location in the maze to newType.

	MazeRec GetMazeRec(const int row, const int col)
		Retrieves the MazeRec struct from a specified location in the maze.

	int GetNumRows()
		Returns the # of rows in the maze.

	int GetNumCols()
		Returns the # of columns in the maze.

	bool InBounds(const int row, const int col)
		Determines if the specified location is within the bounds of the maze.
*/

#ifndef MazeClass_h
#define MazeClass_h

#include "MazeRec.h"			// Provides the structure of the type of data to be stored in each
								//  location in the maze
#include "MazeExceptions.h"		// For custom exceptions, OutOfBoundsException and OutOfMemoryException
using namespace MazeExceptions;

class MazeClass
{
	public:

		MazeClass( /* In */ const int& setRows,	 // # of rows to instantiate MazeClass object with
				   /* In */ const int& setCols ); // # of columns to instantiate MazeClass object with
		/*
		Purpose:			Instantiates a MazeClass object with setRows rows and setCols columns.
							Assigns setRows to numRows and setCols to numCols. For each location in the
							maze, type gets assigned UNVISITED.
		Pre:				setRows and setCols are positive
		Post:				A MazeClass object has been instantiated. numRows has been initiallized to
							setRows and numCols has been initiallized to setCols. For each location in
							the maze, type has been assigned UNVISITED.
		Classification:		Non-default Constructor
		Order of Magnitude:	O(N * M), where N = setRows and M = setCols
		Exceptions Thrown:	OutOfMemoryException
		*/

		~MazeClass();
		/*
		Purpose:			Returns all dynamically allocated memory of a MazeClass object back to the
							heap.
		Pre:				A MazeClass object has been instantiated.
		Post:				All dynamically allocated memory of the MazeClass object has been returned
							to the heap.
		Classification:		Destructor
		Order of Magnitude:	O(1)
		*/

		MazeClass( /* In */ const MazeClass& orig ); // MazeClass object to instantiate a deep copy of
		/*
		Purpose:			Instantiates a deep copy of orig.
		Pre:				orig exists.
		Post:				A MazeClass object has been instatiated with the values of orig.
		Classification:		Copy Constructor
		Order of Magnitude:	O(N * M), where N = orig.numRows and M = orig.numCols
		Exceptions Thrown:	OutOfMemoryException
		*/

		void SetMazeRec( /* In */ const int& row,			// Row # of MazeRec to assign to newType
						 /* In */ const int& col,			// Column # of MazeRec to assign to newType
						 /* In */ const MazeRec& newType );	// The MazeRec to assign to the MazeRec at
															//  location (row, col)
		/*
		Purpose:			Assigns the MazeRec struct at location (row, col) in the maze to newType.
		Pre:				A MazeClass object has been instantiated. (row, col) is a valid location
							within the maze.
		Post:				The MazeRec struct at location (row, col) has been set to newType.
		Classification:		Mutator
		Order of Magnitude:	O(1)
		Exceptions Thrown:	OutOfBoundsException
		*/

		MazeRec GetMazeRec( /* In */ const int& row,	// Row # of MazeRec to retrieve
							/* In */ const int& col );	// Column # of MazeRec to retrieve
		/*
		Purpose:			Retrieves the MazeRec struct from location (row, col) in the maze.
		Pre:				A MazeClass object has been instantiated. (row, col) is a valid location
							within the maze.
		Post:				The MazeRec struct at location (row, col) in the maze has been returned.
		Classification:		Observer / Accessor
		Order of Magnitude:	O(1)
		Exceptions Thrown:	OutOfBoundsException
		*/

		int GetNumRows();
		/*
		Purpose:			Returns the # of rows in the maze.
		Pre:				A MazeClass object has been instantiated.
		Post:				The # of rows in the maze has been returned.
		Classification:		Observer / Accessor
		Order of Magnitude:	O(1)
		*/

		int GetNumCols();
		/*
		Purpose:			Returns the # of columns in the maze.
		Pre:				A MazeClass object has been instantiated.
		Post:				The # of columns in the maze has been returned.
		Classification:		Observer / Accessor
		Order of Magnitude:	O(1)
		*/

		bool InBounds( /* In */ const int& row,	 // Row # of the location to determine if in bounds
					   /* In */ const int& col ); // Column # of the location to determine if in bounds
		/*
		Purpose:			Determines if the specified location is within the bounds of the maze.
		Pre:				A MazeClass object has been instantiated. row and col have been assigned
							values.
		Post:				True has beeen returned if the location (row, col) is within the bounds of
							the maze. Otherwise, false has been returned.
		Classification:		Observer / Predicator
		Order of Magnitude:	O(1)
		*/


	private:

		MazeRec* maze;		// Pointer to the dynamically allocated memory for the maze
		int		 numRows,	// # of rows in the maze
				 numCols;	// # of columns in the maze

}; // End MazeClass

#endif