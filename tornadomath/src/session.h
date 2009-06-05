/***************************************************************************
                          session  -  description
                             -------------------
    begin                : Tue Oct 19 2004
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
#ifndef SESSION_H
#define SESSION_H
#include "stackar.h"
#include <stdio.h>

typedef StackAr<char*, char*> PSZAR;
void breakup_string(StackAr<char *, char* > &ar, char *str);
 
/**
@author A J Noronha
*/
class Session{
public:

	FILE *out;
	FILE *err;
	FILE *in;
	
public:
    Session();

    ~Session();
    void runcommand(const char *str);

};

#endif
