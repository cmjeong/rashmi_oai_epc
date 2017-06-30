
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_py.x@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:25 2015

     Prg:     up 

*********************************************************************21*/
#ifndef __CMXTA_PY_X__
#define __CMXTA_PY_X__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16   cmXtaPyInit           ARGS((Void));
EXTERN S16   cmXtaPyDeInit           ARGS((Void));

typedef struct cmXtaPyCb
{
   PyObject *testGroupDict;
   PyObject *testCaseDict;
   PyObject *commandDict;


   PyObject *loadTestGroups;
   PyObject *loadTestCases;
   PyObject *loadCommands;
   PyObject *parseTestCase;
   PyObject *parseTestGroup;
   PyObject *parseCommand;
   PyObject *nextSiblingOfType;
   PyObject *firstChildOfType;
   PyObject *getVal;
   PyObject *getValList;
   PyObject *validateRe;
   PyObject *getDocTCStep;
   PyObject *getTCDoc;
   PyObject *getTagName;
   PyObject *validatePre;
   PyObject *pModule;
}CmXtaPyCb;

EXTERN Void*   cmXtaPyWrap_getElementsByTagName  ARGS((Void *curStep, Txt  *tagName));
EXTERN Void*   cmXtaPyWrap_nextSibling  ARGS((Void *curStep));
EXTERN Void*   cmXtaPyWrap_firstChild  ARGS((Void *curStep));
EXTERN Void*   cmXtaPyWrap_GetNxtTestStep  ARGS((Void *curStep));
EXTERN CmXtaXmlCb*   cmXtaPyWrap_GetStepInfo  ARGS((Void *curStep));
EXTERN S16   cmXtaPyWrap_loadTestCases  ARGS((Bool parse));
EXTERN S16   cmXtaPyWrap_loadCommands  ARGS((Bool parse));
EXTERN S16   cmXtaPyWrap_getVal  ARGS((CmXtaTCCb  *tcCb, Void *curStep, U8 type, Txt *attrib, Void *val));
EXTERN S16   cmXtaPyWrap_getValList  ARGS((CmXtaTCCb  *tcCb, Void *curStep, U8 type, U8 sep, Txt *attrib, Void *valList, U8 *length));
EXTERN S16   cmXtaPyWrap_validateRe  ARGS((CmXtaTCCb  *tcCb, Void *curStep, Txt *msg));
EXTERN S16   cmXtaPyWrap_SetAttr  ARGS((U8 type, Txt *attrib, Void *val));
EXTERN CmXtaXmlCb*   cmXtaPyWrap_FindFromXml  ARGS((Void *curStep));
EXTERN S16   cmXtaPyWrap_Parse  ARGS((CmXtaXmlCb      *xmlCb));
EXTERN Void *   cmXtaPyWrap_firstChildOfType  ARGS((Void *curStep, U16   elmType));
EXTERN Void *   cmXtaPyWrap_nextSiblingOfType  ARGS((Void *curStep, U16   elmType));
EXTERN S16      cmXtaPyWrap_ValidatePre  ARGS((CmXtaTCCb  *tcCb, Void *curStep));

/*----------------------------------------------------------------------
             Python Utility Functions
-----------------------------------------------------------------------*/
PUBLIC S16 cmXtaPyWrap_loadTestGroups ARGS(( Bool        parse));

PUBLIC Void* cmXtaPyWrap_getNextOfType ARGS((
                           Void *curStep,
                           Void *nextStep,
                           U16   elmType));

PUBLIC CmXtaXmlCb* cmXtaPyWrap_FindFromXml_New ARGS(( Void *curStep));

PUBLIC S16 cmXtaPyWrap_GetTCDoc ARGS((CmXtaXmlCb *xmlCb, Void *doc, Void *pre));

PUBLIC S16 cmXtaPyWrap_GetDocTCStep ARGS((CmXtaTCCb *tcCb,
                           Void *curStep,
                           U16 sp));


#ifdef __cplusplus
}
#endif
#endif /* __CMXTA_PY_X__ */
/********************************************************************30**

         End of file:     cm_xta_py.x@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:25 2015

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
*********************************************************************91*/
