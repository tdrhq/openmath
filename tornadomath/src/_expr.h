/***************************************************************************
                          _expr.h  -  description
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

#ifndef _EXPR_H
#define _EXPR_H
#include "var_ar.h"
#include "expression.h"
#include "_expr.h"
#include "my_string.h"

inline bool isnum(char ch){ if(ch>='0' && ch<='9') return true; 
else return false;
}


//class _expr_term{
//public:
//        union {
//                VALUE val;
//                _oper fn;
//        } term;
//
//        enum { EXPTYPE_VAL, EXPTYPE_OPER } type;
//};

        

/**This does the actual computation works
  *@author A J Noronha
  */
class expression;

#define term TERM
class term{
public:	
	
		//Value_real constant;
		union{
		REAL real;
		Value *pVal;
		_oper *oper;
		} val;
	term(){
		type=type_oper;
		val.oper=NULL;
	}
	
	operator Value_real()
	{
		return Value_real(val.real);
	}
		
	enum { type_constant, type_val, type_oper } type;
};
		
class _expr {
	term* terms;
	int   term_count;
	Value *pargAr;
	//Value *pcnstAr;
		
public:
	_expr();
	~_expr();
    void create(expression* expr);
    term convert_text_to_term(const char *str);
    term get_term_from_fn(const char *name);
    term get_term_from_var(const char *id);
    term  create_term_from_constant(const char *id);
    void build_from_postfix(POSTFIX &postfix);
    term  get_term_from_oper(char ch);
    bool build(expression &expr);
    term get_term_from_arg(const char *str);

    /*!
        \fn _expr::get_param_count()
     */
    
protected:
	int param_count;
public:
	inline int get_param_count()
    	{
		return param_count;
    	}
    bool eval(Value &result);
    bool build(const char *str);

    friend class _oper_expr;
    friend class eqn_solver;
};
#undef TERM 
#endif
