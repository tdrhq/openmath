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
     convert_to_postfix(_postfix, str);
     reverse_stack(_postfix, m_postfix);
     
        
}
/**convert to components in stack. FIFO*/
void convert_to_components(COMPONENTAR &component, const char *str)
{
        String s;
	s=str;
        const char *ps= s;

        const char *p=ps;
	String cur;
        while(*p!='\0')
        {
	        //assert(*p!=' ');
		
	        cur="";

                while(*p==' ') p++;
                if(!*p) break;
		
                if(*p=='%'){
                        cur="%";
                        p++;
                        while(isnum(*p)){
                                cur+=*p;
                                if(isalpha(*p)) cout<<*p
					<<":invalid alphabet\n" ;
                                p++;
                        }
                }
                else if(isliteralchar(*p)) {
                        while(isalpha(*p) || isnum(*p)){
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
                        //oper or brack or
                        cur=*p;
                        p++;
		}
		component.add(cur);
                        
                
        }
	component.debug_dump("str_to_cpt");
                        
        
}
/** No descriptions */
int _ctp_get_oper_pref(const char ch){
	//if(ch=='(') return 4; //bogus!
	if(ch=='~') return 3;
	if(ch=='^') return 2;
	if(ch=='/' || ch=='*' || ch=='.') return 1;
	if(ch=='+' || ch=='-') return 0;
	if(ch=='=') return -1;
	if(ch=='(') return -0xff; 
	//throw(0);
	THROW();
	assert(false);
	return -1;
}

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
void convert_to_postfix(POSTFIX &postfix, const char *str)
{
        COMPONENTAR components, &cpt=components;
        convert_to_components(components, str);

        
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
		else if(isliteralchar(s[0])){
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
					if(isalpha(oper_stack.get_last()[0])) 
					{
						i--;   
						//i want to get 
						//the bracks again.	 
						assert(oper==false);  
						//avoid trouble?
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
                        //_oper *p=_oper_get(s);
                        //if(!p)
                                //fprintf(stderr, "unable to find operator\n");
			assert(!isalpha(s[0]) && !isnum(s[0]) && s[0]!='%');
			int pref=_ctp_get_oper_pref(s[0]);
                        if(oper_stack.getSize()>0) 
				while(_ctp_get_oper_pref(oper_stack.get_last()[0])>=pref){
 					//_ctp_flush_operator(postfix, var_stack,
					 //oper_stack.remove()[0]);	
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
	convert_to_postfix(st,str);
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
