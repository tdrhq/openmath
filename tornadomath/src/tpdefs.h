
#ifndef _TMATH_TYPEDEFS_H_
#define _TMATH_TYPEDEFS_H_
 #include "value.h"
#include "stackar.h" 
class _oper;
class String;

#include "value.h"
typedef StackAr<String, const char*> VARSTACK, VAR_STACK;
typedef StackAr<String, const char*> POSTFIX;
typedef POSTFIX COMPONENTAR;
typedef StackAr<_oper*,_oper*> OPERSTACK, OPER_STACK;
typedef StackAr<String, const char*> StringStack;


#include "_oper.h"
#include "my_string.h"


#endif





