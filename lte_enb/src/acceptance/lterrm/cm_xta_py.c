
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_py.c@@/main/TeNB_Main_BR/2 - Thu Apr 24 17:04:58 2014

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
/* cm_xta_py_c_001.main_5 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"

/* cm_xta_py_c_001.main_5 Removed cm_xta_app.x for Psf-Diameter 1.1 */
#include "cm_xta_py.x"

PRIVATE CmXtaPyCb  pyCb;
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
PUBLIC S16 cmXtaPyInit
(
Void
)
#else
PUBLIC S16 cmXtaPyInit()
#endif
{
   CmXtaPyCb   *cb;
   PyObject *pName;
   PyObject *pModule;
   PyObject *pDict;

   TRC2(cmXtaPyInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyInit(): Initializing python interpreter\n"));

   pName = NULLP;
   pModule = NULLP;
   pDict = NULLP;

   cb = &pyCb;

   /*-- Call Python init function, no return value
        defined, fatal error if init fails --*/
   Py_Initialize();

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyInit(): Loading module cm_xta_py\n"));

   /*-- Load module --*/
   pModule = PyImport_ImportModule("cm_xta_py");
   if (pModule == NULLP)
   {
      if (PyErr_Occurred() != NULLP)
         PyErr_Print();

      CMXTA_DBG_CALLIND((_cmxtap, "Error in loading cm_xta_py\n"), 2);

      CMXTA_DBG_FATAL((_cmxtap, "cmXtaPyInit(): Error in loading cm_xta_py\n"));

      /*-- Shutdown python interpreter --*/
      cmXtaPyDeInit();

      RETVALUE(CMXTA_ERR_INT);
   }
   else
   {
      /*-- Init TC/TG/cmd Dict --*/
      cb->testGroupDict = NULLP;
      cb->testCaseDict = NULLP;
      cb->commandDict = NULLP;

      /* pDict is a borrowed reference */
      pDict = PyModule_GetDict(pModule);

      /*-- No error check for NULL function object and PyCallable_Check --*/
      /*-- Ensure that the objects are indeed function objects and are 
           present --*/

      /* All function objects borrowed references */
      cb->loadTestGroups     = PyDict_GetItemString(pDict, "loadTestGroups");
      Py_INCREF(cb->loadTestGroups);

      cb->loadTestCases     = PyDict_GetItemString(pDict, "loadTestCases");
      Py_INCREF(cb->loadTestCases);

      cb->loadCommands      = PyDict_GetItemString(pDict, "loadCommands");
      Py_INCREF(cb->loadCommands);

      cb->parseTestGroup     = PyDict_GetItemString(pDict, "parseTestGroup");
      Py_INCREF(cb->parseTestGroup);

      cb->parseTestCase     = PyDict_GetItemString(pDict, "parseTestCase");
      Py_INCREF(cb->parseTestCase);

      cb->parseCommand      = PyDict_GetItemString(pDict, "parseCommand");
      Py_INCREF(cb->parseCommand);

      cb->nextSiblingOfType = PyDict_GetItemString(pDict, "nextSiblingOfType");
      Py_INCREF(cb->nextSiblingOfType);

      cb->firstChildOfType  = PyDict_GetItemString(pDict, "firstChildOfType");
      Py_INCREF(cb->firstChildOfType);

      cb->getVal            = PyDict_GetItemString(pDict, "getVal");
      Py_INCREF(cb->getVal);

      cb->validateRe        = PyDict_GetItemString(pDict, "validateRe");
      Py_INCREF(cb->validateRe);

      cb->getValList        = PyDict_GetItemString(pDict, "getValList");
      Py_INCREF(cb->getValList);

      cb->getTCDoc          = PyDict_GetItemString(pDict, "getTCDoc");
      Py_INCREF(cb->getTCDoc);

      cb->getDocTCStep      = PyDict_GetItemString(pDict, "getDocTCStep");
      Py_INCREF(cb->getDocTCStep);

      cb->getTagName        = PyDict_GetItemString(pDict, "getTagName");
      Py_INCREF(cb->getTagName);

      cb->validatePre        = PyDict_GetItemString(pDict, "validatePre");
      Py_INCREF(cb->validatePre);

      cb->pModule        = pModule;

      cmXtaAppPyInit();
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyInit */

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
PUBLIC S16 cmXtaPyDeInit
(
Void
)
#else
PUBLIC S16 cmXtaPyDeInit()
#endif
{
   TRC2(cmXtaPyDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyDeInit(): Shutting down python interpreter\n"));

   cmXtaAppPyDeInit();

   /*-- Check if init done --*/
   if (Py_IsInitialized())
      Py_Finalize();

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyDeInit */

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
PUBLIC S16 cmXtaPyWrap_loadTestGroups
(
Bool        parse
)
#else
PUBLIC S16 cmXtaPyWrap_loadTestGroups(parse)
Bool        parse;
#endif
{
   PyObject *key;
   PyObject *value;
   PyObject *dict;
   PyObject *pFunc;
   PyObject *grpIdObj;
   PyObject *docObj;

   int pos;
   char *cmd;
   char *tg;
   char *doc;

   S16      ret;
   CmXtaXmlCb *xmlCb;

   /* cm_xta_py_c_001.main_3 :Added Initialization */
   int   tstGrpId=CMXTA_MAX_GRP;

   TRC2(cmXtaPyWrap_loadTestGroups)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_loadTestGroups(): load test groups\n"));

   pFunc = pyCb.loadTestGroups;

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      /*-- Get the dictionary --*/
      dict = PyObject_CallObject(pFunc, NULLP);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testgroups, an empty
           dictionary is returned --*/
      if (dict == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadTestGroups(): function call failed\n"));
         RETVALUE(RFAILED);
      }
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadTestGroups(): not a function object\n"));
      RETVALUE(RFAILED);
   }

   /*-- Store the dictionary in the global Cb --*/
   pyCb.testGroupDict = dict;
   
   /* cm_xta_py_c_001.main_4 - Fix for compilation warning and optimisation */
   cmd = NULLP;  
   tg = NULLP;
   doc = NULLP;
   /*-- Iterate over all the elements in the dictionary --*/
   pos = 0;
   while (PyDict_Next(dict, &pos, &key, &value))
   {
      /*-- key and value are borrowed references --*/
      /*-- Cmd and tg are pointing to string allocated by
           Python, copy the data using TAPA memory in the Create 
           function --*/
      if (PyString_Check(key))
         cmd = PyString_AS_STRING(key);

      /*-- The value is a list element --*/
      if (PyList_Check(value))
      {
         /*-- Group Id --*/
         /*-- borrowed reference --*/
         grpIdObj = PyList_GetItem(value, 0);

         if (PyInt_Check(grpIdObj))
            tstGrpId = PyInt_AS_LONG(grpIdObj);

         /*-- Test groups String --*/
         /*-- borrowed reference --*/
         docObj    = PyList_GetItem(value, 3);

         if (PyString_Check(docObj))
            doc = PyString_AS_STRING(docObj);

         /* cm_xta_py_c_001.main_3 :Added NULL check for doc*/
         if(!doc)
         {
            CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadTestGroups(): doc is NULL\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
         /*-- Add the Test group --*/
         if ((ret = cmXtaTCAddTG(tstGrpId, doc)) != CMXTA_ERR_NONE)
         {
            /*-- The only reason could be that the 
                 test group Id were out of range --*/

#ifdef CMXTA_IGNORE_FAIL
            /*-- We still allow rest of the test groups to get loaded, this may result
                 in load failure for all the test cases in this group, but we will be
                 able to run the rest of the test cases --*/
            CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadTestGroups(): invalid grpId(%d)", tstGrpId));
#else
            /*-- This is a fatal error, stop loading TG further --*/
            CMXTA_DBG_FATAL((_cmxtap, "cmXtaPyWrap_loadTestGroups(): invalid grpId(%d)", tstGrpId));

            /*-- Release dictionary reference --*/
            Py_DECREF(dict);

            RETVALUE(CMXTA_ERR_INT);
#endif
         }
         else
         {
            /*-- tg field no longer being used for memory optimization --*/
            /*-- Create new TG Block --*/
            if ((xmlCb = cmXtaXmlCreate((Txt *)cmd, CMXTA_TYPE_TG, 0,
                        NULLP, NULLP, (Txt *)tg, parse)) == NULLP)
            {
               /*-- Memory issues, just return, cleanup will
               happen from the DeInit functions --*/
               CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadTestGroups(): resource error\n"));
               RETVALUE(CMXTA_ERR_RSRC);
            }

            cmXtaCb.tstGrp[tstGrpId - 1].tg = xmlCb;
         }
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_loadTestGroups */

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
PUBLIC S16 cmXtaPyWrap_loadTestCases
(
Bool        parse
)
#else
PUBLIC S16 cmXtaPyWrap_loadTestCases(parse)
Bool        parse;
#endif
{
   PyObject *key;
   PyObject *value;
   PyObject *dict;
   PyObject *pFunc;
   PyObject *grpIdObj;
   PyObject *tstIdObj;
   PyObject *tcObj;

   int pos;
   char *cmd;
   char *tc;

   S16      ret;
   CmXtaXmlCb *xmlCb;
   /* cm_xta_py_c_001.main_3 :Array size increased*/
   Txt     tgId[15];

   /* cm_xta_py_c_001.main_3 :Added Initialization */
   int   tstGrpId=CMXTA_MAX_GRP;
   int   tstId=CMXTA_MAX_TST;

   TRC2(cmXtaPyWrap_loadTestCases)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_loadTestCases(): load test cases\n"));

   pFunc = pyCb.loadTestCases;
   /* cm_xta_py_c_001.main_4 - Fix for compilation warning and optimisation */

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      /*-- Get the dictionary --*/
      dict = PyObject_CallObject(pFunc, NULLP);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (dict == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadTestCases(): function call failed\n"));
         RETVALUE(RFAILED);
      }
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadTestCases(): not a function object\n"));
      RETVALUE(RFAILED);
   }

   /*-- Store the dictionary in the global Cb --*/
   pyCb.testCaseDict = dict;
   
   /* cm_xta_py_c_001.main_4 - Fix for compilation warning and optimisation */
   cmd = NULLP;
   tc = NULLP;
   /*-- Iterate over all the elements in the dictionary --*/
   pos = 0;
   while (PyDict_Next(dict, &pos, &key, &value))
   {
      /*-- key and value are borrowed references --*/
      /*-- Cmd and tc are pointing to string allocated by
           Python, copy the data using TAPA memory in the Create 
           function --*/
      if (PyString_Check(key))
         cmd = PyString_AS_STRING(key);

      /*-- The value is a list element --*/
      if (PyList_Check(value))
      {
         /*-- Group Id --*/
         /*-- borrowed reference --*/
         grpIdObj = PyList_GetItem(value, 0);
         /*-- Test Id --*/
         /*-- borrowed reference --*/
         tstIdObj = PyList_GetItem(value, 1);
         /*-- Test Case String --*/
         /*-- borrowed reference --*/
         tcObj    = PyList_GetItem(value, 2);

         if (PyInt_Check(grpIdObj))
            tstGrpId = PyInt_AS_LONG(grpIdObj);

         if (PyInt_Check(tstIdObj))
            tstId = PyInt_AS_LONG(tstIdObj);

         /*-- Add the Test case --*/
         if ((ret = cmXtaTCAddTC(tstGrpId, tstId)) != CMXTA_ERR_NONE)
         {
            /*-- The only reason could be that the Test Case Id
                 or the test group Id were out of range --*/
#ifdef CMXTA_IGNORE_FAIL
            /*-- We still allow rest of the test cases to get loaded, this may result
                 in load failure for all the test cases in this group, but we will be
                 able to run the rest of the test cases --*/
            CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadTestCases(): invalid grpId(%d)", tstGrpId));
            CMXTA_DBG_ERR((_cmxtap, "or tstId(%d)\n", tstId));
#else
            /*-- This is a fatal error, stop loading TG further --*/
            CMXTA_DBG_FATAL((_cmxtap, "cmXtaPyWrap_loadTestCases(): invalid grpId(%d)", tstGrpId));
            CMXTA_DBG_FATAL((_cmxtap, "or tstId(%d)\n", tstId));

            /*-- Release dictionary reference --*/
            Py_DECREF(dict);

            RETVALUE(CMXTA_ERR_INT);
#endif
         }
         else
         {
            /*-- tc field no longer being used for memory optimization --*/
            /*-- Create new TC Block --*/
            if ((xmlCb = cmXtaXmlCreate((Txt *)cmd, CMXTA_TYPE_TC, 0,
                        NULLP, NULLP, (Txt *)tc, parse)) == NULLP)
            {
               /*-- Memory issues, just return, cleanup will
               happen from the DeInit functions --*/
               CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadTestCases(): resource error\n"));
               RETVALUE(CMXTA_ERR_RSRC);
            }

            sprintf(tgId, "%d", tstGrpId);
            /*-- For TC, add the association to the TG, if present --*/
            xmlCb->t.xmlTC.tg = cmXtaXmlFind(tstGrpId, 0, tgId, FALSE);

            cmXtaCb.tstGrp[tstGrpId - 1].tstList[tstId - 1].tc = xmlCb;
         }
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_loadTestCases */

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
PUBLIC S16 cmXtaPyWrap_loadCommands
(
Bool        parse
)
#else
PUBLIC S16 cmXtaPyWrap_loadCommands(parse)
Bool        parse;
#endif
{
   PyObject *key;
   PyObject *value;
   PyObject *dict;
   PyObject *pFunc;
   int pos;
   char *cmd;
   char *tc;

   CmXtaXmlCb *xmlCb;
   TRC2(cmXtaPyWrap_loadCommands)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_loadCommands(): load compound commands\n"));

   pFunc = pyCb.loadCommands;
   /* cm_xta_py_c_001.main_4 - Fix for compilation warning and optimisation */

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      /*-- Get the dictionary --*/
      dict = PyObject_CallObject(pFunc, NULLP);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (dict == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadCommands(): function call failed\n"));
         RETVALUE(RFAILED);
      }
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadCommands(): not a function object\n"));
      RETVALUE(RFAILED);
   }

   /*-- Store the dictionary in the global Cb --*/
   pyCb.commandDict = dict;
   
   /* cm_xta_py_c_001.main_4 - Fix for compilation warning and optimisation */
   cmd = NULLP;
   tc = NULLP;

   /*-- Iterate over all the elements in the dictionary --*/
   pos = 0;
   while (PyDict_Next(dict, &pos, &key, &value))
   {
      /*-- Cmd and tc are pointing to string allocated by
           Python, copy the data using TAPA memory in the Create 
           function --*/
      if (PyString_Check(key))
         cmd = PyString_AS_STRING(key);

      /*-- tc field no longer being used for memory optimization --*/
      /*-- Create new compound command Block --*/
      if ((xmlCb = cmXtaXmlCreate((Txt *)cmd, CMXTA_TYPE_COMPOUND, 0,
                             NULLP, NULLP, (Txt *)tc, parse)) == NULLP)
      {
         /*-- Memory issues, just return, cleanup will
           happen from the DeInit functions --*/
         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_loadCommands(): resource error\n"));
         RETVALUE(CMXTA_ERR_RSRC);
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_loadCommands */

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
PUBLIC Void* cmXtaPyWrap_getElementsByTagName
(
Void *curStep,
Txt  *tagName
)
#else
PUBLIC Void* cmXtaPyWrap_getElementsByTagName(curStep, tagName)
Void *curStep;
Txt  *tagName;
#endif
{
   PyObject *pElem;

   TRC2(cmXtaPyWrap_getElementsByTagName)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_getElementsByTagName(): \n"));

   pElem = NULLP;

   /*-- Call the getElementsByTagName attribute for the step --*/
   if (!PyObject_HasAttrString((PyObject *)curStep, "getElementsByTagName"))
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_getElementsByTagName(): object attribute not found\n"));
      RETVALUE(NULLP);
   }

   /*-- Find the element for the tag --*/
   /*-- New reference --*/
   pElem = PyObject_CallMethod((PyObject *)curStep, "getElementsByTagName", "(s)", tagName);
   if (pElem == NULLP)
   {
      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           list is returned --*/
      if (PyErr_Occurred() != NULLP)
         PyErr_Print();

      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_getElementsByTagName(): function call failed\n"));
      RETVALUE(NULLP);
   }
   else if (pElem == Py_None)
      RETVALUE(NULLP);

   /*-- pElem is a NodeList, return first elem if required --*/
   RETVALUE(pElem);
}/* cmXtaPyWrap_getElementsByTagName */

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
PUBLIC S16 cmXtaPyWrap_Parse
(
CmXtaXmlCb      *xmlCb /* Transaction Block   --*/
)
#else
PUBLIC S16 cmXtaPyWrap_Parse(xmlCb)
CmXtaXmlCb      *xmlCb; /* Transaction Block   --*/
#endif
{
   PyObject *list;
   PyObject *pFunc;
   PyObject *dict;

   TRC2(cmXtaPyWrap_Parse)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_Parse(): parse XML\n"));

   /*-- Check if already parsed --*/
   if (xmlCb->parsed == TRUE)
      RETVALUE(CMXTA_ERR_NONE);

   if (xmlCb->cmdType == CMXTA_TYPE_TC)
   {
      pFunc = pyCb.parseTestCase;
      dict  = pyCb.testCaseDict;
   }
   else if (xmlCb->cmdType == CMXTA_TYPE_COMPOUND)
   {
      pFunc = pyCb.parseCommand;
      dict  = pyCb.commandDict;
   }
   else
   {
      pFunc = pyCb.parseTestGroup;
      dict  = pyCb.testGroupDict;
   }

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      /*-- New reference --*/
      list = PyObject_CallFunction(pFunc, "(OsO)", Py_None, xmlCb->cmd, dict);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (list == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_Parse(): function call failed\n"));
         RETVALUE(RFAILED);
      }
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_Parse(): not a function object\n"));
      RETVALUE(RFAILED);
   }

   /*-- The value is a list element --*/
   xmlCb->xmlDocNode = PyList_GetItem(list, 0);
   Py_INCREF((PyObject *)xmlCb->xmlDocNode);

   xmlCb->tcNode  = PyList_GetItem(list, 1);
   Py_INCREF((PyObject *)xmlCb->tcNode);

   /*-- Rest valid only if parsing a test case --*/
   if (xmlCb->cmdType == CMXTA_TYPE_TC)
   {
      xmlCb->t.xmlTC.doc      = PyList_GetItem(list, 2);
      if (xmlCb->t.xmlTC.doc == Py_None)
         xmlCb->t.xmlTC.doc = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlTC.doc);

      xmlCb->t.xmlTC.pre      = PyList_GetItem(list, 3);
      if (xmlCb->t.xmlTC.pre == Py_None)
         xmlCb->t.xmlTC.pre = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlTC.pre);

      xmlCb->t.xmlTC.cfg      = PyList_GetItem(list, 5);
      if (xmlCb->t.xmlTC.cfg == Py_None)
         xmlCb->t.xmlTC.cfg = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlTC.cfg);

      xmlCb->t.xmlTC.test     = PyList_GetItem(list, 7);
      if (xmlCb->t.xmlTC.test == Py_None)
         xmlCb->t.xmlTC.test = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlTC.test);

      xmlCb->t.xmlTC.clean    = PyList_GetItem(list, 9);
      if (xmlCb->t.xmlTC.clean == Py_None)
         xmlCb->t.xmlTC.clean = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlTC.clean);

      xmlCb->t.xmlTC.shutdown = PyList_GetItem(list, 11);
      if (xmlCb->t.xmlTC.shutdown == Py_None)
         xmlCb->t.xmlTC.shutdown = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlTC.shutdown);
   }
   else if (xmlCb->cmdType == CMXTA_TYPE_COMPOUND)
   {
      xmlCb->t.xmlCmd.doc      = PyList_GetItem(list, 2);
      if (xmlCb->t.xmlCmd.doc == Py_None)
         xmlCb->t.xmlCmd.doc = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlCmd.doc);

      xmlCb->t.xmlCmd.steps      = PyList_GetItem(list, 4);
      if (xmlCb->t.xmlCmd.steps == Py_None)
         xmlCb->t.xmlCmd.steps = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlCmd.steps);
   }
   else if (xmlCb->cmdType == CMXTA_TYPE_TG)
   {
      xmlCb->t.xmlTG.doc      = PyList_GetItem(list, 2);
      if (xmlCb->t.xmlTG.doc == Py_None)
         xmlCb->t.xmlTG.doc = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlTG.doc);

      xmlCb->t.xmlTG.pre      = PyList_GetItem(list, 3);
      if (xmlCb->t.xmlTG.pre == Py_None)
         xmlCb->t.xmlTG.pre = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlTG.pre);

      xmlCb->t.xmlTG.cfg      = PyList_GetItem(list, 5);
      if (xmlCb->t.xmlTG.cfg == Py_None)
         xmlCb->t.xmlTG.cfg = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlTG.cfg);

      xmlCb->t.xmlTG.shutdown = PyList_GetItem(list, 7);
      if (xmlCb->t.xmlTG.shutdown == Py_None)
         xmlCb->t.xmlTG.shutdown = NULLP;
      else
         Py_INCREF((PyObject *)xmlCb->t.xmlTG.shutdown);
   }

   /*-- Set parsed --*/
   xmlCb->parsed = TRUE;

   /*-- TC field no longer being used for memory optimization --*/
   /*-- Release list reference --*/
   Py_DECREF(list);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_Parse */

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
PUBLIC Void* cmXtaPyWrap_nextSiblingOfType
(
Void *curStep,
U16   elmType
)
#else
PUBLIC Void* cmXtaPyWrap_nextSiblingOfType(curStep, elmType)
Void *curStep;
U16   elmType;
#endif
{
   PyObject *nextSibling;
   PyObject *pFunc;

   TRC2(cmXtaPyWrap_nextSiblingOfType)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_nextSiblingOfType(): find nextSibling of type\n"));

   nextSibling = NULLP;

   pFunc = pyCb.nextSiblingOfType;

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      /*-- New reference --*/
      nextSibling = PyObject_CallFunction(pFunc, "(Oi)", curStep, elmType);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (nextSibling == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_nextSiblingOfType(): function call failed\n"));
         RETVALUE(NULLP);
      }
      else if (nextSibling == Py_None)
         RETVALUE(NULLP);
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_nextSiblingOfType(): not a function object\n"));
      RETVALUE(NULLP);
   }

   RETVALUE(nextSibling);
}/* cmXtaPyWrap_nextSiblingOfType */

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
PUBLIC Void* cmXtaPyWrap_nextSibling
(
Void *curStep
)
#else
PUBLIC Void* cmXtaPyWrap_nextSibling(curStep)
Void *curStep;
#endif
{
   PyObject *nextStep;

   TRC2(cmXtaPyWrap_nextSibling)

   nextStep = NULLP;

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_nextSibling(): find nextSibling\n"));

   /*-- Call the nextSibling attribute for the step --*/
   if (!PyObject_HasAttrString((PyObject *)curStep, "nextSibling"))
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_nextSibling(): object attribute not found\n"));
      RETVALUE(NULLP);
   }

   /*-- Find the next sibling for the step --*/
   /*-- New reference --*/
   nextStep = PyObject_GetAttrString((PyObject *)curStep, "nextSibling");
   if (nextStep == NULLP)
   {
      if (PyErr_Occurred() != NULLP)
         PyErr_Print();

      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_nextSibling(): function call failed\n"));
      RETVALUE(NULLP);
   }
   else if (nextStep == Py_None)
      RETVALUE(NULLP);

   RETVALUE(nextStep);
}/* cmXtaPyWrap_nextSibling */

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
PUBLIC Void* cmXtaPyWrap_firstChildOfType
(
Void *curStep,
U16   elmType
)
#else
PUBLIC Void* cmXtaPyWrap_firstChildOfType(curStep, elmType)
Void *curStep;
U16   elmType;
#endif
{
   PyObject *firstChild;
   PyObject *pFunc;

   TRC2(cmXtaPyWrap_firstChildOfType)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_firstChildOfType(): get firstChild of given type(%d)\n", elmType));

   firstChild = NULLP;

   pFunc = pyCb.firstChildOfType;

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      /*-- New reference --*/
      firstChild = PyObject_CallFunction(pFunc, "(Oi)", curStep, elmType);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (firstChild == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_firstChildOfType(): function call failed\n"));
         RETVALUE(NULLP);
      }
      else if (firstChild == Py_None)
         RETVALUE(NULLP);
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_firstChildOfType(): not a function object\n"));
      RETVALUE(NULLP);
   }

   RETVALUE(firstChild);
}/* cmXtaPyWrap_firstChildOfType */

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
PUBLIC Void* cmXtaPyWrap_firstChild
(
Void *curStep
)
#else
PUBLIC Void* cmXtaPyWrap_firstChild(curStep)
Void *curStep;
#endif
{
   PyObject *firstChild;

   TRC2(cmXtaPyWrap_firstChild)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_firstChild(): get firstChild\n"));
   firstChild = NULLP;

   /*-- Call the firstChild attribute for the step --*/
   if (!PyObject_HasAttrString((PyObject *)curStep, "firstChild"))
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_firstChild(): object attribute not found\n"));
      RETVALUE(NULLP);
   }

   /*-- Find the next sibling for the step --*/
   /*-- New reference --*/
   firstChild = PyObject_GetAttrString((PyObject *)curStep, "firstChild");
   if (firstChild == NULLP)
   {
      if (PyErr_Occurred() != NULLP)
         PyErr_Print();

      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_firstChild(): function call failed\n"));
      RETVALUE(NULLP);
   }
   else if (firstChild == Py_None)
      RETVALUE(NULLP);

   RETVALUE(firstChild);
}/* cmXtaPyWrap_firstChild */

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
PUBLIC Void* cmXtaPyWrap_getNextOfType
(
Void *curStep,
Void *nextStep,
U16   elmType
)
#else
PUBLIC  Void* cmXtaPyWrap_getNextOfType(curStep,nextStep,elmType)
Void *curStep;
Void *nextStep;
U16   elmType;
#endif
{
   Void *nextChild;

   TRC2(cmXtaPyWrap_getNextOfType)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_getNextOfType(): \n"));

   if (nextStep == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_getNextOfType(): Getting the First Child\n"));
      nextChild = cmXtaPyWrap_firstChildOfType((PyObject *)curStep,elmType);
   }
   else
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_getNextOfType(): Getting the Next Sibling Child\n"));
      nextChild = cmXtaPyWrap_nextSiblingOfType((PyObject *)nextStep,elmType);
   }

   RETVALUE(nextChild);
}/* cmXtaPyWrap_getNextOfType */



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
PUBLIC CmXtaXmlCb* cmXtaPyWrap_FindFromXml
(
Void *curStep
)
#else
PUBLIC CmXtaXmlCb* cmXtaPyWrap_FindFromXml(curStep)
Void *curStep;
#endif
{
   PyObject *tagName;
   PyObject *pFunc;
   /* cm_xta_py_c_001.main_3 :Added Initialization */
   Txt *cmd=NULLP;

   CmXtaXmlCb *xmlCb;

   tagName = NULLP;

   TRC2(cmXtaPyWrap_FindFromXml)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_FindFromXml(): \n"));

   tagName = NULLP;

   pFunc = pyCb.getTagName;

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      /*-- New reference --*/
      tagName = PyObject_CallFunction(pFunc, "(O)", curStep);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (tagName == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_FindFromXml(): function call failed\n"));
         RETVALUE(NULLP);
      }
      else if (tagName == Py_None)
      {
         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_FindFromXml(): tagName attribute not found\n"));
         RETVALUE(NULLP);
      }
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_FindFromXml(): not a function object\n"));
      RETVALUE(NULLP);
   }

   if (PyString_Check(tagName))
      cmd = PyString_AS_STRING(tagName);

   /* cm_xta_py_c_001.main_3 :Added NULL check */
   if(!cmd)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_FindFromXml(): cmd is NULL\n"));
      RETVALUE(NULLP);
   }
   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_FindFromXml(): search cmd (%s)\n", cmd));

   /*-- Find compound command Block --*/
   if ((xmlCb = cmXtaXmlFind(0, 0, (Txt *)cmd, TRUE)) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_FindFromXml(): XML Cb not found\n"));
      RETVALUE(NULLP);
   }

   RETVALUE(xmlCb);
}/* cmXtaPyWrap_FindFromXml */

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
PUBLIC S16 cmXtaPyWrap_SetAttr
(
U8   type,
Txt  *attrib,
Void *val
)
#else
PUBLIC S16 cmXtaPyWrap_SetAttr(type, attrib,val)
U8   type;
Txt  *attrib;
Void *val;
#endif
{
   PyObject *attribVal;

   TRC2(cmXtaPyWrap_SetAttr)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_SetAttr(): \n"));

   attribVal = NULLP;

   switch (type)
   {
      case CMXTA_ATTRIB_BOOL :
         if (*(Bool *)val == TRUE)
            attribVal = Py_True;
         else
            attribVal = Py_False;

         break;
      
      case CMXTA_ATTRIB_U8 :
         attribVal = Py_BuildValue("i", *(U8 *)val);
         break;

      default :
         break;
   }

   PyObject_SetAttrString(pyCb.pModule, attrib, attribVal);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_SetAttr */

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
PUBLIC S16 cmXtaPyWrap_getVal
(
CmXtaTCCb  *tcCb,
Void *curStep,
U8   type,
Txt  *attrib,
Void *val
)
#else
PUBLIC S16 cmXtaPyWrap_getVal(tcCb, curStep, type, attrib,val)
CmXtaTCCb  *tcCb;
Void *curStep;
U8   type;
Txt  *attrib;
Void *val;
#endif
{
   PyObject *attribVal;
   PyObject *pFunc;
   Txt *cmd;
   Bool match;
   CmXtaSpCb    *spCb;
   S16 cnt;

   TRC2(cmXtaPyWrap_getVal)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_getVal(): \n"));

   attribVal = NULLP;

   pFunc = pyCb.getVal;

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      match = FALSE;

      /*-- New reference --*/
      attribVal = PyObject_CallFunction(pFunc, "(Ois)", curStep, type, attrib);

      /*-- Check if any error, only error case results
        in NULLP, in case of no testcase, an empty
        dictionary is returned --*/
      if (attribVal == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_getVal(): function call failed\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      else if (attribVal == Py_None)
      {
         /* if CMXTA_RET_ERR_NONE is defined return CMXTA_ERR_NO_VALUE */
         /*-- Attribute not found, value not changed, no error either --*/
         /*-- We are not looking for inherited values either --*/
         /*-- cm_xta_py_c_001.main_1 - returning no value --*/
         if (tcCb == NULLP)
#ifndef CMXTA_RET_ERR_NONE
            RETVALUE(CMXTA_ERR_NONE);
#else
         RETVALUE(CMXTA_ERR_NO_VALUE);
#endif

      }
      else match = TRUE;

      /*-- If we reach here, check if we already have a match --*/
      if ((match == FALSE) && (tcCb != NULLP))
      {
         for (cnt = tcCb->sp - 1; cnt >= 0; cnt--)
         {
            /* Find the cfg step for the test case and associate it with 
               the present step stack */
            spCb = &tcCb->stack[cnt];

            curStep = spCb->curStep;

            /*-- New reference --*/
            attribVal = PyObject_CallFunction(pFunc, "(Ois)", curStep, type, attrib);

            /*-- Check if any error, only error case results
              in NULLP, in case of no testcase, an empty
              dictionary is returned --*/
            if (attribVal == NULLP)
            {
               if (PyErr_Occurred() != NULLP)
                  PyErr_Print();

               CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_getVal(): function call failed\n"));
               RETVALUE(CMXTA_ERR_INT);
            }
            else if (attribVal != Py_None)
            {
               /*-- Attribute found, break --*/
               match = TRUE;
               break;
            }

            /*-- Attribute not found, value not changed, no error either, go 
              the next level --*/
         }
      }

      if (match == FALSE)
      {
         /*-- cm_xta_py_c_001.main_2 --*/
#ifndef CMXTA_RET_ERR_NONE
         /*-- Attribute not found, value not changed, no error either --*/
         RETVALUE(CMXTA_ERR_NONE);
#else
         RETVALUE(CMXTA_ERR_NO_VALUE);
#endif
      }
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_getVal(): not a function object\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   switch (type)
   {
      case CMXTA_ATTRIB_ENUM_U8 :
      case CMXTA_ATTRIB_FLAG :
      if (PyInt_Check(attribVal))
            *(U8 *)val = (U8)PyInt_AS_LONG(attribVal);
         break;

      case CMXTA_ATTRIB_U16 :
      case CMXTA_ATTRIB_ENUM_U16 :
      if (PyInt_Check(attribVal))
            *(U16 *)val = (U16)PyInt_AS_LONG(attribVal);
         break;

      case CMXTA_ATTRIB_BOOL :

         if (PyInt_Check(attribVal))
            *(Bool *)val = (Bool)PyInt_AS_LONG(attribVal);
         break;

      case CMXTA_ATTRIB_ENUM :

         if (PyInt_Check(attribVal))
            *(U16 *)val = (U16)PyInt_AS_LONG(attribVal);
         break;

      case CMXTA_ATTRIB_ENUM_U32 :
         if (PyInt_Check(attribVal))
            *(U32 *)val = (U32)PyInt_AS_LONG(attribVal);
         break;

      case CMXTA_ATTRIB_S16 :

         if (PyInt_Check(attribVal))
            *(S16 *)val = (S16)PyInt_AS_LONG(attribVal);
         break;

      case CMXTA_ATTRIB_S8 :

         if (PyInt_Check(attribVal))
            *(S8 *)val = (S8)PyInt_AS_LONG(attribVal);
         break;

      case CMXTA_ATTRIB_U8 :

         if (PyInt_Check(attribVal))
            *(U8 *)val = (U8)PyInt_AS_LONG(attribVal);
         break;


     case CMXTA_ATTRIB_U32 :

         if (PyInt_Check(attribVal))
            *(U32 *)val = (U32)PyInt_AS_LONG(attribVal);
         break;


      case CMXTA_ATTRIB_TXT :
         if (PyString_Check(attribVal))
         {
            cmd = PyString_AS_STRING(attribVal);
            CMXTA_CPY((U8 *)val, (U8 *)cmd, cmStrlen((CONSTANT U8 *)cmd) + 1);
         }

         break;

      default :
         break;
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_getVal */


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
PUBLIC S16 cmXtaPyWrap_getValList
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
PUBLIC S16 cmXtaPyWrap_getValList(tcCb, curStep, type, sep, attrib, valList, length)
CmXtaTCCb  *tcCb;
Void *curStep;
U8   type;
U8   sep;
Txt  *attrib;
Void *valList;
U8   *length;
#endif
{
   PyObject *attrValList;
   PyObject *pFunc;
   PyObject *obj;
   Txt *cmd;
   Bool match;
   CmXtaSpCb    *spCb;
   S16 cnt;

   TRC2(cmXtaPyWrap_getValList)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_getValList(): \n"));

   attrValList = NULLP;

   pFunc = pyCb.getValList;

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      match = FALSE;

      /*-- New reference --*/
      attrValList = PyObject_CallFunction(pFunc, "(Oiis)", curStep, type, sep, attrib);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (attrValList == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_getValList(): function call failed\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      else if (attrValList == Py_None)
      {
         if (tcCb == NULLP)
            /*-- Attribute not found, value not changed, no error either --*/
            /*-- We are not looking for inherited values either --*/
            RETVALUE(CMXTA_ERR_NONE);
      }
      else match = TRUE;

      /*-- If we reach here, check if we already have a match --*/
      if ((match == FALSE) && (tcCb != NULLP))
      {
         for (cnt = tcCb->sp - 1; cnt >= 0; cnt--)
         {
            /* Find the cfg step for the test case and associate it with 
               the present step stack */
            spCb = &tcCb->stack[cnt];

            curStep = spCb->curStep;

            /*-- New reference --*/
            attrValList = PyObject_CallFunction(pFunc, "(Oiis)", curStep, type, sep, attrib);

            /*-- Check if any error, only error case results
                 in NULLP, in case of no testcase, an empty
                 dictionary is returned --*/
            if (attrValList == NULLP)
            {
               if (PyErr_Occurred() != NULLP)
                  PyErr_Print();

               CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_getValList(): function call failed\n"));
               RETVALUE(CMXTA_ERR_INT);
            }
            else if (attrValList != Py_None)
            {
               /*-- Attribute found, break --*/
               match = TRUE;
               break;
            }

            /*-- Attribute not found, value not changed, no error either, go 
                 the next level --*/
         }
      }
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_getValList(): not a function object\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Iterate over all the elements in the list --*/
   /*-- The value is a list element --*/
   if (PyList_Check(attrValList))
   {
      /*-- Check the length --*/
      *length = PyList_Size(attrValList);

      /*-- Loop through all elements --*/
      for (cnt = 0; cnt < *length; cnt++)
      {
         /*-- Borrowed reference --*/
         obj    = PyList_GetItem(attrValList, cnt);

         switch (type)
         {
            case CMXTA_ATTRIB_ENUM_U8 :
            case CMXTA_ATTRIB_FLAG :
               if (PyInt_Check(obj))
                  *((U8 *)valList + cnt) = (U8)PyInt_AS_LONG(obj);
               break;

            case CMXTA_ATTRIB_BOOL :

               if (PyInt_Check(obj))
                  *((Bool *)valList + cnt) = (Bool)PyInt_AS_LONG(obj);
               break;

            case CMXTA_ATTRIB_U16 :
            case CMXTA_ATTRIB_ENUM_U16 :
               if (PyInt_Check(obj))
                  *((U16 *)valList + cnt) = (U16)PyInt_AS_LONG(obj);
               break;

            case CMXTA_ATTRIB_ENUM :
               if (PyInt_Check(obj))
                  *((U16 *)valList + cnt) = (U16)PyInt_AS_LONG(obj);
               break;

            case CMXTA_ATTRIB_ENUM_U32 :
               if (PyInt_Check(obj))
                  *((U32 *)valList + cnt) = (U32)PyInt_AS_LONG(obj);
               break;

            case CMXTA_ATTRIB_S16 :
               if (PyInt_Check(obj))
                  *((S16 *)valList + cnt) = (S16)PyInt_AS_LONG(obj);
               break;

            case CMXTA_ATTRIB_U8 :
               if (PyInt_Check(obj))
                  *((U8 *)valList + cnt) = (U8)PyInt_AS_LONG(obj);
               break;


            case CMXTA_ATTRIB_U32 :
               if (PyInt_Check(obj))
                  *((U32 *)valList + cnt) = (U32)PyInt_AS_LONG(obj);
               break;


            case CMXTA_ATTRIB_TXT :
               if (PyString_Check(obj))
               {
                  cmd = PyString_AS_STRING(obj);
                  CMXTA_CPY(((U8 *)valList + (cnt * 100)),
                          (U8 *)cmd,
                          cmStrlen((CONSTANT U8 *)cmd) + 1);
               }

               break;

            default :
               break;
         }
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_getValList */

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
PUBLIC S16 cmXtaPyWrap_GetTCDoc
(
CmXtaXmlCb *xmlCb,
Void *doc,
Void *pre
)
#else
PUBLIC S16 cmXtaPyWrap_GetTCDoc(xmlCb, doc, pre)
CmXtaXmlCb *xmlCb;
Void *doc;
Void *pre;
#endif
{
   PyObject *descObj;
   PyObject *modObj;
   PyObject *rfcObj;
   PyObject *ifdefObj;
   PyObject *ifndefObj;
   PyObject *modeObj;

   PyObject *list;
   PyObject *pFunc;

   /* cm_xta_py_c_001.main_3 :Added Initialization */
   Txt *str1=NULLP;

   TRC2(cmXtaPyWrap_GetTCDoc)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_GetTCDoc(): get TC doc\n"));

   pFunc = pyCb.getTCDoc;

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      /*-- New reference --*/
      list = PyObject_CallFunction(pFunc, "(OO)", doc, pre);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (list == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_GetTCDoc(): function call failed\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      else if (list == Py_None)
         /*-- Attribute not found, value not changed, no error either --*/
         RETVALUE(CMXTA_ERR_NONE);
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_GetTCDoc(): not a function object\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Iterate over all the elements in the list --*/
   /*-- The value is a list element --*/
   if (PyList_Check(list))
   {
      /*-- Borrowed reference --*/
      rfcObj    = PyList_GetItem(list, 0);

      /*-- Borrowed reference --*/
      modObj    = PyList_GetItem(list, 1);

      /*-- Borrowed reference --*/
      descObj    = PyList_GetItem(list, 2);

      /*-- Borrowed reference --*/
      ifdefObj    = PyList_GetItem(list, 3);

      /*-- Borrowed reference --*/
      ifndefObj    = PyList_GetItem(list, 4);

      /*-- Borrowed reference --*/
      modeObj    = PyList_GetItem(list, 5);

      /*-- Display doc info --*/
      CMXTA_DBG_CALL((_cmxtap, "\n\n"));

      CMXTA_DBG_CALL((_cmxtap, "Test Case     :\t%s\n", xmlCb->cmd));

      CMXTA_DBG_CALL((_cmxtap, "Alternate Id  :\t%s\n", xmlCb->cmd));

      if (PyString_Check(rfcObj))
         str1 = PyString_AS_STRING(rfcObj);
      CMXTA_DBG_CALL((_cmxtap, "RFC           :\t%s\n", str1));

      if (PyString_Check(modObj))
         str1 = PyString_AS_STRING(modObj);
      CMXTA_DBG_CALL((_cmxtap, "Module        :\t%s\n", str1));

      if (PyString_Check(ifdefObj))
         str1 = PyString_AS_STRING(ifdefObj);
      CMXTA_DBG_CALL((_cmxtap, "Flags         :\t%s\n", str1));

      if (PyString_Check(ifndefObj))
         str1 = PyString_AS_STRING(ifndefObj);
      CMXTA_DBG_CALL((_cmxtap, "Flags Exclude :\t%s\n", str1));

      if (PyString_Check(modeObj))
         str1 = PyString_AS_STRING(modeObj);
      CMXTA_DBG_CALL((_cmxtap, "Mode          :\t%s\n", str1));

      if (PyString_Check(descObj))
         str1 = PyString_AS_STRING(descObj);
      CMXTA_DBG_CALL((_cmxtap, "Description   :\t%s\n", str1));

      CMXTA_DBG_CALL((_cmxtap, "================================================================\n"));
   }

   /*-- Release dictionary reference --*/
   Py_DECREF(list);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_GetTCDoc */

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
PUBLIC S16 cmXtaPyWrap_GetDocTCStep
(
CmXtaTCCb      *tcCb,
Void *curStep,
U16 sp
)
#else
PUBLIC S16 cmXtaPyWrap_GetDocTCStep(tcCb, curStep, sp)
CmXtaTCCb      *tcCb;
Void *curStep;
U16 sp;
#endif
{
   PyObject *list;
   PyObject *intList;
   PyObject *embList;
   PyObject *pFunc;
   PyObject *doc1Obj;
   PyObject *doc2Obj;

   /* cm_xta_py_c_001.main_3 :Added Initialization */
   Txt *str1=NULLP;
   Txt *str2;
   Txt stepCntStr[20];

   U16 length;
   U16 intLen;
   U16 embLen;
   U16 cnt;
   U16 j;

   TRC2(cmXtaPyWrap_GetDocTCStep)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_GetDocTCStep(): get TC step doc\n"));

   pFunc = pyCb.getDocTCStep;

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      /*-- New reference --*/
      list = PyObject_CallFunction(pFunc, "(O)", curStep);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (list == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_GetDocTCStep(): function call failed\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      else if (list == Py_None)
         /*-- Attribute not found, value not changed, no error either --*/
         RETVALUE(CMXTA_ERR_NONE);
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_GetDocTCStep(): not a function object\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Iterate over all the elements in the list --*/
   /*-- The value is a list element --*/
   if (PyList_Check(list))
   {
      /*-- Check the length --*/
      length = PyList_Size(list);

      /*-- Loop through all elements --*/
      for (cnt = 0; cnt < length; cnt++)
      {
         /*-- Borrowed reference --*/
         intList    = PyList_GetItem(list, cnt);

         /*-- Check the length --*/
         intLen = PyList_Size(intList);

         if (intLen == 1)
         {
            /*-- Only one element, print on a single line --*/
            /*-- Test Case String --*/
            /*-- Borrowed reference --*/
            doc1Obj    = PyList_GetItem(intList, 0);

            if (PyString_Check(doc1Obj))
               str1 = PyString_AS_STRING(doc1Obj);

            /*-- Generate stepCnt string --*/
            cmXtaTCGenCount(tcCb, stepCntStr);

            CMXTA_DBG_CALL((_cmxtap, "%-10s%-10s\n", stepCntStr, str1));
         }
         else
         {
            /*-- Only one element, print on a single line --*/
            /*-- Test Case String --*/
            /*-- Borrowed reference --*/
            doc1Obj    = PyList_GetItem(intList, 0);

            /*-- Borrowed reference --*/
            doc2Obj    = PyList_GetItem(intList, 1);

            if ((PyString_Check(doc1Obj)) && (PyString_Check(doc2Obj)))
            {
               str1 = PyString_AS_STRING(doc1Obj);

               str2 = PyString_AS_STRING(doc2Obj);

               /*-- Generate stepCnt string --*/
               cmXtaTCGenCount(tcCb, stepCntStr);

               CMXTA_DBG_CALL((_cmxtap, "%-10s%-10s: %s\n", stepCntStr, str1, str2));
            }

            /*-- Increment stack pointer --*/
            tcCb->sp++;

            /*-- Check if there are any embedded commands --*/
            for (j = 2; j < intLen; j++)
            {
               /*-- Handle sub commands --*/

               /*-- Borrowed reference --*/
               embList    = PyList_GetItem(intList, j);

               /*-- Check the length --*/
               embLen = PyList_Size(embList);

               if (embLen == 1)
               {
                  /*-- Only one element, print on a single line --*/
                  /*-- Test Case String --*/
                  /*-- Borrowed reference --*/
                  doc1Obj    = PyList_GetItem(embList, 0);

                  if (PyString_Check(doc1Obj))
                     str1 = PyString_AS_STRING(doc1Obj);

                  /*-- Generate stepCnt string --*/
                  cmXtaTCGenCount(tcCb, stepCntStr);

                  CMXTA_DBG_CALL((_cmxtap, "%-10s%-10s\n", stepCntStr, str1));
               }
               else
               {
                  /*-- Test Case String --*/
                  /*-- Borrowed reference --*/
                  doc1Obj    = PyList_GetItem(embList, 0);

                  /*-- Borrowed reference --*/
                  doc2Obj    = PyList_GetItem(embList, 1);

                  if ((PyString_Check(doc1Obj)) && (PyString_Check(doc2Obj)))
                  {
                     str1 = PyString_AS_STRING(doc1Obj);

                     str2 = PyString_AS_STRING(doc2Obj);

                     /*-- Generate stepCnt string --*/
                     cmXtaTCGenCount(tcCb, stepCntStr);

                     /*-- Increment the step count --*/
                     cmXtaTCSpIncrStepCnt(tcCb);

                     CMXTA_DBG_CALL((_cmxtap, "%-10s%-10s: %s\n", stepCntStr, str1, str2));
                  }
               }
            }

            /*-- Reset the step count --*/
            cmXtaTCSpResetStepCnt(tcCb);

            /*-- Decrement stack pointer --*/
            tcCb->sp--;
         }
      }
   }

   /*-- Release dictionary reference --*/
   Py_DECREF(list);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_GetDocTCStep */

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
PUBLIC S16 cmXtaPyWrap_ValidatePre
(
CmXtaTCCb *tcCb,
Void *curStep
)
#else
PUBLIC S16 cmXtaPyWrap_ValidatePre(tcCb, curStep)
CmXtaTCCb *tcCb;
Void *curStep;
#endif
{
   PyObject *list;
   PyObject *pFunc;
   PyObject *intList;
   PyObject *strList;
   PyObject *pyObj;
   PyObject *pyObjStr;

   U16 length;
   /* cm_xta_py_c_001.main_3 :Added Initialization */
   U16 strLen=0;
   U16 printLen;
   U16 i;
   /* cm_xta_py_c_001.main_3 :Added Initialization */
   U16 val=0;
   char *cmd=NULLP;

   Bool match;
   Bool dfltMode;
   Bool loadMode;
   Bool extMode;
   Bool multipleMode;

   TRC2(cmXtaPyWrap_ValidatePre)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_ValidatePre(): validate TC\n"));

   multipleMode = FALSE;
   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT_NOSHUTDOWN) == CMXTA_TA_MODE_DFLT_NOSHUTDOWN)
      multipleMode = TRUE;

   dfltMode = FALSE;
   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT) == CMXTA_TA_MODE_DFLT)
      dfltMode = TRUE;

   loadMode = FALSE;
   if ((cmXtaCb.mode & CMXTA_TA_MODE_LOAD) == CMXTA_TA_MODE_LOAD)
      loadMode = TRUE;

   extMode = FALSE;
   if ((cmXtaCb.mode & CMXTA_TA_MODE_EXTERNAL) == CMXTA_TA_MODE_EXTERNAL)
      extMode = TRUE;

   pFunc = pyCb.validatePre;

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      /*-- New reference --*/
      list = PyObject_CallFunction(pFunc, "(O)", curStep);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (list == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_ValidatePre(): function call failed\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      else if (list == Py_None)
         /*-- Attribute not found, value not changed, no error either --*/
         RETVALUE(CMXTA_ERR_NONE);
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_ValidatePre(): not a function object\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Iterate over all the elements in the list --*/
   /*-- The value is a list element --*/
   if (PyList_Check(list))
   {
      /*-- The first element is the string for the flags that should be enabled --*/
      /*-- The second element is the list of the flags that should be enabled --*/
      /*-- Check the length --*/
      /*-- Borrowed reference --*/
      strList = PyList_GetItem(list, 0);

      intList = PyList_GetItem(list, 1);
      length = PyList_Size(intList);

      match = TRUE;
      printLen = 0;
      for (i = 0; i < length; i++)
      {
         /*-- Borrowed reference --*/
         pyObj    = PyList_GetItem(intList, i);
         if (PyInt_Check(pyObj))
            val = (U16) PyInt_AS_LONG(pyObj);

         /*-- Borrowed reference --*/
         pyObjStr    = PyList_GetItem(strList, i);
         if (PyString_Check(pyObjStr))
            cmd = PyString_AS_STRING(pyObjStr);
         /* cm_xta_py_c_001.main_3 :Added Initialization */
         if(!cmd)
         {
            CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_ValidatePre(): cmd is NULL\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
         /*-- Check if flag enabled, else return failed --*/
         if (cmXtaFlIsSet(val) == FALSE)
         {
            match = FALSE;

            /*-- Flag dependency not met, do not run the TC --*/
            CMXTA_DBG_CALLIND((_cmxtap, "Flag [%s] not enabled\n", cmXtaFlagStr[val]), 2);

            strLen = cmStrlen((CONSTANT U8 *)cmd);

            if (printLen == 0)
            {
               /* cm_xta_py_c_001.main_3 :Added tmpLen updation*/
               U16 tmpLen = 0;
               tmpLen = (sizeof(cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag)/
                         sizeof(Txt));
               /*-- Copy the flag information in the result data structure --*/
               CMXTA_CPY((U8 *)cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag,
                      (U8 *)"Missing Flags: ",
                      15);

               /* cm_xta_py_c_001.main_3 :Added strLen validation */
               if (strLen < (tmpLen - 15))
               {
               /*-- Copy the flag information in the result data structure --*/
                  CMXTA_CPY((U8 *)cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag + 15,
                           (U8 *)cmd, strLen + 1);
                  printLen += strLen + 15;
               }
               else
               {
                  Py_DECREF(list);
                  RETVALUE(CMXTA_ERR_INT);
               }
            }
            else
            {
               /*-- Copy the flag information in the result data structure --*/
               CMXTA_CPY((U8 *)cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag + printLen,
                      (U8 *)":", 1);

               /*-- Copy the flag information in the result data structure --*/
               CMXTA_CPY((U8 *)cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag + printLen + 1,
                      (U8 *)cmd,
                      strLen + 1);

               printLen += strLen + 1;
            }
         }
      }

      if (match == FALSE)
      {
         /*-- Release dictionary reference --*/
         Py_DECREF(list);

         RETVALUE(CMXTA_ERR_INT);
      }

      /*-- The third element is the string for the flags that should not be enabled --*/
      /*-- The fourth element is the list of the flags that should not be enabled --*/
      /*-- Check the length --*/
      strList = PyList_GetItem(list, 2);

      intList = PyList_GetItem(list, 3);
      length = PyList_Size(intList);

      for (i = 0; i < length; i++)
      {
         /*-- Borrowed reference --*/
         pyObj    = PyList_GetItem(intList, i);
         if (PyInt_Check(pyObj))
            val = (U16) PyInt_AS_LONG(pyObj);

         /*-- Borrowed reference --*/
         pyObjStr    = PyList_GetItem(strList, i);
         if (PyString_Check(pyObjStr))
            cmd = PyString_AS_STRING(pyObjStr);

         /*-- Check if flag enabled, else return failed --*/
         if (cmXtaFlIsSet(val) == TRUE)
         {
            match = FALSE;

            /*-- Flag dependency not met, do not run the TC --*/
            CMXTA_DBG_CALLIND((_cmxtap, "Extra Flag [%s] enabled\n", cmXtaFlagStr[val]), 2);

            strLen = cmStrlen((CONSTANT U8 *)cmd);

            if (printLen == 0)
            {
               /* cm_xta_py_c_001.main_3 :Added tmpLen updation*/
               U16 tmpLen = 0;
               tmpLen = (sizeof(cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag)/
                         sizeof(Txt));
               
               /*-- Copy the flag information in the result data structure --*/
               CMXTA_CPY((U8 *)cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag,
                      (U8 *)"Extra Flags: ",
                      13);
               /* cm_xta_py_c_001.main_3 :Added strLen validation */
               if (strLen < (tmpLen - 13))
               {
                  /*-- Copy the flag information in the result data structure --*/
                  CMXTA_CPY((U8 *)cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag + 13,
                      (U8 *)cmd, strLen + 1);
                  printLen += strLen + 13;
               }
               else
               {
                  Py_DECREF(list);
                  RETVALUE(CMXTA_ERR_INT);
               }
            }
            else
            {
               /*-- Copy the flag information in the result data structure --*/
               CMXTA_CPY((U8 *)cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag + printLen,
                      (U8 *)":", 1);

               /*-- Copy the flag information in the result data structure --*/
               CMXTA_CPY((U8 *)cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag + printLen + 1,
                      (U8 *)cmd,
                      strLen + 1);

               printLen += strLen + 1;
            }
         }
      }

      if (match == FALSE)
      {
         /*-- Release dictionary reference --*/
         Py_DECREF(list);

         RETVALUE(CMXTA_ERR_INT);
      }

      val = 10;
      /*-- The fifth element is the string for the mode for TA --*/
      /*-- The sixth element is the mode for TA --*/
      /*-- Borrowed reference --*/
      pyObj = PyList_GetItem(list, 4);
      if (PyString_Check(pyObj))
         cmd = PyString_AS_STRING(pyObj);

      pyObj = PyList_GetItem(list, 5);
      if (PyInt_Check(pyObj))
         val = (U16) PyInt_AS_LONG(pyObj);

      /*-- Check if TA running in correct mode, else return failed --*/
      if (((val == CMXTA_MODE_LOAD)     && (loadMode != TRUE)) ||
          ((val == CMXTA_MODE_EXTERNAL) && (extMode  != TRUE)) ||
          ((val == CMXTA_TA_MODE_DFLT)  && (dfltMode != TRUE)))
      {
         /* cm_xta_py_c_001.main_3 :Added tmpLen updation*/
         U16 tmpLen = 0;
         tmpLen = (sizeof(cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag)/
                         sizeof(Txt));
         /*-- Flag dependency not met, do not run the TC --*/
         CMXTA_DBG_CALLIND((_cmxtap, "Mode mismatch: TA mode [%d] TC mode [%d]\n", 
                        cmXtaCb.mode, val), 3);

         /*-- Copy the flag information in the result data structure --*/
         CMXTA_CPY((U8 *)cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag,
                (U8 *)"Mode: ",
                6);
         /* cm_xta_py_c_001.main_3 :Added strLen validation */
         if (cmStrlen((CONSTANT U8 *)cmd) < (tmpLen - 6))
         {
         /*-- Copy the flag information in the result data structure --*/
            CMXTA_CPY((U8 *)cmXtaCb.tstGrp[tcCb->tstGrpId].tstList[tcCb->tstId].flag + 6,
                     (U8 *)cmd, cmStrlen((CONSTANT U8 *)cmd) + 1);
         }
         /*-- Release dictionary reference --*/
         Py_DECREF(list);

         RETVALUE(CMXTA_ERR_INT);
      }
   }

   /*-- Release dictionary reference --*/
   Py_DECREF(list);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_ValidatePre */


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
PUBLIC S16 cmXtaPyWrap_validateRe
(
CmXtaTCCb  *tcCb,
Void *curStep,
Txt  *msg
)
#else
PUBLIC S16 cmXtaPyWrap_validateRe(tcCb, curStep, msg)
CmXtaTCCb  *tcCb;
Void *curStep;
Txt  *msg;
#endif
{
   PyObject *retVal;
   PyObject *pFunc;
   Bool match;

   TRC2(cmXtaPyWrap_validateRe)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_validateRe(): \n"));

   retVal = NULLP;

   pFunc = pyCb.validateRe;

   /*-- Check if a callable object --*/
   if (pFunc && PyCallable_Check(pFunc))
   {
      match = FALSE;

      /*-- New reference --*/
      retVal = PyObject_CallFunction(pFunc, "(Os)", curStep, msg);

      /*-- Check if any error, only error case results
           in NULLP, in case of no testcase, an empty
           dictionary is returned --*/
      if (retVal == NULLP)
      {
         if (PyErr_Occurred() != NULLP)
            PyErr_Print();

         CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_validateRe(): function call failed\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      else if (retVal != Py_True)
      {
         CMXTA_DBG_INFO((_cmxtap, "cmXtaPyWrap_validateRe(): re match failed\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaPyWrap_validateRe(): not a function object\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaPyWrap_validateRe */

/********************************************************************30**

         End of file:     cm_xta_py.c@@/main/TeNB_Main_BR/2 - Thu Apr 24 17:04:58 2014

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
/main/2      ---      mn   ROHC compliance upgrade
/main/3      --- cm_xta_py_c_001.main_2     ss   1. Updated return for 
                                                    CMXTA_RET_ERR_NONE
/main/4      --- cm_xta_py_c_001.main_3     kchaitanya   1. Updated for fixing
                                                          klockwork errors 
/main/5  cm_xta_py_c_001.main_4 spoovalingam   1. Fix for compilation warnings
                                               2. Fix for compilation warning and optimisation 
/main/6      ---- cm_xta_py_c_001.main_5    jj 1. Updated for Psf-Diameter 1.1
                                                release Removed cm_xta_app.[hx]
*********************************************************************91*/

