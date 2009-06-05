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
#include "value.h"

Value::Value()
{
    	init();
}
Value::~Value()
{
	destroy();
		
}
char  Value::gettype()
{
    /// @todo implement me
    return pvalue->gettype();
}
void Value::settype(char type)
{
   if(gettype()!=type){
   	pvalue=_value_create(type);
   }
}
void Value::operator=(Value &val)
{
    	createfrom(val);
}
void Value::operator=(REAL real)
{
    	settype(val_real);
	((Value_real*) pvalue)->value=real;
}
void Value::show()
{
	pvalue->show();
	
}
 Value::Value(Value &val)
{
	pvalue=new Value_real;
	*this=val;	
}
void Value::createfrom(Value &b)
{
      	settype(b.gettype());
    	(*pvalue)=*(b.pvalue);/// @todo implement me
}
void Value::createfrom(Value *b)
{
	createfrom(*b);
}
void Value::destroy()
{
    	delete pvalue;
}
void Value::init()
{
    	pvalue=new Value_real;
}



/*!
    \fn Value::read_binary(ifstream &f)
 */
void Value::read_binary(ifstream &f)
{
	val_type ch;
	f.read((char*) &ch, sizeof(ch));
	settype(ch);
	pvalue->read_binary(f);
}


/*!
    \fn Value::write_binary(ofstream &f)
 */
void Value::write_binary(ofstream &f)
{
 	val_type ch=gettype();
	f.write((char*)&ch, sizeof(ch));
	pvalue->write_binary(f);   
}
