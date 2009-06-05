/***************************************************************************
                          world  -  description
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
#ifndef WORLD_H
#define WORLD_H
#include "_oper.h"
#include "tpdefs.h"
#include "_oper_expr.h"

 #include <fstream>
 using namespace std;
 
 //filenames, where sessions are stored.
 #define PREV_SESSION "PREVSESS"
 #define AUTO_SESSION "AUTOSESS"
 
/**
@author A J Noronha
*/

class World{
	int temp_count;
	
	class _map_var{
		public:
		String name;
		Value val;
	};

	StackAr<_oper*, _oper*>   oper_ar;  //all the opers of the program.
	StackAr<_map_var, _map_var>   var_ar;
	
public:
    World();

    ~World();
    
    _oper* oper_get(const char *name);
    void oper_add(_oper* oper);
    void oper_add(const char* name, const char *defn);
    TERM  get_term_from_literal(char ch);
    TERM get_term_from_varid(const char *str);
  
    Value* __var_find_only(const char *name);
    Value* var_get(const char *name);

private:
    Value* __var_force_add(const char *name);
public:
    Value* var_get_temp(REAL value);
    void oper_showall();
    bool save(const char * file);
    bool load(const char * file);
    bool clean(int n);
    bool  oper_remove(_oper_expr* p);
};

World * getworld(); 
#endif
