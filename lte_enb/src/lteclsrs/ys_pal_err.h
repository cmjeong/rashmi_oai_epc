
/**********************************************************************
 
     Name:    LTECL - Error File
  
     Type:    C include file 
  
     Desc:    Error defines required by LTECL layer
 
     File:    ys_err.h

     Sid:      ys_err.h@@/main/2 - Thu Dec  2 02:27:13 2010
  
     Prg:     ns
*********************************************************************21*/
 
/*
*     The defines declared in this file correspond to those
*     used by the following TRILLIUM software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000XXX     LTECL Layer
*
*/

#ifndef __YS_ERR_H__
#define __YS_ERR_H__

/* defines */

/* Layer name */
#define YS_LAYERNAME               "Ys"

/* Debug printing mask defines */
#define YS_DBGMASK_RES             0     /* encode/decode */
#define YS_DBGMASK_FATAL           1     /* encode/decode */
#define YS_DBGMASK_ERR             2     /* error conds   */
#define YS_DBGMASK_PARAM           3     /* param         */
#define YS_DBGMASK_INFO            4     /* informational */


#define _ysp                       ysCb.apb

#define YS_DBGP(_tskInit, _dbgMask, _layerName, _msgClass, _arg1, _arg2) \
{ \
   if (_dbgMask >= (_msgClass)) \
   { \
      /* ys005.102 TIC_ID:ccpu00119532 DEL: Removed SPrintf stufs */ \
      /* ys005.102 TIC_ID:ccpu00119532 ADD: Calling DBGP which inturn calls SPrintf*/ \
      DBGP(_tskInit, _layerName, _msgClass, (ysCb.apb, "%s", _arg1)); \
      DBGP(_tskInit, _layerName, _msgClass, _arg2);  \
      /* TIC_ID:ccpu00119532 ADD_END: Calling DBGP which inturn calls SPrintf */ \
   } \
}

#ifdef DEBUGP
#define YS_DBG_INT(_msgClass, _arg1, _arg2)    \
      YS_DBGP(&ysCb.ysInit, ysCb.ysInit.dbgMask, YS_LAYERNAME, _msgClass, _arg1, _arg2)
#else
#define YS_DBG_INT(_msgClass, _arg1, _arg2)   
#endif
#define YS_DBG_PRNT(_msgClass, _arg)     \
{\
   if (ysCb.ysInit.dbgMask >= (_msgClass)) \
   { \
      sprintf _arg; \
      SPrint(ysCb.apb); \
   } \
}


/* display error */
#define YS_DBG_ERR(_arg)    YS_DBG_INT(YS_DBGMASK_ERR,   "Failed: ", _arg)
/* display params */
#define YS_DBG_PARAM(_arg)  YS_DBG_INT(YS_DBGMASK_PARAM, "Param : ", _arg)
/* display call flow */
#define YS_DBG_INFO(_arg)   YS_DBG_INT(YS_DBGMASK_INFO,  "Info  : ", _arg)
/* display fatal error */
#define YS_DBG_FATAL(_arg)  YS_DBG_INT(YS_DBGMASK_FATAL, "** FATAL ** : ", _arg)
/* display result dump */
#define YS_DBG_RES(_arg)    YS_DBG_PRNT(YS_DBGMASK_RES, _arg)
/* ys004.102: g++ compilation and warning */
#define YS_LOGERROR(errCls, errCode, errVal, errDesc)                      \
        SLogError(ysCb.ysInit.ent, ysCb.ysInit.inst, ysCb.ysInit.procId,   \
                  /* ys005.102 : MOD: Fixed warnings for g++ compilation on Linux*/ \
                   __FILE__, __LINE__, errCls, errCode, (ErrVal)errVal,     \
                  /* ys005.102 : MOD_END: Fixed warnings for g++ compilation on Linux*/ \
                   errDesc);

#define YSLOGDBGERR(errCode, errVal, errDesc)                          \
        YS_LOGERROR(ERRCLS_DEBUG, errCode, errVal, errDesc)

#if (ERRCLASS & ERRCLS_DEBUG)
#define YS_LOGERR_DBG(errCode, errVal, errDesc)                        \
        YS_LOGERROR(ERRCLS_DEBUG, errCode, errVal, errDesc)
#else
#define YS_LOGERR_DBG(errCode, errVal, errDesc)
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
#define YS_LOGERR_INTPAR(errCode, errVal, errDesc)                       \
        YS_LOGERROR(ERRCLS_INT_PAR, errCode, errVal, errDesc)
#else
#define YS_LOGERR_INTPAR(errCode, errVal, errDesc)
#endif

/* error codes */
#define   EYSBASE 0
/*ys003.102 Removed warning*/
#define   ERRYS         (EYSBASE + 0)   /* reserved */
#define   ERRYST        (EYSBASE + 0)   /* reserved */

#define   YSERR_NONE    EYSBASE

#define   EYS001      (ERRYS +    1)    /*     ys_err.h: 188 */
#define   EYS002      (ERRYS +    2)    /*  ys_ms_cfg.c: 595 */
#define   EYS003      (ERRYS +    3)    /*  ys_ms_cfg.c: 602 */
#define   EYS004      (ERRYS +    4)    /*  ys_ms_cfg.c: 640 */
#define   EYS005      (ERRYS +    5)    /*  ys_ms_cfg.c: 750 */
#define   EYS006      (ERRYS +    6)    /*  ys_ms_cfg.c: 906 */
#define   EYS007      (ERRYS +    7)    /*  ys_ms_cfg.c: 990 */
#define   EYS008      (ERRYS +    8)    /*  ys_ms_cfg.c:1074 */
#define   EYS009      (ERRYS +    9)    /*  ys_ms_cfg.c:1137 */

#define   EYS010      (ERRYS +   10)    /*   ys_ms_ui.c: 222 */
#define   EYS011      (ERRYS +   11)    /*   ys_ms_ui.c: 232 */
#define   EYS012      (ERRYS +   12)    /*   ys_ms_ui.c: 292 */
#define   EYS013      (ERRYS +   13)    /*   ys_ms_ui.c: 301 */
#define   EYS014      (ERRYS +   14)    /*   ys_ms_ui.c: 390 */
#define   EYS015      (ERRYS +   15)    /*   ys_ms_ui.c: 413 */
#define   EYS016      (ERRYS +   16)    /*   ys_ms_ui.c: 436 */
#define   EYS017      (ERRYS +   17)    /*   ys_ms_ui.c: 447 */
#define   EYS018      (ERRYS +   18)    /*   ys_ms_ui.c: 457 */
#define   EYS019      (ERRYS +   19)    /*   ys_ms_ui.c: 510 */
#define   EYS020      (ERRYS +   20)    /*   ys_ms_ui.c: 519 */
#define   EYS021      (ERRYS +   21)    /*   ys_ms_ui.c: 585 */
#define   EYS022      (ERRYS +   22)    /*   ys_ms_ui.c: 625 */
#define   EYS023      (ERRYS +   23)    /*   ys_ms_ui.c: 742 */
#define   EYS024      (ERRYS +   24)    /*   ys_ms_ui.c: 754 */
#define   EYS025      (ERRYS +   25)    /*   ys_ms_ui.c: 764 */
#define   EYS026      (ERRYS +   26)    /*   ys_ms_ui.c: 803 */
#define   EYS027      (ERRYS +   27)    /*   ys_ms_ui.c:1217 */
#define   EYS028      (ERRYS +   28)    /*   ys_ms_ui.c:1224 */
#define   EYS029      (ERRYS +   29)    /*   ys_ms_ui.c:1235 */

#define   EYS030      (ERRYS +   30)    /*   ys_ms_ul.c: 278 */

#define   EYS031      (ERRYS +   31)    /*  ys_ms_utl.c: 816 */
#define   EYS032      (ERRYS +   32)    /*  ys_ms_utl.c:1153 */
#define   EYS033      (ERRYS +   33)    /*  ys_ms_utl.c:1193 */

#define   EYS034      (ERRYS +   34)    /*  ys_pc_msg.c:2427 */
#define   EYS035      (ERRYS +   35)    /*  ys_pc_msg.c:2442 */
#define   EYS036      (ERRYS +   36)    /*  ys_pc_msg.c:2835 */
#define   EYS037      (ERRYS +   37)    /*  ys_pc_msg.c:4079 */
#define   EYS038      (ERRYS +   38)    /*  ys_pc_msg.c:4660 */
#define   EYS039      (ERRYS +   39)    /*  ys_pc_msg.c:4854 */
#define   EYS040      (ERRYS +   40)    /*  ys_pc_msg.c:4866 */

#define   EYS041      (ERRYS +   41)    /*  ys_pc_utl.c: 171 */
#define   EYS042      (ERRYS +   42)    /*  ys_pc_utl.c: 250 */
#define   EYS043      (ERRYS +   43)    /*  ys_pc_utl.c: 300 */
#define   EYS044      (ERRYS +   44)    /*  ys_pc_utl.c: 413 */
#define   EYS045      (ERRYS +   45)    /*  ys_pc_utl.c: 490 */
#define   EYS046      (ERRYS +   46)    /*  ys_pc_utl.c: 526 */
#define   EYS047      (ERRYS +   47)    /*  ys_pc_utl.c: 598 */
#define   EYS048      (ERRYS +   48)    /*  ys_pc_utl.c: 671 */
#define   EYS049      (ERRYS +   49)    /*  ys_pc_utl.c: 944 */
#define   EYS050      (ERRYS +   50)    /*  ys_pc_utl.c:1023 */

#define   EYST001      (ERRYST +    1)    /*      ys_ui.c: 279 */
#define   EYST002      (ERRYST +    2)    /*      ys_ui.c: 289 */
#define   EYST003      (ERRYST +    3)    /*      ys_ui.c: 346 */
#define   EYST004      (ERRYST +    4)    /*      ys_ui.c: 355 */
#define   EYST005      (ERRYST +    5)    /*      ys_ui.c: 450 */
#define   EYST006      (ERRYST +    6)    /*      ys_ui.c: 473 */
#define   EYST007      (ERRYST +    7)    /*      ys_ui.c: 496 */
#define   EYST008      (ERRYST +    8)    /*      ys_ui.c: 507 */
#define   EYST009      (ERRYST +    9)    /*      ys_ui.c: 586 */
#define   EYST010      (ERRYST +   10)    /*      ys_ui.c: 593 */
#define   EYST011      (ERRYST +   11)    /*      ys_ui.c: 601 */
#define   EYST012      (ERRYST +   12)    /*      ys_ui.c: 636 */
#define   EYST013      (ERRYST +   13)    /*      ys_ui.c: 739 */
#define   EYST014      (ERRYST +   14)    /*      ys_ui.c: 813 */
#define   EYST015      (ERRYST +   15)    /*      ys_ui.c: 868 */
#define   EYST016      (ERRYST +   16)    /*      ys_ui.c: 963 */
#define   EYST017      (ERRYST +   17)    /*      ys_ui.c:1048 */
#define   EYST018      (ERRYST +   18)    /*      ys_ui.c:1120 */
#define   EYST019      (ERRYST +   19)    /*      ys_ui.c:1128 */
#define   EYST020      (ERRYST +   20)    /*      ys_ui.c:1252 */
#define   EYST021      (ERRYST +   21)    /*      ys_ui.c:1332 */
#define   EYST022      (ERRYST +   22)    /*      ys_ui.c:1338 */
#define   EYST023      (ERRYST +   23)    /*      ys_ui.c:1348 */
#define   EYST024      (ERRYST +   24)    /*      ys_ui.c:1392 */
#define   EYST025      (ERRYST +   25)    /*      ys_ui.c:1441 */
#define   EYST026      (ERRYST +   26)    /*      ys_ui.c:1538 */
#define   EYST027      (ERRYST +   27)    /*      ys_ui.c:1544 */
#define   EYST028      (ERRYST +   28)    /*      ys_ui.c:1555 */
#define   EYST029      (ERRYST +   29)    /*      ys_ui.c:1562 */
#define   EYST030      (ERRYST +   30)    /*      ys_ui.c:1573 */
#define   EYST031      (ERRYST +   31)    /*      ys_ui.c:1579 */
#define   EYST032      (ERRYST +   32)    /*      ys_ui.c:1592 */
#define   EYST033      (ERRYST +   33)    /*      ys_ui.c:1645 */
#define   EYST034      (ERRYST +   34)    /*      ys_ui.c:1712 */
#define   EYST035      (ERRYST +   35)    /*      ys_ui.c:1727 */
#define   EYST036      (ERRYST +   36)    /*      ys_ui.c:1791 */
#define   EYST037      (ERRYST +   37)    /*      ys_ui.c:1803 */
#define   EYST038      (ERRYST +   38)    /*      ys_ui.c:1813 */
#define   EYST039      (ERRYST +   39)    /*      ys_ui.c:1827 */
#define   EYST040      (ERRYST +   40)    /*      ys_ui.c:1863 */
#define   EYST041      (ERRYST +   41)    /*      ys_ui.c:1976 */
#define   EYST042      (ERRYST +   42)    /*      ys_ui.c:1988 */
#define   EYST043      (ERRYST +   43)    /*      ys_ui.c:1998 */
#define   EYST044      (ERRYST +   44)    /*      ys_ui.c:2012 */
#define   EYST045      (ERRYST +   45)    /*      ys_ui.c:2047 */
#define   EYST046      (ERRYST +   46)    /*      ys_ui.c:2409 */
#define   EYST047      (ERRYST +   47)    /*      ys_ui.c:2422 */
#define   EYST048      (ERRYST +   48)    /*      ys_ui.c:2433 */
#define   EYST049      (ERRYST +   49)    /*      ys_ui.c:2449 */
#define   EYST050      (ERRYST +   50)    /*      ys_ui.c:2493 */
#define   EYST051      (ERRYST +   51)    /*      ys_ui.c:2504 */

#endif /* __YS_ERR_H__ */
/********************************************************************30**
  
         End of file:     ys_err.h@@/main/2 - Thu Dec  2 02:27:13 2010
  
*********************************************************************31*/

/********************************************************************40**
  
        Notes:
 
**********************************************************************/
 
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/2      ---     sgm                   1. eNodeB 1.2 release
/main/2      ys003.102     mn              1. Removed warning.
/main/2      ys004.102     ms              1. g++ compilation.
/main/2      ys005.102   pbyadgi           1. Fixed warnings for g++ compilation on Linux
                                           2. Fix for TIC_ID:ccpu00119532: Changed the
                                              way of debug print.
*********************************************************************91*/
