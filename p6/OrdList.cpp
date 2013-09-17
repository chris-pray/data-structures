/*
AUTHOR:
	Chris Pray

DATE:
	5/10/13

FILENAME:
	OrdList.cpp

PURPOSE:
	This file contains the implementation for all of the methods declared in ordlisttemplate.h

	Structure:		OrdList
	Implementation:	Binary Search Tree
*/

#pragma once

template <class ItemType>
struct node
{
	node<ItemType>* left;	// Left subtree pointer
	ItemType data;			// Data
	node<ItemType>* right;	// Right subtree pointer

}; // End node

template <class ItemType>
OrdListClass<ItemType>::OrdListClass()
{
	//Initialize PDMs
	root	= NULL;
	currPos = NULL;
	prevPos = NULL;

} // End OrdListClass()

template <class ItemType>
OrdListClass<ItemType>::~OrdListClass()
{
	// Return dynamically allocated memory to heap
	Clear();

} // End ~OrdListClass()

template <class ItemType>
OrdListClass<ItemType>::OrdListClass( /* In */ const OrdListClass<ItemType>& orig )	// Deep copy this object
{
	// Initiallize PDMs
	root	= NULL;
	currPos = NULL;
	prevPos = NULL;

	// *this = orig
	operator=( orig );

} // End OrdListClass( const OrdListClass& orig )

template <class ItemType>
bool OrdListClass<ItemType>::IsEmpty()const
{
	return root == NULL;

} // End IsEmpty()const

template <class ItemType>
bool OrdListClass<ItemType>::IsFull()const
{
	return false;

} // End IsFull()const

template <class ItemType>
bool OrdListClass<ItemType>::EndOfList()
{
	// If current position is NULL
	if( currPos == NULL )
	{
		node<ItemType>* temp = root;	// Traversal pointer
		
		// While traversal pointer has a right subtree
		while( temp->right != NULL )
			temp = temp->right;

		// If parent of current position is right-most node
		if(prevPos == temp)
			return true;

	} // End if

	return false;

} // End EndOfList()

template <class ItemType>
void OrdListClass<ItemType>::FirstPosition()
{
	// If not empty
	if( !IsEmpty() )
	{
		currPos = root;
		prevPos = NULL;

		// While the current position is not at the bottom-most left node
		while( currPos->left != NULL )
		{

			prevPos = currPos;
			currPos = currPos->left;

		} // End while

	} // End if

} // End FirstPosition()

template <class ItemType>
void OrdListClass<ItemType>::NextPosition()
{
	// If current position is not NULL
	if( currPos != NULL )
	{
		// If current position has a right subtree
		if( currPos->right != NULL )
		{
			node<ItemType>* nextPos = currPos->right;	// Traversal pointer to next in-order item
			node<ItemType>* prevNextPos = currPos;		// Traversal pointer to parent of next in-order item

			// While there is a left subtree
			while( nextPos->left != NULL )
			{
				prevNextPos = nextPos;
				nextPos = nextPos->left;

			} // End while

			currPos = nextPos;
			prevPos = prevNextPos;

		} // End if
		// Else if current position is a left child
		else if( prevPos != NULL && currPos == prevPos->left )
		{
			currPos = prevPos;

			// If previous position is not root
			if( prevPos != root )
				// Set previous position to its parent
				rFindParent( root );
			// Else previous position is root
			else
				prevPos = NULL;

		} // End else if
		// Else if current position is a right child
		else if( prevPos != NULL )
		{
			node<ItemType>* temp;			// Traversal pointer to next in-order item
			node<ItemType>* prevTemp;		// Traversal pointer to parent of next in-order item
			node<ItemType>* end = prevPos;	// Traveral pointer to a child of item to exit loop at
			bool found = false;				// Indicates whether next in-order item was found

			// While next in-order item has not been found
			while( !found )
			{
				temp = root;
				prevTemp = NULL;

				// If traversal pointer does not equal the child of the last node in a
				//  traversal
				if( temp != end )
				{
					// Traverse the tree from the root to the parent of prevPos or the node traversed to
					//  on the last iteration of the outer loop, whichever is at a lower level
					while( temp->left != end && temp->right != end )
					{
						// If a right traversal is necessary
						if( temp->data.key < end->data.key )
						{
							prevTemp = temp;
							temp = temp->right;

						} // End if
						// Else a left traversal is necessary
						else
						{
							prevTemp = temp;
							temp = temp->left;

						} // End else

					} // End while

					// If the child node indicating the end of the traversal is the left subtree of its
					//  parent
					if( temp->left == end )
					{
						currPos = temp;
						prevPos = prevTemp;
						found = true;

					} // End if
					// Else the child node indicating the end of the traversal is the right subtree of
					//  its parent
					else
						end = temp;

				} // End if
				// Else a traversal is not appropriate
				else
				{
					prevPos = currPos;
					currPos = NULL;
					found = true;

				} // End else

			} // End while

		} // End else if
		// Else the previous position in the tree is NULL, indicating the current position in the tree
		//  is at the root of the tree, and the current position does not have a right subtree
		else
		{
			prevPos = currPos;
			currPos = NULL;

		} // End else

	} // End if

} // End NextPosition()

template <class ItemType>
bool OrdListClass<ItemType>::Find( /* In */ KeyType target )	// The target being searched for
{
	currPos = root;
	prevPos = NULL;

	// Recursively search for the target
	return rFind( target );

} // End Find( KeyType target )

template <class ItemType>
ItemType OrdListClass<ItemType>::Retrieve()const
{
	// If the current position in the tree is NULL
	if( currPos != NULL )
	{
		return currPos->data;

	} // End if

	throw InvalidRetrieveException( "InvalidRetrieveException: Cannot retrieve from this location" );

} // End Retrieve()const

template <class ItemType>
void OrdListClass<ItemType>::Insert( /* In */ ItemType newItem )	// The item to insert into the tree
{
	// If the current position in the list is NULL
	if( currPos == NULL )
	{
		// Dynamically allocate memory for a new node at the current position in the list
		currPos = Allocate();

		currPos->data = newItem;

		// If the tree is not empty
		if( !IsEmpty() )
		{
			// If the new node should be the left child of the previous position in the tree
			if( newItem.key < prevPos->data.key )
				prevPos->left = currPos;
			// Else the new node should be the right child of the previous position in the tree
			else
				prevPos->right = currPos;

		} // End if
		// Else the tree is empty
		else
			root = currPos;

	} // End if
	// Else the current position in the list is not NULL, indicating the item to be inserted is already
	//  in the tree
	else
		throw DuplicateKeyException("DuplicateKeyException: Cannot insert a duplicate key");

} // End Insert( ItemType newItem )

template <class ItemType>
void OrdListClass<ItemType>::Delete( /* In */ KeyType key )	// The key of the node to delete
{
	// If the current position in the tree is not NULL and the key of the node at the current position
	//  in the tree is equal to the key of the node to delete
	if( currPos != NULL && currPos->data.key == key )
	{
		// If the current position in the tree is a leaf
		if( currPos->left == NULL && currPos->right == NULL )
		{
			// If the previous position in the tree is not NULL, indicating the current position in the
			//  tree is not the root of the tree
			if( prevPos != NULL )
			{
				// If the node to be deleted is the left child of the previous position in the tree
				if( currPos->data.key < prevPos->data.key )
					prevPos->left = NULL;
				// Else the node to be deleted is the right child of the previous position in the tree
				else
					prevPos->right = NULL;
					
			} // End if
			// Else the current position in the tree is the root of the tree
			else
				root = NULL;

			delete currPos;

			currPos = prevPos;

			// If the previous position in the tree is not the root of the tree
			if( prevPos != root )
				// Recursively set the previous position in the tree to its parent
				rFindParent( root );
			// Else the previous position in the tree is the root of the tree
			else
				prevPos = NULL;

		} // End if
		// Else if the current position in the tree has a right subtree but no left subtree
		else if( currPos->left == NULL )
		{
			// If the previous position in the tree is not NULL, indicating the current position in the
			//  tree is not the root of the tree
			if( prevPos != NULL )
			{
				// If the node to be deleted is the left child of the previous position in the tree
				if( currPos->data.key < prevPos->data.key )
					prevPos->left = currPos->right;
				// Else the node to be deleted is the right child of the previous position in the tree
				else
					prevPos->right = currPos->right;

			} // End if
			// Else the current position in the tree is the root of the tree
			else
				root = currPos->right;

			delete currPos;

			currPos = prevPos;

			// If the previous position in the tree is not the root of the tree
			if( prevPos != root )
				// Recursively set the previous position in the tree to its parent
				rFindParent( root );
			// Else the previous position in the tree is the root of the tree
			else
				prevPos = NULL;

		} // End else if
		// Else if the current position in the tree has a left subtree but no right subtree
		else if( currPos->right == NULL )
		{
			// If the previous position in the tree is not NULL, indicating the current position in the
			//  tree is not the root of the tree
			if( prevPos != NULL )
			{
				// If the node to be deleted is the left child of the previous position in the tree
				if( currPos->data.key < prevPos->data.key )
					prevPos->left = currPos->left;
				// Else the node to be deleted is the right child of the previous position in the tree
				else
					prevPos->right = currPos->left;

			} // End if
			// Else the current position in the tree is the root of the tree
			else
				root = currPos->left;

			delete currPos;

			currPos = prevPos;

			// If the previous position in the tree is not the root of the tree
			if( prevPos != root )
				// Recursively set the previous position in the tree to its parent
				rFindParent( root );
			// Else the previous position in the tree is the root of the tree
			else
				prevPos = NULL;

		} // End else if
		// Else the current position in the tree has a left and a right subtree
		else
		{
			node<ItemType>* temp = currPos->left;	// A temporary traversal pointer

			// If the left child of the node at the current position in the tree has a right subtree
			if(temp->right != NULL)
			{
				node<ItemType>* prevTemp = temp;	// A temporary pointer to the parent of the
													//  traversal pointer

				temp = temp->right;

				// Set the traversal pointer to the in-order precursor of the node at the current
				//  position in the tree
				while( temp->right != NULL )
				{
					prevTemp = temp;

					temp = temp->right;

				} // End while

				currPos->data = temp->data;

				// If the in-order precursor of the node at the current position in the tree has a left
				//  subtree
				if( temp->left != NULL )
					prevTemp->right = temp->left;
				// Else the in-order precursor of the node at the current position in the tree does not
				//  have a left subtree
				else
					prevTemp->right = NULL;

			} // End if
			// Else the left child of the node at the current position in the tree does not have a right
			//  subtree, indicating the left child of the node at the current position in the tree is
			//  the in-order precursor of the node at the current position in the tree
			else
			{
				currPos->data = temp->data;

				// If the in-order precursor of the node at the current position in the tree has a left
				//  subtree
				if( temp->left != NULL )
					currPos->left = temp->left;
				// Else the in-order precursor of the node at the current position in the tree does not
				//  have a left subtree
				else
					currPos->left = NULL;

			} // End else

			delete temp;

		} // End else

	} // End if

} // End Delete( KeyType key )

template <class ItemType>
void OrdListClass<ItemType>::Clear()
{
	currPos = NULL;
	prevPos = NULL;

	// Recursively clear the tree
	rClear( root );

	root = NULL;

} // End Clear()

template <class ItemType>
int OrdListClass<ItemType>::ReturnLength()const
{
	// Recursively determine the number of nodes in the tree
	return rReturnLength( root );

} // End ReturnLength()const

template <class ItemType>
void OrdListClass<ItemType>::operator=
	( /* In */ const OrdListClass<ItemType>& orig )	// The object to make a deep copy of
{
	// Clear the applying object's tree
	Clear();

	// Recursively make the applying object a deep copy of orig
	rAssign( root, orig.root );

	// If the current position in orig's tree is not NULL
	if( orig.currPos != NULL )
		// Set the current position and the previous position in the applying object's tree to the
		//  appropriate nodes in respect to the current position and the previous position in orig's
		//  tree
		Find( orig.currPos->data.key );
	// Else if the current position in orig's tree is NULL and the previous position in orig's tree is
	//  not NULL
	else if( orig.prevPos != NULL )
	{
		// Set the current position and the previous position in the applying object's tree to the
		//  appropriate nodes in respect to the current position and the previous position in orig's
		//  tree
		Find( orig.prevPos->data.key );
		prevPos = currPos;
		currPos = NULL;

	} // End if

} // End operator=( const OrdListClass& orig )

template <class ItemType>
void OrdListClass<ItemType>::PrintScreen
	( /* In */ FunctionType visit )	// A pointer to the function defined by the client which determines
									//  what happens when the traversal visits a node
{
	// Recursively print the key of each node in the tree to the console using an in-order traversal
	rPrintScreen( visit, root );

} // End PrintScreen( FunctionType visit )

template <class ItemType>
void OrdListClass<ItemType>::PrintFile
	( /* In */	   FunctionType2 visit,	// A pointer to the function defined by the client which
										//  determines what happens when the traversal visits a node
	  /* In/Out */ ofstream& dout )		// An output file stream variable
{
	// Recursively print the key of each node in the tree to a file using a pre-order traversal
	rPrintFile( visit, dout, root );

} // End PrintFile( FunctionType2 visit, ofstream& dout )

template <class ItemType>
void OrdListClass<ItemType>::PrintReverse
	( /* In */ FunctionType visit )	// A pointer to the function defined by the client which determines
									//  what happens when the traversal visits a node
{
	// Recursively print the key of each node in the tree to the console using an in-order traversal,
	//  starting with the last node
	rPrintReverse( visit, root );

} // End PrintReverse( FunctionType visit )

template <class ItemType>
void OrdListClass<ItemType>::PrintAsExists
	( /* In */ FunctionType visit )	// A pointer to the function defined by the client which determines
									//  what happens when the traversal visits a node
{
	ItemType arr[ MAX_ITEMS ];	// Copies of the data at each node in the tree

	// For each index in the array
	for( int i = 0; i < MAX_ITEMS; i++ )
		arr[ i ].key = INT_MIN;

	// Recursively fill the array so hat the items at each sequential index of the array are copies of
	//  the items that appear in a breadth-first traversal of the tree
	rFill( root, arr, 0 );
	
	// For each index in the array
	for( int i = 0; i < MAX_ITEMS; i++ )
	{
		// If the index is less than one
		if( i < 1 )
		{
			cout << "                                      ";

			// If the key of the item at the index is equal to INT_MAX
			if( arr[ i ].key == INT_MAX )
				cout << "  #  ";
			// Else if the key of the item at the index is not equal to INT_MIN
			else if( arr[ i ].key != INT_MIN )
				visit( arr[ i ] );
			// Else the key of the item at the index is equal to INT_MIN
			else
				cout << "     ";

			cout << endl;

		} // End if
		// Else if the index is less than three
		else if( i < 3 )
		{
			// If the index is equal to one
			if( i == 1 )
				cout << "                  ";
			// Else the index is not equal to one
			else
				cout << "                                   ";

			// If the key of the item at the index is equal to INT_MAX
			if( arr[ i ].key == INT_MAX )
				cout << "  #  ";
			// Else if the key of the item at the index is not equal to INT_MIN
			else if( arr[ i ].key != INT_MIN )
				visit( arr[ i ] );
			// Else the key of the item at the index is equal to INT_MIN
			else
				cout << "     ";

			// If the index is equal to two
			if( i == 2 )
				cout << endl;

		} // End else if
		// Else if the index is less than seven
		else if( i < 7 )
		{
			// If the index is equal to three
			if( i == 3 )
				cout << "        ";
			// Else the index is not equal to three
			else
				cout << "               ";

			// If the key of the item at the index is equal to INT_MAX
			if( arr[ i ].key == INT_MAX )
				cout << "  #  ";
			// Else if the key of the item at the index is not equal to INT_MIN
			else if( arr[ i ].key != INT_MIN )
				visit( arr[ i ] );
			// Else the key of the item at the index is equal to INT_MIN
			else
				cout << "     ";

			// If the index is equal to six
			if( i == 6 )
				cout << endl;

		} // End else if
		// Else if the index is less than fifteen
		else if( i < 15 )
		{
			// If the index is equal to seven
			if( i == 7 )
				cout << "   ";
			// Else if the index is not equal to seven
			else
				cout << "     ";
			
			// If the key of the item at the index is equal to INT_MAX
			if( arr[ i ].key == INT_MAX )
				cout << "  #  ";
			// Else if the key of the item at the index is not equal to INT_MIN
			else if( arr[ i ].key != INT_MIN )
				visit( arr[ i ] );
			// Else the key of the item at the index is equal to INT_MIN
			else
				cout << "     ";

			// If the index is equal to fourteen
			if( i == 14 )
				cout << endl;

		} // End else if
		// Else if the index is less than thirty-one
		else if( i < 31 )
		{
			// If the key of the item at the index is equal to INT_MAX
			if( arr[ i ].key == INT_MAX )
				cout << "  #  ";
			// Else if the key of the item at the index is not equal to INT_MIN
			else if( arr[ i ].key != INT_MIN )
				visit( arr[ i ] );
			// Else the key of the item at the index is equal to INT_MIN
			else
				cout << "     ";

		} // End else if

	} // End for

	cout << endl;

} // End PrintAsExists( FunctionType visit )

template <class ItemType>
bool OrdListClass<ItemType>::operator==
	( /* In */ const OrdListClass<ItemType>& rtOp )const	// The object to compare the applying
															//  object's eqallity against
{
	// Recursively determine if the keys in the applying object's tree are equal to the keys in rtOp's
	//  tree
	return rIsEqual( root, rtOp.root );

} // End operator==( const OrdListClass& rtOp )const

template <class ItemType>
bool OrdListClass<ItemType>::operator!=
	( /* In */ const OrdListClass<ItemType>& rtOp )const	// The object to compare the applying
															//  object's ineqallity against
{
	return !operator==( rtOp );

} // End operator!=( const OrdListClass& rtOp )const

template <class ItemType>
OrdListClass<ItemType> OrdListClass<ItemType>::operator+
	( /* In */ const OrdListClass<ItemType>& rtOp )const	// The object to combine with the applying
															//  object
{
	OrdListClass<ItemType> ordUnion( *this );	// A complete tree with nodes with all the keys in the
												//  applying object's tree and rtOp's tree
	int numTotal;								// The number of nodes in the complete tree
	int index = 0;								// An index to an ItemType array, which contains a copy
												//  of the data of each node that will be inserted into
												//  the complete tree

	// Combine all the nodes from rtOp whose keys don't match the keys of any of the items in the
	//  applying object
	rFillUnion( ordUnion, rtOp.root );

	// Get the number of nodes in the union
	numTotal = ordUnion.ReturnLength();

	// If the union is not empty
	if( numTotal > 0 )
	{
		ItemType* arrTotal = new ItemType[ numTotal ];	// Contains all the items in the union
		int numTop,										// Number of nodes in the complete union BST
														//  above the bottom level
			numBottom;									// Number of nodes on the bottom level of the
														//  complete union BST

		// Recursively fill the array with each item from the union in ascending order of keys
		rFillArr( ordUnion.root, arrTotal, index, numTotal );

		// Clear the unions tree
		ordUnion.Clear();

		index = 1;

		// Number of nodes in the complete union BST above the bottom level
		while( (int)pow( 2.0f, (float)index ) - 1 <= numTotal )
		{
			numTop = (int)pow( 2.0f, (float)index ) - 1;

			index++;

		} // End while

		numBottom = numTotal - numTop;
		
		// If the union cannot have a full BST
		if( numBottom > 0 )
		{
			ItemType* arrTop = new ItemType[ numTop ];			// Contains the items of the union's
																//  complete BST above the bottom level
			ItemType* arrBottom = new ItemType[ numBottom ];	// Contains the items of the union's
																//  complete BST on the bottom level
			int indexTop = 0;									// The index of an item in arrTop

			// For each item in arrTotal
			for( int i = 0; i < numTotal; i++ )
			{
				// If the item at index i of arrTotal would be on the bottom level of the union's
				//  complete BST
				if( i % 2 == 0 && i < numBottom * 2 )
					arrBottom[ i / 2 ] = arrTotal[ i ];
				// Else the item at index i of arrTotal would be above the bottom level of the union's
				//  complete BST
				else
				{
					arrTop[ indexTop ] = arrTotal[ i ];
					indexTop++;

				} // End else

			} // End for

			// Fill the union's complete BST with the items above the bottom level
			rCompleteUnion( ordUnion, arrTop, 0, numTop - 1 );

			// Fill the union's complete BST with the items on the bottom level
			rCompleteUnion( ordUnion, arrBottom, 0, numBottom - 1 );

		} // End if
		else
			// Fill the union's complete BST
			rCompleteUnion( ordUnion, arrTotal, 0, numTotal - 1 );

	} // End if

	return ordUnion;

} // End operator+( const OrdListClass& rtOp )const

template <class ItemType>
node<ItemType>* OrdListClass<ItemType>::Allocate()
{
	try
	{
		node<ItemType>* newNode = new node<ItemType>;	// A dynamically allocated node

		newNode->left = NULL;
		newNode->right = NULL;

		return newNode;

	} // End try
	catch( bad_alloc e )	// Failed to dynamically allocate memory for the noe
	{
		throw OutOfMemoryException( "OutOfMemoryException: Cannot allocate node" );

	} // End catch

} // End Allocate()

template <class ItemType>
bool OrdListClass<ItemType>::rFind( /* In */ KeyType key )	// The key to search for
{
	// If the current position in the tree is not NULL
	if( currPos != NULL )
	{
		// If the key being searched for is less than the key of the node at the current position in the
		//  tree
		if( key < currPos->data.key )
		{
			prevPos = currPos;
			currPos = currPos->left;

			// Recursively search for the key
			return rFind( key );

		} // End if
		// Else if the key being searched for is greater than the key of the node at the current
		//  position in the tree
		else if( key > currPos->data.key )
		{
			prevPos = currPos;
			currPos = currPos->right;

			// Recursively search for the target
			return rFind( key );

		} // End else if

		return true;

	} // End if

	return false;

} // End rFind( KeyType key )

template <class ItemType>
void OrdListClass<ItemType>::rClear( /* In */ node<ItemType>* trav )	// A traversal pointer
{
	// If the traversal pointer is not NULL
	if( trav != NULL )
	{
		// Recursively clear the left subtree
		rClear( trav->left );

		// Recursively clear the right subtree
		rClear( trav->right );

		delete trav;

	} // End if

} //End rClear( node* trav )

template <class ItemType>
bool OrdListClass<ItemType>::rIsEqual
	( /* In */ node<ItemType>* applyingTrav,	// Traversal pointer to the applying object's tree
	  /* In */ node<ItemType>* rtOpTrav )const	// Traversal pointer to to rtOp's tree
{
	// If the applying object's traveersal pointer is not NULL
	if( applyingTrav != NULL )
	{
		// If rtOp's traversal pointer is not NULL and the key of the node pointed to by the applying
		//  object's traversal pointer is equal to the key of the node pointed to by rtOp's traversal
		//  pointer
		if( rtOpTrav != NULL && applyingTrav->data.key == rtOpTrav->data.key )
			// Recursively determine if the left subtree of the node pointed to by the applying object's
			//  traversal pointer is equal to the left subtree of the node pointed to by rtOp's
			//  traversal pointer and if the right subtree of the node pointed to by the applying
			//  object's traversal pointer is equal to the right subtree of the node pointed to by
			//  rtOp's traversal pointer
			return rIsEqual( applyingTrav->left, rtOpTrav->left ) &&
				   rIsEqual( applyingTrav->right, rtOpTrav->right );
			
		return false;

	} // End if
	
	return rtOpTrav == NULL;

} // End rIsEqual( node* applyingTrav, node* rtOpTrav )const

template <class ItemType>
void OrdListClass<ItemType>::rAssign
	( /* In/Out */ node<ItemType>*& applyingTrav,	// Traversal pointer to the applying object's tree
	  /* In */	   node<ItemType>* origTrav)		// Traversal pointer to orig's tree
{
	// If the traversal pointer to orig's tree is not NULL
	if( origTrav != NULL )
	{
		// Dynamically allocate a new node to the applying object's traversal pointer
		applyingTrav = Allocate();

		applyingTrav->data = origTrav->data;

		// Store a deep copy of orig's traversal pointer's left subtree in the applying object's
		//  traversal pointer's left subtree
		rAssign( applyingTrav->left, origTrav->left );

		// Store a deep copy of orig's traversal pointer's right subtree in the applying object's
		//  traversal pointer's right subtree
		rAssign( applyingTrav->right, origTrav->right );

	} // End if
	// Else the traversal pointer to orig's tree is NULL
	else
		applyingTrav = NULL;

} // End rAssign( node*& applyingTrav, node* origTrav)

template <class ItemType>
int OrdListClass<ItemType>::rReturnLength( /* In */ node<ItemType>* trav )const	// A traversal pointer
{
	// If the traversal pointer is not NULL
	if( trav != NULL )
		// Return the sum of one, the number of node in the traversal pointer's left subtree, and the
		//  number of node in the traversal pointer's right subtree
		return 1 + rReturnLength( trav->left ) + rReturnLength( trav->right );

	return 0;

} // End rReturnLength( node* trav )const

template <class ItemType>
void OrdListClass<ItemType>::rPrintScreen
	( /* In */ FunctionType visit,		// A pointer to the function defined by the client which
										//  determines what happens when the traversal visits a node
	  /* In */ node<ItemType>* trav)	// A traversal pointer
{
	// If the traversal pointer is not NULL
	if( trav != NULL )
	{
		// Recursively print the key of each node in the traversal pointer's left subtree to the console
		//  using an in-order traversal
		rPrintScreen( visit, trav->left );

		// Print the key of the traversal pointer to the console
		visit( trav->data );

		// Recursively print the key of each node in the traversal pointer's right subtree to the
		//  console using an in-order traversal
		rPrintScreen( visit, trav->right );

	} // End if

} // End rPrintScreen( FunctionType visit, node* trav)

template <class ItemType>
void OrdListClass<ItemType>::rPrintReverse
	( /* In */ FunctionType visit,		// A pointer to the function defined by the client which
										//  determines what happens when the traversal visits a node
	  /* In */ node<ItemType>* trav )	// A traversal pointer
{
	// If the traversal pointer is not NULL
	if( trav != NULL )
	{
		// Recursively print the key of each node in the traversal pointer's right subtree to the
		//  console using an in-order traversal, starting from the node with the largest key
		rPrintReverse( visit, trav->right );

		// Print the key of the traversal pointer to the console
		visit( trav->data );

		// Recursively print the key of each node in the traversal pointer's left subtree to the console
		//  using an in-order traversal, starting from the node with the largest key
		rPrintReverse( visit, trav->left );

	} // End if

} // End rPrintReverse( FunctionType visit, node* trav )

template <class ItemType>
void OrdListClass<ItemType>::rPrintFile
	( /* In */		FunctionType2 visit,	// A pointer to the function defined by the client which
											//  determines what happens when the traversal visits a node
	  /* In/Out */  ofstream& dout,			// An output file stream variable
	  /* In */		node<ItemType>* trav )	// A traversal pointer
{
	// If the traversal pointer is not NULL
	if( trav != NULL )
	{
		// Print the key of the traversal pointer to the output file
		visit( trav->data, dout );

		// Recursively print the key of each node in the traversal pointer's left subtree to the output
		//  file using a pre-order traversal
		rPrintFile( visit, dout, trav->left );

		// Recursively print the key of each node in the traversal pointer's right subtree to the output
		//  file using a pre-order traversal
		rPrintFile( visit, dout, trav->right );

	} // End if

} // End rPrintFile( FunctionType2 visit, ofstream& dout, node* trav )

template <class ItemType>
void OrdListClass<ItemType>::rFill
	( /* In */	   node<ItemType>* trav,	// A traversal pointer
	  /* In/Out */ ItemType arr[],			// The array to fill
	  /* In */	   int index )				// The index of the array at which to assign a value
{
	// If the index is less than the number of elements in the array
	if( index < MAX_ITEMS )
	{
		// If the traversal pointer is not NULL
		if( trav != NULL )
		{
			arr[ index ] = trav->data;

			// Fill the array with the data in the nodes of the traversal pointer's left subtree
			rFill( trav->left, arr, 2 * index + 1 );

			// Fill the array with the data in the nodes of the traversal pointer's right subtree
			rFill( trav->right, arr, 2 * index + 2 );

		} // End if
		// Else the traversal pointer is NULL
		else
			arr[ index ].key = INT_MAX;

	} // End if

} // End rFill( node* trav, ItemType arr[], int index )

template <class ItemType>
void OrdListClass<ItemType>::rFindParent( /* In */ node<ItemType>* trav )	// A traversal pointer
{
	// If the key of the node at the previous position in the tree is less than the key of the node of
	//  the traversal pointer
	if( prevPos->data.key < trav->data.key )
	{
		// If the previous position in the tree is the traversal pointer's left child
		if( prevPos == trav->left )
			prevPos = trav;
		// Else the previous position in the tree is not the traversal pointer's left child
		else
			rFindParent( trav->left );

	} // End if
	// Else the key of the node at the previous position in the tree is greater than the key of the node
	//  of the traversal pointer
	else
	{
		// If the previous position in the tree is the traversal pointer's right child
		if( prevPos == trav->right )
			prevPos = trav;
		// Else the previous position in the tree is not the traversal pointer's right child
		else
			rFindParent( trav->right );

	} // End else

} // End rFindParent( node* trav )

template <class ItemType>
void OrdListClass<ItemType>::rFillUnion
	( /* In/Out */ OrdListClass<ItemType>& ordUnion,	// The union of the applying object and rtOp
	  /* In */	   node<ItemType>* rtOpTrav )const		// A traversal pointer
{
	// If the traversal pointer does not point to NULL
	if( rtOpTrav != NULL )
	{
		// Fill the list with each item from the left subtree of the node pointed to by rtOpTrav whose
		//  key is not equal to the key of any item already in the list
		rFillUnion( ordUnion, rtOpTrav->left );

		// If the key of the item pointed to by rtOpTrav does not equal the key of any item in the list
		if( !ordUnion.Find( rtOpTrav->data.key ) )
			// Insert the item into the list
			ordUnion.Insert( rtOpTrav->data );

		// Fill the list with each item from the right subtree of the node pointed to by rtOpTrav whose
		//  key is not equal to the key of any item already in the list
		rFillUnion( ordUnion, rtOpTrav->right );

	} // End if

} // End rFillUnion( OrdListClass& ordUnion, node* rtOpTrav )const

template <class ItemType>
void OrdListClass<ItemType>::rCompleteUnion
	( /* In/Out */ OrdListClass<ItemType>& ordUnion,	// List that contains a complete tree
	  /* In/Out */ ItemType arr[],						// Array of items
	  /* In */	   int min,								// Minimum index in range
	  /* In */	   int max )const						// Maximum index in range
{
	// If the minimum index is less than or equal to the maximum index
	if( min <= max )
	{
		int mid = ( max - min ) / 2 + min;	// The index of the item to insert into the list

		// If the key of the item at index mid of the array does not equal the key of any item in the
		//  list
		if( !ordUnion.Find( arr[ mid ].key ) )
			// Insert the item into the list
			ordUnion.Insert( arr[ mid ] );

		// Insert an item from the lower half of the range into the list
		rCompleteUnion( ordUnion, arr, min, mid - 1 );

		// Insert an item from the upper half of the range into the list
		rCompleteUnion( ordUnion, arr, mid + 1, max );

	} // End if

} // End rCompleteUnion( OrdListClass& ordUnion, ItemType arr[], const int& min, const int& max )const

template <class ItemType>
void OrdListClass<ItemType>::rFillArr
	( /* In */ node<ItemType>* trav,		// Pointer to the tree to copy items from
	  /* In/Out */ ItemType arr[],			// Array to be filled
	  /* In */ int& index,					// Index at which to insert an item at
	  /* In */ const int& numVals )const	// Max number of elements in the array
{
	// If the index is less than the maximum number of items that can fit in the array and if trav does
	//  not point to NULL
	if( index < numVals && trav != NULL )
	{
		// Fill the array with the copies of the items in the left subtree of trav
		rFillArr( trav->left, arr, index, numVals );

		arr[ index ] = trav->data;
		index++;

		// Fill the array with the copies of the items in the right subtree of trav
		rFillArr( trav->right, arr, index, numVals );

	} // End if

} // End void rFillArr( node* trav, ItemType arr[], int index, const int& numVals )const