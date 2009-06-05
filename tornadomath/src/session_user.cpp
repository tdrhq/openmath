/***************************************************************************
                          session_user  -  description
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
#include "session_user.h"

Session_user::Session_user()
 : Session()
{
	char buf[4096];
	for(;;){
		cout<<"# ";
		cin.getline(buf,4096);
		
		runcommand(buf);
	}
}


Session_user::~Session_user()
{
}


