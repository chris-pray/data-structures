/*
AUTHOR:
	Chris Pray

DATE:
	4/18/13

FILENAME:
	OrdListExceptions.h

PURPOSE:
	This file contains custom exception classes, DuplicateKeyException, RetrieveOnEmptyException, 
	PastEndOfListException, and OutOfMemoryException to be used with OrdListClass objects.
	DuplicateKeyException should be thrown whenever an item is attempted to be inserted into a list when
	the key of the item matches the key of an item already in the list. RetrieveOnEmptyException should
	be thrown whenever an attempt to retrieve an ItemType from an empty list is made.
	PastEndOfListException should be thrown whenever an attempt to move the current position of the list
	before the first position in the list or past the last position in the list. OutOfMemoryException
	should be thrown whenever an attempt to allocate dynamic memory fails.

Summary of Methods:

	DuplicateKeyException::DuplicateKeyException(string msg)
		Non-default constructor for a DuplicateKeyException object. msg is a message passed when the
		exception is thrown.
	DuplicateKeyException::GetMessage()
		Returns PDM message which is set when the exception is thrown.

	RetrieveOnEmptyException::RetrieveOnEmptyException(string msg)
		Non-default constructor for a RetrieveOnEmptyException object. msg is a message passed when the
		exception is thrown.
	RetrieveOnEmptyException::GetMessage()
		Returns PDM message which is set when the exception is thrown.

	PastEndOfListException::PastEndOfListException(string msg)
		Non-default constructor for a PastEndOfListException object. msg is a message passed when the
		exception is thrown.
	PastEndOfListException::GetMessage()
		Returns PDM message which is set when the exception is thrown.

	OutOfMemoryException::OutOfMemoryException(string msg)
		Non-default constructor for an OutOfMemoryException object. msg is a message passed when the
		exception is thrown.
	OutOfMemoryException::GetMessage()
		Returns PDM message which is set when the exception is thrown.
*/

#ifndef OrdListClassExceptions_h
#define OrdListClassExceptions_h

#include<string>		// For string data type
using namespace std;

namespace OrdListClassExceptions
{
	class DuplicateKeyException
	{
		private:

			string message;	// A message describing the exception


		public:

			// Purpose:	Instantiates a DuplicateKeyException object with a custom message. PDM message
			//			has been intitiallized to msg.
			// Pre:		None.
			// Post:	A DuplicateKeyException object has been instantiated. PDM message has been
			//			intitiallized to msg.
			DuplicateKeyException( /* In */ string msg)	// The message to initiallize PDM message with
			{
				// Initiallize PDM message
				message = msg;

			} // End DuplicateKeyException(string msg)

			// Purpose:	Returns PDM message.
			// Pre:		A DuplicateKeyException object has been instantiated.
			// Post:	PDM message has been returned.
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End DuplicateKeyException

	class RetrieveOnEmptyException
	{
		private:

			string message;	// A message describing the exception


		public:

			// Purpose:	Instantiates a RetrieveOnEmptyException object with a custom message. PDM
			//			message has been intitiallized to msg.
			// Pre:		None.
			// Post:	A RetrieveOnEmptyException object has been instantiated. PDM message has been
			//			intitiallized to msg.
			RetrieveOnEmptyException( /* In */ string msg)	// The message to initiallize PDM message
															//  with
			{
				// Initiallize PDM message
				message = msg;

			} // End RetrieveOnEmptyException(string msg)

			// Purpose:	Returns PDM message.
			// Pre:		A RetrieveOnEmptyException object has been instantiated.
			// Post:	PDM message has been returned.
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End RetrieveOnEmptyException

	class PastEndOfListException
	{
		private:

			string message;	// A message describing the exception


		public:

			// Purpose:	Instantiates a PastEndOfListException object with a custom message. PDM message
			//			has been intitiallized to msg.
			// Pre:		None.
			// Post:	A PastEndOfListException object has been instantiated. PDM message has been
			//			intitiallized to msg.
			PastEndOfListException( /* In */ string msg)	// The message to initiallize PDM message
															//  with
			{
				// Initiallize PDM message
				message = msg;

			} // End PastEndOfListException(string msg)

			// Purpose:	Returns PDM message.
			// Pre:		A PastEndOfListException object has been instantiated.
			// Post:	PDM message has been returned.
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End PastEndOfListException

	class OutOfMemoryException
	{
		private:

			string message;	// A message describing the exception


		public:

			// Purpose:	Instantiates an OutOfMemoryException object with a custom message. PDM message
			//			has been intitiallized to msg.
			// Pre:		None.
			// Post:	An OutOfMemoryException object has been instantiated. PDM message has been
			//			intitiallized to msg.
			OutOfMemoryException( /* In */ string msg)	// The message to initiallize PDM message with
			{
				// Initiallize PDM message
				message = msg;

			} // End OutOfMemoryException(string msg)

			// Purpose:	Returns PDM message.
			// Pre:		An OutOfMemoryException object has been instantiated.
			// Post:	PDM message has been returned.
			string GetMessage()
			{
				return message;

			} // End GetMessage()

	}; // End OutOfMemoryException

} // End OrdListClassExceptions

#endif