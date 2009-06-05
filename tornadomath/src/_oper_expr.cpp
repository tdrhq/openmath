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
#include "_oper_expr.h"
#include "world.h"
#include <cstdlib>
using namespace std;


_oper_expr::_oper_expr(const char *name, const char *defn)
 : _oper()
{
	set(name, defn);
}


_oper_expr::~_oper_expr()
{
}


void _oper_expr::eval(ValueStack &terms)
{
    _init_eval(terms);
    Value val;
    exp.eval(val);
    terms.add(val);
}

void _oper_expr::_init_eval(ValueStack &terms)
{
                                         
	
	int params=exp.get_param_count();
	for(int i=params-1; i>=0; i--){
		exp.pargAr[i]=terms.get_last();
		terms.remove();
	}
	
		
}

bool _oper_expr::set(const char *_name,  const char *_defn)
{
        defn=_defn;
	if(!exp.build( _defn)) return false;
	name=_name;
       	return true;
    
}

bool  _oper_expr::want_save()
{
    	return true;
}

const char* _oper_expr::get_defn()
{
    	return defn;
}
