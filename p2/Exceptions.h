/*
AUTHOR:
	Chris Pray

DATE:
	3/19/13

FILENAME:
	Exceptions.h

PURPOSE:
	This file contains custom exception classes, DuplicateKeyException and OutOfMemoryException to be
	used with OrdListClass objects. DuplicateKeyException should be thrown whenever an item is attempted
	to be inserted into a list when the key of the item matches the key of an item already in the list.
	OutOfMemoryException should be thrown whenever an attempt to allocate dynamic memory fails.

SUMMARY OF METHODS:
	
	OutOfMemoryException::OutOfMemoryException(string msg)
		Non-default constructor for an OutOfMemoryException object. msg is a message passed when the
		exception is thrown.
	OutOfMemoryException::GetMessage()
		Returns PDM message which is set when the exception is thrown.

	DuplicateKeyException::DuplicateKeyException(KeyType duplicate, string msg)
		Non-default constructor for a DuplicateKeyException object. duplicate is the key that is already
		in the list. msg is a message passed when the exception is thrown.
	DuplicateKeyException::GetMessage()
		Returns PDM message which is set when the exception is thrown.
	DuplicateKeyException::GetKey()
		Returns PDM key which is set when the exception is thrown.
*/

#ifndef Exceptions_h
#define Exceptions_h

#include<string>		// For string data type
using namespace std;

namespace nmspcExceptions
{
	class OutOfMemoryException
	{
		private:
		
			string message;	// A message to the user explaining why the exception was thrown

		public:

			//Purpose:	Instantiates an OutOfMemoryException object
			//Pre:		None
			//Post:		An OutOfMemoryException object has been instantiated
			OutOfMemoryException(string msg)	// Message that gets assigned to PDM, message
			{
				message = msg;

			} // End OutOfMemoryException(string message)

			//Purpose:	Returns a message stating why the exception was thrown
			//Pre:		An OutOfMemoryException object has been instantiated
			//Post:		The message stating why the exception was thrown has been returned
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End OutOfMemoryException

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	class DuplicateKeyException
	{
		private:

			string message;	// A message to the user explaining why the exception was thrown
			KeyType key;	// The key that is already in the list

		public:

			//Purpose:	Instantiates a DuplicateKeyException object
			//Pre:		None
			//Post:		A DuplicateKeyException object has been instantiated
			DuplicateKeyException(KeyType duplicate,	// Key that gets assigned to PDM, key
								  string  msg)			// Message that gets assigned to PDM, message
			{
				message = msg;
				key = duplicate;

			} // End DuplicateKeyException(string newMessage)

			//Purpose:	Returns a message stating why the exception was thrown
			//Pre:		A DuplicateKeyException object has been instantiated
			//Post:		The message stating why the exception was thrown has been returned
			string GetMessage()
			{
				return message;

			} // End GetMessage()

			//Purpose:	Returns the value of the key which was a duplicate
			//Pre:		A DuplicateKeyException object has been instantiated
			//Post:		The value of the duplicate key has been returned
			KeyType GetKey()
			{
				return key;

			} // End GetKey()

	}; // End DuplicateKeyException

} // End nmspcExceptions

#endif