/*
AUTHOR:
	Chris Pray

DATE:
	2/19/13

FILENAME:
	client.cpp

PURPOSE:
	This program incorporates the use of CubeClass, ListClass, and ListClass5 objects.  A CubeClass
	object is instantiated and initialized with a random color (red, orange, yellow, green, or blue) in
	each cell.  ListClass and ListClass5 objects are used to aid in the calculation of statistics about
	the CubeClass object.  These calculations are finding the color and number of cells in the 3 largest
	contiguous blocks of colors in the CubeClass object, finding the # of times each color (red, orange,
	yellow, green, and blue) appear in the CubeClass object, and finding the locations of the cells that
	are in each ROYGB series in the CubeClass object.  If there are additional blocks of contiguous
	colors in the CubeClass object that are the same size as the 3rd largest block of contiguous colors,
	a count of these is calculated as well.  These statistics are printed to an output file,
	"colors.out".

INPUT:
	None

PROCESSING:
	Program finds contiguous blocks of colors in the CubeClass object and keeps track of the 3 largest 
	contiguous blocks of colors as well as the # of any additional contiguous blocks of colors that are
	the same size as the 3rd largest contiguous block of colors.  The number of cells occupied by each
	color is calculated.  Each unique ROYGB series is found and the locations of the cells in each of
	those series is stored.

OUTPUT:
	Statistics about the CubeClass object are printed to an output file, "colors.out".  A message is
	printed to the console notifying the client that all output has been printed to the file,
	colors.out.  A visual representation of the largest contiguous block of colors in the CubeClass
	object is first printed to the output file, layer by layer of the cube.  Statistics include the
	color and # of cells in the 3 largest contiguous blocks of colors in the CubeClass object, the # of
	any additional contiguous blocks of colors in the CubeClass object with the same size as the 3rd
	largest contiguous block of colors, the # of cells in the CubeClass object occupied by each color
	(red, orange, yellow, green, and blue), and the locations of the cells of each ROYGB series in the
	CubeClass object.

ASSUMPTIONS:
	The total # of red cells in the CubeClass object, the total # of orange cells in the CubeClass
	object, the total # of yellow cells in the CubeClass object,  the total # of green cells in the
	CubeClass object,  the total # of blue cells in the CubeClass object, the total # of additional
	contiguous blocks of colors equal in size to the 3rd largest contiguous block of colors in the
	CubeClass object, the total # of ROYGB series in the CubeClass object, and the maximum # of cells in
	a CubeClass object will never be > 127.  The maximum # of rows, columns, and depths of a CubeClass
	object will never be > 5.

ERROR HANDLING:	
	None

SUMMARY OF METHODS:	
	InitializeCube(CubeClass& cube)
		Initializes a CubeClass object with a random color in each cell.

	FindContiguousBlocks(CubeClass& cube, ListClass& list1, ListClass& list2, ListClass& list3, char&
	redCt, char& orangeCt, char& yellowCt, char& greenCt, char& blueCt, char& counter)
		Finds the 3 largest contiguous blocks of colors in the CubeClass object.  If there are any
		contiguous blocks of colors equal in size to the 3rd largest contiguous block of colors, a count
		of those contiguous blocks is calculated.  The numbers of red, orange, yellow, green, and blue
		cells in the CubeClass object are also calculated.

	SetSameColorList(ListClass& sameColorList, CubeClass& cube, ColorEnum color)
		Fills a list with locations of the cells in a CubeClass object which have the specified color.

	AddContiguousLoc(ListClass& sameColorList,	ListClass& contiguousColorList, CubeClass& cube,
    LocationRec loc)
		Adds a location to a list of locations of cells that are adjacent to one another and have the
		same color in a CubeClass object from a list of locations of cells that are the same color but
		not necessarily adjacent in that CubeClass object if the location is in the bounds of the
		CubeClass object and the location is in the list of same, but not necessarily contiguous,
		colors.

	SetContiguousColorList(ListClass& sameColorList, ListClass& contiguousColorList, CubeClass& cube)
		Fills a list with locations of cells that all have the same color and are adjacent in a
		CubeClass object.

	SortLists(ListClass& contiguousColorList, ListClass& list1, ListClass& list2, ListClass& list3,
	char& counter)
		Given 4 ListClass objects, representing lists of locations of contiguous colors in a CubeClass
		object, sorts the 3 largest by their length.  A counter is adjusted, if necessary, to accomodate
		for additional lists with the same length as the 3rd largest list.

	PrintBlockToFile(ofstream& outFile, CubeClass& cube, ListClass& list)
		Prints the cells of a CubeClass object whose locations are in a ListClass object to a file, one
		layer at a time, starting from the bottom layer, as if being viewed from above, all the way up
		to the top layer.

	PrintContiguousStatsToFile(ofstream& outFile, CubeClass& cube,	ListClass& list1, ListClass& list2,
	ListClass& list3, char& redCt, char& orangeCt, char& yellowCt, char& greenCt, char& blueCt, char&
	counter)
		Prints statistics about a CubeClass object to a file.  Statistics include the color and number
		of cells in the 3 largest contiguous blocks of colors in the CubeClass object, the #, if any, of
		additional blocks of contiguous colors in the CubeClass object with the same size as the 3rd
		largest contiguous block of colors, and the # of cells in the CubeClass object that contain each
		color (red, orange, yellow, green, and blue).

	FindROYGBSeries(CubeClass& cube, LC5Arr& roygbArr,	char& index)
		Finds the locations of the cells of each ROYGB series in a CubeClass object.  Each index, 0
		through numROYGB - 1, if the # of ROYGB series in the CubeClass object is > 0, in an LC5Arr
		array will contain the locations of the cells in one ROYGB series in the CubeClass object.

	PrintROYGBStatsToFile(ofstream& outFile, LC5Arr& roygbArr, const char& index)
		Prints the locations of the cells in each ROYGB series in a CubeClass object to a file if there
		are any ROYGB series.  Otherwise a message stating there are no ROYGB series is printed to the
		file.
*/

// Libraries
#include<iostream>	// For input/output
#include<fstream>	// For file input/output
#include<iomanip>	// For output formatting
#include<string>	// For string datatype

#ifndef list_h
#define list_h
#include "list.h"	// For use of ListClass objects
#endif

#ifndef list5_h
#define list5_h
#include "list5.h"	// For use of ListClass5 objects
#endif

#ifndef cube_h
#define cube_h
#include "cube.h"	// For use of CubeClass objects
#endif

using namespace std;

//Global Constants
const string FILE_NAME = "colors.out";	// Output file name
const char MAX_ROYGB = 25;				// Maximum # of ROYGB series
const short RANGE = 5;					// # of possible cube colors
const string BLANK = "------";			// Used when printing cells of a cube and printing the color of
										//  the cell is not appropriate

// Type Definitions
typedef ListClass5 LC5Arr[MAX_ROYGB];	// A ListClass5 array with MAX_ROYGB elements used for storing
										//  ROYGB series

// Prototypes	
void InitializeCube(CubeClass&);
void FindContiguousBlocks(CubeClass&, ListClass&, ListClass&, ListClass&, char&, char&, char&, char&,
						  char&, char&);
void SetSameColorList(ListClass&, CubeClass&, ColorEnum);
void AddContiguousLoc(ListClass&, ListClass&, CubeClass&, LocationRec);
void SetContiguousColorList(ListClass&, ListClass&, CubeClass&);
void SortLists(ListClass&, ListClass&, ListClass&, ListClass&, char&);
void PrintBlockToFile(ofstream&, CubeClass&, ListClass&);
void PrintContiguousStatsToFile(ofstream&, CubeClass&, ListClass&, ListClass&, ListClass&, char&, char&,
								char&, char&, char&, char&);
void FindROYGBSeries(CubeClass&, LC5Arr&, char&);
void PrintROYGBStatsToFile(ofstream&, LC5Arr&, const char&);

void main()
{
	// Variable Declarations

	// Class Variables
	CubeClass cube;		// Holds random colors
	ListClass list1;	// The locations of the cells part of the largest contiguous block of colors in cube
	ListClass list2;	// The locations of the cells part of the 2nd largest contiguous block of colors in cube
	ListClass list3;	// The locations of the cells part of the 3rd largest contiguous block of colors in cube
	LC5Arr roygbArr;	// Elements contain the locations of the cells part of a unique ROYGB series in cube

	// Char Variables
	char redCt = 0;		// Total # of red cells in cube
	char orangeCt = 0;	// Total # of orange cells in cube
	char yellowCt = 0;	// Total # of yellow cells in cube
	char greenCt = 0;	// Total # of green cells in cube
	char blueCt = 0;	// Total # of blue cells in cube
	char counter = 0;	// # of additional contiguous blocks of colors equal in size to the 3rd largest
						//  contiguous block of colors
	char numROYGBs = 0;	// Total # of ROYGB series in cube

	// Filestream Variables
	ofstream outFile;	// Output filestream variable

	// Initialize cube with random colors
	InitializeCube(cube);

	// Calculate the 3 largest contiguous blocks of colors and count the # of cells each color occupies
	FindContiguousBlocks(cube, list1, list2, list3, redCt, orangeCt, yellowCt, greenCt, blueCt,
		counter);

	// Open the output file
	outFile.open(FILE_NAME.c_str());

	// Print the largest contiguous block of colors, one layer at a time, to the file
	PrintBlockToFile(outFile, cube, list1);

	// Print stats to file
	PrintContiguousStatsToFile(outFile, cube, list1, list2, list3, redCt, orangeCt, yellowCt, greenCt,
		blueCt, counter);

	// Find the locations of cells in each ROYGB series
	FindROYGBSeries(cube, roygbArr, numROYGBs);

	// Print stats to file
	PrintROYGBStatsToFile(outFile, roygbArr, numROYGBs);

	// Close the output file
	outFile.close();

	cout << "Program complete. All output has been printed to colors.out." << endl;

} // End main()

/******************************************************************************************************/

/*
PURPOSE:
	Initializes a CubeClass object with a random color in each cell.

PRE:
	A CubeClass object has been instantiated.

POST:
	The CubeClass object has been initialized with a random color in each cell
*/
void InitializeCube
	(/* Out */ CubeClass& cube)	// An uninitialized cube
{
	LocationRec loc;	// A location in the cube

	// Seed the random number generator
	srand(123456789);

	// Loop through each cell in the cube
	for(char i = 0; i < MAX_ROW; i++)
	{
		for(char j = 0; j < MAX_COL; j++)
		{
			for(char k = 0; k < MAX_DEP; k++)
			{
				// Set location's coordinates to the values of the LCVs
				loc.row = i;
				loc.col = j;
				loc.dep = k;

				// Set the cell specified by loc to a random color
				cube.SetColor(loc, ColorEnum(rand() % RANGE + 1));

			} // End for

		} // End for

	} // End for

} // End InitializeCube(CubeClass& cube)

/******************************************************************************************************/

/*
PURPOSE:
	Finds the 3 largest contiguous blocks of colors in the CubeClass object.  If there are any
	contiguous blocks of colors equal in size to the 3rd largest contiguous block of colors, a count of
	those contiguous blocks is calculated.  The numbers of red, orange, yellow, green, and blue cells
	in the CubeClass object are also calculated.

PRE:
	A CubeClass and 3 ListClass objects have been instantiated.  The CubeClass object has also been
	initialized.  redCt, orangeCt, yellowCt, greenCt, blueCt, and counter have been assigned to 0.

POST:
	list1 contains the locations of the cells in the largest block of contiguous colors.  list2 contains
	the locations of the cells in the 2nd largest block of contiguous colors.  list3 contains the
	locations of the cells in the 3rd largest block of contiguous colors. counter contains the # of
	additional contiguous blocks of colors equal in size to the 3rd largest contiguous block of colors.
	redCt, orangeCt, yellowCt, greenCt, and blueCt contain the numbers of red, orange, yellow, green,
	and blue cells in the CubeClass object, respectively.
*/
void FindContiguousBlocks
	(/* In */  CubeClass& cube,		// An initialized CubeClass object
	 /* Out */ ListClass& list1,	// List of locations of the largest contiguous block of colors
	 /* Out */ ListClass& list2,	// List of locations of the 2nd largest contiguous block of colors
	 /* Out */ ListClass& list3,	// List of locations of the 3rd largest contiguous block of colors
	 /* Out */ char&	  redCt,	// # of red cells in the cube
	 /* Out */ char&	  orangeCt,	// # of orange cells in the cube
	 /* Out */ char&	  yellowCt,	// # of yellow cells in the cube
	 /* Out */ char&	  greenCt,	// # of green cells in the cube
	 /* Out */ char&	  blueCt,	// # of blue cells in the cube
	 /* Out */ char&	  counter)	// # of additional contiguous blocks of colors equal in size to the
									//  3rd largest contiguous block of colors
{
	// Loop through each color
	for(char i = (char)NO_COLOR; i <= (char)BLUE; i++)
	{
		ListClass sameColorList;	// List of locations that are the same color

		// Branch depending on color
		switch(i)
		{
			case (char)RED:
			{
				// Fill the same color list with locations of all red cells
				SetSameColorList(sameColorList, cube, (ColorEnum)i);

				// Set the number of red cells
				redCt = sameColorList.ReturnLength();

				// While the same color list isnt empty
				while(!sameColorList.IsEmpty())
				{
					// Create a new list for locations of a contiguous block of colors
					ListClass contiguousColorList;

					// Fill the contiguous color list with the locations of colors contiguous to the
					//  current position of same color list
					SetContiguousColorList(sameColorList, contiguousColorList, cube);

					// Sort the lists of contiguous colors by the # of cells in each block from largest
					//  to smallest
					SortLists(contiguousColorList, list1, list2, list3, counter);

					// Go to the first position of the same color list
					sameColorList.FirstPosition();

				} // End while

				break;

			} // End case (char)RED

			case (char)ORANGE:
			{
				// Fill the same color list with locations of all orange cells
				SetSameColorList(sameColorList, cube, (ColorEnum)i);

				// Set the number of orange cells
				orangeCt = sameColorList.ReturnLength();

				// While the same color list isnt empty
				while(!sameColorList.IsEmpty())
				{
					// Create a new list for locations of a contiguous block of colors
					ListClass contiguousColorList;

					// Fill the contiguous color list with the locations of colors contiguous to the
					//  current position of same color list
					SetContiguousColorList(sameColorList, contiguousColorList, cube);

					// Sort the lists of contiguous colors by the # of cells in each block from largest
					//  to smallest
					SortLists(contiguousColorList, list1, list2, list3, counter);

					// Go to the first position of the same color list
					sameColorList.FirstPosition();

				} // End while

				break;

			} // End case (char)ORANGE

			case (char)YELLOW:
			{
				// Fill the same color list with locations of all yellow cells
				SetSameColorList(sameColorList, cube, (ColorEnum)i);

				// Set the number of yellow cells
				yellowCt = sameColorList.ReturnLength();

				// While the same color list isnt empty
				while(!sameColorList.IsEmpty())
				{
					// Create a new list for locations of a contiguous block of colors
					ListClass contiguousColorList;

					// Fill the contiguous color list with the locations of colors contiguous to the
					//  current position of same color list
					SetContiguousColorList(sameColorList, contiguousColorList, cube);

					// Sort the lists of contiguous colors by the # of cells in each block from largest
					//  to smallest
					SortLists(contiguousColorList, list1, list2, list3, counter);

					// Go to the first position of the same color list
					sameColorList.FirstPosition();

				} // End while

				break;

			} // End case (char)YELLOW

			case (char)GREEN:
			{
				// Fill the same color list with locations of all green cells
				SetSameColorList(sameColorList, cube, (ColorEnum)i);

				// Set the number of green cells
				greenCt = sameColorList.ReturnLength();

				// While the same color list isnt empty
				while(!sameColorList.IsEmpty())
				{
					// Create a new list for locations of a contiguous block of colors
					ListClass contiguousColorList;

					// Fill the contiguous color list with the locations of colors contiguous to the
					//  current position of same color list
					SetContiguousColorList(sameColorList, contiguousColorList, cube);

					// Sort the lists of contiguous colors by the # of cells in each block from largest
					//  to smallest
					SortLists(contiguousColorList, list1, list2, list3, counter);

					// Go to the first position of the same color list
					sameColorList.FirstPosition();

				} // End while

				break;

			} // End case (char)YELLOW

			case (char)BLUE:
			{
				// Fill the same color list with locations of all blue cells
				SetSameColorList(sameColorList, cube, (ColorEnum)i);

				// Set the number of blue cells
				blueCt = sameColorList.ReturnLength();

				// While the same color list isnt empty
				while(!sameColorList.IsEmpty())
				{
					// Create a new list for locations of a contiguous block of colors
					ListClass contiguousColorList;

					// Fill the contiguous color list with the locations of colors contiguous to the
					//  current position of same color list
					SetContiguousColorList(sameColorList, contiguousColorList, cube);

					// Sort the lists of contiguous colors by the # of cells in each block from largest
					//  to smallest
					SortLists(contiguousColorList, list1, list2, list3, counter);

					// Go to the first position of the same color list
					sameColorList.FirstPosition();

				} // End while

				break;

			} // End case (char)BLUE
			default:
			{
				// Fill the same color list with locations of all NO_COLOR cells
				SetSameColorList(sameColorList, cube, (ColorEnum)i);

				// Set the number of blue cells
				blueCt = sameColorList.ReturnLength();

				// While the same color list isnt empty
				while(!sameColorList.IsEmpty())
				{
					// Create a new list for locations of a contiguous block of colors
					ListClass contiguousColorList;

					// Fill the contiguous color list with the locations of colors contiguous to the
					//  current position of same color list
					SetContiguousColorList(sameColorList, contiguousColorList, cube);

					// Sort the lists of contiguous colors by the # of cells in each block from largest
					//  to smallest
					SortLists(contiguousColorList, list1, list2, list3, counter);

					// Go to the first position of the same color list
					sameColorList.FirstPosition();

				} // End while

				break;

			} // End default

		} // End switch

	} // End for

	// Set the position of each list to its first position
	list1.FirstPosition();
	list2.FirstPosition();
	list3.FirstPosition();

} // End FindContiguousBlocks(CubeClass& cube, ListClass& list1, ListClass& list2, ListClass& list3,
  //  char& redCt, char& orangeCt, char& yellowCt, char& greenCt, char& blueCt, char& counter)

/******************************************************************************************************/

/*
PURPOSE:
	Fills a list with locations of the cells in a CubeClass object which have the specified color.

PRE:
	A ListClass object and a CubeClass object have been instantiated.  color has been assigned a valid
	color (RED, ORANGE, YELLOW, GREEN, BLUE, or NO_COLOR)

POST:
	sameColorList contains the locations of each cell in cube with the color specified by color.
*/
void SetSameColorList
	(/* Out */ ListClass& sameColorList,	// List of all locations of cells in cube with the color
											//  specified by color
	 /* In */  CubeClass& cube,				// A CubeClass object
	 /* In */  ColorEnum  color)			// A color
{
	LocationRec loc;	// A location in the cube

	// Loop through each cell in the cube
	for(char i = 0; i < MAX_ROW; i++)
	{
		for(char j = 0; j < MAX_COL; j++)
		{
			for(char k = 0; k < MAX_DEP; k++)
			{
				// Set location's coordinates to the values of the LCVs
				loc.row = i;
				loc.col = j;
				loc.dep = k;

				// If the location of the cube is the specified color
				if(cube.GetColor(loc) == color)
				{
					// Insert the location into the same color list
					sameColorList.Insert(loc);

				} // End if

			} // End for

		} // End for

	} // End for

} // End SetSameColorList(ListClass& sameColorList, CubeClass& cube, ColorEnum color)

/******************************************************************************************************/

/*
PURPOSE:
	Adds a location to a list of locations of cells that are adjacent to one another and have the same
	color in a CubeClass object from a list of locations of cells that are the same color but not
	necessarily adjacent in that CubeClass object if the location is in the bounds of the CubeClass
	object and the location is in the list of same, but not necessarily contiguous, colors.
PRE:
	2 ListClass objects and a CubeClass object have been instantiated.

POST:
	If the location is in the bounds of cube and is also in sameColorList, loc has been inserted into
	contiguousColorList and removed from sameColorList.
*/
void AddContiguousLoc
	(/* In/Out */ ListClass&  sameColorList,		// List of locations of cells in cube with a
													//  specific color 
	 /* In/Out */ ListClass&  contiguousColorList,	// List of locations of cells in cube which are the
													//  same color and adjacent to each other
	 /* In */     CubeClass&  cube,					// A CubeClass object
	 /* In */     LocationRec loc)					// A location in cube
{
	// If the location is in bounds and is in the list of same colors
	if(cube.InBounds(loc) &&
	   sameColorList.Find(loc))
	{
		// Delete the location from the list
		sameColorList.Delete();

		// Add the location to the list
		contiguousColorList.Insert(loc);

	} // End if

} // End AddContiguousLoc(ListClass& sameColorList,	ListClass& contiguousColorList, CubeClass& cube,
  //  LocationRec loc)

/******************************************************************************************************/

/*
PURPOSE:
	Fills a list with locations of cells that all have the same color and are adjacent in a CubeClass
	object.

PRE:
	2 ListClass objects and a CubeClass object have been instantiated.  sameColorList is not empty.
	contiguousColorList is not full.

POST:
	contiguousColorList contains the location at the current position of sameColorList and all locations
	of cells that are adjacent to that location and in sameColorList.  Each location in
	contiguousColorList is no longer in sameColorList.
*/
void SetContiguousColorList
	(/* In/Out */ ListClass& sameColorList,			// List of all locations of cells in cube with a
													//  specific color 
	 /* Out */    ListClass& contiguousColorList,	// List of locations of cells in cube which are the
													//  same color and adjacent to each other
	 /* In */     CubeClass& cube)					// A CubeClass object
{
	// Get the location from the current position of the same color list
	LocationRec loc = sameColorList.Retrieve();

	// Delete the location from the current position of the same color list
	sameColorList.Delete();

	// Add the location to the contiguous color list
	contiguousColorList.Insert(loc);

	// While the contiguous color list's current position != the length of that list
	while(!contiguousColorList.EndOfList())
	{
		// Adjust the location to the location above the original location of this iteration
		loc.row--;

		// Check if the location belongs in the list of contiguous colors and add it if it does
		AddContiguousLoc(sameColorList, contiguousColorList, cube, loc);

		// Adjust the location to the location to the left of the original location of this iteration
		loc.row++;
		loc.col--;

		// Check if the location belongs in the list of contiguous colors and add it if it does
		AddContiguousLoc(sameColorList, contiguousColorList, cube, loc);

		// Adjust the location to the location below the original location of this iteration
		loc.col++;
		loc.row++;

		// Check if the location belongs in the list of contiguous colors and add it if it does
		AddContiguousLoc(sameColorList, contiguousColorList, cube, loc);

		// Adjust the location to the location to the right of the original location of this iteration
		loc.row--;
		loc.col++;

		// Check if the location belongs in the list of contiguous colors and add it if it does
		AddContiguousLoc(sameColorList, contiguousColorList, cube, loc);

		// Adjust the location to the location in front of the original location of this iteration
		loc.col--;
		loc.dep--;

		// Check if the location belongs in the list of contiguous colors and add it if it does
		AddContiguousLoc(sameColorList, contiguousColorList, cube, loc);

		// Adjust the location to the location behind the original location of this iteration
		loc.dep++;
		loc.dep++;

		// Check if the location belongs in the list of contiguous colors and add it if it does
		AddContiguousLoc(sameColorList, contiguousColorList, cube, loc);

		// Go to the next position in the contiguous color list
		contiguousColorList.NextPosition();

		// If the contiguous color list is not passed the last location of that list
		if(!contiguousColorList.EndOfList())
		{
			// Get the location from the current position of the contiguous color list
			loc = contiguousColorList.Retrieve();

		} // End if

	} // End while

} // End SetContiguousColorList(ListClass& sameColorList, ListClass& contiguousColorList, CubeClass&
  //  cube)

/******************************************************************************************************/

/*
PURPOSE:
	Given 4 ListClass objects, representing lists of locations of contiguous colors in a CubeClass
	object, sorts the 3 largest by their length.  A counter is adjusted, if necessary, to accomodate for
	additional lists with the same length as the 3rd largest list.

PRE:
	4 ListClass objects have been instantiated. counter is defined.

POST:
	list1 contains the list of locations of cells in the largest block of contiguous colors in the
	CubeClass object.  list2 contains the list of locations of cells in the 2nd largest block of
	contiguous colors in the CubeClass object.  list3 contains the list of locations of cells in the 3rd
	largest block of contiguous colors in the CubeClass object.  counter contains the # of additional
	contiguous blocks of colors in the CubeClass object equal in size to the 3rd largest contiguous
	block of colors in that CubeClass object.
*/
void SortLists
	(/* In */     ListClass& contiguousColorList,	// List of locations of adjacent cells in a
													//  CubeClass object with the same color
	 /* In/Out */ ListClass& list1,					// List of locations that are part of the largest
													//  block of contiguous colors in a CubeClass object
	 /* In/Out */ ListClass& list2,					// List of locations that are part of the 2nd
													//  largest block of contiguous colors in a
													//  CubeClass object
	 /* In/Out */ ListClass& list3,					// List of locations that are part of the 3rd
													//  largest block of contiguous colors in a
													//  CubeClass object
	 /* In/Out */ char&	     counter)				// # of additional contiguous blocks of colors equal
													//  in size to the 3rd largest contiguous block of
													//  colors
{
	// If the temporary list of contiguous colors is larger than the currently largest list of
	//  contiguous colors
	if(contiguousColorList.ReturnLength() > list1.ReturnLength())
	{
		// If the 2nd largest and 3rd largest lists of contiguous colors are the same size
		if(list2.ReturnLength() == list3.ReturnLength())
		{
			counter++;

		} // End if
		// Else the 2nd largest and 3rd largest lists of contiguous colors are different sizes
		else
		{
			counter = 0;

		} // End else

		// Put the 3 largest lists of contiguous colors in order from largest to smallest
		list3 = list2;
		list2 = list1;
		list1 = contiguousColorList;

	} // End if
	// Else if the temporary list of contiguous colors is larger than the currently 2nd largest list of
	//  contiguous colors
	else if(contiguousColorList.ReturnLength() > list2.ReturnLength())
	{
		// If the 2nd largest and 3rd largest lists of contiguous colors are the same size
		if(list2.ReturnLength() == list3.ReturnLength())
		{
			counter++;

		} // End if
		// Else the 2nd largest and 3rd largest lists of contiguous colors are different sizes
		else
		{
			counter = 0;

		} // End else

		// Put the 2nd and 3rd largest lists of contiguous colors in order from largest to smallest
		list3 = list2;
		list2 = contiguousColorList;

	} // End else if
	// Else if the temporary list of contiguous colors is larger than the currently 3rd largest list of
	//  contiguous colors
	else if(contiguousColorList.ReturnLength() > list3.ReturnLength())
	{
		// Put the 3rd largest list in its correct order
		list3 = contiguousColorList;

	} // End else if
	// Else if the temporary list of contiguous colors is equal to the currently 3rd largest list of
	//  contiguous colors
	else if(contiguousColorList.ReturnLength() == list3.ReturnLength())
	{
		counter++;

	} // End else if

} // End SortLists(ListClass& contiguousColorList, ListClass& list1, ListClass& list2, ListClass& list3,
  //  char& counter)

/******************************************************************************************************/

/*
PURPOSE:
	Prints the cells of a CubeClass object whose locations are in a ListClass object to a file, one
	layer at a time, starting from the bottom layer, as if being viewed from above, all the way up to
	the top layer.

PRE:
	The output file has been opened.  A CubeClass and a ListClass object have been instantiated.

POST:
	The cells of cube whose locations are in list have been printed to a file, one layer at a time, 
	starting from the bottom layer, as if being viewed from above, all the way up to the top layer.
*/
void PrintBlockToFile
	(/* In/Out */ ofstream&  outFile,	// Output file stream variable
	 /* In */     CubeClass& cube,		// A CubeClass object
	 /* In */     ListClass& list)		// List of locations in cube
{
	LocationRec loc;	// A location in the cube
	ColorEnum color;	// A color of a cell

	outFile << "Largest Contiguous Block:" << endl << endl;

	// Loop through each cell of the cube
	for(char i = MAX_ROW - 1; i >= 0; i--)
	{
		outFile << "Row " << (short)i << " from above" << endl;

		for(char j = MAX_DEP - 1; j >= 0; j--)
		{
			for(char k = 0; k < MAX_COL; k++)
			{
				// Set location's coordinates to the values of the LCVs
				loc.row = i;
				loc.dep = j;
				loc.col = k;

				// If the location is in the list
				if(list.Find(loc))
				{
					// Get the color from the current cell of the cube
					color = cube.GetColor(list.Retrieve());

					// Branch depending on color
					switch(color)
					{
						case RED : outFile << left << setw(7) << "RED"; break;
						case ORANGE : outFile << left << setw(7) << "ORANGE"; break;
						case YELLOW : outFile << left << setw(7) << "YELLOW"; break;
						case GREEN : outFile << left << setw(7) << "GREEN"; break;
						case BLUE : outFile << left << setw(7) << "BLUE"; break;
						default: outFile << left << setw(7) << BLANK; break;

					} // End switch

				} // End if
				// Else the location is not in the list
				else
				{
					outFile << left << setw(7) << BLANK;

				} // End else

			} // End for

			outFile << endl;

		} // End for

		outFile << endl << endl;

	} // End for

} // End PrintBlockToFile(ofstream& outFile, CubeClass& cube, ListClass& list)

/******************************************************************************************************/

/*
PURPOSE:
	Prints statistics about a CubeClass object to a file.  Statistics include the color and number of
	cells in the 3 largest contiguous blocks of colors in the CubeClass object, the #, if any, of
	additional blocks of contiguous colors in the CubeClass object with the same size as the 3rd largest
	contiguous block of colors, and the # of cells in the CubeClass object that contain each color (red,
	orange, yellow, green, and blue).

PRE:
	Output file has been opened.  A CubeClass object and 3 ListClass objects have been instantiated.
	redCt, orangeCt, yellowCt, greenCt, blueCt, and counter have been defined.

POST:
	The statistics including the color and number of cells in the 3 largest contiguous blocks of colors
	in cube, the #, if any, of additional blocks of contiguous colors in cube with the same size as the
	3rd largest contiguous block of colors, and the # of cells in cube that contain each color (red,
	orange, yellow, green, and blue) have been printed to the output file.  Output has been formatted
	nicely.
*/
void PrintContiguousStatsToFile
	(/* In/Out */ ofstream&  outFile,	// An output file stream variable
	 /* In */     CubeClass& cube,		// A CubeClass object
	 /* In */	  ListClass& list1,		// List of locations of cells in the largest contiguous block of
										//  colors in cube
	 /* In */     ListClass& list2,		// List of locations of cells in the 2nd largest contiguous
										//  block of colors in cube
	 /* In */     ListClass& list3,		// List of locations of cells in the 3rd largest contiguous
										//  block of colors in cube
	 /* In */     char&	     redCt,		// # of red cells in cube
	 /* In */     char&	     orangeCt,	// # of orange cells in cube
	 /* In */     char&	     yellowCt,	// # of yellow cells in cube
	 /* In */     char&	     greenCt,	// # of green cells in cube
	 /* In */     char&	     blueCt,	// # of blue cells in cube
	 /* In */     char&	     counter)	// # of additional contiguous blocks of colors equal in size to
										//  the 3rd largest contiguous block of colors
{
	ColorEnum color;	// A color of a cell

	outFile << "The three largest contiguous blocks of colors are:" << endl
			<< left << setw(10) << "Color" << "Number of cells" << endl << endl;

	// Get the color of the largest contiguous block of colors
	color = cube.GetColor(list1.Retrieve());

	// Branch depending on color
	switch(color)
	{
		case RED : outFile << left << setw(10) << "RED"; break;
		case ORANGE : outFile << left << setw(10) << "ORANGE"; break;
		case YELLOW : outFile << left << setw(10) << "YELLOW"; break;
		case GREEN : outFile << left << setw(10) << "GREEN"; break;
		case BLUE : outFile << left << setw(10) << "BLUE"; break;
		default: outFile << left << setw(10) << "NO COLOR"; break;

	} // End switch

	// Print the number of cells in the largest contiguous block of colors
	outFile << (short)list1.ReturnLength() << endl;

	// Get the color of the 2nd largest contiguous block of colors
	color = cube.GetColor(list2.Retrieve());

	// Branch depending on color
	switch(color)
	{
		case RED : outFile << left << setw(10) << "RED"; break;
		case ORANGE : outFile << left << setw(10) << "ORANGE"; break;
		case YELLOW : outFile << left << setw(10) << "YELLOW"; break;
		case GREEN : outFile << left << setw(10) << "GREEN"; break;
		case BLUE : outFile << left << setw(10) << "BLUE"; break;
		default: outFile << left << setw(10) << "NO COLOR"; break;

	} // End switch

	// Print the number of cells in the 2nd largest contiguous block of colors
	outFile << (short)list2.ReturnLength() << endl;

	// Get the color of the 3rd largest contiguous block of colors
	color = cube.GetColor(list3.Retrieve());

	// Branch depending on color
	switch(color)
	{
		case RED : outFile << left << setw(10) << "RED"; break;
		case ORANGE : outFile << left << setw(10) << "ORANGE"; break;
		case YELLOW : outFile << left << setw(10) << "YELLOW"; break;
		case GREEN : outFile << left << setw(10) << "GREEN"; break;
		case BLUE : outFile << left << setw(10) << "BLUE"; break;
		default: outFile << left << setw(10) << "NO COLOR"; break;

	} // End switch

	// Print the number of cells in the 3rd largest contiguous block of colors
	outFile << (short)list3.ReturnLength() << endl << endl;

	// If there are more blocks of contiguous colors the same size as the 3rd largest block of
	//  contiguous colors
	if(counter > 0)
	{
		outFile << "There was/were also " << (short)counter << " more contiguous block(s) of colors "
				<< "with the same number " << endl << "of cells as the third largest contiguous block "
				<< "of colors." << endl << endl << endl;

	} // End if

	outFile << "The number of cells that contain each color:" << endl
			<< left << setw(10) << "Color" << "Number of cells" << endl << endl
			<< left << setw(10) << "RED" << (short)redCt << endl
			<< left << setw(10) << "ORANGE" << (short)orangeCt << endl
			<< left << setw(10) << "YELLOW" << (short)yellowCt << endl
			<< left << setw(10) << "GREEN" << (short)greenCt << endl
			<< left << setw(10) << "BLUE" << (short)blueCt << endl << endl << endl;

} // End PrintContiguousStatsToFile(ofstream& outFile, CubeClass& cube,	ListClass& list1, ListClass&
  //  list2, ListClass& list3, char& redCt, char& orangeCt, char& yellowCt, char& greenCt, char& blueCt,
  //  char& counter)

/******************************************************************************************************/

/*
PURPOSE:
	Finds the locations of the cells of each ROYGB series in a CubeClass object.  Each index, 0 through
	numROYGB - 1, if the # of ROYGB series in the CubeClass object is > 0, in an LC5Arr array will
	contain the locations of the cells in one ROYGB series in the CubeClass object.
	
PRE:
	A CubeClass object has been instantiated.  LC5Arr type has been defined.  numROYGBs has been
	assigned to 0.

POST:
	roygbArr contains the locations of the cells of each ROYGB series in cube in the first numROYGBs
	elements in the array.  Each element contains the locations of cells in one ROYGB series.
*/
void FindROYGBSeries
	(/* In */     CubeClass& cube,		// A CubeClass object
	 /* Out */    LC5Arr&	 roygbArr,	// An array of ROYGB series
	 /* In/Out */ char&		 numROYGBs)	// # of ROYGB series in cube
{
	ListClass   redList;	// List of locations of red cells in the cube
	ListClass   orangeList;	// List of locations of orange cells in the cube
	ListClass   yellowList;	// List of locations of yellow cells in the cube
	ListClass   greenList;	// List of locations of green cells in the cube
	ListClass   blueList;	// List of locations of blue cells in the cube
	ListClass5  roygbList;	// List of locations of a ROYGB series
	LocationRec loc;		// A location of a cell in the cube

	// Loop through each cell of the cube
	for(char i = 0; i < MAX_ROW; i++)
	{
		for(char j = 0; j < MAX_COL; j++)
		{
			for(char k = 0; k < MAX_DEP; k++)
			{
				// Set location's coordinates to the values of the LCVs
				loc.row = i;
				loc.col = j;
				loc.dep = k;

				// Branch depending on color and insert the location into the appropriate list
				switch(cube.GetColor(loc))
				{
					case RED: redList.Insert(loc); break;
					case ORANGE: orangeList.Insert(loc); break;
					case YELLOW: yellowList.Insert(loc); break;
					case GREEN: greenList.Insert(loc); break;
					case BLUE: blueList.Insert(loc); break;
					default: break;

				} // End switch

			} // End for

		} // End for

	} // End for

	// Set the current position of the red list to the first position of the list
	redList.FirstPosition();

	// While the list's current position != the length of the list
	while(!redList.EndOfList())
	{
		// Insert the current element in the red list into the ROYGB list
		roygbList.Insert(redList.Retrieve());

		// Set the current position of the orange list to the first position of the list
		orangeList.FirstPosition();

		// While the list's current position != the length of the list
		while(!orangeList.EndOfList())
		{
			// If the location in the current position of the red list is adjacent to the location in
			//  the current position of the orange list
			if(cube.IsAdjacent(redList.Retrieve(), orangeList.Retrieve()))
			{
				// Insert the current element in the orange list into the ROYGB list
				roygbList.Insert(orangeList.Retrieve());

				// Set the current position of the yellow list to the first position of the list
				yellowList.FirstPosition();

				// While the list's current position != the length of the list
				while(!yellowList.EndOfList())
				{
					// If the location in the current position of the orange list is adjacent to the
					//  location in the current position of the yellow list
					if(cube.IsAdjacent(orangeList.Retrieve(), yellowList.Retrieve()))
					{
						// Insert the current element in the yellow list into the ROYGB list
						roygbList.Insert(yellowList.Retrieve());

						// Set the current position of the green list to the first position of the list
						greenList.FirstPosition();

						// While the list's current position != the length of the list
						while(!greenList.EndOfList())
						{
							// If the location in the current position of the yellow list is adjacent to
							//  the location in the current position of the green list
							if(cube.IsAdjacent(yellowList.Retrieve(), greenList.Retrieve()))
							{
								// Insert the current element in the green list into the ROYGB list
								roygbList.Insert(greenList.Retrieve());

								// Set the current position of the blue list to the first position of
								//  the list
								blueList.FirstPosition();

								// While the list's current position != the length of the list
								while(!blueList.EndOfList())
								{
									// If the location in the current position of the green list is
									//  adjacent to the location in the current position of the blue
									//  list
									if(cube.IsAdjacent(greenList.Retrieve(), blueList.Retrieve()))
									{
										// Insert the current element in the blue list into the ROYGB
										//  list
										roygbList.Insert(blueList.Retrieve());

										// Put the ROYGB series into the current index of the array of
										//  ROYGB series
										roygbArr[numROYGBs] = roygbList;

										numROYGBs++;

										// Find the position of the location of the blue cell in the
										//  ROYGB list
										roygbList.Find(blueList.Retrieve());

										// Delete the current position from the list
										roygbList.Delete();

									} // End if

									// Set the current position to the next position in the blue list
									blueList.NextPosition();

								} // End while

								// Find the position of the location of the green cell in the ROYGB list
								roygbList.Find(greenList.Retrieve());

								// Delete the current position from the list
								roygbList.Delete();

							} // End if

							// Set the current position to the next position in the green list
							greenList.NextPosition();

						} // End while

						// Find the position of the location of the yellow cell in the ROYGB list
						roygbList.Find(yellowList.Retrieve());

						// Delete the current position from the list
						roygbList.Delete();

					} // End if

					// Set the current position to the next position in the yellow list
					yellowList.NextPosition();

				} // End while

				// Find the position of the location of the orange cell in the ROYGB list
				roygbList.Find(orangeList.Retrieve());

				// Delete the current position from the list
				roygbList.Delete();

			} // End if

			// Set the current position to the next position in the orange list
			orangeList.NextPosition();

		} // End while

		// Find the position of the location of the red cell in the ROYGB list
		roygbList.Find(redList.Retrieve());

		// Delete the current position from the list
		roygbList.Delete();

		// Set the current position to the next position in the red list
		redList.NextPosition();

	} // End while

} // End FindROYGBSeries(CubeClass& cube, LC5Arr& roygbArr,	char& index)

/******************************************************************************************************/

/*
PURPOSE:
	Prints the locations of the cells in each ROYGB series in a CubeClass object to a file if there are
	any ROYGB series.  Otherwise a message stating there are no ROYGB series is printed to the file.

PRE:
	Output file has been opened.  Type definition for LC5Arr has been defined.

POST:
	The locations of the cells in each ROYGB series in a CubeClass object have been printed to the
	output file if there were any ROYGB series.  Otherwise a message stating that there were no ROYGB
	series in the CubeClass object has been printed to the output file.  Output has been formatted
	nicely.
*/
void PrintROYGBStatsToFile
	(/* In/Out */       ofstream& outFile,		// An output file stream variable
	 /* In */           LC5Arr&   roygbArr,		// An array of ROYGB series
	 /* In */     const char&	  numROYGBs)	// # of ROYGB series in a CubeClass object
{
	// If there are ROYGB series in the cube
	if(numROYGBs > 0)
	{
		// Format and print column headings
		outFile << "ROYGB Locations (row, column, depth):" << endl
			<< left << setw(10) << "RED" << left << setw(10) << "ORANGE" << left << setw(10) << "YELLOW"
			<< left << setw(10) << "GREEN" << left << setw(10) << "BLUE" << endl << endl;

		// Loop through each index of the array of ROYGB series
		for(char i = 0; i < numROYGBs; i++)
		{
			// Set the current position of the ROYGB series at the current index of the array of ROYGB
			//  series to the first position of that ROYGB series
			roygbArr[i].FirstPosition();

			// While the current position of the ROYGB series at the current index of the array of
			//  ROYGB series != the length of that ROYGB series
			while(!roygbArr[i].EndOfList())
			{
				// Print the coordinates of the location in the current position of the ROYGB series at the
				//  current index of the array of ROYGB series to the output file
				outFile << (short)roygbArr[i].Retrieve().row << ", " << (short)roygbArr[i].Retrieve().col
					<< ", " << (short)roygbArr[i].Retrieve().dep << "   ";

				// Set the current position of the ROYGB series at the current index of the array of ROYGB
				//  series to the next position of that ROYGB series
				roygbArr[i].NextPosition();

			} // End while

			outFile << endl;

		} // End for

	} // End if
	// Else there are no ROYGB series in the cube
	else
	{
		outFile << "There were no ROYGB series in the cube." << endl;

	} // End else

} // End PrintROYGBStatsToFile(ofstream& outFile, LC5Arr& roygbArr, const char& index)