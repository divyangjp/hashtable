/**
* File Name 	: use_hashtable.cpp
* Functionality : This is advanced dictionary project. It reads text file with word and defintions
		  stores them in hashtable. Lookup methods are provided to find definition of the
		  words. Hashtables provide very fast lookup of O(1). 
		  This is working example but not production level code. So if you're thinking to 
		  use this in production environments, tighten the screws and add needed nut-bolts.

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


#include <fstream>
#include <algorithm>
#include "hashtable.h"
#include "smart_ptr.h"

using namespace std;

int main ()
{
	SPtr<D_HashTable> ptrSimHT( new D_HashTable(30) );	
    string word, definition, tmpstr;
	string substr = "@@@@";
	int nextwordcount = 0;

	ifstream infile;
	infile.open ("./data-dict/smt.txt");
	if(!infile)
	{
		cout << "Could not open ./data-dict/smt.txt" << endl;
		exit(1);
	}

        while(!infile.eof()) // To get you all the lines.
        {
        	getline(infile, tmpstr); // Saves the line in tmpstr.
			if( (tmpstr.find(substr) == string::npos) && (tmpstr!=""))
			{
				nextwordcount++;
				if( nextwordcount == 1 )
				{
					word = tmpstr;
				}
				else if( nextwordcount == 2)
				{
					ptrSimHT->insert_data( word , definition );
					cout << "inserted word =" << word << endl;
					word = tmpstr;
					definition = "";
					nextwordcount = 1;
				}
			}
			else
			{
				//tmpstr.replace( tmpstr.begin(), tmpstr.end(), '@@@@', ' ' );
				tmpstr.replace(0, 4, " ");
				definition = definition + tmpstr;
			}
			//ptrSimHT->insert_data( word );

			//if( word.empty() )
				//cout << "Empty String" << endl;
			    //cout<< word << endl; // Prints our word.
        }

	//insert last word of the file. It's not handled in while loop.

	ptrSimHT->insert_data( word , definition );

	cout << endl;
	cout << "*********************************************************" << endl;
	cout <<	"	Test Case 1 : Lookup words 			  " << endl; 
	cout << "*********************************************************" << endl;

	infile.clear();
	infile.seekg(0, ios::beg);
	
	string testword;

	while(!infile.eof())
	{
		testword = "";
		getline( infile, testword , '\n');
		if( (testword.find(substr) == string::npos) && (testword!="") )
		{
			cout << testword << "found at position " << ptrSimHT->lookup(testword) << endl;
			cout << "Definition of word " << testword << ":" << ptrSimHT->lookupdef( testword ) << endl;
			cout << endl;
		}	
	}

	cout << "Word 'Divyang' find. Return code = " << ptrSimHT->lookup("Divyang") << endl;

	cout << endl << "*************** Pretty Print of HT ******************" << endl << endl;
	ptrSimHT->prettyprintHT();

	//I'm using smart-ptr here. So no need to call delete.. :)
	//delete ptrSimHT;
	infile.close();
}

