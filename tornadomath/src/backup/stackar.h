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

#include "dbgapi.h"
#ifndef STACKAR_H
#define STACKAR_H
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
template <class BASE, class BASE_ARG>
class StackAr {
public:
        BASE *ar;
        int _arSize;
        int count;

        public:
        StackAr()
        {
                ar=new BASE[_SA_PAGESIZE_];
		assert(ar);
                _arSize=_SA_PAGESIZE_;
                count=0;
        }

        void setSize(int size)
        {
		assert(size!=0);
		if(size==0) return ;
		assert(ar);
		assert(_arSize>0);
                //plain resizing
                BASE *pnew=new BASE[size];
		assert(pnew);
                _arSize=size; 
		count=min(count, size); 
		if(ar){ 
			for(int last=count-1; last>=0; last--)  {
                        	pnew[last]=ar[last];
				//assert((const char*)pnew[last]!=(const char*)ar[last]);
			}
			
                	delete ar[_arSize] ;
		}
                ar=pnew;
                
        }

        
        BASE& add()
        {
                assert(count<=_arSize);
		assert(count>=0);
                if(count==_arSize)
                        setSize(_arSize+_SA_PAGESIZE_);
                //ar[count]=val;
                count++;
		assert(count<=_arSize);
                return ar[count-1];
        }
        BASE& add(BASE_ARG val)
        {
                BASE & b=add();
                b=val;
                return b;
        }
        
                
        BASE remove()
        {
		assert(count>0);
                count--;
                return ar[count];
        }

        inline BASE& operator[](int term){
                assert(term<count && term>=0);
                return ar[term];
        }

        
	~StackAr(){
		cout<<"deleting stack...\n";
                if(ar) 
			delete ar;
		cout<<"stack deleted...\n";
		
        }

        void clean()
        {
                setSize(count);
        }

        inline int getSize(){
                return count;
        }
  /** No descriptions */
  inline BASE& get_last()
  { assert(count>0); return ar[count-1] ;}
  
  void debug_dump(const char *str){
  	printf("DEBUG: %s:\t", str);
	for(int i=0; i<getSize(); i++){
		///printf("%s  ",(const char*) (*this)[i]);
		cout<<(*this)[i]<<'\t';
	}
	printf(":end\n");
  }
        //StackAr<BASE,BASE_ARG> operator+(BASE *pBaseAr)
 
                
        
};

#endif

/** No descriptions */

