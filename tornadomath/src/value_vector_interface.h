#ifndef __VALUE_VECTOR_INTERFACE_H
#define __VALUE_VECTOR_INTERFACE_H

class Value_vectorInterface
{
public:
    Value_vectorInterface() {}
    virtual ~Value_vectorInterface() {}

    virtual val_type gettype() = 0;

private:
    Value_vectorInterface( const Value_vectorInterface& source );
    void operator = ( const Value_vectorInterface& source );
};


#endif // __VALUE_VECTOR_INTERFACE_H
