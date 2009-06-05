/***************************************************************************
                          my_string  -  description
                             -------------------
    begin                : Fri Oct 15 2004
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
#include "my_string.h"
#include <string.h>
String::String(){
	init();
}
String::~String(){
	assert(buf);
	
	if(buf)
		delete/*[_get_buffer_size()]*/ buf;
	
	
}

void String::operator+=(char ch)
{
    /// @todo implement me
    int len=strlen(buf);
    if(len+2>_get_buffer_size())
    	setsize(len+2);
    buf[len]=ch;
    
    buf[len+1]='\0';
}
bool String::operator==(const char *str)
{
	return (strcmp(buf, str)==0);
}

void String::_set_buffer(int size)
{
	assert(size<4096);  //crash course!!!
	
	char *pnew=new char[size];
	if(size>strlen(buf))
		strcpy(pnew, buf);
	else 
		pnew[0]='\0';
	_size=size;
	delete buf;
	buf=pnew;
}

void String::operator=(char ch)
{
    /// @todo implement me
    if(_get_buffer_size()<2) setsize(2);
    buf[0]=ch;
    buf[1]='\0';
    
    
}
bool strcmp_nc(const char *text);
int String::getLength()
{ 
	return strlen(buf); 
}
void String::operator=(const char *text){
	int len=strlen(text)+1;
	if(len>_get_buffer_size())
		setsize(len);
	strcpy(buf, text);
}
	
String String::operator+(const char*text){
	String ret;
	ret.setsize(getLength()+strlen(text)+2);
	ret=buf;
	strcat(ret.buf, text);
	return ret;
}

void String::operator+=(const char*text){
	setsize(getLength()+strlen(text)+1);
	strcat(buf, text);
}

 String::String(String &str)
{
    /// @todo implement me
    buf=strdup(str.buf);
    _size=strlen(str.buf)+1;
    
}

void String::init()
{
    
    	buf=new char [4];
	_size=4;
	buf[0]='\0';
}

 String::String(const char *str)
{
    	init();
	*this=str;
	
}

bool String::empty()
{
   	return (buf[0]=='\0');
}


/*!
    \fn String::operator[](int n)
 */
const char & String::operator[](int n)
{
	return buf[n];
}


/*!
    \fn String::mid(int pos)
 */
const char * String::mid(int pos)
{
	return &buf[pos];
}
