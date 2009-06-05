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
#include "session.h"
#include "value_normal.h"
#include "stackar.h"
#include "world.h"
#include <stdlib.h>
#include "dbgapi.h"
#include "cmdparser.h"


struct _map_cmd {
	char* cmd;
	bool (*pfn)(cmdparser *);
};
void breakup_string_into_array(char *text,StackAr<String, const char*> &ar){
	char *p=strdup(text);
	char *s=strtok(p," \"");
	String cur;
	bool quote=false;
	while(s){
		cur="";
		
		if(!quote){
			if(*s=='\"') {
				quote=true;
				cur=s+1;
			}
		}else{
			int len=strlen(s);
			if(s[len-1]=='\"') {
				s[len-1]='\0';
				cur+=s;
				quote=false;
			}
			cur+=s;
		}
		s=strtok(NULL, " \"");
	}
	ar.debug_dump("cpts of breakup string");
	delete p;
}			
	
void breakup_string(StackAr<String , const char*> &ar, StackAr<String, const char*> &param_ar,char *str)
{
	//StringStack stk;
	//breakup_string_into_array(str, stk);
	
	String tmp;
	int unused=0;
	//bool last_was_param=false;
	while(str ){
		if(*str=='\0') break;
		while(*str==' ') str++;
		char *p=str;
		tmp="";
		bool end_is_quote=false;
		String end;
		end=" ";
		if(*p=='\"') {
			end_is_quote=true;
			end="\"";
			p++;
		}
		//while((!unused && (*p!=' ')) && *p!='\0'){
		//	if(*p=='\"' && end_is_quote)
		//		break;
		//	tmp+=*p;
		//	p++;
		//}
		char *next=strchr(p, end[0]);
		if(next) next++;
		
		tmp=strtok(p,  end);
		p=next;
		
		if(tmp[0]=='-'&& unused<=0){
			String s;
			for(int i=1;tmp[i]!='\"' && tmp[i]!=' ' && tmp[i]!='\0';
				i++){
				s=tmp[i];
				param_ar.add(s);
				unused++;
			}
			
			//param_ar.add((const char*)tmp+1);
			//last_was_param=true;
			//unused++;
		}else {
			if(unused<=0) param_ar.add("");
			ar.add(tmp);
			//unused--;
		}
		
		if(p) str=p;
		else str=NULL;
		
		
		
	}
			
		

	#ifndef NDEBUG
	printf("DEBUG: breakup_string: ");
	for(int k=0; k<ar.getSize(); k++){
		//puts(ar[k]);
		//puts("  ");
		printf("%s   ", (const char*) ar[k]);
	}
	printf("\n");
	#endif
	
}

 const char *find_param(const char* find,
	int defpos, cmdparser *cmd)
{
// 	//int blcount=0;
// 	//POSITION pos=param->get_top_position();
// 	//int i=0;
// 	for(; pos; i++,pos=param->get_next(pos)){
// 		if(param->get_last()== find){
// 			return (*ar)[i];
// 		}else if(param->get_last()==""){
// 			if(blcount==defpos)
// 				return (*ar)[i];
// 			blcount++;
// 		}
// 	}
	const char *non=cmd->find_default(defpos);
	if(non) return non;
	const char *param =cmd->find_param(find);
	return param;
}	

#define FINDP(name,def) find_param(name, def,cmd )	
#define SESSCMD(name) bool cmd_ ## name (cmdparser * cmd)

//bool cmd_set(StringStack *ar,StringStack *params, Session* p)
SESSCMD(set)
{
	if(cmd->getparamcount()!=2)   {
		cout<<"set: does not take "<<cmd->getparamcount()<<" parameters.\n"; 
		return false;
	}
	
	
	Value *v=getworld()->var_get(FINDP("n",0));
	expression expr;
	
	const char * str=FINDP("x",1);
	cout<<"set: "<<str<<endl;
	
	expr.set(str);
	
	//Value tmp;
	//tmp.createfrom(expr.eval());
	expr.eval(*v);
	
	
	return true;
	
	
}
SESSCMD(show){
	getworld()->var_get(FINDP("n",0))->show();
	cout<<endl;
	return true;
}

SESSCMD(debug_expr)
{
	if(cmd->getparamcount()==0) return false;
	expression expr;
	expr.set(FINDP("x",0) );
	return true;
}	
#include <stdio.h>
SESSCMD(quit)
{ 
	getworld()->save(PREV_SESSION);
	exit(0); 
}
SESSCMD(oper){
	getworld()->oper_add(FINDP("n",0),FINDP("d",1));
	return true;
}
SESSCMD(eval){

	const char *pa=FINDP("x",0);
	if(!pa) return false;
	
	Value val;
	
	////////////////////
	_expr exp;
	if(!exp.build(pa)){
		cout<<"ERROR: failed to evaluate expression\n";
		return false;
	}
	
	exp.eval(val);
	val.show();
	/////////////////////
	
	cout<<endl;
	
	return true;
}
SESSCMD(showalloper){
	getworld()->oper_showall();
	return true;
}

SESSCMD(save){
	getworld()->save(FINDP("x",0));
	return true;
}
SESSCMD(load){
	return getworld()->load(FINDP("x",0));
	
}

SESSCMD(clean){
	String term;
	term=FINDP("x", 0);
	int type;
	if(term.empty()) type=1;
	else{
		type=atoi(term);
	}
	
	return getworld()->clean(type);
}

const _map_cmd map_ar[]={
	{"set", cmd_set},
	{"debug-expr", cmd_debug_expr},
	{"quit", cmd_quit},
	{"oper", cmd_oper},
	{"eval", cmd_eval},
	{"show", cmd_show},
	{"oper-showall", cmd_showalloper},
	{"save", cmd_save},
	{"load", cmd_load},
	{"clean", cmd_clean},
	{NULL, NULL}
};

Session::Session()
{
out=stdout;
in=stdin;
err=stderr;
}


Session::~Session()
{
	
}



//plain cmds, no control loops
void Session::runcommand(const char *str)
{
	//char *null="";
	//assert(true);
	cmdparser  cmd;
	String command;	
	
	int i; 
	TRY{
		cmd.set(str);
		
		command=cmd.get_command();
		if(command.empty()) {
			//cout<<endl;
			return;
		}
	}
	CATCH(...){
		cout<<"ERROR: command parsing failed.\n";
		return;
	}
	
	TRY{
	
		for(i=0; map_ar[i].cmd!=NULL; i++)
			if(command==map_ar[i].cmd) {
				if(!map_ar[i].pfn(&cmd))
					fprintf(stderr, "ERROR: %s: command failed.\n", 
					(const char*) cmd.get_command());
				break;
			}
		if(map_ar[i].cmd==NULL)
			printf("shell: %s: command not found.\n" , (const char*) cmd.get_command());
	
		
	}
	CATCH(...){
		cout<<"ERROR: unhandled exception while exec command.\n";
	}	
	
			   
}
