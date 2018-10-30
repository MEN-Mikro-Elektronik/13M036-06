/***********************  I n c l u d e  -  F i l e  ************************
 *  
 *         Name: m36_pld.h
 *
 *       Author: ds
 *        $Date: 2004/04/15 12:19:49 $
 *    $Revision: 1.2 $
 * 
 *  Description: Prototypes for PLD data array and ident function
 *                      
 *     Switches: -
 *
 *---------------------------------------------------------------------------
 * (c) Copyright 1998 by MEN mikro elektronik GmbH, Nuernberg, Germany 
 ****************************************************************************/
/*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _M36_PLD_H
#define _M36_PLD_H

#ifdef __cplusplus
	extern "C" {
#endif

# ifndef _ONE_NAMESPACE_PER_DRIVER_
        /* variant for swapped access */
#       ifdef ID_SW
#		define M36_PldIdent 	M36_SW_PldIdent
#               define M36_PldData 	M36_SW_PldData
#       endif
# endif

/*--------------------------------------+
|   EXTERNALS                           |
+--------------------------------------*/
extern const u_int8 M36_PldData[];

/*--------------------------------------+
|   PROTOTYPES                          |
+--------------------------------------*/
char* M36_PldIdent(void);


#ifdef __cplusplus
	}
#endif

#endif	/* _M36_PLD_H */
