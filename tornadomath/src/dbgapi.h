
#ifndef _DEBUGAPI_H_
#define _DEBUGAPI_H_

#include <iostream>
#include <assert.h>
using namespace std;

#ifdef NDEBUG
#define TRY try
#define CATCH(r) catch(r)
#define THROW() throw(0)
#else
#define TRY  if(true)
#define CATCH(r) while(0)
#define THROW() assert(false)
#endif


#endif


