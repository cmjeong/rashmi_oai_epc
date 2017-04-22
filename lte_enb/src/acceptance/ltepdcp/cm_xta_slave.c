
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_slave.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:28 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */
#include "cm_inet.h"        /* common inet */

#include "cm_xta.h"
/* cm_xta_slave_c_001.main_4 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */
#include "cm_inet.x"        /* common inet */

#include "cm_xta.x"
#include <stdlib.h>
/* cm_xta_slave_c_001.main_4 Removed cm_xta_app.x for Psf-Diameter 1.1 */
#ifndef CMXTA_MASTER
U16 topCount;
PUBLIC CmXtaCb cmXtaCb;

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 tst
(
Void
)
#else
PUBLIC S16 tst()
#endif
{
   S16  ret;

   TRC2(tst)

   /* Basic Init */
   if (cmXtaSlavePreInit() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_INFO((_cmxtap, "tst(): pre init failed, exiting\n"));

      RETVALUE(CMXTA_ERR_INT);
   }

   /* check and process command line options            */
   if (cmXtaParseDebug() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_INFO((_cmxtap, "tst(): parse debug failed, exiting\n"));

      SExit();
      RETVALUE(CMXTA_ERR_INT);
   }

   if ((ret = cmXtaSlaveTst()) != CMXTA_ERR_NONE)
   {
      if (ret == CMXTA_ERR_INT)
      {
         CMXTA_DBG_INFO((_cmxtap, "tst(): slave mode failed, exiting\n"));
      }

      SExit();
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* tst */
#endif

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaSlaveTst
(
Void
)
#else
PUBLIC S16 cmXtaSlaveTst()
#endif
{
   TRC2(cmXtaSlaveTst)

   /* check and process command line options            */
   if (cmXtaSlaveParseCmdLine() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaSlaveTst(): slave parse cmdline failed, exiting\n"));

      RETVALUE(RFAILED);
   }

   /* Init */
   if (cmXtaSlaveInit() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaSlaveTst(): slave init failed, exiting\n"));

      RETVALUE(RFAILED);
   }

   CMXTA_DBG_INFO((_cmxtap, "cmXtaSlaveTst(): Initiating testing\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaSlaveTst */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaSlavePreInit
(
Void
)
#else
PUBLIC S16 cmXtaSlavePreInit(Void)
#endif
{
   U8 cnt;

   TRC2(cmXtaSlavePreInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaSlavePreInit(): Pre Initializing\n"));

#ifndef SS_MULTIPLE_PROCS
   SSetProcId(CMXTA_PROCID_SLAVE);
#endif

   CMXTA_DBG_INFO((_cmxtap, "cmXtaSlavePreInit(): Pre Init Done\n"));

   /*-- Set default IPC Port --*/
   /*cm_xta_slave_c_002.main_1  Updated the port Base in the FTHA Integartion to change the Master/Slave
    * port*/
   cmXtaCb.ipcPort = 18000;
   cmXtaCb.portBase = 0;
   cmInetAddr("127.0.0.1", &cmXtaCb.localIpcIpAddr);
   cmInetAddr("127.0.0.1", &cmXtaCb.remoteIpcIpAddr);

   /*-- Update total profile/topology count --*/
   topCount = 0;
   for (cnt = 0; cnt < sizeof(cmXtaTop)/sizeof(cmXtaTop[0]); cnt++)
   {
      /*-- Break at first not valid topology --*/
      if (cmXtaTop[cnt].valid == FALSE)
         break;

      topCount++;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaSlavePreInit */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaSlaveInit
(
Void
)
#else
PUBLIC S16 cmXtaSlaveInit(Void)
#endif
{
   S16      ret;
#ifdef CMXTA_FTHA_INTEGRATED
   Pst      pst;
   Buffer *mBuf;
#endif

   TRC2(cmXtaSlaveInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaSlaveInit(): Initializing the Test Architecture\n"));

   /* Register all layer instances */
   if ((ret = cmXtaRegister()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /* cm_xta_slave_c_001.main_1 :Support for multiple proc */
   /*-- If running in multiple binary mode, bring up IPC module
        before we do anything else --*/
   if ((cmXtaCb.masterMode != CMXTA_TA_INST_NONE) &&
       (cmXtaAppIpcInit()  != CMXTA_ERR_NONE))
   {
      CMXTA_DBG_INFO((_cmxtap, "tst(): IPC init failed, exiting\n"));

      SExit();

      RETVALUE(CMXTA_ERR_INT);
   }


   if ((ret = cmXtaAppSlaveInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);


   CMXTA_DBG_INFO((_cmxtap, "cmXtaSlaveInit(): Init Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaSlaveInit */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaSlaveDeInit
(
Void
)
#else
PUBLIC S16 cmXtaSlaveDeInit()
#endif
{
   TRC2(cmXtaSlaveDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaSlaveDeInit(): Shutting down the Test Architecture\n"));

   /*-- Opposite of the steps done in cmXtaSlaveInit --*/

   /*-- Put DeInit functions for rest of the
        modules here, this will happen only once --*/

   (Void)cmXtaAppIpcDeInit();

   (Void)cmXtaAppSlaveDeInit();

   /*-- Destroy all system tasks --*/
   cmXtaDeRegister(TRUE);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaSlaveDeInit(): Test Architecture Shutdown Done\n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaSlaveDeInit */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC Void cmXtaSlaveUsage
(
Void
)
#else
PUBLIC Void cmXtaSlaveUsage()
#endif
{
#ifndef CMXTA_MASTER
   U8  cnt;
#endif
   Txt   pBuf[100];  /* output string buffer */

   TRC2(cmXtaSlaveUsage);

#ifndef CMXTA_MASTER
   sprintf(pBuf, "\nUSAGE: %s [options]\n\n", msArgv[0]);
   SPrint(pBuf);

   sprintf(pBuf, "Global Options:\n===============\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "Common:\n------\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-o filename  ]   - Write output to 'filename'\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-f filename  ]   - Write memory cfg from 'filename'\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-A address   ]   - Set local IPC IP address\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-B address   ]   - Set remote IPC IP address\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-I port      ]   - Set IPC Port\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-S           ]   - Run in Slave mode\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-d 0-9       ]   - Turn ON debug flags\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-h           ]   - Print this usage message\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t[-x           ]   - End of option section\n");
   SPrint(pBuf);

   sprintf(pBuf, "\n");
   SPrint(pBuf);
#endif

   sprintf(pBuf, "Slave:\n------\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[None         ]\n");
   SPrint(pBuf);

   sprintf(pBuf, "\n");
   SPrint(pBuf);

#ifndef CMXTA_MASTER
   /*-- TA Options --*/
   sprintf(pBuf, "TA Options:\n===========\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t[-p profile   ]   - Set TA profile\n");
   SPrint(pBuf);
   for (cnt = 0; cnt < sizeof(cmXtaTop)/sizeof(cmXtaTop[0]); cnt++)
   {
      /*-- Break at first not valid topology --*/
      if (cmXtaTop[cnt].valid == FALSE)
         break;

      sprintf(pBuf, "\t                  - [%2d]: %s\n", cnt, cmXtaTop[cnt].descr);
      SPrint(pBuf);
   }

   sprintf(pBuf, "\n");
   SPrint(pBuf);
#endif

#ifndef CMXTA_MASTER
   cmXtaAppSlaveUsage();
#endif

   RETVOID;
} /* cmXtaSlaveUsage */

#ifndef CMXTA_MASTER
/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 rdConQ
(
Data data
)
#else
PUBLIC S16 rdConQ(data)
Data data;
#endif
{
   TRC2(rdConQ)

#ifdef DOS
   /* check if control-c */
   if (data == 0x03)
   {
      SExit();
   }
#else
#ifdef UNIX
   /* check if control-c */
   if (data == 0x03)
   {
      SExit();
   }
#else
#ifdef MVME162_1
   /* check if control-c */
   if (data == 0x03)
   {
      SExit();
   }
#else
#ifdef WIN32
   /* check if control-c */
   if (data == 0x03)
   {
      SExit();
   }
#else
#endif /* WIN32 */
#endif /* MVME162_1 */
#endif /* UNIX */
#endif /* DOS */

   cmXtaSlaveParseRdConQ(data);

   RETVALUE(CMXTA_ERR_NONE);
}/* rdConQ */
#endif

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaSlaveParseRdConQ
(
Data data
)
#else
PUBLIC S16 cmXtaSlaveParseRdConQ(data)
Data data;
#endif
{
   U32  memAvail;

   TRC2(cmXtaSlaveParseRdConQ)

   switch (data)
   {
      case 'm' :
      case 'M' :
         SRegInfoShow(cmXtaCb.init.region, &memAvail);
         break;

      case 'x' :
      case 'X' :
         SExit();

         break;

      case 'q' :
      case 'Q' :
         /*-- Shutdown the system --*/
         cmXtaSlaveDeInit();

         SExit();

         break;

      default :
         break;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaSlaveParseRdConQ */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaSlaveParseCmdLine
(
Void
)
#else
PUBLIC S16 cmXtaSlaveParseCmdLine()
#endif
{
   S16          ret;                            /* return value         */
   Bool         loop;

   TRC2(cmXtaSlaveParseCmdLine)

   /*-- SSI options skipped, move to TA options --*/
   loop = TRUE;
   /* parse the command line parameters                         */
   while ((loop == TRUE) &&
          ((ret = SGetOpt(msArgc, msArgv, "d:hn:p:x")) != EOF))
   {
      switch(ret)
      {
         case 'x':
            /*-- No match, assume same as -x and move on --*/
            loop = FALSE;
            break;

         case 'h':
            /* help and unknown options display help message    */
            cmXtaSlaveUsage();
            RETVALUE(RFAILED);
            break;

         case 'd':
            /*-- Set debug level --*/
            cmXtaCb.dbgMask = atoi(msOptArg);
            break;

         case 'n':
            /*-- Which node we are running on --*/
            cmXtaCb.curNode = atoi(msOptArg);
            break;

         case 'p':
            /*-- to set the profile --*/
            cmXtaCb.curTopId = atoi(msOptArg);

            if (cmXtaCb.curTopId >= topCount)
            {
               SPrint("ERROR: Invalid profile Id");
               SPrint("\n\n");
               cmXtaSlaveUsage();
               RETVALUE(RFAILED);
            }

            break;

         case '?':
         default:
            /*-- No match, assume same as -x and move on --*/
            /*-- Reset parsed instance --*/
            msOptInd -= 1;
            loop = FALSE;
            break;
      }
   }

   /* check and process command line options            */
   if ((ret = cmXtaAppSlaveParseCmdLine()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaSlaveParseCmdLine */

/* cm_xta_slave_c_002.main_1 All the Layers are required to add the ifndef ACC flag here as this function
 * definition is required whenever the only slave of the Layer is required to
 * run or even in the case when ACC flag is not enabled.This definition is kept
 * in this file as it is required both in case of master and slave*/

/* cm_xta_slave_c_001.main_3: Moved the function to cm_xta_lshhdl.c file as 
 * it is specific to sh */

/********************************************************************30**

         End of file:     cm_xta_slave.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:28 2015

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
/main/1      ----     up  1. Main release
/main/2      ---      cm_xta_slave_c_001.main_1  sk  1. Support for multiple proc
/main/3      ---      aj  1. Updated port base for FTHA Integration  
/main/4      ---      cm_xta_slave_c_001.main_3 pka 1. Moved the ShMiLshCntrlCfm function to 
                                       cm_xta_lshhdl.c file.
/main/5      ----     cm_xta_slave_c_001.main_4 jj 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx]
*********************************************************************91*/
