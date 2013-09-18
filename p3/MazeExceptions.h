/*
AUTHOR:
	Chris Pray

DATE:
	4/4/13

FILENAME:
	MazeExceptions.h

PURPOSE:
	This file contains custom exception classes, RetrieveFromOutOfBoundsException and
	OutOfMemoryException to be used with MazeClass objects. RetrieveFromOutOfBoundsException should be
	thrown whenever an attempt to retrieve a MazePositionType from a location that's outside the bounds
	of the maze is made. OutOfMemoryException should be thrown whenever an attempt to dynamically
	allocate memory for the instantiation of a MazeClass object.

SUMMARY OF METHODS:
	
	RetrieveFromOutOfBoundsException::RetrieveFromOutOfBoundsException(string newMessage)
		Non-default constructor for an RetrieveFromOutOfBoundsException object. msg is a message passed
		when the exception is thrown.
	RetrieveFromOutOfBoundsException::GetMessage()
		Returns PDM message which is set when the exception is thrown.

	OutOfMemoryException::OutOfMemoryException(string newMessage)
		Non-default constructor for an OutOfMemoryException object. msg is a message passed when the
		exception is thrown.
	OutOfMemoryException::GetMessage()
		Returns PDM message which is set when the exception is thrown.
*/

#ifndef MazeExceptions_h
#define MazeExceptions_h

#include<string>		// For string data type
using namespace std;

namespace nmspcMazeExceptions
{
	class RetrieveFromOutOfBoundsException
	{
		private:

			string message;	// A message describing the exception

		public:

			/*
			Purpose:			Instantiates a RetrieveFromOutOfBoundsException object with a custom
								message. PDM message has been intitiallized to newMessage.
			Pre:				None.
			Post:				A RetrieveFromOutOfBoundsException object has been instantiated. PDM
								message has been intitiallized to newMessage.
			Classification:		Non-default Constructor
			Order of Magnitude:	O(1)
			*/
			RetrieveFromOutOfBoundsException(/* In */ string newMessage) // The message to initiallize
																		 //  PDM message with
			{
				// Initiallize PDM message
				message = newMessage;

			} // End RetrieveFromOutOfBoundsException(string newMessage)

			/*
			Purpose:			Returns PDM message.
			Pre:				A RetrieveFromOutOfBoundsException object has been instantiated.
			Post:				PDM message has been returned.
			Classification:		Observer / Accessor
			Order of Magnitude:	O(1)
			*/
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End RetrieveFromOutOfBoundsException

	class OutOfMemoryException
	{
		private:

			string message;	// A message describing the exception

		public:

			/*
			Purpose:			Instantiates an OutOfMemoryException object with a custom message. PDM
								message has been intitiallized to newMessage.
			Pre:				None.
			Post:				An OutOfMemoryException object has been instantiated. PDM message has
								been intitiallized to newMessage.
			Classification:		Non-default Constructor
			Order of Magnitude:	O(1)
			*/
			OutOfMemoryException(/* In */ string newMessage)	// The message to initiallize PDM
																//  message with
			{
				// Initiallize PDM message
				message = newMessage;

			} // End OutOfMemoryException(string newMessage)

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

	}; // End OutOfMemoryException

} // End nmspcMazeExceptions

#endif