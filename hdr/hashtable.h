/**
* File Name 	: hashtable.h
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



#include <iostream>
#include <string>
#include "linklistdev.h"

class D_HashTable
{
	public:
		D_HashTable( int size );
		~D_HashTable();

		void 			insert_data( string word , string definition );
		int 			lookup( string word );
		string			lookupdef( string word );
		void			prettyprintHT();

		static int 		hashFunction( string word, int size );

	private:
		int 			size_;
		linklist<string>** 	lookupTable;	
};
