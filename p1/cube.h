/*
AUTHOR:
	Chris Pray

DATE:
	2/19/13

FILENAME:
	cube.h

PURPOSE:
	This file contains the specification for CubeClass.  It contains 1 default constructor, 2 public
	methods, and 1 private data member.  The functionality provided to the user by the public methods is
	described in the Summary of Methods section of this heading.  location.h is included to provide for
	the use of a LocationRec.  The private data member is cube, which is a 3D array of ColorEnums.  A
	ColorEnum can be NO_COLOR, RED, ORANGE, YELLOW, GREEN, or BLUE.

ASSUMPTIONS:
	Only LocationRecs with coordinates that are within the bounds of cube will be sent to CubeClass.

ERROR HANDLING:
	None

SUMMARY OF METHODS:	
	CubeClass()
		Default constructor.  Initializes a CubeClass object with NO_COLOR in each cell.

	SetColor(LocationRec loc, ColorEnum color)
		Sets the color at the location specified by the caller to the color specified by the caller.

	GetColor(LocationRec loc)
		Returns the color at the location specified by the user.
*/

#ifndef location_h
	#define location_h
	#include "location.h"	// For LocationRec
#endif

const char MAX_ROW = 5;	// Maximum # of rows
const char MAX_COL = 5;	// Maximum # of columns
const char MAX_DEP = 5;	// Maximum # of faces

enum ColorEnum { NO_COLOR, RED, ORANGE, YELLOW, GREEN, BLUE };	// Colors of a CubeClass element

class CubeClass
{
	public:

		/*
		PURPOSE:
			Default constructor.  Initializes a CubeClass object with NO_COLOR in each cell.

		PRE:
			CubeClass has been instantiated.

		POST:
			Each element in the CubeClass object has been initialized with NO_COLOR
		*/
		CubeClass();

		/*
		PURPOSE:
			Sets the color at the location specified by the caller to the color specified by the caller.

		PRE:
			CubeClass has been instantiated.

		POST:
			The color at the location specified by the user has been set to the color specified by the
			user.
		*/
		void SetColor(/* In */ LocationRec loc,		// Location to set color at
					  /* In */ ColorEnum   color);	// Color being set

		/*
		PURPOSE:
			Returns the color at the location specified by the user.

		PRE:
			CubeClass has been instantiated.

		POST:
			The color at the location specified by the user has been returned.
		*/
		ColorEnum GetColor(/* In */ LocationRec loc) const;	// Location of the color to return

		/*
		PURPOSE:
			Determines if the location specified by the user is in the bounds of the cube.

		PRE:
			CubeClass has been instantiated.

		POST:
			If the location is in bounds of the cube, true has been returned.  Otherwise, false has been
			returned.
		*/
		bool InBounds(/* In */ LocationRec loc) const;	// Location to test if in bounds of the cube

		/*
		PUPOSE:
			Determines if the first location specified by the user is adjacent in the cube to the second
			location specified by the user.

		PRE:
			CubeClass has been instantiated.

		POST:
			If the first and second locations specified by the user are in the cube and adjacent to each
			other, true has been returned.  Otherwise, false has been returned.
		*/
		bool IsAdjacent(/* In */ LocationRec loc1,			// First location to test if adjacent with
															//  second location
						/* In */ LocationRec loc2) const;	// Second location to test if adjacent with
															//  first location

	private:

		ColorEnum cube[MAX_ROW][MAX_COL][MAX_DEP];	// Stores ColorEnums
};