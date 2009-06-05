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
#include "value_double.h"
#include <assert.h>
#include <iostream>
using namespace std;

REAL str_to_real(const char *str)
{
	REAL old=0;
	
	REAL ret=0;
	REAL tmp=1;
	bool bdec=false;
	for (int i=0; *str!=0 && i<18; str++, i++){
		if(!isdigit(*str) && (bdec &&*str!='.')) return old;
		int dec=  *str-'0'   ;
		if(!bdec){
			if(*str=='.') {
				bdec=true;
				continue;
			}
			
			ret*=10;
			ret+=dec;
		}
		else {
			tmp/=10;
			ret+=tmp*(*str-'0');
		}
		
		if(old>=ret && old!=0)
			return old;
		
		old=ret;
	}
	return old;
}

char * real_to_str(REAL r, char *a, int maxsize)
{
	//long long whole=(long long) r;
	//long long mult=1;
	//while(mult<r) mult*=10;
	
	return NULL;
}

void Value_real::operator=(Value_Normal &p)
{
	assert(p.gettype()==gettype());
	
    	value=((Value_real*)&p)->value;
    
}

void Value_vector::operator=(Value_Normal &p)
{
    assert(p.gettype()==gettype());
    Value_vector *v=(Value_vector*)&p;
    x=v->x;
    y=v->y;
    z=v->z;
    
}

 Value_real::Value_real(REAL re)
{
   	value=re;
	
}

 Value_real::Value_real()
{
    /// @todo implement me
}

void Value_real::show()
{
    	cout<<value;
}

void Value_vector::show()
{
    	cout<<"["<<x<<","<<y<<","<<z<<"]";
}

void Value_complex::show()
{
    /// @todo implement me
}

void Value_real::read_binary(ifstream &f)
{
    	f.read((char*)   &value, sizeof(value));
}

void Value_real::write_binary(ofstream &f)
{
    	f.write((char*)   &value, sizeof(value));    
}

void Value_vector::read_binary(ifstream &f)
{
    	f.read((char*)   &x, sizeof(x));   	
    	f.read((char*)   &y, sizeof(y));   	
    	f.read((char*)   &z, sizeof(z));   	
}

void Value_vector::write_binary(ofstream &f)
{
    	f.write((char*)   &x, sizeof(x));   	
    	f.write((char*)   &y, sizeof(y));   	
    	f.write((char*)   &z, sizeof(z));
}
void Value_complex::read_binary(ifstream &f)
{
        f.read((char*)   &real, sizeof(real));   	
    	f.read((char*)   &complex, sizeof(complex));   	

}

void Value_complex::write_binary(ofstream &f)
{
      	f.write((char*)   &real, sizeof(real));   	
    	f.write ((char*)   &complex, sizeof(complex));   	

}

void Value_int::read_binary(ifstream &f)
{
        f.read((char*)   &num, sizeof(num));
}

void Value_int::write_binary(ofstream &f)
{
       	f.write((char*)   &num, sizeof(num));
}
