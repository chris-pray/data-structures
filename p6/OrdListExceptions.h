/*
AUTHOR:
	Chris Pray

DATE:
	5/10/13

FILENAME:
	OrdListExceptions.h

PURPOSE:
	This file contains custom exception classes, DuplicateKeyException, InvalidRetrieveException, and
	OutOfMemoryException to be used with OrdListClass objects. DuplicateKeyException should be thrown
	whenever an item is attempted to be inserted into a list when the key of the item matches the key of
	an item already in the list. InvalidRetrieveException should be thrown whenever an attempt to
	retrieve an ItemType from an invalid location is made. An invalid location is when currPos is NULL.
	OutOfMemoryException should be thrown whenever an attempt to allocate dynamic memory fails.

Summary of Methods:

	DuplicateKeyException::DuplicateKeyException( string msg )
		Non-default constructor for a DuplicateKeyException object. msg is a message passed when the
		exception is thrown.
	DuplicateKeyException::GetMessage()
		Returns PDM message which is set when the exception is thrown.

	InvalidRetrieveException::InvalidRetrieveException( string msg )
		Non-default constructor for a InvalidRetrieveException object. msg is a message passed when the
		exception is thrown.
	InvalidRetrieveException::GetMessage()
		Returns PDM message which is set when the exception is thrown.

	OutOfMemoryException::OutOfMemoryException(string msg)
		Non-default constructor for an OutOfMemoryException object. msg is a message passed when the
		exception is thrown.
	OutOfMemoryException::GetMessage()
		Returns PDM message which is set when the exception is thrown.
*/

#ifndef OrdListExceptions_h
#define OrdListExceptions_h

#include <string>		// For string data type
using namespace std;

namespace OrdListExceptions
{
	class DuplicateKeyException
	{
		private:

			string message;	// A message describing the exception


		public:

			// Purpose:				Instantiates a DuplicateKeyException object with a custom message.
			//						PDM message has been intitiallized to msg.
			// Pre:					None.
			// Post:				A DuplicateKeyException object has been instantiated. PDM message
			//						has been intitiallized to msg.
			// Classification:		Non-default constructor
			// Order of Magnitude:	O(1)
			DuplicateKeyException( /* In */ string msg )  // The message to initiallize PDM message with
			{
				message = msg;

			} // End DuplicateKeyException( string msg )

			// Purpose:				Returns PDM message.
			// Pre:					A DuplicateKeyException object has been instantiated.
			// Post:				PDM message has been returned.
			// Classification:		Observer / Accessor
			// Order of Magnitude:	O(1)
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End DuplicateKeyException

	class InvalidRetrieveException
	{
		private:

			string message;	// A message describing the exception


		public:

			// Purpose:				Instantiates an InvalidRetrieveException object with a custom
			//						message. PDM message has been intitiallized to msg.
			// Pre:					None.
			// Post:				An InvalidRetrieveException object has been instantiated. PDM
			//						message has been intitiallized to msg.
			// Classification:		Non-default constructor
			// Order of Magnitude:	O(1)
			InvalidRetrieveException( /* In */ string msg )	// The message to initiallize PDM message
															//  with
			{
				message = msg;

			} // End InvalidRetrieveException( string msg )

			// Purpose:				Returns PDM message.
			// Pre:					An InvalidRetrieveException object has been instantiated.
			// Post:				PDM message has been returned.
			// Classification:		Observer / Accessor
			// Order of Magnitude:	O(1)
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End InvalidRetrieveException

	class OutOfMemoryException
	{
		private:

			string message;	// A message describing the exception


		public:

			// Purpose:				Instantiates an OutOfMemoryException object with a custom message.
			//						PDM message has been intitiallized to msg.
			// Pre:					None.
			// Post:				An OutOfMemoryException object has been instantiated. PDM message
			//						has been intitiallized to msg.
			// Classification:		Non-default constructor
			// Order of Magnitude:	O(1)
			OutOfMemoryException( /* In */ string msg )	// The message to initiallize PDM message with
			{
				message = msg;

			} // End OutOfMemoryException( string msg )

			// Purpose:				Returns PDM message.
			// Pre:					An OutOfMemoryException object has been instantiated.
			// Post:				PDM message has been returned.
			// Classification:		Observer / Accessor
			// Order of Magnitude:	O(1)
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End OutOfMemoryException

} // End OrdListExceptions

#endif
