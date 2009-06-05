/***************************************************************************
 *   Copyright (C) 2004 by arnold j noronha                                *
 *   arn_2000@rediffmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef VALUESTACK_H
#define VALUESTACK_H


#include "stackar.h"
#include "value.h"

/**
@author arnold j noronha
*/
class ValueStack{
	class _stack{
	public:
		Value *pval;
		bool   isref;
		_stack(){
			pval=false;
			isref=false;
		}
		
		~_stack(){
			if(!isref) delete pval;
		}
	};
	
	StackAr<_stack,  _stack&> valstack;
	
public:
    ValueStack();

    ~ValueStack();
    Value& add(Value &val);
    Value& get_last();
    void add(Value *pval);

    Value& add();
    void remove();
    int getcount();
    bool is_last_ref();

};

#endif
