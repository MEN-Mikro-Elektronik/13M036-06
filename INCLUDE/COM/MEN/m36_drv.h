/***********************  I n c l u d e  -  F i l e  ************************
 *
 *         Name: m36_drv.h
 *
 *       Author: ds
 *        $Date: 2009/09/23 17:48:32 $
 *    $Revision: 2.4 $
 *
 *  Description: Header file for M36 driver
 *               - M36 specific status codes
 *               - M36 function prototypes
 *
 *     Switches: _ONE_NAMESPACE_PER_DRIVER_
 *               _LL_DRV_
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

#ifndef _M36_DRV_H
#define _M36_DRV_H

#ifdef __cplusplus
      extern "C" {
#endif

/*-----------------------------------------+
|  TYPEDEFS                                |
+-----------------------------------------*/
/* none */

/*-----------------------------------------+
|  DEFINES                                 |
+-----------------------------------------*/

/* M36 specific status codes (STD) */        /* S,G: S=setstat, G=getstat */
#define M36_CH_ENABLE		M_DEV_OF+0x00    /* G,S: enable/disable curr ch */
#define M36_CH_GAIN			M_DEV_OF+0x01    /* G,S: gain factor of curr ch */
#define M36_BIPOLAR		    M_DEV_OF+0x02    /* G,S: measure mode for all ch */
#define M36_EXT_TRIG		M_DEV_OF+0x03    /* G,S: defines sampling mode */
#define M36_EXT_PIN			M_DEV_OF+0x04    /* G  : state of binary input */
#define M36_CALIBRATE		M_DEV_OF+0x05    /*   S: start calibration */
#define M36_SINGLE_ENDED	M_DEV_OF+0x06    /* G  : type of input adapter */
#define M36_NBR_ENABLED_CH	M_DEV_OF+0x07    /* G  : # of enabled channels */
/* M36_FLASH_ERASE for MEN internal use only!  */
#define M36_FLASH_ERASE		M_DEV_OF+0x08    /*   S: Erase Stratix Flash  */
#define M36_REG_DUMP		M_DEV_OF+0x09    /* G  : helper, dump Reg space */
#define M36_GET_RAWDAT		M_DEV_OF+0x0a    /* G  : get raw 18bit of chan ch */

/* M36 specific status codes (BLK)*/        /* S,G: S=setstat, G=getstat */
#define M36_BLK_FLASH    M_DEV_BLK_OF+0x00 	/* G,S: Write/Read calib. Data */



/*-----------------------------------------+
|  PROTOTYPES                              |
+-----------------------------------------*/
#ifdef _LL_DRV_

#ifndef _ONE_NAMESPACE_PER_DRIVER_
extern void M36_GetEntry(LL_ENTRY* drvP);
extern void M36_SW_GetEntry(LL_ENTRY* drvP);
#endif

#endif /* _LL_DRV_ */

/*-----------------------------------------+
|  BACKWARD COMPATIBILITY TO MDIS4         |
+-----------------------------------------*/
#ifndef U_INT32_OR_64
 /* we have an MDIS4 men_types.h and mdis_api.h included */
 /* only 32bit compatibility needed!                     */
 #define INT32_OR_64  int32
 #define U_INT32_OR_64 u_int32
 typedef INT32_OR_64  MDIS_PATH;
#endif /* U_INT32_OR_64 */


#ifdef __cplusplus
      }
#endif

#endif /* _M36_DRV_H */

