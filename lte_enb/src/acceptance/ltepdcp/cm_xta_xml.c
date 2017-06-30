
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_xml.c@@/main/TeNB_Main_BR/2 - Thu Apr 24 17:04:59 2014

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include <Python.h>
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta.h"
/* cm_xta_xml_c_001.main_3 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"
/* cm_xta_xml_c_001.main_3 Removed cm_xta_app.x for Psf-Diameter 1.1 */
#include "cm_xta_py.x"
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
PUBLIC S16 cmXtaXmlValidateRe
(
CmXtaTCCb  *tcCb,
Void *curStep,
Txt  *msg
)
#else
PUBLIC S16 cmXtaXmlValidateRe(tcCb, curStep, msg)
CmXtaTCCb  *tcCb;
Void *curStep;
Txt  *msg;
#endif
{
   TRC2(cmXtaXmlValidateRe)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaXmlValidateRe(): \n"));

   RETVALUE(cmXtaPyWrap_validateRe(tcCb, curStep, msg));
}/* cmXtaXmlValidateRe */

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
PUBLIC S16 cmXtaXmlGetValList
(
CmXtaTCCb  *tcCb,
Void *curStep,
U8   type,
U8   sep,
Txt  *attrib,
Void *valList,
U8   *length
)
#else
PUBLIC S16 cmXtaXmlGetValList(tcCb, curStep, type, sep, attrib, valList, length)
CmXtaTCCb  *tcCb;
Void *curStep;
U8   type;
U8   sep;
Txt  *attrib;
Void *valList;
U8   *length;
#endif
{
   TRC2(cmXtaXmlGetValList)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaXmlGetValList(): \n"));

   RETVALUE(cmXtaPyWrap_getValList(tcCb, curStep, type, sep, attrib, valList, length));
}/* cmXtaXmlGetValList */

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
PUBLIC Void* cmXtaXmlFirstChildOfType
(
Void *curStep,
U16   elmType
)
#else
PUBLIC Void* cmXtaXmlFirstChildOfType(curStep, elmType)
Void *curStep;
U16   elmType;
#endif
{
   TRC2(cmXtaXmlFirstChildOfType)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaXmlFirstChildOfType(): get firstChild of given type(%d)\n", elmType));

   RETVALUE(cmXtaPyWrap_firstChildOfType(curStep, elmType));
}/* cmXtaXmlFirstChildOfType */

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
PUBLIC Void* cmXtaXmlGetNextOfType
(
Void *curStep,
Void *nextStep,
U16   elmType
)
#else
PUBLIC  Void* cmXtaXmlGetNextOfType(curStep,nextStep,elmType)
Void *curStep;
Void *nextStep;
U16   elmType;
#endif
{
   TRC2(cmXtaXmlGetNextOfType)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaXmlGetNextOfType(): \n"));

   RETVALUE(cmXtaPyWrap_getNextOfType(curStep, nextStep, elmType));
}/* cmXtaXmlGetNextOfType */

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
PUBLIC S16 cmXtaXmlGetVal
(
CmXtaTCCb  *tcCb,
Void *curStep,
U8   type,
Txt  *attrib,
Void *val
)
#else
PUBLIC S16 cmXtaXmlGetVal(tcCb, curStep, type, attrib, val)
CmXtaTCCb  *tcCb;
Void *curStep;
U8   type;
Txt  *attrib;
Void *val;
#endif
{
   TRC2(cmXtaXmlGetVal)

   RETVALUE(cmXtaPyWrap_getVal(tcCb, curStep, type, attrib, val));
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
PUBLIC Void* cmXtaXmlNextSiblingOfType
(
Void *curStep,
U16   elmType
)
#else
PUBLIC Void* cmXtaXmlNextSiblingOfType(curStep, elmType)
Void *curStep;
U16   elmType;
#endif
{
   TRC2(cmXtaXmlNextSiblingOfType)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaXmlNextSiblingOfType(): find nextSibling of type\n"));

   RETVALUE(cmXtaPyWrap_nextSiblingOfType(curStep, elmType));
}/* cmXtaXmlNextSiblingOfType */


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
PUBLIC S16 cmXtaXmlGetDocTC
(
CmXtaTCCb  *tcCb,
Void    *curStep,
U16     sp
)
#else
PUBLIC S16 cmXtaXmlGetDocTC(tcCb, curStep, sp)
CmXtaTCCb  *tcCb;
Void    *curStep;
U16     sp;
#endif
{
   TRC2(cmXtaXmlGetDocTC)

   RETVALUE(cmXtaPyWrap_GetDocTCStep(tcCb, curStep, sp));
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
PUBLIC S16 cmXtaXmlGetDoc
(
CmXtaXmlCb *xmlCb,
Void  *doc,
Void  *pre
)
#else
PUBLIC S16 cmXtaXmlGetDoc(xmlCb, doc, pre)
CmXtaXmlCb *xmlCb;
Void  *doc;
Void  *pre;
#endif
{
   TRC2(cmXtaXmlGetDoc)

   RETVALUE(cmXtaPyWrap_GetTCDoc(xmlCb, doc, pre));
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
PUBLIC CmXtaXmlCb* cmXtaXmlFindFromXml
(
Void  *curStep
)
#else
PUBLIC CmXtaXmlCb* cmXtaXmlFindFromXml(curStep)
Void  *curStep;
#endif
{
   TRC2(cmXtaXmlFindFromXml)

   RETVALUE(cmXtaPyWrap_FindFromXml(curStep));
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
PUBLIC CmXtaXmlCb*  cmXtaXmlFind
(
U8 tstGrpId,
U8 tstId,
Txt            *cmd,   /* Transaction Id      */
Bool parse
)
#else
PUBLIC CmXtaXmlCb* cmXtaXmlFind (tstGrpId, tstId, cmd, parse)
U8 tstGrpId;
U8 tstId;
Txt            *cmd;   /* Transaction Id      */
Bool parse;
#endif
{
   S16      ret;
   CmXtaXmlCb  *xmlCb;

   TRC2(cmXtaXmlFind)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaXmlFind(): tg(%d) tc(%d) cmd (%s)\n",
                 tstGrpId, tstId, cmd));

   xmlCb = NULLP;

   /*-- Check if we are looking for a specific test case --*/
   if ((tstGrpId != 0) && (tstId != 0) &&
       (tstGrpId <= CMXTA_MAX_GRP)     &&
       (tstGrpId <= cmXtaCb.tstGrpCnt) &&
       (tstId    <= CMXTA_MAX_TST)     &&
       (tstId    <= cmXtaCb.tstGrp[tstGrpId - 1].numTests))
      xmlCb = cmXtaCb.tstGrp[tstGrpId - 1].tstList[tstId - 1].tc;
   /*-- Check if we are looking for a specific test group --*/
   else if ((tstGrpId != 0) &&
            (tstGrpId <= CMXTA_MAX_GRP)     &&
            (tstGrpId <= cmXtaCb.tstGrpCnt))
      xmlCb = cmXtaCb.tstGrp[tstGrpId - 1].tg;
   else
   {
      /*-- Find the transaction control block in
       *   the hash list --*/
      ret = cmHashListFind (&cmXtaCb.xmlLstCp,
                            (U8  *) cmd,
                            (U16  ) strlen(cmd),
                            0,
                            (PTR *) &xmlCb);
   }

   /*-- Check if we need to parse the XML message --*/
   if ((xmlCb != NULLP) &&
       ((xmlCb->cmdType != CMXTA_TYPE_LEAF) &&
        (xmlCb->cmdType != CMXTA_TYPE_DIR) &&
        (xmlCb->cmdType != CMXTA_TYPE_INT)) &&
       (parse == TRUE) &&
       ((ret = cmXtaXmlParse(xmlCb)) != CMXTA_ERR_NONE))
      RETVALUE(NULLP);

   RETVALUE(xmlCb);
} /* cmXtaXmlFind */

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
PUBLIC CmXtaXmlCb*  cmXtaXmlCreate
(
Txt            *cmd,   /* Transaction Id      */
U8             cmdType,   /* BCP Message Type    */
U8             subType,   /* BCP Message Type    */
CmXtaHdl          func,
Txt            *doc,
Txt            *tc,   /* Transaction Id      */
Bool           parse
)
#else
PUBLIC CmXtaXmlCb* cmXtaXmlCreate (cmd, cmdType,subType, func, doc, tc, parse)
Txt            *cmd;   /* Transaction Id      */
U8             cmdType;   /* BCP Message Type    */
U8             subType;   /* BCP Message Type    */
CmXtaHdl          func;
Txt            *doc;
Txt            *tc;   /* Transaction Id      */
Bool           parse;
#endif
{
   S16         ret;
   CmXtaXmlCb   *xmlCb;
   Txt      *testDoc;

   TRC2(cmXtaXmlCreate)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaXmlCreate(): cmd (%s) cmdType(%d) subType(%d)\n",
                 cmd, cmdType, subType));

   testDoc = NULLP;
   xmlCb = NULLP;

   /*-- Ensure we have a correct cmdType --*/
   if ((cmdType != CMXTA_TYPE_LEAF)       &&
       (cmdType != CMXTA_TYPE_COMPOUND)   &&
       (cmdType != CMXTA_TYPE_INT)        &&
       (cmdType != CMXTA_TYPE_TG)         &&
       (cmdType != CMXTA_TYPE_DIR)         &&
       (cmdType != CMXTA_TYPE_TC))
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaXmlCreate(): Invalid cmdType\n"));
      RETVALUE(NULLP);
   }

   /*-- Allocate Transaction control block --*/
   CMXTA_ALLOC(&xmlCb, sizeof (CmXtaXmlCb));
   if (xmlCb == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaXmlCreate(): resource error\n"));
      RETVALUE(NULLP);
   }

   /*-- TC field no longer being used for memory optimization --*/
   /*-- Allocate Transaction control block --*/
   if ((cmdType != CMXTA_TYPE_LEAF) &&
       (cmdType != CMXTA_TYPE_DIR) &&
       (cmdType != CMXTA_TYPE_INT))
   {
   }
   else
   {
      CMXTA_ALLOC(&testDoc, (cmStrlen((CONSTANT U8 *)doc) + 1) * sizeof (U8));
      if (testDoc == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "cmXtaXmlCreate(): resource error\n"));
         cmXtaXmlDelete(xmlCb);
         RETVALUE(NULLP);
      }

      CMXTA_CPY(testDoc, doc, (cmStrlen((CONSTANT U8 *)doc) + 1) * sizeof (U8));
   }


   /*-- Init types --*/
   xmlCb->cmdType = cmdType;

   /*-- TC field no longer being used for memory optimization --*/

   xmlCb->doc = testDoc;
   xmlCb->subType = subType;
   xmlCb->parsed = FALSE;
   CMXTA_CPY(xmlCb->cmd, cmd, cmStrlen((CONSTANT U8 *)cmd));

   if ((cmdType == CMXTA_TYPE_LEAF)  ||
       (cmdType == CMXTA_TYPE_DIR)   ||
       (cmdType == CMXTA_TYPE_INT))
   {
      /*-- If the handler function is empty, map it to internal invalid handler. 
        This is allowed so that user may be allowed to define dummy place holder
        commands and change the same before it really hits the code --*/
      if (func != NULLP)
         xmlCb->func = func;
      else
         xmlCb->func = cmXtaHdlIntInvalid;
   }

   /*-- Check if we need to parse the XML message --*/
   if ((parse == TRUE) &&
       ((xmlCb->cmdType != CMXTA_TYPE_LEAF)  &&
        (xmlCb->cmdType != CMXTA_TYPE_DIR)  &&
        (xmlCb->cmdType != CMXTA_TYPE_INT))  &&
       ((ret = cmXtaXmlParse(xmlCb)) != CMXTA_ERR_NONE))
   {
      cmXtaXmlDelete (xmlCb);
      RETVALUE(NULLP);
   }

   /*-- Insert Transaction into global transaction list --*/
   ret = cmHashListInsert(&cmXtaCb.xmlLstCp, (PTR) (xmlCb),
                          (U8 *) xmlCb->cmd,
                          strlen(xmlCb->cmd));

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaXmlCreate(): resource error\n"));
      cmXtaXmlDelete (xmlCb); 
      RETVALUE(NULLP);
   }

   RETVALUE(xmlCb);
} /* cmXtaXmlCreate */

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
PUBLIC S16  cmXtaXmlDelete
(
CmXtaXmlCb      *xmlCb  /* Transaction Block   */
)
#else
PUBLIC S16  cmXtaXmlDelete (xmlCb)
CmXtaXmlCb      *xmlCb; /* Transaction Block   */
#endif
{
   TRC2(cmXtaXmlDelete)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaXmlDelete(): deleting (%s)\n", xmlCb->cmd));

   /*-- Release from XML List --*/
   cmHashListDelete (&cmXtaCb.xmlLstCp, (PTR) xmlCb);

   /*-- TC field no longer being used for memory optimization --*/
   /*-- Release memory for the message and the documentation --*/
   if (xmlCb->doc != NULLP)
   {
      CMXTA_FREE(xmlCb->doc, (cmStrlen((CONSTANT U8 *)xmlCb->doc) + 1) * sizeof (U8));
   }

   /*-- Finally, delete transaction control block (TCB) --*/
   CMXTA_FREE(xmlCb, sizeof (CmXtaXmlCb));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaXmlDelete */

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
PUBLIC S16  cmXtaXmlParse
(
CmXtaXmlCb      *xmlCb /* Transaction Block   --*/
)
#else
PUBLIC S16  cmXtaXmlParse (xmlCb)
CmXtaXmlCb      *xmlCb; /* Transaction Block   --*/
#endif
{
   S16         ret;

   TRC2(cmXtaXmlParse)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaXmlParse(): parse cmd (%s)\n", xmlCb->cmd));

   if ((ret = cmXtaPyWrap_Parse(xmlCb)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaXmlParse */

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
PUBLIC S16  cmXtaXmlValidate
(
U8       type
)
#else
PUBLIC S16  cmXtaXmlValidate (type)
U8       type;
#endif
{
   Bool err;
   S16 grpCnt;
   S16 tstCnt;

   TRC2(cmXtaXmlValidate)

   err = FALSE;

   if (type == CMXTA_TYPE_TC)
   {
      /*-- Check the validity of the test cases --*/
      for (grpCnt = 0; grpCnt < cmXtaCb.tstGrpCnt; grpCnt++)
      {
         /*-- Check the TC Id --*/
         if (cmXtaCb.tstGrp[grpCnt].numTests >= CMXTA_MAX_TST)
         {
            /* cm_xta_xml_c_001.main_2 :Corrected debug print */
            CMXTA_DBG_FATAL((_cmxtap, "cmXtaXmlValidate(): tstCnt(%d) greater than max tstCnt(%d)\n",
                              cmXtaCb.tstGrp[grpCnt].numTests, CMXTA_MAX_TST));
            RETVALUE(CMXTA_ERR_INT);
         }

         for (tstCnt = 0; tstCnt < cmXtaCb.tstGrp[grpCnt].numTests; tstCnt++)
         {
            /*-- Check if missing --*/
            if (cmXtaCb.tstGrp[grpCnt].tstList[tstCnt].tcSet == FALSE)
            {
               CMXTA_DBG_FATAL((_cmxtap, "cmXtaXmlValidate(): missing tcId(%d.%d)\n", grpCnt+1, tstCnt+1));
               err = TRUE;
            }
         }
      }
   }
   else
   {
      /*-- Check the validity of the test groups --*/
      if (cmXtaCb.tstGrpCnt >= CMXTA_MAX_GRP)
      {
         CMXTA_DBG_FATAL((_cmxtap, "cmXtaXmlValidate(): grpId(%d) greater than max grp(%d)\n",
                       cmXtaCb.tstGrpCnt, CMXTA_MAX_GRP));
         RETVALUE(CMXTA_ERR_INT);
      }
      else
      {
         for (grpCnt = 0; grpCnt < cmXtaCb.tstGrpCnt; grpCnt++)
            if (cmXtaCb.tstGrp[grpCnt].state != CMXTA_IDLE)
            {
               CMXTA_DBG_FATAL((_cmxtap, "cmXtaXmlValidate(): missing grpId(%d)\n", grpCnt+1));
               err = TRUE;
            }
      }
   }

   if (err == TRUE)
      RETVALUE(CMXTA_ERR_INT);
   else
      RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaXmlValidate */

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
PUBLIC S16 cmXtaXmlInit
(
)
#else
PUBLIC S16 cmXtaXmlInit ()
#endif
{
   S16      ret;

   TRC2(cmXtaXmlInit)

   /*-- Init Embedded Python module --*/
   if ((ret = cmXtaPyInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   /*-- Initialize hash list --*/
   ret = cmHashListInit(&cmXtaCb.xmlLstCp,   /* HL Control point */
                        100,   /* HL Bins for a txn */
                        CMXTA_OFFSET_OF(CmXtaXmlCb, tstHlEnt),
                        FALSE,             /* Allow dup keys */
                        CM_HASH_KEYTYPE_STR,
                        cmXtaCb.init.region,  /* Mem region */
                        cmXtaCb.init.pool);   /* Mem Pool */

   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaXmlInit(): init failed\n"));
   }

   RETVALUE(ret);
} /* cmXtaXmlInit */

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
PUBLIC S16 cmXtaXmlDeInit
(
Void
)
#else
PUBLIC S16 cmXtaXmlDeInit ()
#endif
{
   CmXtaXmlCb   *xmlCb;

   TRC2(cmXtaXmlDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaXmlDeInit(): shutdown initiated\n"));

   /*-- Delete all pending transactions --*/
   while (cmHashListGetNext(&cmXtaCb.xmlLstCp,
            NULLP, (PTR *)&xmlCb) == CMXTA_ERR_NONE)
      cmXtaXmlDelete(xmlCb);

   cmHashListDeinit(&cmXtaCb.xmlLstCp);

   /*-- DeInit Embedded Python module --*/
   cmXtaPyDeInit();

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaXmlDeInit */

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
PUBLIC S16 cmXtaXmlDumpSimpleCmd
(
Void
)
#else
PUBLIC S16 cmXtaXmlDumpSimpleCmd ()
#endif
{
   CmXtaXmlCb *xmlCb;
   Txt   pBuf[500];  /* output string buffer */

   TRC2(cmXtaXmlDumpSimpleCmd)

   xmlCb = NULLP;
   sprintf(pBuf, "\nintCmdDict = {\n");
   SPrint(pBuf);

   /*-- Browse all simple commands --*/
   while (cmHashListGetNext(&cmXtaCb.xmlLstCp,
            (PTR)xmlCb, (PTR *)&xmlCb) == CMXTA_ERR_NONE)
   {
      if ((xmlCb->cmdType == CMXTA_TYPE_INT) ||
          (xmlCb->cmdType == CMXTA_TYPE_DIR))
      {
         sprintf(pBuf, "   \'%s\' : \'%s\',\n", xmlCb->cmd, xmlCb->doc);
         SPrint(pBuf);
      }
   }

   sprintf(pBuf, "}\n");
   SPrint(pBuf);

   xmlCb = NULLP;
   sprintf(pBuf, "\nsimpleCmdDict = {\n");
   SPrint(pBuf);

   /*-- Browse all simple commands --*/
   while (cmHashListGetNext(&cmXtaCb.xmlLstCp,
            (PTR)xmlCb, (PTR *)&xmlCb) == CMXTA_ERR_NONE)
   {
      if (xmlCb->cmdType == CMXTA_TYPE_LEAF)
      {
         sprintf(pBuf, "   \'%s\' : \'%s\',\n", xmlCb->cmd, xmlCb->doc);
         SPrint(pBuf);
      }
   }

   sprintf(pBuf, "}\n");
   SPrint(pBuf);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaXmlDumpSimpleCmd */

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
PUBLIC S16 cmXtaXmlLoadSimpleCmd
(
U16 cmdCnt,
CmXtaCmd *cmdLst
)
#else
PUBLIC S16 cmXtaXmlLoadSimpleCmd (cmdCnt, cmdLst)
U16 cmdCnt;
CmXtaCmd *cmdLst;
#endif
{
   U16      cnt;
   CmXtaXmlCb *xmlCb;
   CmXtaCmd *cmd;

   TRC2(cmXtaXmlLoadSimpleCmd)

   for (cnt = 0; cnt < cmdCnt; cnt++)
   {
      cmd = &cmdLst[cnt];
      if ((xmlCb = cmXtaXmlCreate(cmd->cmd, cmd->cmdType,
                             cmd->subType, cmd->func,
                             cmd->doc, cmd->tc, FALSE)) == NULLP)
      {
         RETVALUE(CMXTA_ERR_RSRC);
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaXmlLoadSimpleCmd */

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
PUBLIC S16 cmXtaXmlLoadTestGroups
(
Bool        parse
)
#else
PUBLIC S16 cmXtaXmlLoadTestGroups (parse)
Bool        parse;
#endif
{
   S16 ret;

   TRC2(cmXtaXmlLoadTestGroups)

   /*-- Get all test groups --*/
   if ((ret = cmXtaPyWrap_loadTestGroups(parse)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   if ((ret = cmXtaXmlValidate(CMXTA_TYPE_TG)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaXmlLoadTestGroups */

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
PUBLIC S16 cmXtaXmlLoadTestCases
(
Bool        parse
)
#else
PUBLIC S16 cmXtaXmlLoadTestCases (parse)
Bool        parse;
#endif
{
   S16 ret;

   TRC2(cmXtaXmlLoadTestCases)

   /*-- Get all test cases --*/
   if ((ret = cmXtaPyWrap_loadTestCases(parse)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   if ((ret = cmXtaXmlValidate(CMXTA_TYPE_TC)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaXmlLoadTestCases */

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
PUBLIC S16 cmXtaXmlLoadCommands
(
Bool        parse
)
#else
PUBLIC S16 cmXtaXmlLoadCommands (parse)
Bool        parse;
#endif
{
   S16 ret;

   TRC2(cmXtaXmlLoadCommands)

   /*-- Get all compound commands --*/
   if ((ret = cmXtaPyWrap_loadCommands(parse)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaXmlLoadCommands */

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
PUBLIC S16 cmXtaXmlLoadFiles
(
Bool        parse
)
#else
PUBLIC S16 cmXtaXmlLoadFiles (parse)
Bool        parse;
#endif
{
   S16      ret;

   TRC2(cmXtaXmlLoadFiles)

   if ((ret = cmXtaXmlLoadTestGroups(parse)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   if ((ret = cmXtaXmlLoadTestCases(parse)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   if ((ret = cmXtaXmlLoadCommands(parse)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaXmlLoadFiles */

/********************************************************************30**

         End of file:     cm_xta_xml.c@@/main/TeNB_Main_BR/2 - Thu Apr 24 17:04:59 2014

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
/main/2      ----     up  1. Main release
/main/3      ---      cm_xta_xml_c_001.main_2   kchaitanya   1. Updated for fixing
                                                              klockwork errors
/main/4      ----     cm_xta_xml_c_001.main_3   nh   1. Updated for Psf-Diameter 1.1
                                                    release Removed cm_xta_app.[hx]
*********************************************************************91*/

