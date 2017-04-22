#! /usr/bin/python
import sys
import re
from xml.dom import minidom
from MibAttribManager import *

numCellEntries  = 2

# PATH variables
TR196_2_XML_FILE = "../../../libs/platform/tr_docs/tr-196-2-0-1.xml"
TR181_XML_FILE = "../../../libs/platform/tr_docs/tr-181-2-8-0.xml"
TR262_XML_FILE = "../../../libs/platform/tr_docs/tr-262-1-0-0_RADISYS.xml"
TR157_XML_FILE = "../../../libs/platform/tr_docs/tr-157-1-5-0_RADISYS.xml"
RADISYS_EXT_XML_FILE = "../../../libs/platform/tr_docs/RADISYS_data_model_extension.xml"
TIP_EXT_XML_FILE = "../../../libs/platform/tr_docs/TIP_data_model_extension.xml"

TR196_HEADER_FILE = "../../fap/management/tr069-v2/autogen/Tr196DataModel.h"
TR196_2_HEADER_FILE = "../../fap/management/tr069-v2/autogen/Tr196DataModel2.h"
TR181_HEADER_FILE = "../../fap/management/tr069-v2/autogen/Tr181DataModel.h"
TR262_HEADER_FILE = "../../fap/management/tr069-v2/autogen/Tr262DataModel.h"
TR157_HEADER_FILE = "../../fap/management/tr069-v2/autogen/Tr157DataModel.h"
RADISYS_HEADER_FILE = "../../fap/management/tr069-v2/autogen/RadisysExtDataModel.h"
TIP_HEADER_FILE = "../../fap/management/tr069-v2/autogen/TipExtDataModel.h"
MIB_GRP_ENUM_HEADER = "../../fap/management/tr069-v2/autogen/MibGroupEnum.h"
CPP_FILE = "../../fap/management/tr069-v2/autogen/Tr069DataModel.cpp"

AUTOCODE_MSG = '/*\n * AUTOMATICALLY GENERATED CODE:\n * DO NOT EDIT !\n */\n\n'

TR196_PREFIX    = "Device.Services."      #FAPService.1."
TR157_PREFIX    = "Device."      #FAPService.1."
TR262_PREFIX    = "Device."      #FAP."

# Multiple object dictionaries, to count number of instances of a single object
tr181_MultipleObjCounter = {
                              'PolicerNumberOfEntries':0,
                              'QueueNumberOfEntries':0,
                              'LANDeviceNumberOfEntries':0                              
                           }

tr157_MultipleObjCounter = {
                              'SupportedAlarmNumberOfEntries':0,
                              'CurrentAlarmNumberOfEntries':0,
                              'HistoryEventNumberOfEntries':0,
                              'ExpeditedEventNumberOfEntries':0
                           }

tr262_MultipleObjCounter = {
                              'ConfigNumberOfEntries':1,
                              'CryptoProfileNumberOfEntries':2
			   }

tr196_MultipleObjCounter = {
                              'MemberDetailNumberOfEntries':0,
                              'RulesNumberOfEntries':0,
                              'IntraFreqCellNumberOfEntries':0,
                              'InterFreqCellNumberOfEntries':0,                      
                              'GSMNumberOfEntries':0,
                              'AssocNumberOfEntries':0,
                              'IKESANumberOfEntries':0,
                              'ChildSANumberOfEntries':0,
                              'VirtualInterfaceNumberOfEntries':0,
                              'SecretNumberOfEntries':0,
                              'PkeyNumberOfEntries':0,
                              'CryptoProfileNumberOfEntries':0,
                              'QueuedEventNumberOfEntries':0,
                              'PLMNListNumberOfEntries':0,
                              'CarrierNumberOfEntries':0,
                              'UTRANFDDFreqNumberOfEntries':0,
                              'TunnelNumberOfEntries':0,
                              'CDMA2000BandNumberOfEntries':0,
                              'CDMA2000NumberOfEntries':0,
                              'LTECellNumberOfEntries':1,     
                              'UMTSNumberOfEntries':1,
                              'CellNumberOfEntries':16,
                              'CarrierMeasNumberOfEntries':1,
                              'GERANFreqGroupNumberOfEntries':0,
                              'GSMNumberOfEntries':0
                          }
rsys_ext_MultipleObjCounter = {
      'XRsysGSMNumberOfEntries':0,
      'XRsysGERANFreqGroupNumberOfEntries':0,
      'CarrierNumberOfEntries':8,
      'LTECellNumberOfEntries':16,
      'UTRANTDDFreqNumberOfEntries':0,
      'UMTSTDDNumberOfEntries':0
      }


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
class CodeGenerator:
    """Data Model Code Generator from XML documents (TR196, TR181 and whatever may come)"""
    
    def __init__(self, TR_filename, hdrFile, prefix, multipleObjDict, integrator, fileStart=AUTOCODE_MSG, verbose=False ):
        self.filename = TR_filename
        self.hdrFile = hdrFile
        self.prefix = prefix
        self.fileStart = fileStart
        self.multipleObjDict = multipleObjDict
        self.mioInstances = {}
        self.integrator = integrator
        self.verbose = verbose
        self.mibGroups = []        
        self.numCell = 0

        print "* * * Data Model Code Generator * * *"
        print "Setting verbose mode to", self.verbose
        
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    def GenerateForOneInstance(self, object, objName, instance):
        if self.verbose:
            print "DEBUG! Generating code for instance ", instance, " for object ", objName
        selfParameterList = object.getElementsByTagName('parameter')     
        for param in selfParameterList:
            paramAttr = param.attributes.keys()
            if 'name' not in paramAttr:
                continue
            else:
                paramName = param.attributes['name'].value

            self.paramData = ['','','','']     # type, value, minVal, maxVal
            RadisysFields={}
            childNodesList = param.childNodes                    
            for child in childNodesList:
                if child.nodeName == 'syntax':
                    self.__dataSyntaxParser(child)
                elif child.nodeName == 'RADISYS':
                    RadisysFields = self.__dataRadisysParser(child)
                    # gets value from <default> if <RADISYS> doesn't specify one
                    if RadisysFields['value'] == '':
                        RadisysFields['value'] = self.paramData[1]
                            
            if (not RadisysFields) or (RadisysFields['supported']).upper()=='FALSE':
                if self.verbose:
                    print "DEBUG! Attribute ", paramName, " for object ", objName, " is not included"
                continue

            #if param.attributes[u'name'].value in self.multipleObjDict:
            #    self.multipleObjDict[param.attributes[u'name'].value] = RadisysFields['value']
                       
            # Identify the access mode, whether the parameter is readonly or writable from HeMS
            accessMode = self.__browseForAttribute('access', object, param, RadisysFields)
            if accessMode == 'readOnly' or accessMode =='':
                accessMode = 'READ_ONLY'
            else:
                accessMode = 'READ_WRITE'                      
                    
            # Identify the notification mode for this parameter
            notify = RadisysFields['notificationType']
            if notify == '' or notify=='0':
                notifyMode = 'NO_NOTIFICATION'
            elif notify =='1':
                notifyMode = 'PASSIVE_NOTIFICATION'
            elif notify == '2':
                notifyMode = 'ACTIVE_NOTIFICATION'     

            # Identify the changeApplies for this parameter
            changeApply = RadisysFields['changeApplies']
            if changeApply == '' or changeApply=='0':
                changeApply = 'Immediate'
            elif changeApply == '1':
                changeApply = 'OnReboot'
            elif changeApply == '2':
                changeApply = 'OnEnable'

            forcedInfMode = self.__browseForAttribute('forcedInform', object, param, RadisysFields)
            if forcedInfMode == '':
                forcedInfMode = 'false'  
                        
            mibDn = 'FAP.0'
            if RadisysFields['mib_dn']:
                mibDn = RadisysFields['mib_dn']       
                        
            mibParam = 'PARAM_ID_INVALID'
            if RadisysFields['mib_id']:
                mibParam = RadisysFields['mib_id'] 
                if ( MAM.verifyParam(mibParam) == False):
                    mibParam = 'PARAM_ID_INVALID'
                if 'XTRA' in mibParam:
                    mibParam = 'PARAM_ID_INVALID'                   

            if '{i}' in objName:
                objInst = '{'+str(instance)+'}'
                newObjName = objName.replace('{i}', str(objInst))

                #check if operator replaces an object name
                fullName = newObjName
                if RadisysFields[u'name'] != '':
                    fullName += RadisysFields['name'] 
                else:
                    fullName += param.attributes[u'name'].value  

                mibDnStr = mibDn
                if '{i}' in mibDnStr:
                    mibDnInst='{'+str(instance-1)+'}'
                    mibDnStr = mibDnStr.replace('{i}', mibDnInst)

                #check if the parameter was a list in which case we change its type
                isAList = 'false'
                if (',' in RadisysFields['value']) :
                    isAList = 'true'

                entryStr = self.__buildString(fullName, accessMode, isAList, notifyMode, 
                                              forcedInfMode, changeApply, RadisysFields, mibDnStr, mibParam)
                self.hdr.write(entryStr)                            						
                if self.verbose:
                    print "DEBUG! Wrote into header file:", entryStr
            else:
                #check if the parameter was a list in which case we change its type
                isAList = 'false'
                if (',' in RadisysFields['value']) :
                    isAList = 'true'

                #check if operator replaces an object name
                fullName = objName
                if RadisysFields['name'] != '':
                    fullName += RadisysFields['name'] 
                else:
                    fullName += param.attributes[u'name'].value

                if '{i}' in mibDn:
                    cellInst='{'+str(numCellEntries)+'}'
                    mibDn = mibDn.replace('{i}', cellInst)

                entryStr = self.__buildString(fullName, accessMode, isAList, notifyMode, 
                                              forcedInfMode, changeApply, RadisysFields, mibDn, mibParam)
                self.hdr.write(entryStr)                            
                    
                if self.verbose:
                    print "DEBUG! Wrote into header file:", entryStr
                    
    
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    def processXMLFile(self): 
        try:
            xmldoc = minidom.parse(self.filename)
               
        except(IOError), e:
            print "\n\nERROR: unable to open file ", self.filename, "Ending program.\n", e
            raw_input("\nPress enter Key to exit\n")
            sys.exit()           

        self.objectList = xmldoc.getElementsByTagName("object")
        if self.verbose:
            print "Original <object> list length is :", len(self.objectList)
    
        self.__removeProfileObjs()
        if self.verbose:
            print "<object> list length after <profile> removal is :", len(self.objectList)

        self.hdr = open(self.hdrFile, "w")
        self.hdr.write(self.fileStart)
    
        mioPattern = re.compile('.*{i}\.')
        # <object>
        for elem in self.objectList:
            objAttrs = elem.attributes.keys()
            if 'name' in objAttrs:
                
                objName = elem.attributes['name'].value
                if self.verbose:
                    print 'DEBUG! Object Name is: ', objName                                      

                # check if there is an <RADISYS> element in the object
                # this is valid for NSN and NEC
                integratorName = ''
                if self.integrator != 'Radisys':
                    rsysObjList = elem.getElementsByTagName('RADISYS')
                    for rsysObj in rsysObjList:
                        if rsysObj.parentNode.nodeName == 'parameter':
                            # we don't want to deal with override elements of parameters in here
                            continue
                        # listing child nodes inside <RADISYS>
                        for childNode in rsysObj.childNodes:
                            if childNode.nodeName == 'override':
                                childAttrs = childNode.attributes.keys()
                                
                                sameIntegrator = False
                                for attr in childAttrs:
                                    if 'integrator' in attr:
                                        if childNode.attributes[u'integrator'].value == self.integrator :
                                            sameIntegrator = True
                                        
                                    if 'name' in attr and sameIntegrator:
                                        objName = childNode.attributes[u'name'].value
   
                # If this is a multi instance object, get the number of instances
                # at the end of this step, add to the map of MIOs and their instances
                cellObj='FAPService.{'+str(numCellEntries)+'}'
                objName = objName.replace('FAPService.{i}', cellObj)
                mioRegResult = mioPattern.match(objName)
                if mioRegResult:
                    numEntries = 0
                    if mioRegResult.group(0) != objName:
                        if self.verbose:
                            print "DEBUG! ", objName, " instances are derived from higher MIO"
                        mioReg = mioPattern.match(objName)
                        if mioReg:
                            mioObjName = mioReg.group(0)
                            mioKeys = self.mioInstances.keys()
                        else:
                            print "ERROR!! MIO object name could not be found in ", objName
                            continue
 
                        if mioObjName in mioKeys:
                            numEntries = self.mioInstances[mioObjName];
                            if self.verbose:
                                print "DEBUG! Number of instances of ", objName, " is ", numEntries
                        else:
                            print "WARNING! Object ", objName, "not found in mioInstaces"
                            numEntries = 0
                    else:
                        objAttrs = elem.attributes.keys()
                        childNodesList = elem.childNodes                    
                        for child in childNodesList:
                            if child.nodeName == 'RADISYS':
                                # gets value from <default> if <RADISYS> doesn't specify one
                                RadisysFields = self.__dataRadisysParser(child)
                                if RadisysFields['value'] == '':
                                    print 'WARNING! object', objName, 'has no defined number of instances.'
                                    numEntries = 0
                                else:
                                    numEntries = RadisysFields['value']

                        if numEntries == 0:
                            continue

                        self.mioInstances[objName] = numEntries

                    if numEntries == 0:
                        print 'WARNING! Object ', objName, 'is not included'
                        continue

                    if self.verbose:
                        print 'DEBUG! Object ', objName, 'has ', numEntries, ' instances'
                        
                    self.GenerateForOneInstance(elem, objName, int(numEntries))
                else:
                    self.GenerateForOneInstance(elem, objName, 1)
              
                # Run through the parameters in the object for generating the code
                # selfParameterList = elem.getElementsByTagName('parameter')     
                # for param in selfParameterList:
                #     paramAttr = param.attributes.keys()
                #     if 'name' not in paramAttr:
                #         continue
                #     else:
                #         paramName = param.attributes['name'].value
                    
                #     self.paramData = ['','','','']     # type, value, minVal, maxVal
                #     RadisysFields={}
                #     childNodesList = param.childNodes                    
                #     for child in childNodesList:
                #         if child.nodeName == 'syntax':
                #             self.__dataSyntaxParser(child)
                #         elif child.nodeName == 'RADISYS':
                #             RadisysFields = self.__dataRadisysParser(child)
                #             # gets value from <default> if <RADISYS> doesn't specify one
                #             if RadisysFields['value'] == '':
                #                 RadisysFields['value'] = self.paramData[1]
                            
                #     paramAttr = param.attributes.keys()
    
                #     if not RadisysFields:
                #         continue
    
                #     if (RadisysFields['supported']).upper()=='FALSE':
                #        continue                        
                    
                #     if param.attributes[u'name'].value in self.multipleObjDict:
                #         self.multipleObjDict[param.attributes[u'name'].value] = RadisysFields['value']
                #        
                #     # Identify the access mode, whether the parameter is readonly or writable from HeMS
                #     accessMode = self.__browseForAttribute('access', elem, param, RadisysFields)
                #     if accessMode == 'readOnly' or accessMode =='':
                #         accessMode = 'READ_ONLY'
                #     else:
                #         accessMode = 'READ_WRITE'                      
                    
                #     # Identify the notification mode for this parameter
                #     notify = RadisysFields['notificationType']
                #     if notify == '' or notify=='0':
                #         notifyMode = 'NO_NOTIFICATION'
                #     elif notify =='1':
                #         notifyMode = 'PASSIVE_NOTIFICATION'
                #     elif notify == '2':
                #         notifyMode = 'ACTIVE_NOTIFICATION'     

                #     forcedInfMode = self.__browseForAttribute('forcedInform', elem, param, RadisysFields)
                #     if forcedInfMode == '':
                #         forcedInfMode = 'false'  
                        
                #     mibDn = 'FAP.0'
                #     if RadisysFields['mib_dn']:
                #         mibDn = RadisysFields['mib_dn']       
                        
                #     mibParam = 'PARAM_ID_INVALID'
                #     if RadisysFields['mib_id']:
                #         mibParam = RadisysFields['mib_id'] 
                #         if ( MAM.verifyParam(mibParam) == False):
                #             mibParam = 'PARAM_ID_INVALID'
                #         if 'XTRA' in mibParam:
                #             mibParam = 'PARAM_ID_INVALID'                   
    
                #     # Repeat instances of <parameters> when needed
                #     if '{i}' in objName:
                #         mioReg = mioPattern.match(objName)
                #         if mioReg:
                #             mioObjName = mioReg.group(0)
                #             mioKeys = self.mioInstances.keys()
                #         else:
                #             print "ERROR!! MIO object name could not be found in ", objName
                #             continue

                #         if mioObjName in mioKeys:
                #             numEntries = self.mioInstances[mioObjName];
                #         else:
                #             print "WARNING! Object ", objName, "not found in mioInstaces"
                #             numEntries = 1

                #         if numEntries == 0:
                #             print "WARNING! Parameter ", paramName, "is not included"
                #             continue
                #         else:
                #             if self.verbose:
                #                 print "DEBUG! Parameter ", paramName, "of ", objName, " has ", numEntries, " instances"
                            

                #         val=param.attributes[u'name'].value
                #         for iter in range(1, int(numEntries)+1):          
                #             newObjName = objName.replace('{i}', str(iter))

                #             #check if operator replaces an object name
                #             fullName = newObjName
                #             if RadisysFields[u'name'] != '':
                #                 fullName += RadisysFields['name'] 
                #             else:
                #                 fullName += param.attributes[u'name'].value  

                #             mibDnStr = mibDn    
                #             if '{i}' in mibDnStr:
                #                 mibDnStr = mibDnStr.replace('{i}', str(iter-1))

                #             #check if the parameter was a list in which case we change its type
                #             isAList = 'false'
                #             if (',' in RadisysFields['value']) :
                #                 isAList = 'true'
    
                #             entryStr = self.__buildString(fullName, accessMode, isAList, notifyMode, 
                #                                           forcedInfMode, RadisysFields, mibDnStr, mibParam)
                            
                #             self.hdr.write(entryStr)                            						
                #     else:
                #         #check if the parameter was a list in which case we change its type
                #         isAList = 'false'
                #         if (',' in RadisysFields['value']) :
                #             isAList = 'true'

                 #        #check if operator replaces an object name
                 #        fullName = objName
                 #        if RadisysFields['name'] != '':
#                            print 'DBG: #1 SINGLE objName ', str(objName), ' RadisysFields[N]', RadisysFields['name'], 'param.val ', param.attributes[u'name'].value
                 #            fullName += RadisysFields['name'] 
                 #        else:
                 #            fullName += param.attributes[u'name'].value

                 #        if '{i}' in mibDn:
                 #            mibDn = mibDn.replace('{i}', str(1))

                 #        entryStr = self.__buildString(fullName, accessMode, isAList, notifyMode, 
                 #                                      forcedInfMode, RadisysFields, mibDn, mibParam)
                        
                 #        self.hdr.write(entryStr)                            
                    
                 #    if self.verbose:
                 #        print "Wrote into header file:", entryStr
                    
        self.hdr.close()    
        
        print "Generation of file", self.hdrFile, "completed!"   
    

    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    def __removeProfileObjs(self):
        i = 0
        for item in self.objectList:
            if item.parentNode.tagName  == 'profile':
                self.objectList.remove(item)
                i += 1
        if self.verbose:
            print " Removed", i," <profile> objects\n"
            #raw_input("first parse of the list...")  


    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    # parse <syntax> node and retreives data type, value and range
    def __dataSyntaxParser(self, syntaxNode):
                     
        for tag in syntaxNode.childNodes:
            #NOTE: it seems necessary to parse the list because there are empty/non syntax syntaxNode.childNodes
            if tag.nodeName.lower() == 'string':            
                self.paramData[0] = 'STRING'
                self.paramData[2:4] = self.__rangeValueParser(tag)
            elif tag.nodeName.lower() == 'unsignedint':
                self.paramData[0] = 'U_INT'
                self.paramData[2:4] = self.__rangeValueParser(tag)
            elif tag.nodeName.lower() == 'boolean':
                self.paramData[0] = 'BOOLEAN'
            elif tag.nodeName.lower() == 'int':
                self.paramData[0] = 'INT'
                self.paramData[2:4] = self.__rangeValueParser(tag)
            elif tag.nodeName.lower() == 'datetime':
                self.paramData[0] = 'DATE_TIME'
            elif tag.nodeName.lower() == 'datatype':
                self.paramData[0] = 'DATA_TYPE'
    
            elif tag.nodeName.lower() == 'default':
                if tag.hasAttributes():
                                              
                   if 'value' in tag.attributes.keys():
                       self.paramData[1] = tag.attributes['value'].value


    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    # parse <syntax> node and retreives data type
    def __rangeValueParser(self, node):
        range=['','']       # min, max
        
        if node.nodeName == 'string':        
            for c in node.childNodes:
                if c.nodeName == 'size':        
                    if 'maxLength' in c.attributes.keys():
                        range[0] = '0'
                        range[1] = c.attributes['maxLength'].value
                        continue
                    
                if c.nodeName == 'enumeration':
                    if 'value' in c.attributes.keys():                    
                        str = c.attributes['value'].value
                        if range[0] == '':
                            range[0] = len(str)
                            range[1] = len(str)
                        elif range[0] > len(str):
                            range[0] = len(str)
                        elif range[1] < len(str):
                            range[1] = len(str)        
                           
        elif node.nodeName == 'unsignedInt' or node.nodeName == 'int':
            for c in node.childNodes:
                if c.nodeName == 'range':        
                    if 'minInclusive' in c.attributes.keys():
                        range[0] = c.attributes['minInclusive'].value
                    if 'maxInclusive' in c.attributes.keys():
                        range[1] = c.attributes['maxInclusive'].value
    
        return range


    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    # parse <RADISYS> node and retreives dictionary
    def __dataRadisysParser(self, rsysNode):
        d = {'supported':'FALSE',       'access':'', 
             'notificationType':'0',    'forcedInform':'',
             'changeApplies':'',
             'integrator':'',           'value':'',
             'mib_dn':'',        
             'mib_id':'PARAM_ID_INVALID',
             'mibGroup':'GROUP_ID_INVALID',
             'name':''
             }
        attrList = []
        rsysChildren = rsysNode.childNodes
    
        for child in rsysChildren:        
            if child.nodeType == child.TEXT_NODE:  #3:                
                continue
    
            if child.hasAttributes():
                attrList = child.attributes.keys()                
    
            if child.nodeName == 'default':
                if 'supported' in attrList:
                    d['supported'] = child.attributes[u'supported'].value
                    if d['supported'] == '':
                        print "WARNING! parameter with attribute \'support\' not specified!"
                        return d
                    if (d['supported'].upper() == 'FALSE'):
                        return d
                                   
                if 'access' in attrList:
                    if child.attributes['access'].value == 'readWrite':
                        d['access'] = 'READ_WRITE' 
    
                #if 'activeNotify' in attrList:                
                #    if child.attributes['activeNotify'].value == 'forceDefault':
                #        d['activeNotify'] = '2'
                if 'notificationType' in attrList:                
                    d['notificationType'] = child.attributes['notificationType'].value
                        
                if 'forcedInform' in attrList:
                    d['forcedInform'] = child.attributes['forcedInform'].value

                if 'changeApplies' in attrList:                
                    d['changeApplies'] = child.attributes['changeApplies'].value
                
                if 'value' in attrList:
                    d['value'] = child.attributes[u'value'].value

            elif child.nodeName == 'MIB_dn':
                if child.firstChild != None:
                    d['mib_dn'] = child.firstChild.data                 
        
            elif child.nodeName == 'MIB_id':
                if child.firstChild != None:
                    d['mib_id'] = child.firstChild.data

            elif child.nodeName == 'mibGroup':
                if child.firstChild != None:
                    d['mibGroup'] = child.firstChild.data       
                    if d['mibGroup'] not in self.mibGroups:
                        self.mibGroups.append(d['mibGroup'])         
                
            # <override>
            elif child.nodeName == 'override':
                if 'integrator' in attrList and child.attributes[u'integrator'].value == self.integrator:                    
                    d['integrator'] = child.attributes[u'integrator'].value
                else:
                    continue
                
                if 'supported' in attrList:
                    d['supported'] = child.attributes[u'supported'].value
                    
                if 'value' in attrList:
                    d['value'] = child.attributes[u'value'].value
                
                if 'suggestedValue' in attrList:
                    d['suggestedValue'] = child.attributes[u'suggestedValue'].value
                    
                if 'notificationType' in attrList:
                    d['notificationType'] = child.attributes[u'notificationType'].value
                
                if 'changeApplies' in attrList:                
                    d['changeApplies'] = child.attributes['changeApplies'].value
                
                if 'name' in attrList:
                    d['name'] = child.attributes[u'name'].value
                
        return d

    
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    def __browseForAttribute(self, name, obj, param, RadisysFields):    
        value = ''
    
        if name in obj.attributes.keys():
            value = obj.attributes[name].value
    
        paramAttr = param.attributes.keys()
        if name in paramAttr:
            value = param.attributes[name].value
            
        if RadisysFields[name] != '':
            value = RadisysFields[name]        
            if self.verbose:   
                print "<RADISYS> overwrites " + name+" field with", value   
    
        return value    


    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    def __buildString(self, fullName, accessMode, isAList, notifyMode, forcedInfMode, changeApply, 
                      RadisysFields, mibDn, mibParam):
        aStr = ''      
        
        aStr = "{\"" + self.prefix + fullName + "\",\n\t"
        aStr += accessMode + ", "        
        aStr += self.paramData[0]
        aStr += ", \""+ str(self.paramData[2]) 
        aStr += "\", \""+ str(self.paramData[3]) +"\""
        aStr += ", " + isAList
        aStr += ", %s" % (notifyMode) +", "+ forcedInfMode.lower()
        aStr += ", %s" % (changeApply)
        aStr += ",\t\""+ RadisysFields['value']+ "\",\t" + RadisysFields['mibGroup']
        aStr += ",\t\""+ mibDn + "\",\t"+ mibParam + " },\n"
        
        return aStr    


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
class Tr069FilesGenerator:
    """Class to generate Tr069DataModel files """
    
    def __init__(self, cppName, vendors, headersList=[]):
        self.cppFile = cppName
        self.vendors = vendors
        self.hList = headersList
        print 'Creation of ', self.cppFile, 'file'
        self.__createFiles()
        
    def __createFiles(self):            
        cpp = open(self.cppFile, "w")
        hdr = open( (self.cppFile.split('.cpp')[0] + '.h'), 'w')    
        cpp.write(AUTOCODE_MSG)
        hdr.write(AUTOCODE_MSG)             
        
        l = self.cppFile.split('/')
        fileName = l[l.__len__()-1]        
        hdr.write("\n#include <MibAttributeId.h>")
        hdr.write("\n#include <DataModelTypes.h> \n\n")
        cpp.write(("\n#include \""+fileName.replace('.cpp', '.h') +"\"\n\n"))
        hdr.write("namespace tr069\n{\n\n")
        cpp.write("namespace tr069\n{\n\n")
        
        for ven in self.vendors:
            hdr.write("extern const ExtDMAttrDefinition "+ven.lower()+"DataModel[];\n")       
            cpp.write("const ExtDMAttrDefinition "+ven.lower()+"DataModel[] = \n{\n")       
            for h in self.hList:
                if ven in h:
                    cpp.write(" #include \""+ h.split('../../fap/management/tr069-v2/autogen/')[1] +"\"\n")
            cpp.write("};\n\n")        

            hdr.write("extern const size_t "+ven.lower()+"DataModelArrayLength;\n")       
            cpp.write("const size_t "+ven.lower()+"DataModelArrayLength = sizeof("+ven.lower()+"DataModel)/sizeof("+ven.lower()+"DataModel[0]);\n\n")       
        
        cpp.write("\n}\n")   
        hdr.write("\n}\n") 
        cpp.close()
        hdr.close()


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
class MibGroupFunctionProto:
    """Class to generate function prototypes for Mib group parameter"""
    
    def __init__(self, name, list):
        self.name = name
        self.list = list
        self.protoNames = []
        print 'Creation of ', self.name, 'file'
        self.__createFile()
        
    def __createFile(self):            
        file = open(self.name, "w")    
        file.write(AUTOCODE_MSG)       
        macro = self.name.replace('.','')
        macro = macro.replace('/','_')
        macro = macro.replace('-','_')
        file.write(("\n#ifndef "+macro+"__\n#define "+macro+"__\n\n"))
        file.write("\n\n#include <MibAttributeId.h>\n")
        file.write("#include <mib-common/MibAttributeValues.h>\n")
        file.write("#include <DataModelTypes.h>\n")
        file.write("#include \"../FuncPtrTypes.h\"\n\n")
        file.write("namespace tr069\n{\n")

        for item in self.list:
            file.write(self.__createPrototype(item) )                        
                            
        file.write("\n}\n\n#endif\n\n")
        file.close()

    def __createPrototype(self, item):
        protoName = "\n\n/*\n * Automatic generated functions to handle parameters of MIB group:"
        name = self.__ConvertNameStile(item)
        protoName += "\n * "+ name +"\n */\n" 
        protoName += "\nValidationFailureDescriptor  Process"+name+"Spv(const Tr069AttributeValues&, MibAttributeValues&);"
        protoName += "\nGPV_RETURN_TYPE  Process"+name+"Gpv( GPV_PARAMETERS );"
        self.protoNames.append(name)
        return protoName
    
    def __ConvertNameStile(self, name):
        """Convert CAP_STYLE into CamelCase"""
        l = name.split('_')
        fname = ''
        for i in l:
            fname += i[0].upper() + i[1:].lower()
        return fname

    def GetProtoNamesList(self):
        return self.protoNames


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
class MibGroupFunctionEnum:
    """Class to generate function prototypes Enumeration for Mib group parameter"""
    
    def __init__(self, fileName, list):
        self.file = fileName
        self.list = list
        print 'Creation of ', self.file, 'file'
        self.__createEnumFile()
        
    def __createEnumFile(self):            
        file = open(self.file, "w")    
        file.write(AUTOCODE_MSG)       
        macro = self.file.replace('.','')
        macro = macro.replace('/','_')
        macro = macro.replace('-','_')
        file.write(("\n#ifndef "+macro+"__\n#define "+macro+"__\n\n"))
        file.write("\n\n#include <system/EnumToString.h>\n\n")
#        fileName = ( MIB_GRP_ENUM_FILE.split('/') ).pop()
#        fileName.strip('.h')
        file.write("namespace tr069\n{\n\n")
        file.write("ENUM_START(ExtDataModelAttrGroupId)\n{\n")

        file.write(("    ENUM_ELEMENT_VAL(GROUP_ID_FIRST,0)\n"))

        for item in self.list:
#            if self.list[0] == item:
#                file.write(("    ENUM_ELEMENT_VAL("+item+",0)\n"))
#            else:
                file.write(("    ENUM_ELEMENT("+item+")\n"))

        file.write(("    ENUM_ELEMENT(NUM_GROUP_IDS)\n"))
        file.write(("    ENUM_ELEMENT(GROUP_ID_INVALID)\n"))

        file.write("}\nENUM_END(ExtDataModelAttrGroupId)\n")                            
        file.write("\n}\n\n#endif\n\n")
        file.close()



# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
if __name__ == "__main__":  
   
    print "* * * Data Model Code Generator * * *"

    # commenting other vendors as not being used.
    #vendors = ['Radisys', 'NSN', 'NEC']
    vendors = ['Radisys']
    HDRList = []
    GroupNameList = []

    MAM = MibAttribManager()


    for v in vendors:
        print "* * * Creating variant: ", v    
        print "* * Processing file: ", TR181_XML_FILE   
    
        hdr181 = TR181_HEADER_FILE.split('.h')[0] + v + '.h'               

        CG181 = CodeGenerator(TR181_XML_FILE, hdr181, '', tr181_MultipleObjCounter, v)      
        CG181.processXMLFile()
        
        HDRList.append(hdr181)
    
        for item in CG181.mibGroups:
            if item not in GroupNameList:
                GroupNameList.append(item)
    
        print "* * Processing file: ", TR196_2_XML_FILE
        hdr196 = TR196_2_HEADER_FILE.split('.h')[0] + v + '.h'
    
        startMsg = AUTOCODE_MSG

        CG196 = CodeGenerator(TR196_2_XML_FILE, hdr196, TR196_PREFIX, tr196_MultipleObjCounter, v, fileStart=startMsg, verbose=False)
        CG196.processXMLFile()    
        
        HDRList.append(hdr196)

        for item in CG196.mibGroups:
            if item not in GroupNameList:
                GroupNameList.append(item)
    
        print "* * Processing file: ", RADISYS_EXT_XML_FILE
        hdrair = RADISYS_HEADER_FILE.split('.h')[0] + v + '.h'
    
        CGRSYS = CodeGenerator(RADISYS_EXT_XML_FILE, hdrair, '', rsys_ext_MultipleObjCounter, v)       
        CGRSYS.processXMLFile()          
        
        HDRList.append(hdrair)
        
        for item in CGRSYS.mibGroups:
            if item not in GroupNameList:
                GroupNameList.append(item)           

        print "* * Processing file: ", TIP_EXT_XML_FILE
        hdrtip = TIP_HEADER_FILE.split('.h')[0] + v + '.h'
    
        CGTIP = CodeGenerator(TIP_EXT_XML_FILE, hdrtip, '', rsys_ext_MultipleObjCounter, v)       
        CGTIP.processXMLFile()          
        
        HDRList.append(hdrtip)
        
        for item in CGTIP.mibGroups:
            if item not in GroupNameList:
                GroupNameList.append(item)           

        print "* * Processing file: ", TR262_XML_FILE   
        hdr262 = TR262_HEADER_FILE.split('.h')[0] + v + '.h'               

        CG262 = CodeGenerator(TR262_XML_FILE, hdr262, TR262_PREFIX, tr262_MultipleObjCounter, v)      
        CG262.processXMLFile()
        
        HDRList.append(hdr262)
    
        for item in CG262.mibGroups:
            if item not in GroupNameList:
                GroupNameList.append(item)
    
        print "* * Processing file: ", TR157_XML_FILE   
        hdr157 = TR157_HEADER_FILE.split('.h')[0] + v + '.h'               

        startMsg = AUTOCODE_MSG

        CG157 = CodeGenerator(TR157_XML_FILE, hdr157, TR157_PREFIX, tr157_MultipleObjCounter, v, fileStart=startMsg)      
        CG157.processXMLFile()
        
        HDRList.append(hdr157)
    
        for item in CG157.mibGroups:
            if item not in GroupNameList:
                GroupNameList.append(item)
        
    print "* * Creating .cpp file and Headers"
    cpp = Tr069FilesGenerator(CPP_FILE, vendors, HDRList)       

    MibGroupFunctionEnum(MIB_GRP_ENUM_HEADER, GroupNameList)
 
    MAM.writeLog()
        
    print "\n* Process Complete! Bye! *"
   
   
