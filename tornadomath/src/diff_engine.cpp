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
 /*
 i am going to use this area to develop an algorithm for differentiating.
 
 Suppose i got
 %1 b + c 'log
 
 Obviously, the fn is log(%1+b,c);
 now diff of this is (1/(%1+b))/ln c
 i.e. 
 	1 %1 b + c 'ln /
	
 should i start with 'log?
 ok, log has a diff given by, log(f,g)=ln(f)/ln(g)
   => log'(f,g)=ln'(f)f'ln(g)-ln'(g)g'ln(f))
                ----------------------------
			ln(g)*ln(g)
 		f'/f-log(f,g)g'/g
	      =	-----------------
	      		ln(g)
	      =f D f / f g log g D g / - g ln /      ( ... phew)
	      
   here's my algo: 
   	everytime i get a var, i dump it into a stacks
	when i get an operator,
		i take
	 
 
 */


#include "diff_engine.h"
#include "expression.h"

diff_engine::diff_engine()
{
}


diff_engine::~diff_engine()
{
}




/*!
    \fn diff_engine::differentiate(StringStack &function,StringStack &result)
 */
bool  diff_engine::differentiate(StringStack &function,StringStack &result)
{
    	//basic principle:
	//d/dx f(g(x))=g'(x).f'(g(x))
	//in postfix parlance this is :
	// for every fn i get diff it and store the diff in a stack,
	
	//pull_out_and_diff(
	return true;
}


/*!
    \fn diff_engine::add_function(const char *name, const char* diff)
 */
void diff_engine::add_function(const char *name, const char* diff)
{
    	connector &cn=connects.add();
	cn.name=name;
	StringStack temp;
	convert_to_postfix(temp, diff);
	reverse_stack(temp, cn.diff);
	
	cn.diff.debug_dump("diff_engine_postfix");
	
}
