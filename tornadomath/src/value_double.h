/***************************************************************************
                          value_double  -  description
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
#ifndef VALUE_DOUBLE_H
#define VALUE_DOUBLE_H

#include "value_normal.h"
#include <fstream>
using namespace std;

typedef char val_type;
#define val_int 'n'
#define val_real 'r'
#define val_vector 'v'
#define val_complex 'c'


#ifdef REAL_IS_DOUBLE
typedef double REAL;
#else
typedef long double REAL;
#endif

REAL str_to_real(const char *);
char * real_to_str(REAL r, char *a, int maxsize);
/**
@author A J Noronha
*/
class Value_real : public  Value_Normal
{
public:
	REAL value;
	
public:

   virtual char gettype(){ return val_real; }
    virtual void operator=(Value_Normal &p);
     Value_real(REAL re);
     Value_real();
    virtual void show();
     virtual void read_binary(ifstream &f);
    virtual void write_binary(ofstream &f);

};

class Value_complex: public  Value_Normal
{
public:
	REAL real;
	REAL complex;
public:
	virtual char gettype() { return val_complex; }
    	virtual void show();
	 virtual void read_binary(ifstream &f);
    virtual void write_binary(ofstream &f);
};

class Value_vector: public  Value_Normal
{
	
public:
REAL x,y,z;
	virtual char gettype(){ return val_vector; }
    void operator=(Value_Normal &p);
    virtual void show();
     virtual void read_binary(ifstream &f);
    virtual void write_binary(ofstream &f);
};

class Value_int: public  Value_Normal
{
public:
	int num;
public:
	virtual char gettype(){ return val_int; } 
	     virtual void read_binary(ifstream &f);
    virtual void write_binary(ofstream &f);
};




#endif
