/***************************************************************************
                          expression.cpp  -  description
                             -------------------
    begin                : Fri Oct 8 2004
    copyright            : (C) 2004 by A J Noronha
    email                : arn_2000@rediffmail.com
 ***************************************************************************/


#include "my_string.h"
#include "expression.h"
#include "_expr.h"
#include "stackar.h"
#include "_oper.h"
#include "dbgapi.h"
#include <ctype.h>
#include <stdio.h>
#include "world.h"
#include <stdlib.h>

bool is_literal_char(const char ch);

bool is_operator(const char *s);

bool is_oper_char(const char ch);

void reverse_stack(StringStack &from, StringStack &to){
	while(from.get_top_position()){
		
		to.add(from.get_last());
		from.remove();
		
	}
}

expression::expression(){
        str="";
                
}
expression::~expression(){
}
/** */
void expression::set(const  char *_str){
     str=_str;
     StringStack _postfix;
     convert_to_postfix(_postfix);;
     reverse_stack(_postfix, m_postfix);
     
        
}
/**convert to components in stack. FIFO*/
void expression::convert_to_components(COMPONENTAR &component)
{
        String s=str;
        const char *ps= s;

        const char *p=ps;
	String cur;
        while(*p!='\0')
        {
	        assert(*p!=' ');
		
	        cur="";

                while(*p==' ') p++;
                
                if(*p=='%'){
                        cur="%";
                        p++;
                        while(isnum(*p)){
                                cur+=*p;
                                if(isalpha(*p)) cout<<*p<<":invalid alphabet\n" ;
                                p++;
                        }
                }
                else if(isalpha(*p)) {
                        while(is_literal_char(*p)){
                                cur+=*p;
                                p++;
                        }
                }
                else if(isnum(*p)){
			
			while(isnum(*p) || *p=='.'){
				cur+=*p;
				p++;
			}
		}
		else{
                   	if(*p=='-' && isdigit(p[1])){
				if(component.get_last ()=="(" 
				||is_operator(component.get_last())){
					cur+=*p;
					p++;
					while(isnum(*p) || *p=='.'){
						cur+=*p;
						p++;
					}
				}
				
			}
			else{
						
				cur=*p;
				p++;
				
				#ifdef NEWVER
				if(is_oper_char(*p)){
					if(*p!='-')  //minus cannot come second?
					{
						cur+=*p;
						p++;
					}
				}
				#endif
				
			}
			
			
		}
		component.add(cur);
                        
                
        }
	component.debug_dump("str_to_cpt");
                        
        
}

#ifdef NEWVER
struct _basic_oper_defn{
	char *name;
	int priority;
	bool rtol;
}
_bo_ar[]={
	{"=", -1, true },
	{"+", 0, false },
	{"-", 0, false },	
	{"/", 1, false },		
	{"*", 1, false },			
	{"^", 2, false },				
 	{NULL, 0, false }
};

_basic_oper_defn * _bo_findoper(const char *text)
{
	for(int i=0; _bo_ar[i].name!=NULL; i++)
	{
		if(strcmp(_bo_ar[i].name, text)==0) 
			return &_bo_ar[i];
	}
	return NULL;
}
	
	/** No descriptions */
int _ctp_get_oper_pref(const char ch){
	char s[2] = "1";
	s[0] =ch;

	_basic_oper_defn *p=_bo_findoper(s);	
	if(!p){
		THROW();
		return -0xff;
	}
	return p->priority;
	

}
bool _ctp_is_oper_righttoleft(const char ch)  
{
	char s[2] = "1";
	s[0] = ch;

	_basic_oper_defn *p=_bo_findoper(s);
	if(!p){
		THROW();
		return false;
	}
	return p->rtol;
	
	
}
bool is_oper_char(const char ch)
{
	return (ch=='<' || ch=='>'
		||ch=='+'
		||ch=='-'
		||ch=='*'
		||ch=='/'
		||ch=='='
		||ch=='^'
		||ch=='.'
		||ch=='!'
		||ch=='~'
		);
}			
bool is_literal_char(const char ch)
{
	if(isalpha(ch) || ch=='_'|| isdigit(ch))
	return true;
}
bool is_literal(const char* s)
{
	if(isdigit(s[0])) return false;
	if(is_literal_char(s[0]) ) return true;
	return false;	
}
bool is_number(const char *s)
{
	if(s[0]=='-' && isdigit(s[1])) return true;
	if(isdigit(*s)) return true;
	return false;
}
bool is_operator(const char *s)
{
	return _bo_findoper(s)?true:false;	
}

#endif

inline void _ctp_end_brackets(POSTFIX &postfix, StringStack &oper_stack)
{
	while(oper_stack.getSize())
	{
		if(oper_stack.get_last()=="("){
			oper_stack.remove();
			break;
		}
		
		String s;
		
		s=oper_stack.get_last();
		oper_stack.remove();
		
		if(isalpha(s[0])) {
			//don't worry: this seems allright!!!
			String name;
			name="'";
			name+=s;
			postfix.add(name);
		}else{
			postfix.add(s);
		}
		
			
			
				
	}
}
void expression::convert_to_postfix(POSTFIX &postfix)
{
        COMPONENTAR components, &cpt=components;
        convert_to_components(components);

        
        StackAr<String, const char*> oper_stack;
        
        components.add(")");
	oper_stack.add("(");
	String s;
	
        //start from beg:
        for(int i=0; i<cpt.getSize(); i++){
                bool oper=false;
               
		s=cpt[i];
                if(s[0]=='%')
                        postfix.add(s);
		else if(isalpha(s[0])){
                        if(!(cpt[i+1]=="("))
                                postfix.add(s);
                        else{
                                i++;
                                //oper=true;
                                oper_stack.add("(");
				oper_stack.add(cpt[i-1]);
				oper_stack.add("(");
				
                        }
                } 
		else if(isnum(s[0]))
                        postfix.add(s);
		else if(s=="(")
			oper_stack.add("(");
                else if(s==")" || s==","){
			
 			_ctp_end_brackets(postfix, oper_stack );
			if(s==",")
				oper_stack.add("(");
			else if(s==")"){
				if(oper_stack.getSize()) 
					if(isalpha(oper_stack.get_last()[0])) {
						i--;   //i want to get the bracks again.	 
						assert(oper==false);  //avoid trouble?
					}
			}
			//postfix.debug_dump("bracket work complete");
                } 
		else {
			if(s=="-") {
				if(i==0) s="~";
				else {
					const char *last=cpt[i-1];
					if(last[0]!='%' 
						&& !isnum(last[0]) 
						&& !isalpha(last[0]))
						s="~";
				}
			}
					
			oper=true;
		}
		

                if(oper){
                        
			assert(!isalpha(s[0]) && !isnum(s[0]) && s[0]!='%');
			int pref=_ctp_get_oper_pref(s[0]);
			int testpref;
			bool rtol=_ctp_is_oper_righttoleft(s[0]);
			
                        if(oper_stack.getSize()>0) 
				while(
					(testpref=
					_ctp_get_oper_pref(oper_stack.get_last()[0])
					)>=pref){
					
 					if(testpref==pref && rtol)
						break;
					//else destack
					
					postfix.add(oper_stack.get_last());
					oper_stack.remove();
								
                       		 }
                        oper_stack.add(s);
                }
        }
        postfix.debug_dump("postfix");
    
}


/*!
    \fn expression::get_param_count()
 */
int  expression::get_param_count()
{
	POSTFIX st;
	int ct=0;
	convert_to_postfix(st);
	for(POSITION pos=st.get_top_position();
		pos;
		pos=st.get_next(pos)){
		if(st.get(pos)[0]=='%'){
			int n=atoi((const char*)st.get(pos)+1);
			if(n>ct) ct=n;
		}
	}
	
	return ct;
}


/*!
    \fn expression::eval()
 */

Value expression::eval(Value &ret)
{


	
	ValueStack  valstack;
	String str_oper;
	str_oper="oper";
    	POSITION pos=m_postfix.get_top_position();
    	for(; pos; pos=m_postfix.get_next(pos)){
        	const char*s=m_postfix.get(pos);
		if(s[0]=='%' || isalpha(s[0]) )
		{
			//ValueRef vref(getworld()->var_get(s));			
			valstack.add(getworld()->var_get(s));
		}
		else if (isdigit(s[0])){

			valstack.add()=str_to_real(s);
			
		}
		else {
			_oper* p;
			if(s[0]=='\'')
			         p=getworld()->oper_get(s+1);
			else 
				p=getworld()->oper_get(str_oper+s);
			
			p->eval(valstack) ;
		}
	}
	
	ret=valstack.get_last();
	valstack.remove();
	return ret;
			
		
	
}
