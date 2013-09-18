/*
AUTHOR:
	Chris Pray

DATE:
	4/25/13

FILENAME:
	MazeCkient.cpp

PURPOSE:
	This file reads in a file name from a user, validates the filename, and, if it is valid and found,
	reads in data from the file specifying the dimensions of a maze as well as the locations of walls
	in the maze, if there are any. A valid file name contains only letters, a period, and three letters
	after the period. All valid paths through the maze are found, using recursion, and printed to the
	file whose name is specified by constant, OUT_FILE_NAME. Valid paths are ones that go from the
	entrance, at location (0, 0), to the exit, at location (mazeWidth - 1, mazeLength - 1), in a direct
	path without crossing the same location more than once. If either the entrance or the exit are
	blocked by a wall, the maze will not contain any valid paths.

INPUT:
	This file reads a file name from the user, validates the file name, and attempts to open the file. A
	valid file name contains only letters, a period, and three letters after the period. If the file was
	successfully opened, data is read from the file. This data specifies the dimensions of the maze
	which is created and the locations of walls in the maze, if there are any.

PROCESSING:
	First, the input file name read from the user is validated. If it is in the correct format, the
	program attempts to open the file. If successful, the dimensions of the maze are read from the file.
	A MazeClass object gets instantiated with these dimensions. Next, the locations of walls in the
	maze, if there are any, are read from the file, building the walls of the maze as they are read,
	until the end of the file is reached. Then the program uses recursion to search through the maze to
	find all valid paths through the maze, starting at the entrance to the maze (0, 0). For each move to
	a new location within the maze, a character ('N', 'S', 'E', or 'W') representing the direction moved
	is concatenated onto a string in order to keep track of the path through the maze. In each recursive
	call, if the exit from the maze is reached (the base case), the path (represented by NORTH, SOUTH,
	EAST, and/or WEST moves) is printed to the output file (OUT_FILE_NAME) and the solution backtracks
	to the previous location. If the exit from the maze was not reached, another call to the recursive
	function is made from the current location in the maze to an adjacent location within the maze,
	diminishing the problem size by one location on each recursive call. From each location in the maze,
	adjacent locations within the maze are checked in the order, EAST, SOUTH, WEST, and then NORTH. If a
	location is reached which is not the exit from the maze and there are no possible adjacent locations
	to move to, a backtrack is made to the previous location. On each path through the maze, valid
	locations to move to are marked as UNVISITED in the location's MazeRec. Each location can only be
	traveled once on each path through the maze. Once a location marked as UNVISITED is traveled, it 
	becomes marked as VISITED. If either the entrance to the maze or the exit from the maze are blocked
	by a wall, no searches through the maze are performed since there are no valid paths in this case.
	The program prompts the user along the way to notify the progress of the execution, including when
	execution is finished and all valid paths through the maze have been written to the output file.

OUTPUT:
	Prompts are output to the console which tell the user to enter the name of an input file and also to
	let the user know the progress of the program. In addition, the paths through the maze that were
	found, get written to the file whose name is specified by constant, OUT_FILE_NAME. The paths, if
	any are found, are labeled as "Solution #1" through "Solution #N", where N is the last path that
	was found. Otherwise, if either the entrance to the maze or the exit from the maze are blocked, a
	statement stating so is written to the file.

ASSUMPTIONS:
	(1)	The input file will contain the dimensions of the maze
	(2)	The data in the input file will be in the correct format

ERROR CHECKING:
	The input file name is validated. A valid file name must contain only letters and a period and
	three letters after the period. The user is given as many chances as necessary to enter a valid
	file name, or they can press 'Q' or 'q' to quit the program. These chances to re-enter the file
	name are given in the case a valid file name is not found as well.

EXCEPTION HANDLING:
	(1) OutOfMemoryException
			Thrown whenever an attempt to dynamically allocate memory for the instantiation of a
			MazeClass object fails
	(2) OutOfBoundsException
			Thrown whenever an attempt to access or modify a MazeRec from a location that's outside the
			bounds of the maze is made

*/

// Header Files / Libraries
#include "MazeClass.h"			// For MazeClass objects
#include <iostream>				// For standard input/output
#include <string>				// For string datatype
#include <fstream>				// For file input/output
using namespace std;

// Prototypes
void SolveMaze(MazeClass&, string&, ofstream&, int&, int&, int&);
	// Finds every path through the maze from the location (row, col) in the maze to the exit from the
	//  maze. Each path is printed to an output file.
void SetMazeLoc(MazeClass&, const int, const int, const MazeLocEnum);
	// Marks the MazeRec at location (row, col) in the maze as either WALL, UNVISITED, or VISITED.
bool TryMove(MazeClass&, char, string&, int&, int&);
	// Attempts to move in a specified direction in the maze, modifying the row and column #s and the
	//  string representing the path through the maze appropriately.
void BackTrack(MazeClass&, string&, int&, int&);
	// Moves to the previous location in the maze, modifying the row and column #s and the string
	//  representing the path through the maze appropriately.

// Constants
const char OUT_FILE_NAME[] = "solution.out";	// Output file name
const int MIN_FILENAME_LENGTH = 5;				// Min length of input file name
const int FIRST_SOLUTION = 1;					// First solution #
const int ROW_START = 0;						// 1st row in the maze
const int COL_START = 0;						// 1st column int he maze

void main()
{
	// Variables
	string solution;						// Each character ('N', 'S', 'E', or 'W') represents a
											//  direction taken through the maze
	ifstream din;							// Input file stream variable
	ofstream dout;							// Output file stream variable
	string inFileName;						// Input file name
	bool validFileName;						// Gets true if input file name is valid, false otherwise
	unsigned int index;						// Position of a character in inFileName
	int row;								// A row # in the maze
	int col;								// A column # in the maze
	int numRows;							// Max # of rows in the maze
	int numCols;							// Max # of columns in the maze
	int solutionNumber = FIRST_SOLUTION;	// The current solution #

	//**************************************************************************************************
	// Prompt for and get input file name, validate input file name, open input file

	do // Do at least once
	{
		validFileName = true;

		// Prompt use for and get input file name
		cout << "Please enter the input file name, or press 'Q' to quit:" << endl;
		cin >> inFileName;

		// If the user entered 'Q' or 'q'
		if( ( inFileName.compare( "Q" ) == 0 ) || ( inFileName.compare( "q" ) == 0 ) )
		{
			// Terminate program
			return;

		} // End if

		// If the length of the input file name is long enough
		if( inFileName.length() >= MIN_FILENAME_LENGTH )
		{
			index = 0;

			// While the input file name is valid and the index of the current character being tested
			//  is < the 4th from the last
			while( validFileName &&
				index < inFileName.length() - 4 )
			{
				// If the character at the current index of inFileName is a letter
				if( isalpha( inFileName[ index ] ) )
				{
					// Increment index by one
					index++;

				} // End if
				// Else the character at the current index of inFileName is not a letter
				else
				{
					// Input file name is not valid
					validFileName = false;

				} // End else

			} // End while

			// If the input file name is valid
			if( validFileName )
			{
				// If the character at the current index of inFileName is '.'
				if( inFileName[ index ] == '.' )
				{
					// Increment index by one
					index++;

					// While the input file name is valid and the index of the current character being
					//  tested is < the length of inFileName
					while( validFileName && index < inFileName.length() )
					{
						// If the character at the current index of inFileName is a letter
						if( isalpha( inFileName[ index ] ) )
						{
							// Increment index by one
							index++;

						} // End if
						else
						{
							// Input file name is not valid
							validFileName = false;

						} // End else

					} // End while

				} // End if
				// Else the character at the current index of inFileName is not '.'
				else
				{
					// Input file name is not valid
					validFileName = false;

				} // End else

			} // End if

		} // End if
		// Else the length of the input file name is not long enough
		else
		{
			// Input file name is not valid
			validFileName = false;

		} // End else

		// If the input file name is not valid
		if( !validFileName )
		{
			cout << "File name is not in correct format." << endl;

		} // End if

		// If the input file name is valid
		if( validFileName )
		{
			// Open the input file and associate it with din
			din.open( inFileName.c_str() );

			// If the input file not opened
			if( !din )
			{
				cout << "File not found." << endl;

				// Input file name is not valid
				validFileName = false;

			} // End if

		} // End if

	} // End do
	// While the input file name is not valid
	while( !validFileName );

	cout << "File name validated." << endl;

	//**************************************************************************************************
	// Build the maze

	// Get the # of rows and # of columns
	din >> numRows >> numCols;

	try
	{
		// Instantiate the maze with numRows rows and numCols columns
		MazeClass maze(numRows, numCols);

		// Get the coordinates of the 1st wall
		din >> row >> col;

		// While the input file is not at the end of the file
		while( din )
		{
			// Mark location (row, col) as WALL
			SetMazeLoc(maze, row, col, WALL);

			// Get the coordinates of the next wall
			din >> row >> col;

		} // End while

		// Close the input file
		din.close();

		cout << "Maze built." << endl;

		//**********************************************************************************************
		// Discover and Print All Valid Paths Through the Maze

		// Associate the output file stream variable with the output file
		dout.open( OUT_FILE_NAME );

		// If the entrance to the maze is not blocked by a wall
		if( maze.GetMazeRec( ROW_START, COL_START ).type != WALL )
		{
			// If the exit from the maze is not blocked by a wall
			if( maze.GetMazeRec( numRows - 1, numCols - 1 ).type != WALL )
			{
				// Concatenate an 'S' to the string representing the path through the maze, indicating a
				//  southward movement into the maze
				solution += "S";

				// Initiallize the row and column #s to the row and column #s at the entrance to the
				//  maze
				row = ROW_START;
				col = COL_START;
				
				// Find and print all paths through the maze to the output file
				SolveMaze( maze, solution, dout, solutionNumber, row, col );

			} // End if
			// Else the exit from the maze is blocked by a wall
			else
			{
				dout << "The exit from the maze is blocked." << endl;

			} // End else

		} //  End if
		// Else the entrance to the maze is blocked by a wall
		else
		{
			dout << "The entrance to the maze is blocked." << endl;

		} // End else

		// Close the output file
		dout.close();

		cout << "Results have been sent to: " << OUT_FILE_NAME << endl;

	} // End try
	catch( OutOfBoundsException e)	// Failed attempt to access or modify a MazeRec outside the bounds
									//  of the maze
	{
		cout << e.GetMessage() << endl;

	} // End catch
	catch( OutOfMemoryException e )	// Could not dynamically allocate memory
	{
		cout << e.GetMessage() << endl;

		return;

	} // End catch

} // End main

//******************************************************************************************************

/* 
Purpose:	Finds every path through the maze from the location (row, col) in the maze to the exit from
			the maze. Each path is printed to an output file.
Pre:		maze has been instantiated. The values of the characters in solution represent the path
			taken from the entrance to the maze to the location (row, col) in the maze. dout has been
			associated with the output file. solutionNumber contains the current solution number.
			(row, col) is a location within the bounds of the maze.
Post:		Each path through the maze from the location (row, col) in the maze to the exit from the
			maze has been found and printed to the output file.
*/
void SolveMaze( /* In/Out */ MazeClass& maze,			// The maze
				/* In/Out */ string&	solution,		// The string representing the path through the maze
				/* In/Out */ ofstream&	dout,			// The output file stream variable
				/* In/Out */ int&		solutionNumber,	// The current solution number
				/* In */	 int&		row,			// The row # of a location in the maze
				/* In */	 int&		col)			// The column # of a location in the maze
{
	// If the current location in the maze is the exit from the maze
	if( row == maze.GetNumRows() - 1 &&
		col == maze.GetNumCols() - 1 )
	{
		char* print = &solution[ 0 ];	// Points to a character that represents a direction taken in
										//  the maze

		// Concatenate an 'S' to the string representing the path through the maze, indicating a
		//  southward movement out of the maze
		solution += "S";

		dout << "Solution #" << solutionNumber << ":" << endl;

		// For each character in the string representing the path through the maze
		for( int i = 0; i < solution.length(); i++ )
		{
			// Branch depending on what the character being pointed to is
			switch( *print )
			{
				case 'N' : dout << "NORTH"; break;

				case 'S' : dout << "SOUTH"; break;

				case 'E' : dout << "EAST"; break;

				case 'W' : dout << "WEST"; break;

			} // End switch

			// If not on the last iteration of the loop
			if( i != solution.length() - 1 )
			{
				dout << ", ";

				// Point to the next character in the string representing the path through the maze
				print++;

			} // End if
			// Else on the last iteration of the loop
			else
			{
				dout << endl << endl;

			} // End else

		} // End for

		// Increment the solution # by one
		solutionNumber++;

		// Erase the last character from the string representing the path through the maze
		solution.erase( solution.length() - 1 );

		// Backtrack to the previous position in the maze
		BackTrack( maze, solution, row, col );

		// Return to the calling function
		return;

	} // End if

	// If able to move to an adjacent location in the maze east of the current location in the maze
	if( TryMove( maze, 'E', solution, row, col ) )
	{
		// Find all paths in the maze from the adjacent location to the east of the current location and
		//  print them to the output file
		SolveMaze( maze, solution, dout, solutionNumber, row, col );

	} // End if

	// If able to move to an adjacent location in the maze south of the current location in the maze
	if( TryMove( maze, 'S', solution, row, col ) )
	{
		// Find all paths in the maze from the adjacent location to the south of the current location
		//  and print them to the output file
		SolveMaze( maze, solution, dout, solutionNumber, row, col );

	} // End if

	// If able to move to an adjacent location in the maze west of the current location in the maze
	if( TryMove( maze, 'W', solution, row, col ) )
	{
		// Find all paths in the maze from the adjacent location to the west of the current location and
		//  print them to the output file
		SolveMaze( maze, solution, dout, solutionNumber, row, col );

	} // End if

	// If able to move to an adjacent location in the maze north of the current location in the maze
	if( TryMove( maze, 'N', solution, row, col ) )
	{
		// Find all paths in the maze from the adjacent location to the north of the current location
		//  and print them to the output file
		SolveMaze( maze, solution, dout, solutionNumber, row, col );

	} // End if

	// Backtrack to the previous position in the maze
	BackTrack( maze, solution, row, col );

} // End SolveMaze( MazeClass& maze, string& solution, ofstream& dout, int& solutionNumber, int row,
  //  int col)

//******************************************************************************************************

/* 
Purpose:	Marks the MazeRec at location (row, col) in the maze as either WALL, UNVISITED, or VISITED.
Pre:		maze has been instantiated. (row, col) is a location within the bounds of the maze. newType
			has been assigned a value.
Post:		The MazeRec at location (row, col) in the maze has been marked with the value of newType.
*/
void SetMazeLoc( /* In/Out */		MazeClass&  maze,		// The maze
				 /* In */	  const int			row,		// The row # of a location in the maze
				 /* In */	  const int			col,		// The column # of a location in the maze
				 /* In */	  const MazeLocEnum newType )	// The value to mark the MazeRec at location
															//  (row, col) in the maze with
{
	MazeRec mazeItem;	// Gets the data to set the MazeRec at location (row, col) in the maze to
	
	// Assign the type field of the MazeRec to newType
	mazeItem.type = newType;

	try
	{
		// Assign the MazeRec at location (row, col) in the maze to newItem
		maze.SetMazeRec( row, col, mazeItem );

	} // End try
	catch( OutOfBoundsException e )	// Failed attempt to modify a MazeRec outside the bounds of the maze
	{
		cout << e.GetMessage() << endl;

	} // End catch

} // End SetMazeLoc( MazeClass& maze, const int row, const int col, const MazeLocEnum newType )

//******************************************************************************************************

/* 
Purpose:	Attempts to move in a specified direction in the maze, modifying the row and column #s and
			the string representing the path through the maze appropriately.
Pre:		maze has been instantiated. The value of direction is 'N', 'S', 'E', or 'W'. solution has
			been declared. (row, col) is a location within the bounds of the maze.
Post:		If the move was successful, true has been returned and the value of the last character in
			solution represents the direction of the move taken and row or col has been updated to
			reflect the direction taken. Otherwise, false has been returned and the values of the
			parameters have not been changed.
*/
bool TryMove( /* In */	   MazeClass& maze,			// The maze
			  /* In */	   char		  direction,	// A character representing the direction to move
			  /* In/Out */ string&    solution,		// The string representing the path through the maze
			  /* In/Out */ int&		  row,			// The row # of a location in the maze
			  /* In/Out */ int&		  col )			// The column # of a location in the maze
{
	// Branch depending on the value of the character representing a direction
	switch( direction )
	{
		case 'N' :
		{
			// If location directly to the north of location (row, col) in the maze is within the bounds
			//  of the maze and marked as UNVISITED
			if( maze.InBounds( row - 1, col ) && maze.GetMazeRec( row - 1, col ).type == UNVISITED )
			{
				// Mark location (row, col) in the maze as VISITED
				SetMazeLoc( maze, row, col, VISITED );

				// Decrement the row # by one
				row--;

				// Concatenate an 'N' to the string representing the path through the maze, indicating a
				//  northward movement in the maze
				solution += "N";

				return true;

			} // End if
			// Else location directly to the north of location (row, col) in the maze is either not
			//  within the bounds of the maze or is not marked as UNVISITED
			else
			{
				return false;

			} // End else

		} // End case

		case 'S' :
		{
			// If location directly to the south of location (row, col) in the maze is in the bounds of
			//  the maze and marked as UNVISITED
			if( maze.InBounds( row + 1, col ) && maze.GetMazeRec( row + 1, col ).type == UNVISITED )
			{
				// Mark location (row, col) in the maze as VISITED
				SetMazeLoc( maze, row, col, VISITED );

				// Increment the row # by one
				row++;

				// Concatenate an 'S' to the string representing the path through the maze, indicating a
				//  southward movement in the maze
				solution += "S";

				return true;

			} // End if
			// Else location directly to the south of location (row, col) in the maze is either not
			//  within the bounds of the maze or is not marked as UNVISITED
			else
			{
				return false;

			} // End else

		} // End case

		case 'E' :
		{
			// If location directly to the east of location (row, col) in the maze is in the bounds of
			//  the maze and marked as UNVISITED
			if( maze.InBounds( row, col + 1 ) && maze.GetMazeRec( row, col + 1 ).type == UNVISITED )
			{
				// Mark location (row, col) in the maze as VISITED
				SetMazeLoc( maze, row, col, VISITED );

				// Increment the column # by one
				col++;

				// Concatenate an 'E' to the string representing the path through the maze, indicating a
				//  eastward movement in the maze
				solution += "E";

				return true;

			} // End if
			// Else location directly to the east of location (row, col) in the maze is either not
			//  within the bounds of the maze or is not marked as UNVISITED
			else
			{
				return false;

			} // End else

		} // End case

		case 'W' :
		{
			// If location directly to the west of location (row, col) in the maze is in the bounds of
			//  the maze and marked as UNVISITED
			if( maze.InBounds( row, col - 1 ) && maze.GetMazeRec( row, col - 1 ).type == UNVISITED )
			{
				// Mark location (row, col) in the maze as VISITED
				SetMazeLoc( maze, row, col, VISITED );

				// Decrement the column # by one
				col--;

				// Concatenate an 'W' to the string representing the path through the maze, indicating a
				//  westward movement in the maze
				solution += "W";

				return true;

			} // End if
			// Else location directly to the west of location (row, col) in the maze is either not
			//  within the bounds of the maze or is not marked as UNVISITED
			else
			{
				return false;

			} // End else

		} // End case

	} // End switch

} // End TryMove( MazeClass maze, char direction, string& solution, int& row, int& col )

//******************************************************************************************************

/* 
Purpose:	Moves to the previous location in the maze, modifying the row and column #s and the string
			representing the path through the maze appropriately.
Pre:		maze has been instantiated. solution's length is >= 1. (row, col) is a location within the
			bounds of the maze.
Post:		The last character in solution has been removed. (row, col) now represents the previous
			location in the maze.
*/
void BackTrack( /* In/Out */ MazeClass& maze,		// The maze
				/* In/Out */ string&	solution,	// The string representing the path through the maze
				/* In/Out */ int&		row,		// The row # of a location in the maze
				/* In/Out */ int&		col )		// The column # of a location in the maze
{
	try
	{
		// Mark location (row, col) in the maze as UNVISITED
		SetMazeLoc( maze, row, col, UNVISITED );

		// Branch depending on the value of the last character in the string representing the path
		//  through the maze
		switch( solution[ solution.length() - 1 ] )
		{
			case 'N' : row++; break;

			case 'S' : row--; break;

			case 'E' : col--; break;

			case 'W' : col++; break;

		} // End switch

		// Erase the last character from the string representing the path through the maze
		solution.erase( solution.length() - 1 );

	} // End try
	catch( OutOfBoundsException e )	// Failed attempt to modify a MazeRec outside the bounds of the maze
	{
		cout << e.GetMessage() << endl;

	} // End catch

} // End BackTrack( MazeClass& maze, string& solution, int& row, int& col )