/***************************************************************************
                          expression.h  -  description
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

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "_expr.h"
#include "stackar.h"
#include "my_string.h"
#include "tpdefs.h"

	
	
extern void reverse_stack(StringStack &from, StringStack &to);

/**
  *@author A J Noronha
  */
inline bool isliteralchar(char ch){
       return (isalpha(ch) || ch=='_');
}
inline bool isconst(const char* str){
	if(isdigit(*str)) return true;
	if(*str!='-') return false;
	/*else, ie if there's a minus sign*/ 
	if(isdigit(str[1])) return true;
	return false;
}

  //purpose: only to hold the alphabetical function defn.
class expression {
        String str;
	
	
	POSTFIX m_postfix;
        //_expr *expr;  //every expression is related to the postfix at load time.
public: 
	void convert_to_components(COMPONENTAR &component); 
	expression();
	void convert_to_postfix(POSTFIX &pos);
	~expression();
  	void set(const char *str);
  	/** No descriptions */
  	
    	Value eval(Value &ret);
 protected:
 
  	
  	
  public:
    	int  get_param_count();
	
	friend class _expr;
};

#endif
