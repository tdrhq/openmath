#ifndef STRING_H
#define STRING_H
//#include <string.h>
//#include <string.h>
#include <string.h>
/**to do something right do it yourself
  *@author A J Noronha
  */
 #include "dbgapi.h"
  #define _STRING_PAGE_ 16
class String {
	char *buf;
	unsigned int    _size;
public: 
	String();
	~String();
	
	bool operator==(const char* text);
	inline operator const char* (){
		return buf;
	}
	bool strcmp_nc(const char *text);
	int getLength();
	void operator=(const char *text);
	String operator+(const char*text);
	void operator+=(const char*text);
    void operator+=(char ch);
    void operator=(char ch);

    /*!
        \fn String::operator=(String &str);
     */
    void operator=(String &str)
    {
        (*this)=(const char*) (str);
	assert(buf!=str.buf);
    }
     	String(String &str);
    	void init();
  
        
protected:
	void _set_buffer(int size);
						
	inline int _get_buffer_size(){ return _size;}
public:
	void setsize(int size){
		_set_buffer(((size/_STRING_PAGE_)+1)*_STRING_PAGE_ );
	}
public:
     	String(const char *str);
    bool empty();
    const char & operator[](int n);
    const char * mid(int pos);

    
protected:

};
#endif
