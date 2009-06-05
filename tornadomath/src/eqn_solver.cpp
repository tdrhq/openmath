/***************************************************************************
 *   Copyright (C) 2004 by arnold j noronha                                *
 *   arn_2000@rediffmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "eqn_solver.h"

eqn_solver::eqn_solver()
{
}


eqn_solver::~eqn_solver()
{
}




/*!
    \fn eqn_solver::set(_oper_expr* poper)
 */
bool  eqn_solver::set(_oper_expr* poper)
{
	expr=&(poper->exp);
}
bool eqn_solver::get_next_point(){
	tmp=(beg+end)/2;
	tmp_val=eval(tmp);
}

bool eqn_solver::iterator(){
	get_next_point();
	if(beg_val<tmp_val && tmp_val<end_val){
		if(beg_val<0 && tmp_val>0){
			end=tmp;
			end_val=tmp_val;
		}
		else if(end_val<0 && tmp_val>0){
			beg=tmp;
bool eqn_solver::solve();