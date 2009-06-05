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
#include "cmdparser.h"

//param types
#define  NOPARAM 0
#define  OPTIONAL 1
#define  NONOPTIONAL

//no params mean just one param!
bool breakup(const char *str, StringStack &compo){
	String cur;
	const char *ch=str;

	while(*ch==' ' && *ch) ch++;
	while(*ch){
		cur="";
		int leftcnt=0;
		for(; *ch; ch++){
			if(*ch=='(') leftcnt++;
			else if(*ch==')') leftcnt--;
			else if(*ch==' '){
				if(leftcnt<=0) break;
			}
			if(leftcnt<0) return false;
			cur+=*ch;
		}
		while(*ch==' ' && *ch) ch++;
		compo.add_end(cur);
		if(!*ch) break;
		

	}
	
	return true;
		
}

//cool ... now let me separate the different types...

cmdparser::cmdparser()
{
}


cmdparser::~cmdparser()
{
}



String getnext(const char * &str){
	int ct=0;
	String ret;
	while(*str==' '){
		if(*str==0)	break;
		str++;
	}
	while(*str!=0 && *str!=' '){
		if(*str=='(') ct++;
		else if(*str==')') ct--;
		if(ct<0) THROW();
		ret+=*str;
		str++;
	}
	if(ct!=0) THROW();
	return ret;
}

bool isattrib(const char* param){
	return (param[0]=='-')	;
} 
/*!     
    \fn cmdparser::set(const char *str)
 */
void cmdparser::set(const char *str)
{
m_cmd="";
	text=str;
	breakup(str, components);
        components.debug_dump("cmdparser");
	if(components.getcount()>=1) m_cmd=components.get_last();
	
	/*text=str;
	non_param.removeall();
	paramdata.removeall();
	paramorder.removeall();
	
	//fine now what?
	const char *p=text;
	m_cmd=getnext(p);
	if(m_cmd.empty())	return;
	bool last_attrib=false;
	String cur;
	for(;;){ 	
		cur=getnext(p);
		if(cur.empty()) break;
		if(isattrib(cur)){
			if(last_attrib) paramorder.add("");
			last_attrib=true;		 		
		}
		else{
			if(last_attrib) 
				paramdata.add(cur);
			else{
				non_param.add(cur);
			}
			last_attrib=false;
		}
	}          */
	
}       


/*!
    \fn cmdparser::find_default(int num)
 */
const char* cmdparser::find_default(int num)
{
	if(components.getcount()<=num) return NULL;
	POSITION pos=components.get_top_position() ;
	pos=components.get_next(pos);
	int n=0;
	for(;	pos; pos=components.get_next(pos))
	{
		
		String &s=components.get(pos);
		//if(s[0]=='-') return NULL;
		if(n==num) return s;
		n++;
	}
	
			
	return NULL;
}


/*!
    never will work!!!
 */
const char * cmdparser::find_param(const char*param)
{
	return NULL;
	/*String tofind;
	tofind="-";
	tofind+=param;  
	if(components.getcount()<=1) return NULL
	POSITION pos=components.get_top_position() ;
	pos=components.get_next(pos);
    	for(; pos; pos=compo.get_next(pos) ){
		if( components.get(pos)==tofind){
			 pos=getnext(pos);
			 String &s=
	}
	return NULL;    */
}



/*!
    \fn cmdparser::getparamcount()
 */
int  cmdparser::getparamcount()
{
    	return (components.getcount()-1);
	
	//return (paramorder.getSize() + non_param.getSize());
	
}


/*!
    \fn cmdparser::get_command()
 */
const char*  cmdparser::get_command()
{
	return m_cmd;
}


/*!
    \fn cmdparser::get_param_type(char ch)
 */
int  cmdparser::get_param_type(char ch)
{
assert(false);
       return 1;
}


/*!
    \fn cmdparser::get_short_name(const char *s)
 */
char  cmdparser::get_short_name(const char *s)
{
	   //cur_cmd->gnu_long;
	   assert(false);
	   return 'c';
}


/*!
    \fn cmdparser::find_command(const char *name)
 */
commanddefn* cmdparser::find_command(const char *name)
{
	//commanddefn *p=cmd;
	//for(; p->name[0]='\0'; p++)
	////	if(strcmp(p->name, name)) return p;
	//return NULL;
	assert(false);
	return NULL;
}


/*!
    \fn cmdparser::find(const char *start) 
 */
const char * cmdparser::find(const char *start) 
{
	assert(components.getcount()>=1);
        POSITION pos=components.get_next(
	  		components.get_top_position() 
			);
	int len=strlen(start);  
	for(;pos; pos=components.get_next(pos)){
		if(strncmp(components.get(pos),start,len)==0)
			return components.get(pos).mid(len);
	}
	return NULL;
		
}
