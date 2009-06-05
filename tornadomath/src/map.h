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
#ifndef MAP_H
#define MAP_H

/**
@author arnold j noronha
*/
template<class MAPFROM, class MAPTO>
class Map{
	struct _map{
		MAPFROM mapfrom;
		MAPTO   mapto;
		int     hash;
	};
	//StackAr<_map
public:
    Map();

    ~Map();

};
template<class MAPFROM, class MAPTO>
Map<MAPFROM,MAPTO>::Map()
{
}

template<class MAPFROM, class MAPTO>
Map<MAPFROM,MAPTO>::~Map()
{
}

#endif
