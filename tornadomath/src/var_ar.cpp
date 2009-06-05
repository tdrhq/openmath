/***************************************************************************
                          var_ar.cpp  -  description
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

#include "var_ar.h"
#include "dbgapi.h"

template <class TVALTYPE>
var_ar<TVALTYPE>::var_ar(){
}
template <class TVALTYPE>
var_ar<TVALTYPE>::~var_ar(){
}
/** No descriptions */
template <class TVALTYPE>
_VarNode<TVALTYPE>* var_ar<TVALTYPE>::_find(int ref)
{
        for(int i=0; i<getSize(); i++){
                if(ar[i].isRef(ref)) return &ar[i];
        }
        return NULL;

}
/** No descriptions */
template <class TVALTYPE>
void var_ar<TVALTYPE>::set(int ref, TVALTYPE val)
{
        _VarNode<TVALTYPE> *nd=_findex(ref);
        assert(nd);
        
        nd->val=val;

}
/** finds and creates if necessary
 */
 template <class TVALTYPE>
_VarNode<TVALTYPE> * var_ar<TVALTYPE>::_findex(int ref)
{
        _VarNode<TVALTYPE> *nd= _find(ref);
        if(!nd)
                nd=&(add());
        nd->ref=ref;
}
/** operator = (const _VarNode& ) */
template <class TVALTYPE>
_VarNode<TVALTYPE>& _VarNode<TVALTYPE>::operator = (const _VarNode& asgn){
        this->ref=asgn.ref;
        this->val=asgn.val;
}
/** No descriptions */
template <class TVALTYPE>
TVALTYPE& var_ar<TVALTYPE>::get(int ref){
        return _findex(ref)->val;
}

