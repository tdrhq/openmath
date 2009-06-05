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
#include "valuestack.h"

ValueStack::ValueStack()
{
}


ValueStack::~ValueStack()
{
}




/*!
    \fn ValueStack::add(value &val)
 */
Value& ValueStack::add(Value &val)
{
    	add()=val;
	return *(valstack.get_last().pval);
}


/*!
    \fn ValueStack::get_last()
 */
Value& ValueStack::get_last()
{
    	return *valstack.get_last().pval;
}


/*!
    \fn ValueStack::add(Value *pval)
 */
void ValueStack::add(Value *pval)
{
   	valstack.add().pval   =pval;
	valstack.get_last().isref=true;
}




/*!
    \fn ValueStack::add()
 */
Value& ValueStack::add()
{
    	valstack.add().pval=new Value;
	return get_last();
}


/*!
    \fn ValueStack::remove()
 */
void ValueStack::remove()
{
    	valstack.remove();
}


/*!
    \fn ValueStack::getcount()
 */
int ValueStack::getcount()
{
    	return valstack.getcount();
}


/*!
    \fn ValueStack::is_last_ref()
 */
bool ValueStack::is_last_ref()
{
   	return valstack.get_last().isref;
}
