/*
AUTHOR:
	Chris Pray

DATE:
	4/4/13

FILENAME:
	StackExceptions.h

PURPOSE:
	This file contains custom exception classes, OutOfMemoryException and RetrieveOnEmptyException to be
	used with StackClass objects. OutOfMemoryException should be thrown whenever an attempt to
	dynamically allocate memory for a stack node fails. RetrieveOnEmptyException should be thrown
	whenever an attempting to retrieve an item from an empty stack.

SUMMARY OF METHODS:
	
	OutOfMemoryException::OutOfMemoryException(string newMessage)
		Non-default constructor for an OutOfMemoryException object. msg is a message passed when the
		exception is thrown.
	OutOfMemoryException::GetMessage()
		Returns PDM message which is set when the exception is thrown.

	RetrieveOnEmptyException::RetrieveOnEmptyException(string newMessage)
		Non-default constructor for an RetrieveOnEmptyException object. msg is a message passed when the
		exception is thrown.
	RetrieveOnEmptyException::GetMessage()
		Returns PDM message which is set when the exception is thrown.
*/

#ifndef StackExceptions_h
#define StackExceptions_h

#include<string>		// For string data type
using namespace std;

namespace nmspcStackExceptions
{
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

	class RetrieveOnEmptyException
	{
		private:

			string message;	// A message describing the exception

		public:

			/*
			Purpose:			Instantiates a RetrieveOnEmptyException object with a custom message.
								PDM message has been intitiallized to newMessage.
			Pre:				None.
			Post:				A RetrieveOnEmptyException object has been instantiated. PDM message has
								been intitiallized to newMessage.
			Classification:		Non-default Constructor
			Order of Magnitude:	O(1)
			*/
			RetrieveOnEmptyException(/* In */ string newMessage)	// The message to initiallize PDM
																	//  message with
			{
				// Initiallize PDM message
				message = newMessage;

			} // End RetrieveOnEmptyException(string newMessage)

			/*
			Purpose:			Returns PDM message.
			Pre:				A RetrieveOnEmptyException object has been instantiated.
			Post:				PDM message has been returned.
			Classification:		Observer / Accessor
			Order of Magnitude:	O(1)
			*/
			string GetMessage()
			{
				return message;

			} // End string GetMessage()

	}; // End RetrieveOnEmptyException

} // End nmspcStackExceptions

#endif