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
#ifndef VALUE_NORMAL_H
#define VALUE_NORMAL_H

#include <fstream>
using namespace std;
/**
@author A J Noronha
*/
class Value_Normal{

public:
    Value_Normal();

    virtual ~Value_Normal();
    
    virtual char gettype()=0;
    virtual void operator=(Value_Normal &p);
    virtual void show();
    virtual void read_binary(ifstream &f) = 0;
    virtual void write_binary(ofstream &f) = 0;
   
    
    
};

Value_Normal* _value_create(char type);
#endif
