/***************************************************************************
                          value_normal  -  description
                             -------------------
    begin                : Sat Oct 16 2004
    copyright            : (C) 2004 by A J Noronha
    email                : arn_2000@rediffmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "value_normal.h"
#include "dbgapi.h"
#include "value.h"
Value_Normal* _value_create(char type)
{
	switch(type){
	case 'r': return new Value_real;
	case 'v': return new Value_vector;
	case 'c': return new Value_complex;
	case 'n': return new Value_int;
	default:
	assert(false);
	
	THROW();
	return NULL;
	}
	
}


Value_Normal::Value_Normal()
{
}

Value_Normal::~Value_Normal()
{
}

void Value_Normal::operator=(Value_Normal &p)
{
    assert(false);
    
}

void Value_Normal::show()
{
    /// @todo implement me
}
