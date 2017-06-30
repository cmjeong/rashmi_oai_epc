/********************************************************************20**

     Name:     sb_isup.c -  inop file

     Type:     C source file

     Desc:     C code for inop

     File:     sb_isup.c

     Sid:      sb_isupp.c@@/main/2 - Thu Jul 26 07:54:29 2007

     Prg:      nct

*********************************************************************21*/



/*
 * header include files -- defines (.h)
 */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* Common timer */
#include "cm_os.h"
#include "cm_hash.h"       /* common hash */
#include "cm_tpt.h"        /* common transport addressing */
#include "cm_dns.h"        /* Common DNS library */
#include "sct.h"           /* SCT Interface */
#include "lsb.h"           /* LSB Interface */
#include "lhi.h"
#include "hit.h"
#include "hi_acc.h"
#include "sb.h"
#include "hi.h"
#include "sb_acc.h"
#include "sb_ibdy.h"

#include <arpa/inet.h> /* for inet_addr() */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timer */
#include "cm_os.x"
#include "cm_hash.x"       /* common hash */
#include "cm_tpt.x"        /* common transport addressing */
#include "cm_dns.x"        /* Common DNS library */
#include "sct.x"           /* SCT Interface */
#include "lsb.x"           /* LSB Interface */
#include "lhi.x"
#include "hit.x"
#include "hi_acc.x"
#include "sb_ibdy.x"


/* local defines */

/*  public variable declarations */


PUBLIC S32 lineNo = 1;                 /* crnt lno in cfg file scan */

PUBLIC Keys addr_kw[]=
{
   {"CM_NETADDR_IPV4", CM_NETADDR_IPV4},
   {"CM_NETADDR_IPV6", CM_NETADDR_IPV6},
   {"", MATCH_FAILED}
};

/* extern variable declarations */

/*
*
*       Fun:   sbISParsU32
*
*       Desc:  parse argument into U32
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes:
*
*       File:  cfv2_cr3.c
*
*/
#ifdef ANSI
PUBLIC S16 sbISParsU32
(
CfTkn *tkn,
U32 low,
U32 high,
U32 *ret
)
#else
PUBLIC S16 sbISParsU32(tkn, low, high, ret)
CfTkn *tkn;
U32 low;
U32 high;
U32 *ret;
#endif
{
   Txt str[100];
   TRC2(sbISParsU32)

   if (!tkn->args[0].pres || *tkn->args[0].val != '=')
      sbICPrntError("sbISParsU32: equals sign missing\n");

   if (!tkn->args[1].pres)
   {
      sbICPrntError("sbISParsU32: arg not present");
      RETVALUE(RFAILED);
   }

   *ret = (U32)sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);
   if (*ret < low || *ret > high)
   {
      osSprintf(str, "%s(%d): sbISParsU32() - value out of range low %x, high %x, val %x",
                __FILE__, __LINE__, low, high, *ret);
      sbICPrntError(str);
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of sbISParsU32 */


/*
*
*       Fun:   sbISMatchKw
*
*       Desc:  parse argrument with string lookup
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: if match not found, error
*
*       File:  cfv2_cr3.c
*
*/
#ifdef ANSI
PUBLIC S16 sbISMatchKw
(
Keys *kw,
CfTkn *tkn,
U32 *retVal
)
#else
PUBLIC S16 sbISMatchKw(kw, tkn, retVal)
Keys *kw;
CfTkn *tkn;
U32 *retVal;
#endif
{
   S32 val;

   TRC2(sbISMatchKw)

   if (!tkn->args[0].pres || *tkn->args[0].val != '=')
      sbICPrntError("%s(%d): sbISMatchKw() - equals sign missing\n");

   if (!tkn->args[1].pres)
   {
      sbICPrntError("sbISMatchKw: arg not present");
      RETVALUE(RFAILED);
   }

   val = osMatchKeyword(kw, (S8*)tkn->args[1].val);
   if(val == MATCH_FAILED)                /* match successful */
      RETVALUE(RFAILED);

   *retVal = (U32)val;
   RETVALUE(ROK);
} /* end of sbISMatchKw */


/*
*
*       Fun:   sbISMatchU32
*
*       Desc:
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes:
*
*       File:  cfv2_cr3.c
*
*/
#ifdef ANSI
PUBLIC S16 sbISMatchU32
(
Keys *kw,
CfTkn *tkn,
U32 low,
U32 high,
U32 *retVal
)
#else
PUBLIC S16 sbISMatchU32(kw, tkn, low, high, retVal)
Keys *kw;
CfTkn *tkn;
U32 low;
U32 high;
U32 *retVal;
#endif
{
   Txt str[100];
   S32 val;

   TRC2(sbISMatchU32)

   if (!tkn->args[0].pres || *tkn->args[0].val != '=')
      sbICPrntError("%s(%d): sbISMatchU32() - equals sign missing\n");

   if (!tkn->args[1].pres)
   {
      sbICPrntError("sbISMatchU32: arg not present");
      RETVALUE(RFAILED);
   }

   val = osMatchKeyword(kw, (S8*)tkn->args[1].val);
   if(val == MATCH_FAILED)                /* match successful */
   {
      /* match failed, convert to U32 */
      *retVal = (U32)sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);
      if (*retVal < low || *retVal > high)
      {
         osSprintf(str,
                   "%s(%d): sbISMatchU32() - value out of range low %x, high %x, val %x",
                   low, high, *retVal);
         sbICPrntError(str);
         RETVALUE(RFAILED);
      }
      RETVALUE(ROK);
   }

   *retVal = (U32)val;
   RETVALUE(ROK);
} /* end of sbISMatchU32 */

/*
*
*       Fun:   sbISPrntTkn
*
*       Desc:  print out token
*
*       Ret:   none.
*
*       Notes:
*
*       File:  cfv2_cr1.c
*
*/

#ifdef ANSI
PUBLIC Void sbISPrntTkn
(
CfTkn *tkn
)
#else
PUBLIC Void sbISPrntTkn(tkn)
CfTkn *tkn;
#endif
{
   S32 i;

   TRC2(sbISPrntTkn)

   if (!tkn->tok.pres)
      osPrintf("%s(%d): sbISPrntTkn() - token not present\n");

   osPrintf("[%s] ", tkn->tok.val);
   for (i = 0; i < (S32)tkn->nmbArgs; i++)
   {
      osPrintf("[%s] ", tkn->args[i].val);
   }
   osPrintf("\n");

   RETVOID;
} /* end of sbISPrntTkn */


#ifdef ANSI
PUBLIC S16 sbISParsTptAddr
(
 CfTkn *tkn,
 CmTptAddr *srcAddr
)
#else
PUBLIC S16 sbISParsTptAddr(tkn, srcAddr)
CfTkn *tkn;
CmTptAddr *srcAddr;
#endif
{
  U32 val;
 
  TRC2(sbISParsTptAddr)
 
 if (!tkn->args[0].pres)
     RETVALUE(RFAILED);
 
 val = osMatchKeyword(addr_kw, (S8*)tkn->args[0].val);
 srcAddr->type = (U16) val;
 
 if (!tkn->args[1].pres)
     RETVALUE(RFAILED);
 
  srcAddr->u.ipv4TptAddr.port = (U16) sbISStrtoul((S8*)tkn->args[1].val, NULLP, NULLP);
 
 
 if (!tkn->args[2].pres)
     RETVALUE(RFAILED);
      srcAddr->u.ipv4TptAddr.address = ntohl(inet_addr((S8 *)tkn->args[2].val));
  RETVALUE(ROK);
} /* end of sbISParsTptAddr */
 

#ifdef ANSI
PUBLIC S16 sbISParsNetAddr
(
 CfTkn *tkn,
 CmNetAddr *srcAddr
 )
#else
PUBLIC S16 sbISParsNetAddr(tkn, srcAddr)
CfTkn *tkn;
CmNetAddr *srcAddr;
#endif
{
  U32 val;

  TRC2(sbISParsSrcAddr)

 if (!tkn->args[0].pres)
     RETVALUE(RFAILED);

 val = osMatchKeyword(addr_kw, (S8*)tkn->args[0].val);
 srcAddr->type = (U16) val;

 if (!tkn->args[1].pres)
     RETVALUE(RFAILED);

      srcAddr->u.ipv4NetAddr = ntohl(inet_addr((S8 *)tkn->args[1].val));
  RETVALUE(ROK);
} /* end of sbISParsNetAddr */


#ifdef ANSI
PUBLIC S16 sbISParsSrcAddr
(
 CfTkn *tkn,
 SctNetAddrLst *srcAddr
 )
#else
PUBLIC S16 sbISParsSrcAddr(tkn, srcAddr)
CfTkn *tkn;
SctNetAddrLst *srcAddr;
#endif
{
  U32 val;
  U16  i,k=1;

  TRC2(sbISParsSrcAddr)

 if (!tkn->args[0].pres)
     RETVALUE(RFAILED);

 val =  sbISStrtoul((S8*)tkn->args[0].val, NULLP, NULLP);
 if (val == MATCH_FAILED)
         RETVALUE(RFAILED);
 if(val == 0)
 {
   srcAddr->nmb = 0;
   RETVALUE(ROK);
 }
 else
 {
  srcAddr->nmb = (U16) val;
  for(i=0;i<srcAddr->nmb;i++)
  {
    if (!tkn->args[k].pres)
       RETVALUE(RFAILED);
    val = osMatchKeyword(addr_kw, (S8*)tkn->args[k].val);
    if (val == MATCH_FAILED)
            RETVALUE(RFAILED);
    switch(val)
    {
     case CM_NETADDR_IPV4:
      srcAddr->nAddr[i].type = CM_NETADDR_IPV4;
      if (!tkn->args[k+1].pres)
        RETVALUE(RFAILED);
      srcAddr->nAddr[i].u.ipv4NetAddr = ntohl(inet_addr((S8 *)tkn->args[k+1].val));
      break;
     case CM_NETADDR_IPV6:
      srcAddr->nAddr[i].type = CM_NETADDR_IPV6;
      break;

    }
    k += 2;

  }
 }

  RETVALUE(ROK);
} /* end of sbISParsSrcAddr */


/*
*
*       Fun:   sbISLineToTkn
*
*       Desc:  Convert Line format to Token Format
*
*       Ret:   Number of arguments on success
*              RFAILED on error
*
*       Notes:
*
*       File:  cfv2_cr1.c
*
*/
#ifdef ANSI
PUBLIC S16 sbISLineToTkn
(
S8 *line,
CfTkn *tkn
)
#else
PUBLIC S16 sbISLineToTkn(line, tkn)
S8 *line;
CfTkn *tkn;
#endif
{
   S8 *lPtr;
   S8 word[LINELEN];
   S32 i;

   TRC2(sbISLineToTkn)

   lPtr = osGetWord(line, word);

   if (osStrlen(word) >= sizeof(tkn->tok.val)) /* make sure there's room */
      RETVALUE(-1);

   osStrcpy((S8*)tkn->tok.val, word);
   tkn->tok.pres = TRUE;
   tkn->tok.len = osStrlen((S8*)tkn->tok.val);
   tkn->nmbArgs = 0;
   for (i = 0; i < MAXARGS; i++)
   {
      lPtr = osGetWord(lPtr, word);

      if (osStrlen(word) >= sizeof(tkn->tok.val)) /* make sure there's room */
         RETVALUE(-1);

      if (*word == '\0' || *word == '#') /* end of line or comment */
      {
         tkn->args[i].pres = FALSE;
         break;
      }

      osStrcpy((S8*)tkn->args[i].val, word);
      tkn->args[i].pres = TRUE;
      tkn->args[i].len = osStrlen((S8*)tkn->args[i].val);
      tkn->nmbArgs++;
   }

   RETVALUE(tkn->nmbArgs);
} /* end of sbISLineToTkn */



/*
*
*       Fun:   sbISStrtoul
*
*       Desc:  wrapper for strtoul 
*
*       Ret:    ascii string to long value 
*
*       Notes: None
*
*       File:  sb_isupp.c
*
*/
#ifdef ANSI
PUBLIC U32 sbISStrtoul
(
CONSTANT S8 *str,
S8 **ptr,
S32 base
)
#else
PUBLIC U32 sbISStrtoul(str, ptr, base)
CONSTANT S8 *str;
S8 **ptr;
S32 base;
#endif
{
   TRC2(sbISStrtoul)
   RETVALUE(strtoul(str, ptr, base));

} /* end of sbISStrtoul */


/********************************************************************30**

         End of file:     sb_isupp.c@@/main/2 - Thu Jul 26 07:54:29 2007

*********************************************************************31*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/


/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      sb    1. File Added for inter-op SCTP Testing 
/main/2      ---    rsr/ag  1. Updated for Release of 1.3  
*********************************************************************91*/

