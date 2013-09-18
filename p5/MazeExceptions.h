/*
AUTHOR:
	Chris Pray

DATE:
	4/25/13

FILENAME:
	MazeExceptions.h

PURPOSE:
	This file contains custom exception classes, OutOfBoundsException and OutOfMemoryException to be
	used with MazeClass objects. OutOfBoundsException should be thrown whenever an attempt to access or
	modify a MazeRec from a location that's outside the bounds of the maze is made. OutOfMemoryException
	should be thrown whenever an attempt to dynamically allocate memory for the instantiation of a
	MazeClass object fails.

SUMMARY OF METHODS:
	
	OutOfBoundsException::OutOfBoundsException(const string msg)
		Non-default constructor for an OutOfBoundsException object. msg is a message passed when the
		exception is thrown.
	OutOfBoundsException::GetMessage()
		Returns PDM message which is set when the exception is thrown.

	OutOfMemoryException::OutOfMemoryException(const string msg)
		Non-default constructor for an OutOfMemoryException object. msg is a message passed when the
		exception is thrown.
	OutOfMemoryException::GetMessage()
		Returns PDM message which is set when the exception is thrown.
*/

#ifndef MazeExceptions_h
#define MazeExceptions_h

#include <string>		// For string data type
using namespace std;

namespace MazeExceptions
{
	class OutOfBoundsException
	{
		private:

			string message;	// A message describing the exception


		public:

			/*
			Purpose:			Instantiates an OutOfBoundsException object with a custom message. PDM
								message has been intitiallized to msg.
			Pre:				None.
			Post:				An OutOfBoundsException object has been instantiated. PDM message has
								been intitiallized to msg.
			Classification:		Non-default Constructor
			Order of Magnitude:	O(1)
			*/
			OutOfBoundsException( /* In */ const string& msg )	// The message to initiallize PDM
																//  message with
			{
				// Initiallize PDM message
				message = msg;

			} // End OutOfBoundsException( const string msg )

			/*
			Purpose:			Returns PDM message.
			Pre:				An OutOfBoundsException object has been instantiated.
			Post:				PDM message has been returned.
			Classification:		Observer / Accessor
			Order of Magnitude:	O(1)
			*/
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End OutOfBoundsException

	class OutOfMemoryException
	{
		private:

			string message;	// A message describing the exception


		public:

			/*
			Purpose:			Instantiates an OutOfMemoryException object with a custom message. PDM
								message has been intitiallized to msg.
			Pre:				None.
			Post:				An OutOfMemoryException object has been instantiated. PDM message has
								been intitiallized to msg.
			Classification:		Non-default Constructor
			Order of Magnitude:	O(1)
			*/
			OutOfMemoryException( /* In */ const string& msg )	// The message to initiallize PDM
																//  message with
			{
				// Initiallize PDM message
				message = msg;

			} // End OutOfMemoryException( const string msg )

			/*
			Purpose:			Returns PDM message.
			Pre:				An OutOfMemoryException object has been instantiated.
			Post:				PDM message has been returned.
			Classification:		Observer / Accessor
			Order of Magnitude:	O(1)
			*/
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End OutOfMemoryEXception

} // End MazeExeptions

#endif