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
#ifndef _OPER_EXPR_H
#define _OPER_EXPR_H

#include "_oper.h"

/**
@author arnold j noronha
*/
class _oper_expr : public _oper
{
public:
	//expression expr;
	_expr exp;
	String defn;
	
    _oper_expr(const char *name, const char *_defn);

    virtual ~_oper_expr();
    void eval(ValueStack & terms);
    void _init_eval(ValueStack &);
    bool set(const char *_name,  const char *defn);
    virtual bool  want_save();
    virtual const char* get_defn();
    friend class eqn_solver;

};

#endif
