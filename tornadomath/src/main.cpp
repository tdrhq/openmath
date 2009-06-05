/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Fri Oct  8 19:58:32 EDT 2004
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
#include <iostream>
#include <stdlib.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif



#include "world.h"

using namespace std;

#include "gt_lib.h"
#include "session_user.h"
int main(int argc, char *argv[])
{
  cout << gettext("openMath Beta, Release 0.1.2 Jan-2005") << endl;
  cout << gettext("(c) 2004-2005 A J Noronha. ")<<endl;
  cout << gettext("You are free to redistribute or modifu this program under the\n"
  	  "the terms of the GNU General Public License version 2.0\n\n");

  cout<<"Restoring previous session ... ";
  cout.flush();
  
  if(!getworld()->load(PREV_SESSION)){
  	cout<<"failed.\n";
	cout<<"Loading default session ... ";
	if(getworld()->load(AUTO_SESSION))
		cout<<" okay. \n";
	else cout<<" failed. \n";
  }
  else cout<<" okay, use 'clean' to revert.\n";
  
			
  Session_user sess;
  
  return EXIT_SUCCESS;
}
