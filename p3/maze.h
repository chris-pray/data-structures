/*
AUTHOR:
	Chris Pray

DATE:
	4/4/13

FILENAME:
	maze.h

PURPOSE:
	This file contains the specification for a dynamically allocated two-dimensional maze class. The
	user of this class supplies the dimensions of a maze object at run-time. A maze is instantiated as
	an open two-dimensional plane and it is up to the user to build the maze through the use of this
	class's operations. The data that each location in the maze will contain is defined in
	MazePositionType.h, which must be supplied by the user.
	
ASSUMPTIONS:
	(1) When using the class non-default constructor, the user must pass positive integers as the
		dimensions of the maze
	(2) A valid row # and a valid column # must be passed to methods SetPosition and GetPosition. Valid
		row #s are between 0 and numRows - 1, inclusive. Valid column #s are between 0 and numCols - 1,
		inclusive.

EXCEPTION HANDLING:
	bad_alloc is caught in the non-default constructor and the copy constructor if an attempt to
	allocate dynamic memory fails 

SUMMARY OF METHODS:

	MazeClass(int setNumRows, int setNumCols)
		Instantiates a MazeClass object with setNumRows rows and setNumCols columns. Assigns numRows to
		setNumRows and numCols to setNumCols. For each location in the maze, status gets assigned
		UNVISITED and triedEast, triedSouth, triedWest, and triedNorth each get assigned false.

	MazeClass(const MazeClass& orig)
		Instantiates a deep copy of orig.

	~MazeClass()
		Returns all dynamically allocated memory of a MazeClass object back to the heap.

	void SetPosition(int row, int col, MazePositionType newPosition)
		Sets the MazePositionType struct at a specified location in the maze to newPosition.

	MazePositionType GetPosition(int row, int col)
		Retrieves the MazePositionType struct from a specified location in the maze.

	int GetNumRows()
		Returns the # of rows in the maze.

	int GetNumCols()
		Returns the # of columns in the maze.
*/

#ifndef MazeClass_h
#define MazeClass_h

#include "MazePositionType.h"	// Provides the structure of the type of data to be stored in each 
								//  location of the maze
#include "MazeExceptions.h"		// For custom exceptions, RetrieveFromOutOfBoundsException and
								//  OutOfMemoryException
using namespace nmspcMazeExceptions;

class MazeClass
{
	public:

		// Constructors and Destructor

		MazeClass(/* In */ const int setNumRows,	// # of rows to instantiate object with
				  /* In */ const int setNumCols);	// # of columns to instantiate object with
		/*
		Purpose:			Instantiates a MazeClass object with setNumRows rows and setNumCols columns.
							Assigns numRows to setNumRows and numCols to setNumCols. For each location
							in the maze, status gets assigned UNVISITED and triedEast, triedSouth,
							triedWest, and triedNorth each get assigned false.
		Pre:				setNumRows and setNumCols are positive
		Post:				A MazeClass object has been instantiated. numRows has been initiallized to
							setNumRows and numCols has been initiallized to setNumCols. For each
							location in the maze, status has been assigned UNVISITED and triedEast,
							triedSouth, triedWest, and triedNorth each have been assigned false.
		Classification:		Non-default Constructor
		Order of Magnitude:	O(N * M), where N = setNumRows and M = setNumCols
		Exceptions Thrown:	OutOfMemoryException
		*/

		MazeClass(/* In */ const MazeClass& orig); // The MazeClass object to instantiate a deep copy of
		/*
		Purpose:			Instantiates a deep copy of orig.
		Pre:				orig exists.
		Post:				A MazeClass object has been instatiated with the values of orig.
		Classification:		Copy Constructor
		Order of Magnitude:	O(N * M), where N = orig.numRows and M = orig.numCols
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


		// ADT MazeClass Operations

		void SetPosition(/* In */ const int				 row,		   // The row at which to set the
																	   //  MazePositionType struct
						 /* In */ const int				 col,		   // The column at which to set the
																	   //  MazePositionType struct
						 /* In */ const MazePositionType newPosition); // The MazePositionType struct to
																	   //  assign the MazePositionType
																	   //  struct at location
																	   //  (row, col) to
		/*
		Purpose:			Sets the MazePositionType struct at location (row, col) in the maze to
							newPosition.
		Pre:				A MazeClass object has been instantiated. (row, col) is a valid location
							within the maze.
		Post:				The MazePositionType struct at position (row, col) has been set to
							newPosition
		Classification:		Mutator
		Order of Magnitude:	O(1)
		*/

		MazePositionType GetPosition(/* In */ const int row,	// The row at which to retrieve
									 /* In */ const int col);	// The column at which to retrieve
		/*
		Purpose:			Retrieves the MazePositionType struct from location (row, col) in the maze.
		Pre:				A MazeClass object has been instantiated. (row, col) is a valid location
							within the maze.
		Post:				The MazePositionType struct at position (row, col) in the maze has been
							returned.
		Classification:		Observer / Accessor
		Order of Magnitude:	O(1)
		Exceptions Thrown:	RetrieveFromOutOfBoundsException
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


	private:

		MazePositionType* maze;	// Pointer to the dynamically allocated memory for the maze
		int numRows,			// # of rows in the maze
			numCols;			// # of columns in the maze

}; // End MazeClass

#endif