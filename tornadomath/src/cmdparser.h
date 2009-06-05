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
#ifndef CMDPARSER_H
#define CMDPARSER_H

#include "my_string.h"
#include "stackar.h"
#include "tpdefs.h"
/**
@author arnold j noronha
*/
struct commanddefn{
	char *name;
	char *non_param;
	char *param;
	char *param_optional;
	char *gnu_long;	
};

class cmdparser{
	//commanddefn *cmds;
	//commanddefn *cur_cmd;
	String text;
	StringStack components;
	//StringStack 	non_param;
	//StringStack  	paramorder;
	//StringStack  	paramdata;
	//String name;
	
public:
    cmdparser();

    ~cmdparser();
    void set(const char *str);
    const char* find_default(int num);
    const char * find_param(const char*param);
    int  getparamcount();
    const char*  get_command();
    int  get_param_type(char ch);
    char  get_short_name(const char *s);
    commanddefn* find_command(const char *name);
    const char * find(const char *start) ;

protected:
    String  m_cmd;
};

#endif
