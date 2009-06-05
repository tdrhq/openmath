/***************************************************************************
                          var_ar.h  -  description
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

#ifndef VAR_AR_H
#define VAR_AR_H


#include "tpdefs.h"
#include "_oper.h"
#include "_expr.h"
#include "stackar.h"

class _oper;
/**
  *@author A J Noronha
  */


template<class TVALTYPE>
class _VarNode{
public:
      int ref;  //for letters use 0xff'a'
      TVALTYPE val;

      _VarNode(int _ref){ ref=_ref; val=0;}
      _VarNode() { ref=0; val=0; }
      bool isRef(char ch)
      {
              return (ref==(0xff00 |ch));
      }
      inline bool isRef(int _ref)
      {
              return _ref==ref;
      }
      inline void setRef(int _ref)
      {
              ref=_ref;
      }
      inline void setRef(char ch) { setRef(0xff00 | ch); }
  /** operator = (const _VarNode& ) */
  _VarNode& operator = (const _VarNode& );
}; 
      
      
template<class TVALTYPE>
class var_ar : protected StackAr<_VarNode<TVALTYPE>, _VarNode<TVALTYPE>&>  {
public: 
	var_ar();
	~var_ar();
  /** No descriptions */
  _VarNode<TVALTYPE>* _find(int ref);
  /** No descriptions */
  void set(int ref, TVALTYPE val);
  /** finds and creates if necessary
 */
  _VarNode<TVALTYPE> * _findex(int ref);
  /** No descriptions */
  TVALTYPE& get(int ref);
};

#endif
