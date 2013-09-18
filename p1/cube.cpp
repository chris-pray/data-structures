/*
AUTHOR:
	Chris Pray

DATE:
	2/19/13

FILENAME:
	cube.cpp

PURPOSE:
	This file contains the implementation for all of the methods declared in cube.h
*/

#ifndef cube_h
	#define cube_h
	#include "cube.h"	// For class declarations
#endif

/******************************************************************************************************/

CubeClass::CubeClass()
{
	// Loop through each element of the array
	for(char i = 0; i < MAX_ROW; i++)
	{
		for(char j = 0; j < MAX_COL; j++)
		{
			for(char k = 0; k < MAX_DEP; k++)
			{
				// Set the element at position [i][j][k] to NO_COLOR
				cube[i][j][k] = NO_COLOR;

			} // End for

		} // End for

	} // End for

} // End CubeClass()

/******************************************************************************************************/

void CubeClass::SetColor(/* In */ LocationRec loc,	// Location to set color at
						 /* In */ ColorEnum color)	// Color being set
{
	cube[loc.row][loc.col][loc.dep] = color;

} // End CubeClass::SetColor(LocationRec loc, ColorEnum color)

/******************************************************************************************************/

ColorEnum CubeClass::GetColor(/* In */ LocationRec loc)	const	// Location of the color to return
{
	return cube[loc.row][loc.col][loc.dep];

} // End GetColor(LocationRec loc)

/******************************************************************************************************/

bool CubeClass::InBounds(/* In */ LocationRec loc) const	// Location to test if in bounds of the cube
{
	return loc.row >= 0 &&
		   loc.row < MAX_ROW &&
	       loc.col >= 0 &&
		   loc.col < MAX_COL &&
		   loc.dep >= 0 &&
		   loc.dep < MAX_DEP;

} // End InBounds(LocationRec loc)

/******************************************************************************************************/

bool CubeClass::IsAdjacent(/* In */ LocationRec loc1,		// First location to test if adjacent with
															//  second location
						   /* In */ LocationRec loc2) const	// Second location to test if adjacent with
															//  first location
{
	return InBounds(loc1) && InBounds(loc2) &&
		((loc1.row == loc2.row + 1 && loc1.col == loc2.col && loc1.dep == loc2.dep) ||
		 (loc1.row == loc2.row && loc1.col == loc2.col + 1 && loc1.dep == loc2.dep) ||
		 (loc1.row == loc2.row - 1 && loc1.col == loc2.col && loc1.dep == loc2.dep) ||
		 (loc1.row == loc2.row && loc1.col == loc2.col - 1 && loc1.dep == loc2.dep) ||
		 (loc1.row == loc2.row && loc1.col == loc2.col && loc1.dep == loc2.dep + 1) ||
		 (loc1.row == loc2.row && loc1.col == loc2.col && loc1.dep == loc2.dep - 1));

} // End IsAdjacent(LocationRec loc1, LocationRec loc2)