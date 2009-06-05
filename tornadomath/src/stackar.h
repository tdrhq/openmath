/***************************************************************************
                          stackar.h  -  description
                             -------------------
    begin                : Fri Oct 8 2004
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

#ifndef STACKAR_H
#define STACKAR_H

#include "dbgapi.h"
//#ifndef min
inline int min(int x, int y){ return (x<y?x:y) ; }
//#define min _min
//#endif

#include "std_tmath.h"
/**
  *@author A J Noronha
  */
#include <stdio.h>  //will null work
#define _SA_PAGESIZE_ 1
typedef void* _ST_POSITION;
#undef POSITION
#define POSITION _ST_POSITION
template <class BASE, class BASE_ARG>
#define Stack StackAr;
class StackAr {
public:
       // BASE *ar;
        //int _arSize;
	class Node{
	public:
		BASE val;
	protected:
		Node *prev;
		Node *next;
	public:
		Node(){
			next=prev=NULL;
		}
		#ifndef NDEBUG
		~Node(){
			//assert(!(next || prev));
			if(next) assert(next->prev != this);
			if(prev) assert(prev->next != this);
		}
		#endif
		
		void setnext(Node *p){
			//Node *ret=next;
			next=p;
			if(p) p->prev=this;
		}
		void setprev(Node *p){
			prev=p;
			if(p) p->next=this;
		}
		
		inline Node * getnext(){
			return next;
		}
		inline Node * getprev(){
			return prev;
		}
		 
		
	};
	
	Node *top, *bottom;

	
	//Node *pLast;
        int count;

        public:
        StackAr()
        {
		bottom=top=NULL;

		
		count=0;
                //ar=new BASE[_SA_PAGESIZE_];
		//assert(ar);
                //_arSize=_SA_PAGESIZE_;
                //count=0;
        }



        
        BASE& add()
        {
		assert(count<4096); //crash course!
		
		Node *pnew=new Node;
		pnew->setnext(top);
		top=pnew;
		count++;

		if(!bottom) bottom=top;
		
		return (top->val);

        }
	BASE& add_end(){
	
		assert(count<4096);
		if(bottom) {
			bottom->setnext(new Node);
			bottom=bottom->getnext();
		} else top=bottom=new Node;
		
		count++;
		
		return bottom->val;
	}
	
        BASE& add(BASE_ARG val)
        {
                BASE & b=add();
                b=val;
                                                                                 
                return b;
        }
        void add_end(BASE_ARG val){
		BASE &b=add_end();
		b=val;
	}
	
	void removeafter(POSITION pos){
		Node *p= (Node*) pos;
		if(!p) {
			remove();
			return;
		}
		
		Node *tmp=p->getnext();
		//p->next=tmp->next;
		assert(tmp);
		p->setnext(tmp->getnext());
		delete tmp;
	}
	
	void remove(POSITION pos){
		Node* cur=(Node*)pos;
		if(cur->prev) {
			cur->prev->setnext(cur->getnext()); 
			count--;
			delete cur;
		}
		else remove();
		
		
	}
	
		
                
        void remove()
        {

		__remove_only();
        }
	void remove_end(){
		assert(bottom);
		Node *tmp=bottom;
		
		bottom=bottom->getprev();
		if(bottom) bottom->setnext(NULL);
		else top=NULL;

		bottom=tmp->prev;
		count--;
		
		delete tmp;
	}
	
        void __remove_only()
	{
		assert(top!=NULL);
		Node*tmp=top;
		top=top->getnext();
		if(top) top->setprev(NULL);
		else bottom=NULL;
		
		count--;
		//if(!top) bottom=NULL;
		delete tmp;
	}
		
        BASE& operator[](int term){
		int t=count-term-1;
		assert(t>=0);
		Node *cur=top;
		for(int i=0; i<t; i++)
			cur=cur->getnext();
		assert(cur);
		return cur->val;
			


        }

        
	~StackAr(){
		removeall();
		
		
        }

        inline int getSize(){
                return count;
        }
  /** No descriptions */
	inline BASE& get_last()
  	{ 
	  	assert(count>0); 
		return (top->val);
 	}
	POSITION get_top_position()
	{
		return (void*) top;
	}
	BASE&    get(POSITION pos)
	{
		assert(pos);
		
		return ((Node*)pos)->val;
	}
	POSITION get_next(POSITION old)
	{
		return ((Node*)old)->getnext();
	} 
	POSITION find_pos(BASE_ARG arg)
	{
		for(Node *cur=top; cur; cur=cur->getnext()){
			if(cur->val==arg) return (void*)cur;
		}
		return NULL;
	}
	
	BASE& find(BASE_ARG arg){
		return ((Node*) find_pos(arg))->val;
	}
#ifndef NDEBUG	
  	void debug_dump(const char *str){
 
  		printf("DEBUG: %s:\t", str);
		for(int i=getSize()-1; i>=0; i--){
			///printf("%s  ",(const char*) (*this)[i]);
			cout<<(*this)[i]<<'\t';
		}
		printf(":end\n");
  
  	}
#else 
 	 inline void debug_dump(const char*){}
#endif
    /*!
        \fn StackAr::getcount()
     */
    	inline int  getcount()
    	{
     	   	return count;
    	}
    
     	void removeall()
	{
    		while(count>0)
			__remove_only();	
	}
	
	
 
	
};

#endif

