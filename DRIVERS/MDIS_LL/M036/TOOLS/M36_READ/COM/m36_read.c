/****************************************************************************
 ************                                                    ************
 ************                 M 3 6 _ R E A D                    ************
 ************                                                    ************
 ****************************************************************************
 *
 *       Author: ds
 *
 *  Description: Configure and read M36 input channel
 *
 *     Required: usr_oss.l usr_utl.l
 *     Switches: -
 *
 *---------------------------------------------------------------------------
 * Copyright (c) 1998-2019, MEN Mikro Elektronik GmbH
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MEN/men_typs.h>
#include <MEN/usr_oss.h>
#include <MEN/usr_utl.h>
#include <MEN/mdis_api.h>
#include <MEN/m36_drv.h>

static const char IdentString[]=MENT_XSTR(MAK_REVISION);

/*--------------------------------------+
|   DEFINES                             |
+--------------------------------------*/

/*--------------------------------------+
|   PROTOTYPES                          |
+--------------------------------------*/
static void usage(void);
static void PrintError(char *info);

/********************************* usage ************************************
 *
 *  Description: Print program usage
 *
 *---------------------------------------------------------------------------
 *  Input......: -
 *  Output.....: -
 *  Globals....: -
 ****************************************************************************/
static void usage(void)
{
	printf("Usage: m36_read [<opts>] <device> [<opts>]\n");
	printf("Function: Configure and read M36 channel\n");
	printf("Options:\n");
	printf("    device       device name                 [none]\n");
	printf("    -c=<chan>    channel number (0..7/15)    [0]\n");
	printf("    -g=<gain>    gain factor                 [x1]\n");
	printf("                  0 = x1\n");
	printf("                  1 = x2\n");
	printf("                  2 = x4\n");
	printf("                  3 = x8\n");
	printf("                  4 = x16 (on-board jumper must be set !)\n");
	printf("    -m=<mode>    measuring mode              [unipolar]\n");
	printf("                  0=unipolar\n");
	printf("                  1=bipolar\n");
	printf("    -t=<trig>    trigger mode                [intern]\n");
	printf("                  0 = internal trigger	\n");
	printf("                  1 = external trigger	\n");
	printf("    -d=<mode>    display mode                [raw hex]\n");
	printf("                  0 = raw hex value \n");
	printf("                  1 = hex and volt	\n");
	printf("                  2 = hex and ampere (only for gain factor x8)\n");
	printf("    -l           loop mode                   [no]\n");
	printf("\n");
	printf("Copyright (c) 1998-2019, MEN Mikro Elektronik GmbH\n%s\n", IdentString);
}

/********************************* main *************************************
 *
 *  Description: Program main function
 *
 *---------------------------------------------------------------------------
 *  Input......: argc,argv	argument counter, data ..
 *  Output.....: return	    success (0) or error (1)
 *  Globals....: -
 ****************************************************************************/
int main(int argc, char **argv)
{
	MDIS_PATH path=0;
	int32	chan, gain, mode, disp, loopmode, value, trig, n, gainfac;
	char	*device, *str, *errstr, buf[40];
	double	volt, curr;

	/*--------------------+
    |  check arguments    |
    +--------------------*/
	if ((errstr = UTL_ILLIOPT("c=g=m=t=d=l?", buf))) {	/* check args */
		printf("*** %s\n", errstr);
		return(1);
	}

	if (UTL_TSTOPT("?")) {						/* help requested ? */
		usage();
		return(1);
	}

	/*--------------------+
    |  get arguments      |
    +--------------------*/
	for (device=NULL, n=1; n<argc; n++)
		if (*argv[n] != '-') {
			device = argv[n];
			break;
		}

	if (!device) {
		usage();
		return(1);
	}

	chan     = ((str = UTL_TSTOPT("c=")) ? atoi(str) : 0);
	gain     = ((str = UTL_TSTOPT("g=")) ? atoi(str) : 0);
	mode     = ((str = UTL_TSTOPT("m=")) ? atoi(str) : 0);
	trig     = ((str = UTL_TSTOPT("t=")) ? atoi(str) : 0);
	disp     = ((str = UTL_TSTOPT("d=")) ? atoi(str) : 0);
	loopmode = (UTL_TSTOPT("l") ? 1 : 0);

	/* check for option conflict */
	if ((disp == 2) && (gain != 3)) {
		printf("\n*** option -d=2 only available with option -g=3\n\n");
		usage();
		return(1);
	}

	gainfac = 1 << gain;		/* calculate gain factor */

	/*--------------------+
    |  open path          |
    +--------------------*/
	if ((path = M_open(device)) < 0) {
		PrintError("open");
		return(1);
	}

	/*--------------------+
    |  config             |
    +--------------------*/
	/* set measuring mode */
	if ((M_setstat(path, M36_BIPOLAR, mode)) < 0) {
		PrintError("setstat M36_BIPOLAR");
		goto abort;
	}
	/* set current channel */
	if ((M_setstat(path, M_MK_CH_CURRENT, chan)) < 0) {
		PrintError("setstat M_MK_CH_CURRENT");
		goto abort;
	}
	/* enable channel */
	if ((M_setstat(path, M36_CH_ENABLE, 1)) < 0) {
		PrintError("setstat M36_CH_ENABLE");
		goto abort;
	}
	/* check for SW gain */
	if (gain != 4) {
		/* set gain */
		if ((M_setstat(path, M36_CH_GAIN, gain)) < 0) {
			PrintError("setstat M36_CH_GAIN");
			goto abort;
		}
	}
	/* set trigger mode */
	if ((M_setstat(path, M36_EXT_TRIG, trig)) < 0) {
		PrintError("setstat M36_EXT_TRIG");
		goto abort;
	}

    /*--------------------+
    |  print info         |
    +--------------------*/
	printf("channel number      : %d\n", chan);
	printf("gain factor         : x%d\n", gainfac);
	printf("measuring mode      : %s\n",(mode==0 ? "unipolar":"bipolar"));
	printf("trigger mode        : %s\n\n",(trig==0 ? "intern":"extern"));

	/*--------------------+
    |  read               |
    +--------------------*/
	do {
		if ((M_read(path,&value)) < 0) {
			PrintError("read");
			goto abort;
		}
		switch (disp) {
			/* raw hex value */
			case 0:
				printf("read: 0x%04x (%s)\n",
					value, (mode==0 ? "unipolar":"bipolar"));
				break;
			/* voltage */
			case 1:
				if (mode)
					volt = (int16)value * 20.0 / 0xffff;	/* bipolar */
				else
					volt = (u_int16)value * 10.0 / 0xffff;	/* unipolar */
				printf("read: 0x%04x = %7.4f V (%s)\n",
					value, volt, (mode==0 ? "unipolar":"bipolar"));
				break;
			/* current */
			case 2:
				if (mode)
					curr = (int16)value * 40.0 / 0xffff;	/* bipolar */
				else
					curr = (u_int16)value * 20.0 / 0xffff;	/* unipolar */
				printf("read: 0x%04x = %7.4f mA (%s)\n",
					value, curr, (mode==0 ? "unipolar":"bipolar"));
				break;
			/* invalid */
			default:
				printf("*** option -d=%d out of range (-d=0..2)\n", disp);
		}

		UOS_Delay(100);
	} while(loopmode && UOS_KeyPressed() == -1);

	/*--------------------+
    |  cleanup            |
    +--------------------*/
	abort:
	if (M_close(path) < 0)
		PrintError("close");

	return(0);
}

/********************************* PrintError ********************************
 *
 *  Description: Print MDIS error message
 *
 *---------------------------------------------------------------------------
 *  Input......: info	info string
 *  Output.....: -
 *  Globals....: -
 ****************************************************************************/

static void PrintError(char *info)
{
	printf("*** can't %s: %s\n", info, M_errstring(UOS_ErrnoGet()));
}



