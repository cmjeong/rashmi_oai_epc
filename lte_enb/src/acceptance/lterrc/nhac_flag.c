
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      nhac_flag.c@@/main/2 - Fri Jul  1 01:13:01 2011

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

#include "cm_xta.h"
#include "cm_xta_app.h"

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"
#include "cm_xta_app.x"

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
PUBLIC S16 cmXtaAppLoadFindnCreate
(
Void  *msg,
Bool  *newCall,
CmXtaLoadCb  **loadCb
)
#else
PUBLIC S16 cmXtaAppLoadFindnCreate(msg, newCall, loadCb)
Void  *msg;
Bool  *newCall;
CmXtaLoadCb  **loadCb;
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppLoadFindnCreate() */

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
PUBLIC S16 cmXtaAppLoadFreeMsg
(
Void     *loadMsg
)
#else
PUBLIC S16 cmXtaAppLoadFreeMsg(loadMsg)
Void     *loadMsg;
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppLoadFreeMsg() */

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
PUBLIC S16 cmXtaAppLoadDelete
(
CmXtaLoadCb  *loadCb,
Bool      fail
)
#else
PUBLIC S16 cmXtaAppLoadDelete(loadCb, fail)
CmXtaLoadCb  *loadCb;
Bool      fail;
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppLoadDelete() */

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
PUBLIC S16 cmXtaAppLoadInit
(
)
#else
PUBLIC S16 cmXtaAppLoadInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}

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
PUBLIC S16 cmXtaAppLoadGetCurStep
(
Void  *loadMsg,
CmXtaLoadCb  *loadCb,
U16   *curLoadIndx,
U16   *retransLoadIndx
)
#else
PUBLIC S16 cmXtaAppLoadGetCurStep(loadMsg, loadCb, curLoadIndx, retransLoadIndx)
Void  *loadMsg;
CmXtaLoadCb  *loadCb;
U16   *curLoadIndx;
U16   *retransLoadIndx;
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}

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
PUBLIC S16 cmXtaAppLoadEngine
(
CmXtaLoadCb    *loadCb,
Void        *loadMsg,
Bool        retransMode,
U16         curLoadIndx,
U16         retransLoadIndx
)
#else
PUBLIC S16 cmXtaAppLoadEngine(loadCb, loadMsg, retransMode, curLoadIndx,retransLoadIndx)
CmXtaLoadCb    *loadCb;
Void        *loadMsg;
Bool        retransMode;
U16         curLoadIndx;
U16         retransLoadIndx;
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}

/* DEBUGP has value of 17 in cm_xta_py.py. Hence the following 
   arrays have been populated to accomodate this. */
/*nh002.301: index of DEBUGP changed due the changed in common xta python
             Added new flags */   
Bool cmXtaFlag[CMXTA_MAX_FLAGS] = 
{
   FALSE,
   TRUE,
#ifdef NH_LOG_TO_FILE   
   TRUE,
#else
   FALSE,
#endif   
   FALSE,
#ifdef TENB_MULT_CELL_SUPPRT
   TRUE,
#else
   FALSE,
#endif   
#ifdef NH_ASN_COND_VALIDATE
   TRUE,
#else
   FALSE,
#endif   
#ifdef RRC_PHY_CFG_SUPP
   TRUE,
#else
   FALSE,
#endif   
#ifdef LTERRC_REL9
   TRUE,
#else
   FALSE,
#endif   
#ifdef NHU_VER1
   TRUE,
#else
   FALSE,
#endif   
#ifdef CTF_VER1
   TRUE,
#else
   FALSE,
#endif   
#ifdef NHU_VER2
   TRUE,
#else
   FALSE,
#endif   
#ifdef CTF_VER2
   TRUE,
#else
   FALSE,
#endif   
#ifdef LNH_VER1
   TRUE,
#else
   FALSE,
#endif
#ifdef LTE_ADV
   TRUE,
#else
   FALSE,
#endif 
   FALSE,
   FALSE,
   FALSE,
#ifdef DEBUGP
   TRUE,
#else
   FALSE,
#endif   
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE
};

Txt  cmXtaFlagStr[CMXTA_MAX_FLAGS][50] =
{
"Unknown Ifdef",
   "Unknown Ifndef",
   "NH_LOG_TO_FILE",
   "Unknown Ifdef",
   "TENB_MULT_CELL_SUPPRT",
   "NH_ASN_COND_VALIDATE",
   "RRC_PHY_CFG_SUPP",
   "LTERRC_REL9",
   "NHU_VER1",
   "CTF_VER1",
   "NHU_VER2",
   "CTF_VER2",
   "LNH_VER1",
   "LTE_ADV",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"DEBUGP",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
"Unknown Ifdef",
};

/* CmXtaTop not defined Anywhere. Commenting it out. */
/*PUBLIC CmXtaTop cmXtaTopo =
{
   3
};*/


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
PUBLIC S16 cmXtaAppTst
(
Void
)
#else
PUBLIC S16 cmXtaAppTst()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTst */

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
PUBLIC S16 cmXtaAppInit
(
Void
)
#else
PUBLIC S16 cmXtaAppInit(Void)
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppInit */

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
PUBLIC S16 cmXtaAppDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppDeInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppDeInit */

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
PUBLIC S16 cmXtaAppParseCmdLine
(
Void
)
#else
PUBLIC S16 cmXtaAppParseCmdLine()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppParseCmdLine */

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
PUBLIC Void cmXtaAppUsage
(
Void
)
#else
PUBLIC Void cmXtaAppUsage()
#endif
{
   RETVOID;
} /* cmXtaAppUsage */


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
PUBLIC S16 cmXtaAppTCCreate
(
CmXtaTCCb         *tcCb
)
#else
PUBLIC S16 cmXtaAppTCCreate(tcCb)
CmXtaTCCb    *tcCb;
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppTCCreate() */

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
PUBLIC S16  cmXtaAppTCDelete
(
CmXtaTCCb         *tcCb       /* Transaction Block   */
)
#else
PUBLIC S16  cmXtaAppTCDelete (tcCb)
CmXtaTCCb      *tcCb;         /* Transaction Block   */
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppTCDelete */

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
PUBLIC S16 cmXtaAppInitQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC S16 cmXtaAppInitQ(msgQ)
CmXtaMsgQ   *msgQ;
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaAppInitQ */

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
PUBLIC Void cmXtaAppFlushQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC Void cmXtaAppFlushQ(msgQ)
CmXtaMsgQ *msgQ;
#endif
{
   RETVOID;
} /* cmXtaAppFlushQ */

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
PUBLIC S16 cmXtaAppPyInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaAppPyInit */

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
PUBLIC S16 cmXtaAppPyDeInit
(
Void
)
#else
PUBLIC S16 cmXtaAppPyDeInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaAppPyDeInit */

/********************************************************************30**

         End of file:     nhac_flag.c@@/main/2 - Fri Jul  1 01:13:01 2011

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
/main/1      ---    up               1. Main release
/main/2      ---    st               1. Commenting out CmXtaTop. It shall be used by the specific layer.
/main/1      ---    chebli           1. RRC Release 2.1.
/main/2      ---    sbalakrishna     1. Updated for Release of 3.1.
            nh002.301 mpatel         2. DEBUGP index is changed due to index change in python file
*********************************************************************91*/
