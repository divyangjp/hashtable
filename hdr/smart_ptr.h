/**
* File Name     : smart_ptr.h
* Functionality : Referenc counting templated Auto ptr
		  implementation

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

#ifndef _SMART_PTR_H
#define _SMART_PTR_H

#include <iostream>
#include <exception>

using namespace std;

class RefCount
{
	public:
		RefCount():iCount_(0)
		{ 
		#ifdef DEBUG
			cout << "RefCount Ctor" << endl;
		#endif
		}
		~RefCount(){};

		void refIncrease()
		{ 
			iCount_++; 
		#ifdef DEBUG	
			cout << iCount_ << endl;
		#endif
		}
		void refDecrease()
		{ 
			iCount_--; 
		#ifdef DEBUG	
			cout << iCount_ << endl;
		#endif
		}
		int  getCount() { return iCount_; }
	private:
		int iCount_;
};


template < class T >
class SPtr
{
	public:
		SPtr() throw( bad_alloc ) :  TP_( NULL ), rc_(0) 
		{
			rc_ = new RefCount();
			rc_->refIncrease();
		}
		SPtr( T* TP ) throw( bad_alloc ) : TP_( TP ) 
		{
			rc_ = new RefCount();
			rc_->refIncrease();
		}
		SPtr( const SPtr& spobj )
		{
			TP_ = spobj.TP_;
			rc_ = spobj.rc_;
			rc_->refIncrease();
		}
		SPtr& operator=( const SPtr& spobj )
		{
			TP_ = spobj.TP_;
			rc_ = spobj.rc_;
			rc_->refIncrease();
			return *this;
		}

		friend bool operator!( const SPtr& spobj )
		{
			return ( spobj.TP_ == NULL );
		}
		
		~SPtr()
		{
			rc_->refDecrease();
			if( rc_->getCount() == 0 )
			{
				delete TP_;
				delete rc_;
			}
		}

		T& operator*()
		{
			return *TP_;
		}

		T* operator->()
		{
			return TP_;
		}

	private:
		T* 		TP_;
		RefCount*	rc_;	
};



#endif		// _SMART_PTR_H


