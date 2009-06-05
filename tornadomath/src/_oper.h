/***************************************************************************
                          _oper.h  -  description
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

#ifndef _OPER_H
#define _OPER_H

#include "var_ar.h"
#include "stackar.h"
#include "tpdefs.h"
#include "expression.h"
#include "_expr.h"
#include "stackar.h"

#include "my_string.h"

/**does an operation between two objects.
(only identifies the operation part and assings it a literal)
creating an object automatically adds to object array.

  *@author A J Noronha
  */
#include "valuestack.h"

class _oper {
     
public: 
	_oper();
	virtual ~_oper();
	/** operator <= (const _oper& ) */

	/** No descriptions */
	virtual int get_variable_count();
	/** Basically just takes howmanyever variables required and puts into postfix*/
	
	/** No descriptions */
	virtual const char* get_code();
	virtual bool  want_save();
	const char* getname();
	char  get_operator_ch();
	
	public:
		//operations
	virtual void eval(ValueStack &eval_stack);
    virtual const char* get_defn();
		
	protected:
	String  name;
	//String  D;   //inline parsing?
	//String  param_defn;
    
    //expression expr;
    
    
    int param_count;
};

extern void operator_setup();



#define DEFOPER(classname, nameext, pc) class _oper_ ## classname  : public _oper{  \
	public: \
	_oper_ ## classname (){ \
		name=#nameext; \
		param_count=pc; \
	} 
	
#define ENDOPER(name) };//__auto_ ## name;

//evaluate function
#define EVAL virtual void eval(ValueStack &values)
///@no-parse

#define FNSINGLE(_name_, fnname) DEFOPER(_name_,_name_,1)        \
EVAL {                                       \
	Value b=values.get_last();           \
	values.remove();                      \
	Value &ret=values.add();             \
                                               \
	if(b.gettype()=='r'){                 \
		ret=fnname (((Value_real*)b.getvalue())->value);\
	}else THROW();                       \
}                                            \
ENDOPER(_name_)	

//Math function styling
#ifdef MATH
#error math already defined. unable to proceed
#endif

#ifdef REAL_IS_DOUBLE
#define MATH(a) a
#else
#define MATH(a) a ## l
#endif


#define FNDOUBLE(_name_, fnname) DEFOPER(_name_,_name_,2)   \
EVAL{  \
	Value b;    \
	b=values.get_last();    \
	values.remove();   \
		Value a;   \
	a=values.get_last();   \
	values.remove();   \
	Value &ret=values.add();    \
 	if(a.gettype()==val_real &&   \
b.gettype()==val_real){   \
		REAL r=fnname(( (Value_real*)(a.getvalue()))->value  \
			,((Value_real*)(b.getvalue()))->value);  \
		ret.settype(val_real);  \
		((Value_real*)(ret.getvalue()))->value=r;  \
} \
	else \
{  \
	 	perror(#_name_ " : unsupported operation\n"); \
		THROW(); \
	}	\
}  \
ENDOPER(_name_)  ;



#define GET_USER_COMMAND(a,b) \
	values.add(a); \
	values.add(b); \
	String s; \
	s+=getname(); \
	s+=a.gettype(); \
	s+=b.gettype(); \
	_oper* __p=getworld()->oper_get(s); \
	if(!__p) THROW(); \
	else { __p->eval(values); \
	    }
	
#endif


