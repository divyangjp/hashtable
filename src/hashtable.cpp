/**
* File Name 	: hashtable.cpp
* Functionality :

* Copyright (C) 2012 Divyang Patel

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include <string.h>
#include "hashtable.h"

using namespace std;


D_HashTable::D_HashTable( int size )
{
	size_ = size;
	lookupTable = new linklist<string>*[size_];
	
	// Initialize lookupTable values to NULL.
	// This is important. Why? You'll see.

	for( int i = 0; i < size_ ; i++ )
	{
		lookupTable[i] = NULL;
	}
}

D_HashTable::~D_HashTable()
{
#ifdef DEBUG
	cout << endl << "D_HashTable dtor called" << endl;

	cout << "First freeing up memory of linked lists" << endl;
#endif
	for( int i = 0 ; i < size_ ; i++ )
	{
		linklist<string>* ptrList = lookupTable[i];
		delete ptrList;
	}

#ifdef DEBUG
	cout << "Now finally delete the lookupTable" << endl;
#endif

	delete[] lookupTable;

#ifdef DEBUG
	cout << "Destruction complete" << endl;
#endif

}

void D_HashTable::insert_data( string word , string definition )
{
	int bucketnum;
	bucketnum = D_HashTable::hashFunction( word , size_);


	linklist<string>* ptrList;

	// If at the bucketnum of lookupTable is not NULL,
	// then the linklist is present. Use it to insert word.

	if( lookupTable[bucketnum] != NULL )
	{
		ptrList = lookupTable[bucketnum];

		int wordPresent = ptrList->find( word );

		// find returns 0 if the element is not present.
		// So if wordPresent is 0 then add the word to the list.
		if( wordPresent == 0 )
		{
			ptrList->append( word , definition );
		}
	}

	// If it's NULL. Create new linklist. Store pointer of that list
	// in the lookupTable[bucketnum]. Add word to the list.

	else
	{
		ptrList = new linklist<string>;
		lookupTable[bucketnum] = ptrList;
		ptrList->append( word , definition );
	}

#ifdef DEBUG
	cout << "'" << word << "'" << " inserted at position " << bucketnum << endl;
#endif

}


int D_HashTable::lookup( string word )
{
	int bucketnum;

	bucketnum = D_HashTable::hashFunction( word , size_);

	linklist<string>* ptrList;
	ptrList = lookupTable[bucketnum];

	// If ptrList is NULL means there is no list of words
	// at that bucketnum. So word is not present. Return -1.

	if( ptrList == NULL )
	{
		return -1;
	}

	// If ptrList is not NULL, so we search for the word in 
	// the list present. If we can find the word return bucketnum.
	// If word not found in the list, return -1

	else
	{
		int wordPresent = ptrList->find( word );

		if( wordPresent == 0 )		// word not found in list. Return -1
		{
			return -1;
		}
		else				// word found in list. Return bucketnum
		{
			return bucketnum;
		}
	
	}

	//return -100;			// Control should never reach here...
}


void D_HashTable::prettyprintHT()
{
	for( int i = 0 ; i < size_ ; i++ )
	{
		linklist<string>* ptrList = lookupTable[i];
	
		cout << "Bucket-" << i << "  -->  ";
		if(ptrList)
		{
			ptrList->print();
		}
		else
		{
			cout << endl;
		}
	}
}

int D_HashTable::hashFunction( string word, int size )
{
	int wordlength = word.length();
   	char ch[wordlength];
   	//ch = word.toCharArray();
	memcpy( ch, word.data(), wordlength );

   	unsigned int i, sum;
   	for (sum=0, i=0; i < word.length(); i++)
     		sum += ch[i];

   	return sum % size;	
}


string D_HashTable::lookupdef( string word )
{
	int bucketnum;
	string definition;

    bucketnum = D_HashTable::hashFunction( word , size_);

    linklist<string>* ptrList;
    ptrList = lookupTable[bucketnum];

    // If ptrList is NULL means there is no list of words
    // at that bucketnum. So word is not present. Return -1.

    if( ptrList == NULL )
    {
    	return NULL;
    }

    // If ptrList is not NULL, so we search for the word in
    // the list present. If we can find the word return bucketnum.
    // If word not found in the list, return -1

    else
    {
    	int wordPresent = ptrList->find( word );

        if( wordPresent == 0 )          // word not found in list. Return -1
        {
            return NULL;
        }
        else                            // word found in list. Return bucketnum
        {
			definition = ptrList->definitionOf( word );
        	return definition;
        }

    }

    //return -100;                  // Control should never reach here...

}
