/***************************************************************************
                          world  -  description
                             -------------------
    begin                : Sat Oct 16 2004
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
#include "world.h"
#include "_oper_expr.h"
#include"_oper.h"


World g_world;
World * getworld(){
	return &g_world;
}
World::World()
{
	temp_count=0;
	operator_setup();
}
World::~World()
{
}

_oper* World::oper_get(const char *name)
{

	for(POSITION pos=oper_ar.get_top_position();
		pos; pos=oper_ar.get_next(pos)){
		if(strcmp(name, oper_ar.get(pos)->getname())==0)
			return oper_ar.get(pos);
	}

	THROW();
	
	return NULL;
}
/*!
    \fn World::oper_add(_oper* oper)
 */
void World::oper_add(_oper* oper)
{
      
    oper_ar.add(oper);
}




/*!
    \fn World::oper_add(const char* name, const char *defn, int priority)
 */
void World::oper_add(const char* name, const char *defn)
{
    	_oper_expr *poper= new _oper_expr(name,defn);
    
}

/*fn World::__var_find_only(const char *name)
 */
Value* World::__var_find_only(const char *name)
{
	//POSITION pos=var_ar.find_pos(name);
	for(POSITION pos=var_ar.get_top_position(); 
		pos; 
		pos=var_ar.get_next(pos))
		if(strcmp(name,var_ar.get(pos).name)==0)
			return &(var_ar.get(pos).val);
	return NULL;
}


/*!
    \fn World::var_get(const char *name)
 */
Value* World::var_get(const char *name)
{
	Value* p=__var_find_only(name);
	if(p) return  p;
	else return __var_force_add(name); 
}


/*!
    \fn World::__var_force_add()
 */
Value* World::__var_force_add(const char *name)
{
	
	_map_var &a=var_ar.add();
	a.name=name;
	return &(a.val);
	
}


/*!
    \fn World::var_get_temp(REAL value)
 */
Value* World::var_get_temp(REAL value)
{
	char name[20];
	sprintf(name, "{#%d}", temp_count);
	temp_count++;
	*(var_get(name)) =value;
	
	return NULL;
}


/*!
    \fn World::oper_showall()
 */
void World::oper_showall()
{
    	for(int i=0; i<oper_ar.getSize(); i++){
		cout<<oper_ar[i]->getname()<<' ';
	}
	cout<<endl;
	
}


/*!
    \fn World::save(const char * file)
 */
void writestring(ofstream &f, const char *str){
	int len=strlen(str);
	f.write((char*) &len, sizeof(len));
	f.write(str, len);
}
void readstring(ifstream &f, String &str){
        int len=0;
	f.read((char*) &len, sizeof(len));
	if(!f) THROW();
	//assert(len<f.getwidth() && f.getwidth()!=0);
	if(!f) THROW();	
	str.setsize(len+1);
	f.read((char*)(const char*) str, len);
	((char*)(const char*) str)[len]='\0';
}

bool World::save(const char * file)
{      
	 POSITION pos ;
    	ofstream f(file,ios::binary | ios::out );
	assert(f);
	
	for( pos=oper_ar.get_top_position();
		pos; pos=oper_ar.get_next((pos))){
		_oper *p=oper_ar.get(pos);
		
		if(!p->want_save()) continue;
		
		writestring(f, p->getname());
		writestring(f, p->get_defn());
	#ifndef NDEBUG
		cout<<"saving "<<p->getname()<<"   "<<p->get_defn()<<endl;
	#endif
		//f<<p->getname()<<'\n'<<p->get_defn()<<endl;
	}
	
	writestring(f, ""); //blank line 
	//char a[30];
	for( pos=var_ar.get_top_position();
		pos; pos=var_ar.get_next((pos))){


		
		writestring(f, var_ar.get(pos).name);
		var_ar.get(pos).val.write_binary(f); 
	#ifndef NDEBUG
		cout<<"saving "<<var_ar.get(pos).name<<"   "
			<<endl;
	#endif	

	}
	writestring(f, "");
	f.close();
	return true;
	
}


bool World::load(const char *file)
{
	ifstream f(file, ios::binary | ios::in);
	//assert(f);
	if(!f) return false;
	String str,defn;
TRY{
	while(1){
		readstring(f, str);
		if(!file) break;
		if(str=="") break;
	
		readstring(f, defn);
	#ifndef NDEBUG
		cout<<"loading "<<str<<"   "
			<<defn<<endl;
	#endif			
		oper_add(str, defn);
	}
	
	while(1){
	
		readstring(f, str);
		if(str=="") break;
	#ifndef NDEBUG
		cout<<"loading "<<str<<"   "
			<<endl;
	#endif				
		
		var_get(str)->read_binary(f);
	}
    }
    CATCH( ... ){
    	cout<<"ERROR: loading, extent of damage cannot be predicted.\n";
    }
		
	
    return true;	
		
    
}


/*!
    \fn World::clean(int n)
 */
bool World::clean(int n)
{

	while(oper_ar.get_top_position()){
		//if(oper_ar.get(pos)->want_save()){
		//	 oper_ar.removeafter(last);
		//	 pos=oper_ar.get_next(pos);
		//	 continue;
		//}
		
		delete oper_ar.get_last();
		oper_ar.remove();

		
	}
	var_ar.removeall();
	operator_setup();
	
	
	if(n==1) {
		return load(AUTO_SESSION);
	}
	else if(n==2){
		return load(PREV_SESSION);
	}
	
	return true;
		
}


/*!
    \fn World::oper_remove(_oper_expr* p)
 */
bool  World::oper_remove(_oper_expr* p)
{
	POSITION last=NULL;
	for(POSITION pos=oper_ar.get_top_position();
		pos; pos=oper_ar.get_next(pos)){
		if(oper_ar.get(pos)==p){
			 oper_ar.removeafter(last);
			 return true;
		}
		last=pos;
	}
	return false;
	
	
}
