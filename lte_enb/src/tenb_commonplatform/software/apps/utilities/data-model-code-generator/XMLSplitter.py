from xml.dom import minidom
import DataModelCodeGenerator

G_TR196_TR098_XML = "../../fap/management/tr069-v2/autogen/tr196_tr098_generated.xml"
G_Radisys_XML = "../../fap/management/tr069-v2/autogen/Radisys_generated.xml"
G_NSN_XML = "../../fap/management/tr069-v2/autogen/NSN_generated.xml"
G_NEC_XML = "../../fap/management/tr069-v2/autogen/NEC_generated.xml"

FIRST_TAG   = '<dm:document xmlns:dm="urn:broadband-forum-org:cwmp:datamodel-1-0" \n\txmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"\n\txsi:schemaLocation="urn:broadband-forum-org:cwmp:datamodel-1-0 cwmp-datamodel.xsd">\n'
LAST_TAG    = '</dm:document>'

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

class XMLSplitter:
    # Class to generate split SystemTeam XML file into several other XML files
            
    def __init__(self, sourceFile):
        xmldoc = minidom.parse(sourceFile)        
        self.objectList = xmldoc.getElementsByTagName("object")

        print ' length of element list is ' , len(self.objectList) 
        self.__removeObjs(self.objectList, 'profile')
        print ' new length of element list is ' , len(self.objectList) 


    def __removeObjs(self, list, objName):
        for item in list:
        ##            x = item.removeChild( objName )
        ##            print x
            if item.parentNode.tagName  == objName:
               list.remove(item)               
                
                
    def splitFiles(self):
        print '* * Generating these files'
        print ' - ', G_TR196_TR098_XML
        print ' - ', G_Radisys_XML
        print ' - ', G_NSN_XML
        print ' - ', G_NEC_XML
        
        ## TODO: pass this list from input
        #self.outputFile = { 'fTR':G_TR196_TR098_XML, 
        #                    'fAIR':G_Radisys_XML,
        #                    'fNSN':G_NSN_XML, 
        #                    'fNEC':G_NEC_XML }

        #for f in self.outputFile.keys():
        #    print "DBG: opening file for key', f
            
        #    f = open( self.outputFile[f], 'w' )
        #    f.write(FIRST_TAG)
        
        fTR = open(G_TR196_TR098_XML, 'w')
        fAIR = open(G_Radisys_XML, 'w')
        fNSN = open(G_NSN_XML, 'w')
        fNEC = open(G_NEC_XML, 'w')
        
        fTR.write(FIRST_TAG)
        fAIR.write(FIRST_TAG)
        fNSN.write(FIRST_TAG)
        fNEC.write(FIRST_TAG)

        self.workingList = self.objectList
        self.__removeObjs(self.workingList, 'Radisys')
                        
        for o in self.workingList:
            # populate all files
            fTR.write(o.toxml().encode("utf-8") )            
            
            
        # in TR remove AIR, NSN, NEC
        # etc
        fTR.write(LAST_TAG)
        fAIR.write(LAST_TAG)
        fNSN.write(LAST_TAG)
        fNEC.write(LAST_TAG)
        
        fTR.close
        fAIR.close
        fNSN.close
        fNEC.close


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
if __name__ == "__main__":  

    print "* * *  Files Splitter"
    fsp = XMLSplitter(DataModelCodeGenerator.TR196_XML_FILE)
    fsp.splitFiles()
    
    print "\n\n\t\tWARNING: Work in progress: do NOT use this script!\n"
    
    raw_input("DONE - Check splitting output (press enter)")
    
    
