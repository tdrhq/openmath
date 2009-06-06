/***************************************************************************
                          _expr.cpp  -  description
                             -------------------
    begin                : Fri Oct 8 2004
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

#include "_expr.h"
#include <ctype.h>
#include "world.h"
#include "expression.h"
#include <stdlib.h>


_expr::_expr(){
	pargAr=NULL;
	param_count=0;
	terms=NULL;
}
_expr::~_expr(){
	if(pargAr) delete[] pargAr;
	if(terms) delete[] terms;
}


/*!
    \fn _expr::create(expression* expr)
 */
void _expr::create(expression* expr)
{
    /// @todo implement me
    
    
}

term get_term_from_literal(const char *name){
	Value *val=getworld()->var_get(name);
	term ret;
	ret.type=term::type_val;
	ret.val.pVal=val;
	return ret;
}


/*!
    \fn _expr::convert_text_to_term(const char *str)
 */
term _expr::convert_text_to_term(const char *str)
{
    /// @todo implement me
    if(str[0]=='\'')
    	return get_term_from_fn(str+1);
    else if(isalpha(str[0]) || str[0]=='_' )
    	return get_term_from_literal(str);
    else if(str[0]=='%')  {
    	return get_term_from_arg( &str[1]) ;
    }
    else if(isdigit(str[0]))
    	return create_term_from_constant(str);
    else 
    	return get_term_from_oper(str[0]);
}


/*!
    \fn _expr::get_term_from_fn(const char *name)
 */
term _expr::get_term_from_fn(const char *name)
{
    /// @todo implement me
    term ret;
    ret.type=term::type_oper;
    ret.val.oper=getworld()->oper_get(name);
    assert(ret.val.oper);
    if(!ret.val.oper) THROW();
    
   
    return ret;
}



term  _expr::create_term_from_constant(const char *id)
{
    	term ret;
    	ret.type=term::type_constant;
    	ret.val.real=str_to_real(id);
    	return ret;
}

void _expr::build_from_postfix(POSTFIX &postfix)
{
	POSITION pos=postfix.get_top_position();
    	for(int i=0; i<term_count; i++, pos=postfix.get_next(pos)){
		assert(pos);
    		terms[i]=convert_text_to_term(postfix.get(pos));
	}
	
}

term  _expr::get_term_from_oper(char ch)
{
	String name;
	name="oper";
	name+=ch;
	
    	return get_term_from_fn(name);
}



bool _expr::build(expression &expr)
{
	//one. resize the arrays
	param_count= expr.get_param_count();
	if(param_count) pargAr=new Value[param_count];
	else pargAr=NULL;

	term_count= expr.m_postfix.getcount();
	if(term_count)
		terms=new term[term_count];
	TRY{
		build_from_postfix(expr.m_postfix);
	}CATCH( ...){
		return false;
	}
	
	return  true;
}


/*!
    \fn _expr::get_term_from_arg(const char *str)
 */
term _expr::get_term_from_arg(const char *str)
{
	assert(strlen(str));
	int i=atoi(str);
	i--;
	assert(i>=0 && i<param_count);
	if(i<0 || i>param_count) THROW();
	term ret;
	ret.type=term::type_val;
	ret.val.pVal=&pargAr[i];
	return ret;
	
}


/*!
    \fn _expr::eval(Value &result)
 */
bool _expr::eval(Value &result)
{
	ValueStack  valstack;

    	for(int i=0; i<term_count; i++){
	
        	//const char*s=m_postfix.get(pos);
		term &t=terms[i];
		
		if(t.type==term::type_val)
		{
			//ValueRef vref(getworld()->var_get(s));			
			valstack.add(t.val.pVal);
		}
		else if (t.type==term::type_constant){
			valstack.add()=(t.val.real);		
		}
		else {
			assert(t.type==term::type_oper);  //have i added anything new
			_oper* p=t.val.oper;
			
			TRY{
				p->eval(valstack) ;
			} CATCH( ... ){
				cout<<"ERROR: evaluation of "<<p->getname()<<" failed.\n";
				result=0;
				return false;
			}
		}
	}
	
	result=valstack.get_last();
	valstack.remove();
	return true;
}


/*!
    \fn _expr::build(const char *str)
 */
bool _expr::build(const char *str)
{
	expression expr;
	
	expr.set(str);
	return build(expr);
	
}


