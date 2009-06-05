/***************************************************************************
                          _oper.cpp  -  description
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

#include "_oper.h"
#include "world.h"
#include <math.h>

_oper::_oper()
{
	getworld()->oper_add(this);
}

_oper::~_oper()
{
}
/** operator <= (const _oper& ) */

void _oper::eval(ValueStack& eval_stack)
{

}

bool _oper::want_save()
{   return false; }



/** No descriptions */
int _oper::get_variable_count(){
        return 0;
}
/** TODO: fns represented by apostrophe. 'log,   'exp etc. opers as usual */
const char* _oper::get_code(){
        return NULL;
}


/*!
    \fn _oper::getname()
 */
const char* _oper::getname()
{

    return name;
}



char  _oper::get_operator_ch()
{

    return 0;
}


DEFOPER(set,oper=,2)
EVAL{
	Value rval=values.get_last();
	values.remove();
	
	if(!values.is_last_ref()){
		cout<<"Invalid lvalue \n";
		THROW();
	}
	values.get_last()=rval;
}
ENDOPER(set);

DEFOPER(add,oper+,2)
EVAL{            
	//values.add(values.remove()+values.remove());  
	Value b;
	b=values.get_last();
	values.remove();
	
	Value a;
	a=values.get_last();
	values.remove();
	
	Value &ret=values.add();
	if(a.gettype()=='r'&& b.gettype()=='r'){
		REAL ra=  ((Value_real*)(a.getvalue()))->value;
		REAL rb=  ((Value_real*)(b.getvalue()))->value;
		REAL r=	ra+rb;
		
		ret.settype(val_real);
		((Value_real*)(ret.getvalue()))->value=r;
	}
	else 
	{
		GET_USER_COMMAND(a,b);
		perror("add: unsupported operation\n");
		THROW();
	}	
	
		
}
ENDOPER(add);

DEFOPER(sub,oper-,2)
EVAL{
	Value b;
	b=values.get_last();
	values.remove();
	
	Value a;
	a=values.get_last();
	values.remove();
	
	//values.add(b-a);
	Value &ret=values.add();
	if(a.gettype()==val_real &&
		b.gettype()==val_real){
		REAL r=((Value_real*)(a.getvalue()))->value
			-((Value_real*)(b.getvalue()))->value;
		ret.settype(val_real);
		((Value_real*)(ret.getvalue()))->value=r;
	}
	else 
	{
		GET_USER_COMMAND(a,b);
		perror("oper-: unsupported operation\n");
		THROW();
	}	
		
}

ENDOPER(sub)

DEFOPER(div,oper/,2)
EVAL{
	Value b;
	b=values.get_last();
	values.remove();
	
	Value a;
	a=values.get_last();
	values.remove();
	
	//values.add(b-a);
	Value &ret=values.add();
	if(a.gettype()==val_real &&
		b.gettype()==val_real){
		REAL r=((Value_real*)(a.getvalue()))->value
			/((Value_real*)(b.getvalue()))->value;
		ret.settype(val_real);
		((Value_real*)(ret.getvalue()))->value=r;
	}
	else 
	{
			GET_USER_COMMAND(a,b);
		perror("oper-: unsupported operation\n");
		THROW();
	}	
		
}
ENDOPER(div)

DEFOPER(mult,oper*,2)
EVAL{
	Value b;
	b=values.get_last();
	values.remove();
	
	Value a;
	a=values.get_last();
	values.remove();
	
	//values.add(b-a);
	Value &ret=values.add();
	if(a.gettype()==val_real &&
		b.gettype()==val_real){
		REAL r=((Value_real*)(a.getvalue()))->value
			*((Value_real*)(b.getvalue()))->value;
		ret.settype(val_real);
		((Value_real*)(ret.getvalue()))->value=r;
	}
	else if (a.gettype()==val_vector && b.gettype()==val_vector){
		Value_vector &vb=*(Value_vector *) b.getvalue();
		Value_vector &va=*(Value_vector *) a.getvalue();
	
		ret.settype(val_vector);		
		Value_vector &_ret=*((Value_vector *) ret.getvalue());
		_ret.x=va.y*vb.z  -  va.z*vb.y;
		_ret.y=-va.x*vb.z  +  va.z*vb.x;
		_ret.z=va.x*vb.y  -  va.y*vb.x;
		
		
	}
	else 
	{
				GET_USER_COMMAND(a,b);
		perror("oper*: unsupported operation\n");
		THROW();
	}	
		
}
ENDOPER(mult)  ;

DEFOPER(dot,oper.,2)
EVAL{
	Value b;
	b=values.get_last();
	values.remove();
	
	Value a;
	a=values.get_last();
	values.remove();
	
	//values.add(b-a);
	Value &ret=values.add();

	if (a.gettype()==val_vector && b.gettype()==val_vector){
	
		Value_vector &vb=*(Value_vector *) b.getvalue();
		Value_vector &va=*(Value_vector *) a.getvalue();
	
		ret.settype(val_real);		
		//Value_ret &_ret=*((Value_vector *) ret.getvalue());
		ret=va.x*vb.x+va.y*vb.y+va.z*vb.z;
		
		
	}
	else 
	{
			GET_USER_COMMAND(a,b);
		perror("oper.: unsupported operation\n");
		THROW();
	}	
		
}
ENDOPER(dot)  ;
DEFOPER(powop,oper^,2)
EVAL{
	Value b;
	b=values.get_last();
	values.remove();
	
	Value a;
	a=values.get_last();
	values.remove();
	
	//values.add(b-a);
	Value &ret=values.add();
	if(a.gettype()==val_real &&
		b.gettype()==val_real){
		REAL r=MATH(pow)(((Value_real*)(a.getvalue()))->value,
			((Value_real*)(b.getvalue()))->value);
		ret.settype(val_real);
		((Value_real*)(ret.getvalue()))->value=r;
	}
	else 
	{
		GET_USER_COMMAND(a,b);
		perror("oper-: unsupported operation\n");
		THROW();
	}	
		
}

ENDOPER(sub);

inline REAL _mylog_(REAL a, REAL base){
	return MATH(log) (a)/log(base);
}
 
DEFOPER(log,log,2)
EVAL{
	Value b;
	b=values.get_last();
	values.remove();
	
	Value a;
	a=values.get_last();
	values.remove();
	
	//values.add(b-a);
	Value &ret=values.add();
	if(a.gettype()==val_real &&
		b.gettype()==val_real){
		REAL r=_mylog_(( (Value_real*)(a.getvalue()))->value
			,((Value_real*)(b.getvalue()))->value);
		ret.settype(val_real);
		((Value_real*)(ret.getvalue()))->value=r;
	}
	else 
	{
		perror("oper-: unsupported operation\n");
		THROW();
	}	
		
}
ENDOPER(log)  ;


DEFOPER(ln,ln,1)
EVAL{
	Value b=values.get_last();
	values.remove();
	
	b= MATH(log)(((Value_real*)b.getvalue())->value);
	values.add(b);
}

ENDOPER(ln)     ;

DEFOPER(negate,oper~,1)
EVAL{
	Value b=values.get_last();
	values.remove();
	
	b= -(((Value_real*)b.getvalue())->value);
	values.add(b);
}

ENDOPER(ln)     ;
DEFOPER(v,v,3)
EVAL{
	Value c=values.get_last();
	values.remove();
	
	Value b=values.get_last();
	values.remove();

	Value a=values.get_last();
	values.remove();
	Value &ret=values.add();
	ret.settype('v');
	Value_vector* v= ((Value_vector*) ret.getvalue());
	if(c.gettype()=='r' && b.gettype()=='r' && a.gettype()=='r')
	{
		v->x=((Value_real*) a.getvalue())->value;
		v->y=((Value_real*) b.getvalue())->value;
		v->z=((Value_real*) c.getvalue())->value;
	}
	else THROW();

}
ENDOPER(v);

DEFOPER(Z,Z,3)
EVAL{
	Value c=values.get_last();
	values.remove();
	
	Value b=values.get_last();
	values.remove();

	Value &ret=values.add();
	ret.settype(val_complex);
	Value_complex* z= ((Value_complex*) ret.getvalue());
	if(c.gettype()=='r' && b.gettype()=='r')
	{
		z->complex=((Value_real*) c.getvalue())->value;
		z->real   =((Value_real*) b.getvalue())->value;
	}
	else THROW();

}
ENDOPER(Z);
DEFOPER(exp, exp,1)
EVAL {
	Value b=values.get_last();
	values.remove();
	Value &ret=values.add();

	if(b.gettype()=='r'){
		ret=MATH(exp)(((Value_real*)b.getvalue())->value);
	}else THROW();
}
ENDOPER(exp);

DEFOPER(re, re,1)
EVAL {
	Value b=values.get_last();
	values.remove();
	Value &ret=values.add();

	if(b.gettype()==val_complex){
		ret=(((Value_complex*)b.getvalue())->real);
	}else THROW();
}
ENDOPER(re);

DEFOPER(im, im,1)
EVAL {
	Value b=values.get_last();
	values.remove();
	Value &ret=values.add();

	if(b.gettype()==val_complex){
		ret=(((Value_complex*)b.getvalue())->complex);
	}else THROW();
}
ENDOPER(im);

FNSINGLE(log10, log10l);
REAL _sec(REAL val){
	return (1/ MATH(cos) (val));
}
REAL _cosec(REAL val){
	return (1/MATH(sin)(val));
}
REAL _cot(REAL val){
	return (1/MATH(tan)(val));
}
 
REAL _pow10_(REAL a){
	return MATH(pow)(10, a);
}


FNSINGLE(tan,MATH(tan));
FNSINGLE(sin, MATH(sin));
FNSINGLE(cos, MATH(cos));
FNSINGLE(sinh, MATH(sinh)); 
FNSINGLE(cosh, MATH(cosh));    
FNSINGLE(tanh, MATH(tanh));  
FNSINGLE(sec,_sec);
FNSINGLE(cosec, _cosec);
FNSINGLE(cot, _cot);
FNDOUBLE(pow, MATH(pow));
FNSINGLE(pow10, _pow10_ );
FNSINGLE(acos, MATH(acos));
FNSINGLE(asin, MATH(asin));
FNSINGLE(atan, MATH(atan));

#define SETUP(name) p=(void*)new _oper_ ## name;
void operator_setup(){
     void *p;
     
     ///basic
     	SETUP(add);
     	SETUP(sub);
     	SETUP(div);
     	SETUP(mult);
     	SETUP(set);
	SETUP(dot);
	SETUP(powop);
	SETUP(negate);
	
     //trign
     	SETUP(tan);
     	SETUP(cot);
     	SETUP(sin);
     	SETUP(cos);
     	SETUP(cosec);
     	SETUP(sec);
	SETUP(asin);
	SETUP(acos);
	SETUP(atan);

     //hyperbolic
     	SETUP(sinh);
     	SETUP(cosh);
     	SETUP(tanh);
     
     //logs and exp
     	SETUP(ln);
     	SETUP(log);
     	SETUP(log10);
     	SETUP(exp);
     	SETUP(pow10);
		SETUP(pow);
	
     //converters
     	SETUP(v);
	SETUP(Z);
	
     //components...
     	SETUP(re);
	SETUP(im);
}


/*!
    \fn _oper::get_defn()
 */
const char* _oper::get_defn()
{
	assert(false);
	return NULL;
}
