

/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for portable definitions for Layer Manager
               Interface primitives.
  
     File:     ys_ptmi.c 
  
     Sid:      ys_ptmi.c@@/main/2 - Thu Dec  2 02:27:24 2010
  
     Prg:      rk
  
**********************************************************************/

/** @file ys_ptmi.c
@brief This file contains the definitions for Layer Manager
       Interface primitives that are invoked from YS to Layer Manager
       (Confirmations and Indications) Portable functions corresponding
       to these primitives are also defined.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management defines for LTE-CL */
#include "tfu.h"

#include "ys_pal_err.h"        /* YS error defines */


/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"


/*ys004.102 MSPD merge for PHY 1.7*/
#if !(defined(LCYSMILYS) && defined(SM))
#define PTYSMILYS
#endif

#define YS_MAX_LYS_USR 2 

/* portable functions at LYS interface */
#ifdef PTYSMILYS
EXTERN S16 PtMiLysCfgCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 PtMiLysStsCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 PtMiLysStaCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 PtMiLysStaInd ARGS((Pst *pst, YsMngmt *usta));
EXTERN S16 PtMiLysCntrlCfm ARGS((Pst *pst, YsMngmt *cfm));
EXTERN S16 PtMiLysTrcInd ARGS((Pst *pst, YsMngmt *trc,Buffer *mBuf));
#endif

/* ***********LYS interface Mapping matrices ********************/

/** @brief Configuration Confirm primitive Matrix 
 *  This matrix defines the mapping between the configuration confirm
 *  primitive called by the upper interface of YS layer and the 
 *  corresponding primitives of the YS layer service user(s).
 *
 *  The parameter YS_MAX_LYS_USR defines the maximum number of Layer 
 *  managers of YS at the LYS interface. This is an array of functions
 *  per primitive invoked by YS whose size is YS_MAX_LYS_USR.
 * 
 *  The dispatching is performed by the configurable variable: selector.
 *  The selector is configured on a per SAP basis. The selectors are:
 *
 *  LCYSMILYS - loosely coupled LYS interface
 *  TCYSMILYS - Tightly coupled LYS interface
 *  
 *  In a similar fashion, the matrices for Status, Statistics and
 *  Control confirms and, Status and trace indications are defined.
 **/
PRIVATE CONSTANT LysCfgCfm YsMiLysCfgCfmMt[YS_MAX_LYS_USR] =
{
#ifdef LCYSMILYS
   cmPkLysCfgCfm,                  /* 0 - loosely coupled */
#else
   PtMiLysCfgCfm,                  /* 0 - loosely coupled */
#endif
#ifdef SM 
   SmMiLysCfgCfm,                  /* 1 - Tightly coupled SM */
#else
   PtMiLysCfgCfm,                  /* 1 - Tightly coupled SM  */
#endif
};

/** @brief Statistics Confirm primitive Matrix */
PRIVATE CONSTANT LysStsCfm YsMiLysStsCfmMt[YS_MAX_LYS_USR] =
{
#ifdef LCYSMILYS
   cmPkLysStsCfm,                  /* 0 - loosely coupled */
#else
   PtMiLysStsCfm,                  /* 0 - loosely coupled */
#endif
#ifdef SM 
   SmMiLysStsCfm,                  /* 1 - Tightly coupled SM */
#else
   PtMiLysStsCfm,                  /* 1 - Tightly coupled SM  */
#endif
};

/** @brief Status Confirm primitive Matrix */
PRIVATE CONSTANT LysStaCfm YsMiLysStaCfmMt[YS_MAX_LYS_USR] =
{
#ifdef LCYSMILYS
   cmPkLysStaCfm,                  /* 0 - loosely coupled */
#else
   PtMiLysStaCfm,                  /* 0 - loosely coupled */
#endif
#ifdef SM 
   SmMiLysStaCfm,                  /* 1 - Tightly coupled SM */
#else
   PtMiLysStaCfm,                  /* 1 - Tightly coupled SM  */
#endif
};


/** @brief Status Indication primitive Matrix */
PRIVATE CONSTANT LysStaInd YsMiLysStaIndMt[YS_MAX_LYS_USR] =
{
#ifdef LCYSMILYS
   cmPkLysStaInd,                  /* 0 - loosely coupled */
#else
   PtMiLysStaInd,                  /* 0 - loosely coupled */
#endif
#ifdef SM 
   SmMiLysStaInd,                  /* 1 - Tightly coupled SM */
#else
   PtMiLysStaInd,                  /* 1 - Tightly coupled SM  */
#endif
};


/** @brief Control Confirm primitive Matrix */
PRIVATE CONSTANT LysCntrlCfm YsMiLysCntrlCfmMt[YS_MAX_LYS_USR] =
{
#ifdef LCYSMILYS
   cmPkLysCntrlCfm,                  /* 0 - loosely coupled */
#else
   PtMiLysCntrlCfm,                  /* 0 - loosely coupled */
#endif
#ifdef SM 
   SmMiLysCntrlCfm,                  /* 1 - Tightly coupled SM */
#else
   PtMiLysCntrlCfm,                  /* 1 - Tightly coupled SM  */
#endif
};


/** @brief Trace Indication primitive Matrix */
PRIVATE CONSTANT LysTrcInd YsMiLysTrcIndMt[YS_MAX_LYS_USR] =
{
#ifdef LCYSMILYS
   cmPkLysTrcInd,                  /* 0 - loosely coupled */
#else
   PtMiLysTrcInd,                  /* 0 - loosely coupled */
#endif
#ifdef SM 
   SmMiLysTrcInd,                  /* 1 - Tightly coupled SM */
#else
   PtMiLysTrcInd,                  /* 1 - Tightly coupled SM  */
#endif
};


#ifdef YS


/**
 * @brief Layer Manager Configuration confirm handler. 
 *
 * @details
 *
 *     Function : YsMiLysCfgCfm
 *     
 *     This function handles the configuration
 *     confirm invoked by YS to Layer Manager.
 *     -# Based on the pst->selector value it invokes one of the
 *        functions cmPkLysCfgCfm() or SmMiLysCfgCfm().
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *cfm, the configuration confirm structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 YsMiLysCfgCfm
(
Pst      *pst,    /* post structure  */
YsMngmt  *cfm     /* config confirm structure  */
)
#else
PUBLIC S16 YsMiLysCfgCfm(pst, cfm)
Pst      *pst;    /* post structure  */
YsMngmt  *cfm;    /* config confirm structure  */
#endif    
{
   
   TRC3(YsMiLysCfgCfm);

   (*YsMiLysCfgCfmMt[pst->selector])(pst, cfm);

   RETVALUE(ROK);
   
}/*-- YsMiLysCfgCfm --*/


/**
 * @brief Layer Manager Statistics confirm handler. 
 *
 * @details
 *
 *     Function : YsMiLysStsCfm
 *     
 *     This function handles the statistics
 *     confirm invoked by YS to Layer Manager.
 *     -# Based on the pst->selector value it invokes one of the
 *        functions cmPkLysStsCfm() or SmMiLysStsCfm().
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *cfm, the statistics confirm structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 YsMiLysStsCfm
(
Pst      *pst,    /* post structure  */
YsMngmt  *cfm     /* statistics confirm structure  */
)
#else
PUBLIC S16 YsMiLysStsCfm(pst, cfm)
Pst      *pst;    /* post structure  */
YsMngmt  *cfm;    /* statistics confirm structure  */
#endif    
{
   
   TRC3(YsMiLysStsCfm);

   (*YsMiLysStsCfmMt[pst->selector])(pst, cfm);

   RETVALUE(ROK);
   
}/*-- YsMiLysStsCfm --*/


/**
 * @brief Layer Manager Status confirm handler. 
 *
 * @details
 *
 *     Function : YsMiLysStaCfm
 *     
 *     This function handles the status
 *     confirm invoked by YS to Layer Manager.
 *     -# Based on the pst->selector value it invokes one of the
 *        functions cmPkLysStaCfm() or SmMiLysStaCfm().
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *cfm, the status confirm structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 YsMiLysStaCfm
(
Pst      *pst,    /* post structure  */
YsMngmt  *cfm     /* status confirm structure  */
)
#else
PUBLIC S16 YsMiLysStaCfm(pst, cfm)
Pst      *pst;    /* post structure  */
YsMngmt  *cfm;    /* status confirm structure  */
#endif    
{
   
   TRC3(YsMiLysStaCfm);
    
   (*YsMiLysStaCfmMt[pst->selector])(pst,cfm);

   RETVALUE(ROK);
   
}/*-- YsMiLysStaCfm --*/


/**
 * @brief Layer Manager Control confirm handler. 
 *
 * @details
 *
 *     Function : YsMiLysCntrlCfm
 *     
 *     This function handles the control
 *     confirm invoked by YS to Layer Manager.
 *     -# Based on the pst->selector value it invokes one of the
 *        functions cmPkLysCntrlCfm() or SmMiLysCntrlCfm().
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *cfm, the control confirm structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 YsMiLysCntrlCfm
(
Pst      *pst,    /* post structure  */
YsMngmt  *cfm     /* control confirm structure  */
)
#else
PUBLIC S16 YsMiLysCntrlCfm(pst, cfm)
Pst      *pst;    /* post structure  */
YsMngmt  *cfm;    /* control confirm structure  */
#endif    
{
   
   TRC3(YsMiLysCntrlCfm);

   (*YsMiLysCntrlCfmMt[pst->selector])(pst,cfm);

   RETVALUE(ROK);
   
}/*-- YsMiLysCntrlCfm --*/


/**
 * @brief Layer Manager Unsolicited Status Indication handler. 
 *
 * @details
 *
 *     Function : YsMiLysStaInd
 *     
 *     This function handles the unsolicited status
 *     Indication invoked by YS to Layer Manager.
 *     -# Based on the pst->selector value it invokes one of the
 *        functions cmPkLysStaInd() or SmMiLysStaInd().
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *usta, the status indication structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 YsMiLysStaInd
(
Pst      *pst,    /* post structure  */
YsMngmt  *usta    /* status indication structure  */
)
#else
PUBLIC S16 YsMiLysStaInd(pst, usta)
Pst      *pst;    /* post structure  */
YsMngmt  *usta;    /* status indication structure  */
#endif    
{
   
   TRC3(YsMiLysStaInd);

   (*YsMiLysStaIndMt[pst->selector])(pst,usta);

   RETVALUE(ROK);
   
}/*-- YsMiLysStaInd --*/



/**
 * @brief Layer Manager Trace Indication handler. 
 *
 * @details
 *
 *     Function : YsMiLysTrcInd
 *     
 *     This function handles the trace
 *     Indication invoked by YS to Layer Manager.
 *     -# Based on the pst->selector value it invokes one of the
 *        functions cmPkLysTrcInd() or SmMiLysTrcInd().
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *trc, the trace event
 *  @param[in]  Buffer *mBuf, the trace message
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 YsMiLysTrcInd
(
Pst      *pst,    /* post structure  */
YsMngmt  *trc,    /* Trace event  */
Buffer   *mBuf    /* Trace message  */
)
#else
PUBLIC S16 YsMiLysTrcInd(pst, trc, mBuf)
Pst      *pst;    /* post structure  */
YsMngmt  *trc;    /* Trace event  */
Buffer   *mBuf;   /* Trace message  */
#endif    
{
   
   TRC3(YsMiLysTrcInd);

   (*YsMiLysTrcIndMt[pst->selector])(pst,trc,mBuf);

   RETVALUE(ROK);
   
}/*-- YsMiLysTrcInd --*/

#endif /*-- MK --*/

#ifdef PTYSMILYS

/**
 * @brief Portable Function definition for Layer Manager Configuration
 *         confirm handler. 
 *
 * @details
 *
 *     Function : PtMiLysCfgCfm
 *     
 *     This function handles the configuration
 *     confirm invoked by YS to Layer Manager.
 *     Users of YS who intend to provide a glue logic 
 *     for portability of Configuration Confirm are expected 
 *     to fill in the code in this function definition.
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *cfm, the configuration confirm structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 PtMiLysCfgCfm
(
Pst *pst,               /* post structure */
YsMngmt *cfm            /* Config Confirm */
)
#else
PUBLIC S16 PtMiLysCfgCfm  (pst, cfm)
Pst *pst;               /* post structure */
YsMngmt *cfm;           /* Config Confirm */
#endif
{
   TRC3(PtMiLysCfgCfm)

   RETVALUE(ROK);
}/* end of PtMiLysCfgCfm */



/**
 * @brief Portable Function definition for Layer Manager Statistics 
 *         confirm handler. 
 *
 * @details
 *
 *     Function : PtMiLysStsCfm 
 *     
 *     This function handles the statistics 
 *     confirm invoked by YS to Layer Manager.
 *     Users of YS who intend to provide a glue logic 
 *     for portability of statistics Confirm are expected 
 *     to fill in the code in this function definition.
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *cfm, the statistics confirm structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 PtMiLysStsCfm
(
Pst *pst,               /* post structure */
YsMngmt *cfm            /* Statistics Confirm */
)
#else
PUBLIC S16 PtMiLysStsCfm  (pst, cfm)
Pst *pst;               /* post structure */
YsMngmt *cfm;           /* Statistics Confirm */
#endif
{
   TRC3(PtMiLysStsCfm)

   RETVALUE(ROK);
}/* end of PtMiLysStsCfm */



/**
 * @brief Portable Function definition for Layer Manager Status 
 *         confirm handler. 
 *
 * @details
 *
 *     Function : PtMiLysStaCfm 
 *     
 *     This function handles the status 
 *     confirm invoked by YS to Layer Manager.
 *     Users of YS who intend to provide a glue logic 
 *     for portability of status Confirm are expected 
 *     to fill in the code in this function definition.
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *cfm, the status confirm structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 PtMiLysStaCfm
(
Pst *pst,               /* post structure */
YsMngmt *cfm            /* Status Confirm */
)
#else
PUBLIC S16 PtMiLysStaCfm  (pst, cfm)
Pst *pst;               /* post structure */
YsMngmt *cfm;           /* Status Confirm */
#endif
{
   TRC3(PtMiLysStaCfm)
   RETVALUE(ROK);
}/* end of PtMiLysStaCfm */



/**
 * @brief Portable Function definition for Layer Manager Status 
 *        Indication handler. 
 *
 * @details
 *
 *     Function : PtMiLysStaInd 
 *     
 *     This function handles the status 
 *     indication invoked by YS to Layer Manager.
 *     Users of YS who intend to provide a glue logic 
 *     for portability of status indication are expected 
 *     to fill in the code in this function definition.
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *cfm, the status indication structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 PtMiLysStaInd
(
Pst *pst,               /* post structure */
YsMngmt *usta           /* Status Indication */
)
#else
PUBLIC S16 PtMiLysStaInd  (pst, usta)
Pst *pst;               /* post structure */
YsMngmt *usta;          /* Status indication */
#endif
{
   TRC3(PtMiLysStaInd)
   RETVALUE(ROK);
}/* end of PtMiLysStaInd */



/**
 * @brief Portable Function definition for Layer Manager Control 
 *         confirm handler. 
 *
 * @details
 *
 *     Function : PtMiLysCntrlCfm 
 *     
 *     This function handles the control 
 *     confirm invoked by YS to Layer Manager.
 *     Users of YS who intend to provide a glue logic 
 *     for portability of control Confirm are expected 
 *     to fill in the code in this function definition.
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *cfm, the control confirm structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 PtMiLysCntrlCfm
(
Pst *pst,               /* post structure */
YsMngmt *cfm            /* Control Confirm */
)
#else
PUBLIC S16 PtMiLysCntrlCfm (pst, cfm)
Pst *pst;               /* post structure */
YsMngmt *cfm;           /* Control Confirm */
#endif
{
   TRC3(PtMiLysCntrlCfm)
   RETVALUE(ROK);
}/* end of PtMiLysCntrlCfm */



/**
 * @brief Portable Function definition for Layer Manager Trace 
 *        Indication handler. 
 *
 * @details
 *
 *     Function : PtMiLysTrcInd 
 *     
 *     This function handles the trace 
 *     indication invoked by YS to Layer Manager.
 *     Users of YS who intend to provide a glue logic 
 *     for portability of trace indication are expected 
 *     to fill in the code in this function definition.
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  YsMngmt *cfm, the trace indication structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 PtMiLysTrcInd
(
Pst *pst,               /* post structure */
YsMngmt *trc,           /* Trace Event */
Buffer *mBuf            /* Trace message */
)
#else
PUBLIC S16 PtMiLysTrcInd (pst, trc,mBuf)
Pst *pst;               /* post structure */
YsMngmt *trc;           /* Trace Event */
Buffer *mBuf;           /* Trace message */
#endif
{
   TRC3(PtMiLysTrcInd)
   RETVALUE(ROK);
}/* end of PtMiLysTrcInd */

#endif /*--PTYSMILYS--*/


/**********************************************************************
 
         End of file:     ys_ptmi.c@@/main/2 - Thu Dec  2 02:27:24 2010
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/2      ---     sgm                   1. eNodeB 1.2 release
/main/1      ys004.102     vr              1. MSPD merge for PHY 1.7
*********************************************************************91*/
