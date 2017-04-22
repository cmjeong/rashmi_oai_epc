/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains


     File:     wr_sw_version.c

     Sid:      fc_sw_version_pal_fdd.c@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:43:34 2014

     Prg:      sasahni

*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include <stdio.h>
#include <string.h>
#include "wr.h"

#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
/*
 *       Fun:     wrGetSwVersion
 *
 *       Desc:    This will display software verion string to caller.
 *
 *       Ret:     ROK   - OK / RFAILED - Failure
 *
 *       Notes :  None.
 */
/* TeNB_TIP_TYPE-1_<rel version-updated only when l3 and ul2 is
 * releasd>.<sub-rel when only l3 or ul2 is released>.<test binary release
 * version> */
const char * wrSwVersion = "TeNB_TIP_TYPE-1_v1.0.0";

PUBLIC const char * wrGetSwVersion(Void)
{
   RETVALUE(wrSwVersion);
}

const char * wrSwVersion_LL2 = "TeNB_TIP_TYPE-1_v1.0.0";
PUBLIC const char * wrGetSwVersion_LL2(Void)
{
   RETVALUE(wrSwVersion_LL2);
}


const char * wrSwVersion_UL2 = "TeNB_TIP_TYPE-1_v1.1.0";
PUBLIC const char * wrGetSwVersion_UL2(Void)
{
   RETVALUE(wrSwVersion_UL2);
}

/********************************************************************30**

           End of file:     fc_sw_version_pal_fdd.c@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:43:34 2014

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1        ---      sasahni         1. initial release
*********************************************************************91*/

