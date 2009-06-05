#ifndef ___VARNODE_INTERFACE_H
#define ___VARNODE_INTERFACE_H

class _VarNodeInterface
{
public:
    _VarNodeInterface() {}
    virtual ~_VarNodeInterface() {}


private:
    _VarNodeInterface( const _VarNodeInterface& source );
    void operator = ( const _VarNodeInterface& source );
};


#endif // ___VARNODE_INTERFACE_H
