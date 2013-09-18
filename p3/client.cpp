/*
AUTHOR:
	Chris Pray

DATE:
	4/4/13

FILENAME:
	client.cpp

PURPOSE:
	This file reads in a file name from a user, validates the filename, and, if it is valid and found,
	reads in data from the file specifying the dimensions of a maze as well as the locations of walls
	in the maze, if there are any. A valid file name contains only letters, a period, and three letters
	after the period. All valid paths through the maze are found and printed to the file whose name is
	specified by constant, OUT_FILE_NAME. Valid paths are ones that go from the entrance, at location
	(0, 0), to the exit, at location (mazeWidth - 1, mazeLength - 1), in a direct path without crossing
	the same location more than once. If either the entrance or the exit are blocked by a wall, the maze
	will not contain any valid paths.

INPUT:
	This file reads a file name from the user, validates the file name, and attempts to open the file.
	If the file was successfully opened, data is read from the file. This data specifies the dimensions
	of the maze which is created and the locations of walls in the maze, if there are any.

PROCESSING:
	First, the input file name read from the user is validated. If it is in the correct format, the
	program attempts to open the file. If successful, the dimensions of the maze are read from the file.
	A MazeClass object gets instantiated with these dimensions. Next, the locations of walls in the
	maze, if there are any, are read from the file, building the walls of the maze as they are read,
	until the end of the file is reached. Then the program searches through the maze to find all valid
	paths through the maze. For each move to a new location within the maze, the direction moved gets
	pushed onto a stack in order to keep track of the path through the maze. If a backtrack is
	necessary, an appropriate number of pops from the stack are called. Each time a valid path through
	the maze is encountered, a copy of the stack is made, and each item on the copied stack is pushed
	onto a third stack, so that the items in the third stack are the items of the original stack but in
	reverse order. Finally, the items in this third stack are popped and written to the output file, so
	that when the program has finished executing, the output file contains a sequential order of all
	valid paths through the maze. If either the entrance to the maze or the exit from the maze are
	blocked by a wall, no searches through the maze are performed since there are no valid paths in this
	case. The program prompts the user along the way to notify the progress of the execution, including
	when execution is finished and all valid paths through the maze have been written to the output
	file.

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
	(1) The input file name is validated. A valid file name must contain only letters and a period and
		three letters after the period. The user is given as many chances as necessary to enter a valid
		file name, or they can press 'Q' or 'q' to quit the program. These chances to re-enter the file
		name are given in the case a valid file name is not found as well.
	(2) An error message is printed to the console any time a push is attempted on a full stack.

EXCEPTION HANDLING:
	(1) nmspcStackExceptions::OutOfMemoryException
			Thrown on a failure to dynamically allocate memory for a StackClass operation
	(2) RetrieveOnEmptyException
			Thrown when attempting to retrieve from an empty stack.
	(3) nmspcMazeExceptions::OutOfMemoryException
			Thrown on a failure to dynamically allocate memory when instantiating a MazeClass object.
	(4) RetrieveFromOutOfBoundsException
			Thrown when attempting to retrieve a MazePositionType struct from a location that's outside
			the bounds of a MazeClass object.

*/

// Header Files / Libraries
#include "maze.h"	// For use of MazeClass objects
#include "stack.H"	// For use of StackClass objects
#include<iostream>	// For standard input/output
#include<string>	// For string datatype
#include<fstream>	// For file input/output
#include<cstdlib>	// For exit
using namespace std;

// Prototypes (SUMMARY OF METHODS)
bool InBounds(int, int, int, int);					// Determines if a specified location is within the
													//  bounds of the maze.
void PrintSolution(StackClass&, ofstream&);			// Prints the directions through the maze from start
													//  to finish to a file.
void BackTrack(StackClass, int&, int&);				// Determines the previous move in the maze and
													//  backtracks by setting row or col appropriately.
void SetStatus(MazeClass&, int, int, PositionEnum);	// Sets the status member of the MazePositionType
													//  struct at a specified location in the maze.
void SetTriedEast(MazeClass&, int, int, bool);		// Sets the triedEast member of the MazePositionType
													//  struct at a specified location in the maze.
void SetTriedSouth(MazeClass&, int, int, bool);		// Sets the triedSouth member of the
													//  MazePositionType struct at a specified location
													//  in the maze.
void SetTriedWest(MazeClass&, int, int, bool);		// Sets the triedWest member of the MazePositionType
													//  struct at a specified location in the maze.
void SetTriedNorth(MazeClass&, int, int, bool);		// Sets the triedNorth member of the
													//  MazePositionType struct at a specified location
													//  in the maze.

// Constants
const char OUT_FILE_NAME[] = "solution.out";	// Output file name
const int MIN_FILENAME_LENGTH = 5;				// Min length of input file name
const int FIRST_SOLUTION = 1;					// First solution #
const int ROW_START = 0;						// 1st row in the maze
const int COL_START = 0;						// 1st column int he maze

void main()
{
	// Variables
	StackClass stack;						// Keeps track of path through maze
	StackClass stackCopy;					// Gets a copy of variable stack
	StackClass printStack;					// Reverse order of directions in variable stackCopy
	ItemType item;							// An item to be pushed onto a StackClass object
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
		if( (inFileName.compare("Q") == 0) || (inFileName.compare("q") == 0) )
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
				if( (inFileName[index] >= 'a' && inFileName[index] <= 'z') ||
					(inFileName[index] >= 'A' && inFileName[index] <= 'Z') )
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
				if( inFileName[index] == '.' )
				{
					// Increment index by one
					index++;

					// While the input file name is valid and the index of the current character being
					//  tested is < the length of inFileName
					while( validFileName && index < inFileName.length() )
					{
						// If the character at the current index of inFileName is a letter
						if( (inFileName[index] >= 'a' && inFileName[index] <= 'z') ||
							(inFileName[index] >= 'A' && inFileName[index] <= 'Z') )
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
			// Set location (row, col) to a wall
			SetStatus(maze, row, col, WALL);

			// Get the coordinates of the next wall
			din >> row >> col;

		} // End while

		// Close the input file
		din.close();

		cout << "Maze built." << endl;

		//**********************************************************************************************
		// Discover and Print All Valid Paths Through the Maze

		// Open the output file and associate it with dout
		dout.open(OUT_FILE_NAME);

		// Go to the entrance of the maze
		row = ROW_START;
		col = COL_START;

		// If the entrance to the maze is not a wall
		if( maze.GetPosition(row, col).status != WALL )
		{
			// If the exit from the maze is not a wall
			if( maze.GetPosition(numRows - 1, numCols - 1).status != WALL )
			{
				item.direction = SOUTH;

				// If the stack is not full
				if( !stack.IsFull() )
				{
					// Enter the maze
					stack.Push(item);

				} // End if
				// Else the stack is full
				else
				{
					cout << "Error: Stack is full." << endl;

				} // End else

				// Mark the entrance of the maze as visited
				SetStatus(maze, row, col, VISITED);

				// While the stack of directions is not empty
				while( !stack.IsEmpty() )
				{
					// If at the exit from the maze
					if(row == numRows - 1 && col == numCols -1)
					{
						item.direction = SOUTH;

						// If the stack is not full
						if( !stack.IsFull() )
						{
							// Exit the maze
							stack.Push(item);

						} // End if
						// Else the stack is full
						else
						{
							cout << "Error: Stack is full." << endl;

						} // End else

						// Copy the stack of directions
						stackCopy = stack;

						// While the copied stack of directions is not empty
						while( !stackCopy.IsEmpty() )
						{
							// If the stack is not full
							if( !printStack.IsFull() )
							{
								try
								{
									// Push the top item from the copied stack of directions onto the
									//  stack used to print the directions
									printStack.Push( stackCopy.Retrieve() );

								} // End try
								catch(RetrieveOnEmptyException e)
								{
									cout << e.GetMessage() << endl;

								} // End catch

							} // End if
							// Else the stack is full
							else
							{
								cout << "Error: Stack is full." << endl;

							} // End else

							// Pop the top item from the copied stack of directions
							stackCopy.Pop();

						} // End while

						// Print the solution # to the output file
						dout << "Solution #" << solutionNumber << ":" << endl;

						// Print the path through the maze
						PrintSolution(printStack, dout);

						dout << endl << endl;

						// Pop the top item of the stack of directions
						stack.Pop();

						// Mark the exit from the maze as unvisited
						SetStatus(maze, row, col, UNVISITED);

						// Backtrack to the previous location in the maze
						BackTrack(stack, row, col);

						// Pop the top item of the stack of directions
						stack.Pop();

						// Increment the solution # by one
						solutionNumber++;

					} // End if
					// If the location to the east of the current location in the maze is in the maze,
					//  marked as unvisited, and has not yet been tried
					else if( InBounds(row, col + 1, numRows, numCols) &&
						maze.GetPosition(row, col + 1).status == UNVISITED &&
						maze.GetPosition(row, col).triedEast == false )
					{
						// Mark the current location in the maze as tried going east before moving east
						SetTriedEast(maze, row, col, true);

						item.direction = EAST;

						// If the stack is not full
						if( !stack.IsFull() )
						{
							// Move east
							stack.Push(item);

						} // End if
						//
						else
						{
							cout << "Error: Stack is full." << endl;

						} // End else

						// Increment col by one
						col++;

						// Set the new current location in the maze as visited
						SetStatus(maze, row, col, VISITED);

					} // End if
					// Else if the location to the south of the current location in the maze is in the
					//  maze, marked as unvisited, and has not yet been tried
					else if( InBounds(row + 1, col, numRows, numCols) &&
						maze.GetPosition(row + 1, col).status == UNVISITED &&
						maze.GetPosition(row, col).triedSouth == false )
					{
						// Mark the current location in the maze as tried going south before moving
						//  south
						SetTriedSouth(maze, row, col, true);

						item.direction = SOUTH;

						// If the stack is not full
						if( !stack.IsFull() )
						{
							// Move south
							stack.Push(item);

						} // End if
						// Else the stack is full
						else
						{
							cout << "Error: Stack is full." << endl;

						} // End else

						// Increment row by one
						row++;

						// Set the new current location in the maze as visited
						SetStatus(maze, row, col, VISITED);

					} // End else if
					// Else if the location to the west of the current location in the maze is in the
					//  maze, marked as unvisited, and has not yet been tried
					else if( InBounds(row, col - 1, numRows, numCols) &&
						maze.GetPosition(row, col - 1).status == UNVISITED &&
						maze.GetPosition(row, col).triedWest == false )
					{
						// Mark the current location in the maze as tried going west before moving west
						SetTriedWest(maze, row, col, true);

						item.direction = WEST;

						// If the stack is not full
						if( !stack.IsFull() )
						{
							// Move west
							stack.Push(item);

						} // End if
						// Else the stack is full
						else
						{
							cout << "Error: Stack is full." << endl;

						} // End else

						// Decrement col by one
						col--;

						// Set the new current location in the maze as visited
						SetStatus(maze, row, col, VISITED);

					} // End else if
					// Else if the location to the north of the current location in the maze is in the
					//  maze, marked as unvisited, and has not yet been tried
					else if( InBounds(row - 1, col, numRows, numCols) &&
						maze.GetPosition(row - 1, col).status == UNVISITED &&
						maze.GetPosition(row, col).triedNorth == false )
					{
						// Mark the current location in the maze as tried going north before moving
						//  north
						SetTriedNorth(maze, row, col, true);

						item.direction = NORTH;

						// If the stack is not full
						if( !stack.IsFull() )
						{
							// Move north
							stack.Push(item);

						} // End if
						// Else the stack is full
						else
						{
							cout << "Error: Stack is full." << endl;

						} // End else

						// Decrement row by one
						row--;

						// Set the new current location in the maze as visited
						SetStatus(maze, row, col, VISITED);

					} // End else if
					// Else nowhere to go
					else
					{
						// Set the current location in the maze as unvisited and not tried going in any
						//  direction
						SetStatus(maze, row, col, UNVISITED);
						SetTriedEast(maze, row, col, false);
						SetTriedSouth(maze, row, col, false);
						SetTriedWest(maze, row, col, false);
						SetTriedNorth(maze, row, col, false);

						// Backtrack to the previous location in the maze
						BackTrack(stack, row, col);

						// Pop the top item of the stack of directions
						stack.Pop();

					} // End else

				} // End while

			} // End if
			// Else the exit to the maze is a wall
			else
			{
				dout << "The exit to the maze is blocked." << endl;

			} // End else

		} // End if
		// Else the entrance to the maze is a wall
		else
		{
			dout << "The entrance to the maze is blocked." << endl;

		} // End else

		// Close the output file
		dout.close();

		cout << "All output has been sent to file: " << OUT_FILE_NAME << endl;

	} // End try
	catch(RetrieveFromOutOfBoundsException e)
	{
		dout << e.GetMessage() << endl;

	} // End catch
	catch(nmspcMazeExceptions::OutOfMemoryException e)
	{
		cout << e.GetMessage() << endl;

		// Terminate program
		exit(EXIT_FAILURE);

	} // End catch
	catch(nmspcStackExceptions::OutOfMemoryException e)
	{
		cout << e.GetMessage() << endl;

		// Terminate program
		exit(EXIT_FAILURE);

	} // End catch

} // End main()

//******************************************************************************************************

/*
Purpose:	Determines if the location (row, col) is within the bounds of the maze.
Pre:		numRows and numCols contain the # of rows and the # of columns in the maze, respectively.
Post:		True has been returned if location (row, col) is within the bounds of the maze. Otherwise, 
			false has been returned.
*/
bool InBounds(/* In */ int row,		// Row # of the location to check
			  /* In */ int col,		// Column # of the location to check
			  /* In */ int numRows,	// # of rows in the maze
			  /* In */ int numCols)	// # of coluimns in the maze
{
	// Return true if the location (row, col) is within the maze, otherwise return false
	return row >= 0 && row < numRows && col >= 0 && col < numCols;

} // End InBounds(int row, int col, int numRows, int numCols)

//******************************************************************************************************

/*
Purpose:	Prints the directions through the maze from start to finish to a file.
Pre:		solution contains valid directions through the maze. dout has been associated with an output
			file.
Post:		The directions through the maze have been printed to the file associated with dout.
*/
void PrintSolution(/* In/Out */ StackClass& solution,	// Contains directions through the maze
				   /* In/Out */ ofstream&   dout)		// Output file stream variable
{
	// While the stack is not empty
	while( !solution.IsEmpty() )
	{
		try
		{
			// Branch depending on the direction on the top of the stack
			switch( solution.Retrieve().direction )
			{
				case EAST: dout << "EAST "; break;

				case SOUTH: dout << "SOUTH "; break;

				case WEST: dout << "WEST "; break;

				case NORTH: dout << "NORTH "; break;

			} // End switch

		} // End try
		catch(RetrieveOnEmptyException e)
		{
			cout << e.GetMessage() << endl;

		} // End catch

		// Pop the top element from the stack
		solution.Pop();

	} // End while

} // End PrintSolution(StackClass& solution, ofstream& dout)

//******************************************************************************************************

/*
Purpose:	Determines the previous move in the maze and backtracks by setting row or col appropriately.
Pre:		stack is not empty. (row, col) is the current location in the maze.
Post:		(row, col) is the previous location in the maze.
*/
void BackTrack(/* In */		StackClass stack,	// Contains the directions through the maze thus far
			   /* In/Out */ int&	   row,		// Row # in the maze
			   /* In/Out */ int&	   col)		// Column # in the maze
{
	try
	{
		// Branch depending on the direction on the top of the stack
		switch( stack.Retrieve().direction )
		{
			case EAST: col--; break;

			case SOUTH: row--; break;

			case WEST: col++; break;

			case NORTH: row++; break;

		} // End switch

	} // End try
	catch(RetrieveOnEmptyException e)
	{
		cout << e.GetMessage() << endl;

	} // End catch

} // End BackTrack(StackClass stack, int& row, int& col)

//******************************************************************************************************

/*
Purpose:	Sets the status member of the MazePositionType struct at location (row, col) in the maze.
Pre:		maze exists. (row, col) is a valid location within the maze.
Post:		The status member of the MazePositionType struct at location (row, col) in the maze has been
			set to newStatus.
*/
void SetStatus(/* In/Out */ MazeClass&   maze,		// The maze
			   /* In */		int			 row,		// Row # in the maze
			   /* In */		int			 col,		// Column # in the maze
			   /* In */		PositionEnum newStatus)	// Value to set the status member of the
													//  MazePositionType struct at location (row, col)
													//  in the maze to
{
	MazePositionType position;	// A MazePositionType struct

	try
	{
		// Assign position to the MazePositionType struct at location (row, col) in the maze
		position = maze.GetPosition(row, col);

		// Assign the status member of position
		position.status = newStatus;

		// Assign the MazePositionType struct at location (row, col) in the maze to position
		maze.SetPosition(row, col, position);

	} // End try
	catch(RetrieveFromOutOfBoundsException e)
	{
		cout << e.GetMessage() << endl;

	} // End catch

} // End SetStatus(MazeClass& maze, int row, int col, PositionEnum newStatus)

//******************************************************************************************************

/*
Purpose:	Sets the triedEast member of the MazePositionType struct at location (row, col) in the maze.
Pre:		maze exists. (row, col) is a valid location within the maze.
Post:		The triedEast member of the MazePositionType struct at location (row, col) in the maze has
			been set to tried.
*/
void SetTriedEast(/* In/Out */ MazeClass& maze,		// The maze
				  /* In */	   int		  row,		// Row # in the maze
				  /* In */     int		  col,		// Column # in the maze
				  /* In */     bool		  tried)	// Value to set the triedEast member of the
													//  MazePositionType struct at location (row, col)
													//  in the maze to
{
	MazePositionType position;	// An element in the maze

	try
	{
		// Set position to the element at location (row, col) in the maze
		position = maze.GetPosition(row, col);

		// Set position.triedEast
		position.triedEast = tried;

		// Set the element at location (row, col) to position
		maze.SetPosition(row, col, position);

	} // End try
	catch(RetrieveFromOutOfBoundsException e)
	{
		cout << e.GetMessage() << endl;

	} // End catch

} // End SetTriedEast(MazeClass& maze, int row, int col, bool tried)

//******************************************************************************************************

/*
Purpose:	Sets the triedSouth member of the MazePositionType struct at location (row, col) in the
			maze.
Pre:		maze exists. (row, col) is a valid location within the maze.
Post:		The triedSouth member of the MazePositionType struct at location (row, col) in the maze has
			been set to tried.
*/
void SetTriedSouth(/* In/Out */ MazeClass& maze,	// The maze
				   /* In */	    int		   row,		// Row # in the maze
				   /* In */     int		   col,		// Column # in the maze
				   /* In */     bool	   tried)	// Value to set the triedSouth member of the
													//  MazePositionType struct at location (row, col)
													//  in the maze to
{
	MazePositionType position;	// An element in the maze

	try
	{
		// Set position to the element at location (row, col) in the maze
		position = maze.GetPosition(row, col);

		// Set position.triedSouth
		position.triedSouth = tried;

		// Set the element at location (row, col) to position
		maze.SetPosition(row, col, position);

	} // End try
	catch(RetrieveFromOutOfBoundsException e)
	{
		cout << e.GetMessage() << endl;

	} // End catch

} // End SetTriedSouth(MazeClass& maze, int row, int col, bool tried)

//******************************************************************************************************

/*
Purpose:	Sets the triedWest member of the MazePositionType struct at location (row, col) in the maze.
Pre:		maze exists. (row, col) is a valid location within the maze.
Post:		The triedWest member of the MazePositionType struct at location (row, col) in the maze has
			been set to tried.
*/
void SetTriedWest(/* In/Out */ MazeClass& maze,		// The maze
				  /* In */	   int		  row,		// Row # in the maze
				  /* In */     int		  col,		// Column # in the maze
				  /* In */     bool		  tried)	// Value to set the triedWest member of the
													//  MazePositionType struct at location (row, col)
													//  in the maze to
{
	MazePositionType position;	// An element in the maze

	try
	{
		// Set position to the element at location (row, col) in the maze
		position = maze.GetPosition(row, col);

		// Set position.triedWest
		position.triedWest = tried;

		// Set the element at location (row, col) to position
		maze.SetPosition(row, col, position);

	} // End try
	catch(RetrieveFromOutOfBoundsException e)
	{
		cout << e.GetMessage() << endl;

	} // End catch

} // End SetTriedWest(MazeClass& maze, int row, int col, bool tried)

//******************************************************************************************************

/*
Purpose:	Sets the triedNorth member of the MazePositionType struct at location (row, col) in the
			maze.
Pre:		maze exists. (row, col) is a valid location within the maze.
Post:		The triedNorth member of the MazePositionType struct at location (row, col) in the maze has
			been set to tried.
*/
void SetTriedNorth(/* In/Out */ MazeClass& maze,	// The maze
				   /* In */	    int		   row,		// Row # in the maze
				   /* In */     int		   col,		// Column # in the maze
				   /* In */     bool	   tried)	// Value to set the triedNorth member of the
													//  MazePositionType struct at location (row, col)
													//  in the maze to
{
	MazePositionType position;	// An element in the maze

	try
	{
		// Set position to the element at location (row, col) in the maze
		position = maze.GetPosition(row, col);

		// Set position.triedNorth
		position.triedNorth = tried;

		// Set the element at location (row, col) to position
		maze.SetPosition(row, col, position);

	} // End try
	catch(RetrieveFromOutOfBoundsException e)
	{
		cout << e.GetMessage() << endl;

	} // End catch

} // End SetTriedNorth(MazeClass& maze, int row, int col, bool tried)