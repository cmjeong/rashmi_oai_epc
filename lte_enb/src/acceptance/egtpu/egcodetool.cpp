
/***********************************************************************

************************************************************************

   Name: eGTP Tool for Code Generation

   Type: C++ Source Code
   
   Desc: Code Generator for application specific IE files

   File: egcodetool.cpp

   Sid:      egcodetool.cpp@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:55 2015

   Prg: an

************************************************************************/

/* Header Include Files */

#include<iostream>
#include<string>
#include<map>
#include<list>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<deque>
#include<iomanip>

using namespace std;
#include "egcodetool.h"

// Global variables
// All Comparisons are done case insensitive 
RuntimeStringCmp ignorecase(RuntimeStringCmp::nocase);

map<string, GmPtr, RuntimeStringCmp> gmList(ignorecase); // This stores all command and lists of IEs in each GTP Message 
IeMap  ieList(ignorecase);
IeMultiMap ieListbyCode(ignorecase);
map<string, listSubIePtr, RuntimeStringCmp> group(ignorecase);
listSubIePtr listPtr;
list<SubIePtr>  grpIeList;
list<SubIePtr>  subGrpIeList;
ostringstream header;
string intfPrefix;


bool nocase_compare(char c1, char c2)
{
   return(toupper(c1) == toupper(c2));
}

bool stringComparei(const string& s1, const string& s2)
{
   if (s1.size() == s2.size() &&
      equal (s1.begin(), s1.end(),
             s2.begin(), nocase_compare))
   {
      return(true);
   }
   else
      return(false);
}


int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      cout << "Usage : egcodetool <prefix>" << '\n';
      cout << "<prefix>  prefix is an interface(s11/s5/s8)" << '\n';
      cout << "Example: egcodetool s11" << '\n';
      exit(-1);
   }
   
   try 
   {
      string a = argv[1];
      intfPrefix = a;
      egParseIEFile();
      egParseGMFile(argv[1]);
      egGenOutputFiles(argv[1]);

   }
   catch (exception& e)
   {
       cerr << "Standard Exception: " << e.what() << " Processing failed" << endl;
       exit(-1);
   }
   catch (...)
   {
       cerr << "Aborting : Processing failed" <<endl;
       exit(-1);
   }
   cout << "processing successful" << endl;
   return(0);
}

void egParseIEFile()
{
   
   string filename;
   filename = "ie_dictionary.txt";

   ifstream ieFile(filename.c_str());
   if (!ieFile)
   {
      cerr << "Can't open IE Dictionary file for reading" << filename << endl;
      throw 0;
   }

   // Start Parsing  
   int lineno = 0;
   while (!ieFile.eof())
   {
   lineno++;
   char str[256];
      
   ieFile.getline(str, 256);
   istringstream line(str);

        // Extract the formatted data into the string a       
        string a;
        line >> a;
   cout << lineno << " " << a << endl;

   if (a.size() == 0)
   {
   // blank line
   }
   else if (a[0] == '#')
   {
   // comment line
   }
   else if (stringComparei(a, "HEADER"))
   {
   // Process header
   // This can be used as a comment 
   }
   else if (stringComparei(a, "TLIV"))
   {
          // Process TLIV
         string type,dataType, funcPtr, code, minLen, maxLen;
         typedef IeMultiMap::value_type value_type;

         line >> type >> code >> dataType >> funcPtr >> minLen >> maxLen;
         IePtr attr = new Ie(type, code, dataType , funcPtr, minLen, maxLen);
         ieList[type] = attr;
         ieListbyCode.insert(value_type(code, attr));

   }
   else if (stringComparei(a, "ENUMERATE"))
   {
   }
   else if (stringComparei(a, "GROUPED"))
   {
       // Process Grouped
   }
   else if (stringComparei(a, "include"))
   {
   }
   else
   {
       cerr << "Processing failed in " << filename << " at line number " << lineno << endl;
       cerr << "Line must be either blank or start with #|VENDOR|HEADER|TLIV|GROUPED" << endl;
            throw 0;
   }
   } // while end
} // end of IE Parse file

void egParseGMFile(const char *prefix)
{
   string filename(prefix);
   filename = "gm_dictionary_" + filename + ".txt";

   ifstream gmFile(filename.c_str());
   if (!gmFile)
   {
      cerr << "can't open GTP Message dictionary file for reading" << filename << endl;
      throw 0;
   }
   int lineno = 0;
   while (!gmFile.eof())
   {
      lineno++;
      char str[256];
      
      gmFile.getline(str, 256);
      istringstream line(str);
      string a;
      line >> a;
      cout << lineno << " " << a << endl;
      if (a.size() == 0)
      {
         // blank line
      }
      else if (a[0] == '#')
      {
         // comment line
      }
      else if (stringComparei(a, "HEADER"))
      {
         // Process header
         // This can be used as a comment
      }
      else if (stringComparei(a, "Message"))
      {
         string   name, code, fncPtr;
         line >> name >> code >> fncPtr;

         GmPtr   msg = new Message(name, code, fncPtr);
         gmList[name] = msg;

      }
      else if (stringComparei(a, "TLIV"))
      {  
         // Process TLIV
         string msgName, ieName, ieType, ieClass, minLen, maxLen , pos , instance, isList;

         line >> msgName >> ieName >> ieType >> ieClass >> instance >> isList >> pos;

         if (gmList.find(msgName) == gmList.end())
         {
             cerr << "Processing failed in " << filename << " at line number " << lineno << endl;
             cerr << "Message" << msgName << "must be defined as a Message" << endl;
             throw 0;
         }
         if (ieList.find(ieName) == ieList.end())
         {
            cerr << "Processing failed in " << filename << " at line number " << lineno << endl;
            cerr << "IE" << ieName << " must be defined as an IE in IE dictionary file" << endl;
            throw 0;
         }
         
         MessageIePtr msgIePtr = new MessageIe(ieName, ieClass, ieType, pos, instance, isList);

         gmList[msgName]->add(msgIePtr);

       }
       else if (stringComparei(a, "GROUPED"))
       {
          string msgName, groupedIe, subGroupedIe, subIe, ieClass, grInst, subGrpInst, instance, isList;
          line >> msgName >> groupedIe >> subGroupedIe >> subIe >> ieClass >> grInst >> subGrpInst >> instance >> isList;

          if (!(msgName.length() && groupedIe.length() && subGroupedIe.length() && subIe.length() && ieClass.length() && grInst.length() && subGrpInst.length() && instance.length() && isList.length() ))
          {
             cerr << "Processing failed in " << filename << " at line number " << lineno << endl;
             cerr << "GROUPED line must contain <msgName> <groupedIe> <subIe> <ieClass> <grInst> <instance>" << endl;
             throw 0;
          } /* end of if statement */

          /* Find if the subIe is present. If not present throw error  */
          if (ieList.find(subIe) == ieList.end())
          {
             cerr << "Processing failed in " << filename << " at line number " << lineno << endl;
             cerr << "subIe " << subIe << " must be defined as an IE" << endl;
             throw 0;
          }
        
          // Check the subgrouped Ie is null or not. If it is a null then it is first level of
          // group or else it is second level of grouped 
          if(stringComparei(subGroupedIe.c_str(), "NULLP"))
          {
              SubIePtr  subIePtr = new SubIe(subIe, msgName, groupedIe, subGroupedIe, ieClass, grInst, subGrpInst, instance, isList); 
              grpIeList.push_back(subIePtr); 
          }
          else
          {
              SubIePtr subIePtr = new SubIe(subIe, msgName, groupedIe, subGroupedIe, ieClass, grInst, subGrpInst, instance, isList);
              subGrpIeList.push_back(subIePtr);
          }
       }
       else if (stringComparei(a, "include"))
       {
           string includePrefix;
           line >> includePrefix; 
           egParseGMFile(includePrefix.c_str());
       }
       else
       {
           cerr << "Processing failed in " << filename << " at line number " << lineno << endl;
      cerr << "Line must be either blank or start with #|HEADER|Message|TLIV|include" << endl;
           throw 0;
       }
   } // while end
} // end of geParseGEFile

//This function generates the code using the prefix sent as input parameter.
void egGenOutputFiles(char *prefix)
{
   //make the prefix as a string 
   string file(prefix);
   //xfile would represent the .x file corresponding to the prefix interface
   string xfile("smeg" + file + ".x");
   //hfile would represent the .h file corresponding to the prefix interface
   string hfile("smeg" + file + ".h");

   // Generate Stack manager files to send IE/GM configuration to eGTP Protocol 
   OutFile cf("smeg" + file + ".c", "Source file for filling LM configuration");
   OutFile hf(hfile, "Header file for defines for LM configuration");
   OutFile xf("smeg" + file + ".x", "typedef file for LM configuration");

   // Add include header files in c file
   cf.add("/* Header Include Files (.h) */");
   cf.add("#include \"envopt.h\"            /* Environment Options */");
   cf.add("#include \"envdep.h\"            /* Environment Dependent */");
   cf.add("#include \"envind.h\"            /* Environment Independent */");
   cf.add("#include \"gen.h\"            /* General */");
   cf.add("#include \"ssi.h\"            /* System Services */");
   cf.add("#include \"cm_tkns.h\"         /* Common Tokens */");
   cf.add("#include \"cm_hash.h\"         /* Common Hash List */");
   cf.add("#include \"cm_mblk.h\"         /* Common memory */");
   cf.add("#include \"cm_llist.h\"           /* Common Link List */");
   cf.add("#include \"cm5.h\"               /* Common Structures */");
   cf.add("#include \"cm_inet.h\"           /* Common IP network */");
   cf.add("#include \"cm_tpt.h\"           /* Common Transport */");
   cf.add("#include \"hit.h\"            /* TUCL layer */");
   cf.add("#include \"egt.h\"            /* EU layer */");
   cf.add("#include \"leg.h\"      /* layer manager */");
   cf.add("#include \"eg_util.h\"      /* UTIL */");
   cf.add("#include \"eg_edm.h\"      /* EDM MODULE */");
   cf.add("#include \"" + hfile + "\"");
   cf.bl();
   cf.add("/* Header Include Files (.x) */");
   cf.bl();
   cf.add("#include \"gen.x\"            /* General */");
   cf.add("#include \"ssi.x\"            /* System Services */");
   cf.add("#include \"cm_tkns.x\"         /* Common Tokens */");
   cf.add("#include \"cm_hash.x\"         /* Common Hash List */");
   cf.add("#include \"cm_mblk.x\"         /* Common memory */");
   cf.add("#include \"cm_llist.x\"           /* Common Link List */");
   cf.add("#include \"cm5.x\"               /* Common Structures */");
   cf.add("#include \"cm_inet.x\"           /* Common IP network */");
   cf.add("#include \"cm_tpt.x\"           /* Common Transport */");
   cf.add("#include \"hit.x\"            /* TUCL layer */");
   cf.add("#include \"egt.x\"            /* EU layer */");
   cf.add("#include \"leg.x\"      /* layer manager */");
   cf.add("#include \"eg_util.x\"      /* UTIL */");
   cf.add("#include \"smeg_apputl.x\"      /* Application MODULE */");
   cf.add("#include \"" + xfile + "\"");
   cf.bl(2);

   // Prepare Attribute related defines in h file
   hf.add("/*  Interface IE Codes */");
   hf.bl(1);
   // Add function header for AVP dictionary function
   cf.addFuncHeader((string)"egMakeIeDict",
                   "This function populates the IEs in IE Dictionary",
               (string)"EG_ROK/EG_RFAILED");
   cf.add("#ifdef ANSI");
   cf.add("PUBLIC S16 egMakeIeDict");
   cf.add("(");
   cf.add("LegIeEntry *legIeEntry,");
   cf.add("U8      *nmbIe,");
   cf.add("U16      *posIdx");
   cf.add(")");
   cf.add("#else");
   cf.add("PUBLIC S16 egMakeIeDict(legIeEntry,nmbIe, posIdx)");
   cf.add("LegIeEntry *legIeEntry;");
   cf.add("U8      *nmbIe;");
   cf.add("U16      *posIdx;");
   cf.add("#endif");
   cf.add("{");
   cf.add("   U8  ieCount;                  /* Number of IEs inserted */");
   cf.add("   U8  prevIndex;                            /* Previous Index  */");
   cf.bl();
   cf.add("   ieCount = 0;");
   cf.add("   prevIndex = 0;");
   cf.bl();

   // Loop through all ies and insert hash defines
   // Prepare hash define from IE name by converting all letters to uppercase 

   multimap<string, IePtr, RuntimeStringCmp>::iterator pos;
   for(pos = ieListbyCode.begin(); pos != ieListbyCode.end(); ++pos)
   {
       string ieCode = pos->first;
      
       IePtr iePtr = pos->second;
       string attrName = iePtr->name();
       // Add hash defines in header file for each attribute   
       ostringstream def;
       def.setf(ios_base::left, ios_base::adjustfield);
       def << "#define " << setw(60) << iePtr->name() << " " << setw(10) << iePtr->code();
       hf.add(def);

       cf.add("   /* Populating " + iePtr->name() + " */");
       cf.add("   egMakeIeEntry(&legIeEntry[ieCount], "); 
       cf.add("                    " + iePtr->name() + ",");
       cf.add("                    TRUE ," + iePtr->dataType() + " ,(" + iePtr->funcPtr() + ") " + "," + iePtr->getMinLen() + "," + iePtr->getMaxLen() + ");");
     
       cf.add("   posIdx[" + iePtr->name() + "] = ieCount+1; "); 
       cf.add("   ieCount++;"); 
       cf.bl(1);
   }

   hf.bl(2);
   cf.add("   /* Return the number of IEs inserted  */");
   cf.add("   *nmbIe = ieCount;");
   cf.add("   RETVALUE(ROK);");
   cf.add("}  /* End of egMakeIeDeict() */");
   cf.bl(2);

   hf.add("/* Message Codes   */");
   hf.bl(1);
   map<string, GmPtr, RuntimeStringCmp>::iterator msgPos;
   // Loop through all messages and insert hash defines
   for(msgPos = gmList.begin(); msgPos != gmList.end(); ++msgPos)
   {
       string msgName = msgPos->first;
       GmPtr msgPtr = msgPos->second;
       ostringstream def;

       def.setf(ios_base::left, ios_base::adjustfield);
       def << "#define " << setw(30) << msgPtr->name() << " " << setw(10) << msgPtr->code();
       hf.add(def);
       cf.bl(2);
       cf.addFuncHeader("egMake" + intfPrefix + msgName + "GmEntry",
                                "This function makes the GM Entry for " + msgName, string("None"));
       cf.bl(2);
       cf.add("#ifdef ANSI");
       cf.add("PRIVATE void egMake" + intfPrefix + msgName + "GmEntry");
       cf.add("(");
       cf.add("LegMsgEntry               *gm" + msgName + "Cb                         /* GM Control Block */");
       cf.add(")");
       cf.add("#else");
       cf.add("PRIVATE void egMake" + intfPrefix + msgName + "GmEntry(gm" + msgName + "Cb)");
       cf.add("LegMsgEntry               *gm" + msgName + "Cb;");
       cf.add("#endif");
       cf.add("{");
       cf.add("   U8 ieCnt = 0;");
       cf.add("   U8 grpCnt = 0;");
       cf.add("   U8 grpCnt1 = 0;");
       cf.add("   U8 ret = RFAILED;");
		 cf.add("   LegIeProperties **ieProperties;");
       cf.add("   TRC2(egMake" + intfPrefix + msgName + "GmEntry);");
       cf.bl();
       cf.add("   /* Populate the " + msgName + " GM Entry */");
       cf.add("   gm" + msgName + "Cb->msgType = " + msgPtr->name() + ";");

       string nmbIe("EG_" + intfPrefix + "_" + msgName + "_NMB_IES");
       for_each(nmbIe.begin(), nmbIe.end(), hdefine);

       cf.add("   gm" + msgName + "Cb->nmbIeProp = " + nmbIe + ";");
		 cf.add("   gm" + msgName + "Cb->validateIe = (EscFun)NULLP;");

       ostringstream nmbdef;
       nmbdef.setf(ios_base::left, ios_base::adjustfield);
       nmbdef << "#define " << setw(30) << nmbIe << " " << setw(10) << msgPtr->numIe();
       hf.add(nmbdef);
       cf.bl();
       cf.add("   /* Populate " + msgName + " IE Properties */");
       cf.bl();
       
       int i = 0;
       while(msgPtr->numIe() > i)
       {
          MessageIePtr msgIePtr = msgPtr->ie(i);
          cf.add("   /* Populate " + msgIePtr->getName() + " IE Properties */");
          string ieClass = msgIePtr->getIeClass();
          string inst = msgIePtr->getInstance();
          string isList = msgIePtr->getIsList();
          string pos, posval;
          if (stringComparei(ieClass, "AQ_AVP_FIXED"))
          {
          }
          else
          {
            pos = "FALSE";
            posval = "0";
          }
          cf.add("   egMakeAppIeProp(&gm" + msgName + "Cb->ieProperties[ieCnt],");
          cf.add("                    " + ((ieList.find(msgIePtr->getName())->second))->name() + "," + ieClass + "," +
                             inst + "," + isList + ");");
          cf.bl(1);      
          cf.add("   gm" + msgName + "Cb->posIndex[" + inst + "][" + ((ieList.find(msgIePtr->getName())->second))->name() + "]  = " + "ieCnt + 1;"); 

          i++;
          bool flag = true;
          int  cnt = 0;
          if(stringComparei(((ieList.find(msgIePtr->getName())->second))->dataType(),"EG_GROUPED"))
          {
             cf.bl(1);
             cf.add("   grpCnt = 0;");
             cf.add("   ret = SGetSBuf(DFLT_REGION,DFLT_POOL,(Data **)&(gm" + msgName +"Cb->ieProperties[ieCnt].groupedIe) ,sizeof(LegGroupedIe));");
				 cf.add("   if( ret == ROK && (gm"+msgName+"Cb->ieProperties[ieCnt].groupedIe) != NULLP)");
				 cf.add("   {");
             cf.bl(1);

			   
             list<SubIePtr> ::iterator grpPos;
             // Loop through all grouped 
             for(grpPos = grpIeList.begin(); grpPos != grpIeList.end(); ++grpPos)
             {
                if( stringComparei((*grpPos)->getMsgName(),msgName ) 
                   && stringComparei(  (*grpPos)->getGroupedIe(),(msgIePtr->getName())) 
                   && stringComparei(  (*grpPos)->getGrInst(), inst))
                {
                  cnt++;
                }
             } /* end of for */
             cf.add("      ieProperties = &gm"+msgName+"Cb->ieProperties[ieCnt].groupedIe->ieProperties;");
				 cf.add("      ret = SGetSBuf(DFLT_REGION,DFLT_POOL ,(Data **)(ieProperties),(sizeof(LegIeProperties)*(EG_"+ msgName + "_" + (msgIePtr->getName())  + inst + "_GRP_NMB_IES )));");
				 cf.add("      if( ret == ROK && ieProperties != NULLP)"); 
				 cf.add("      {");
             cf.bl(1);

             // Loop through all grouped 
             for(grpPos = grpIeList.begin(); grpPos != grpIeList.end(); ++grpPos)
             {

                if( stringComparei((*grpPos)->getMsgName(),msgName ) 
                   && stringComparei(  (*grpPos)->getGroupedIe(),(msgIePtr->getName()) ) 
                   && stringComparei(  (*grpPos)->getGrInst(), inst))
                {
                   
              			cf.add("   egMakeAppChildIeEntry(&(gm" + msgName + "Cb->ieProperties[ieCnt].groupedIe), grpCnt++, " + 
									 ((ieList.find((*grpPos)->getSubIe()))->second)->name() + "," + 
									 (*grpPos)->getIeClass() + "," + (*grpPos)->getInstance() + "," 
									 + (*grpPos)->getIsList() + ",");
              			if(flag)
                   	{
            				cf.add("EG_" + msgName + "_" + (*grpPos)->getGroupedIe()+ inst + 
													 "_GRP_NMB_IES" + ");");
                     	cf.bl(1);
            				flag = false;
                      	ostringstream def;
                      	def.setf(ios_base::left, ios_base::adjustfield);
                      	def << "#define " <<  "EG_"  << msgName << "_" << (*grpPos)->getGroupedIe() 
										  << inst << "_GRP_NMB_IES" << " " << setw(10) << cnt;
                      	hf.add(def);

              			}
              			else
         				{
            				cf.add( "0 );");
                      	cf.bl(1);
              			}

		    				// Second level of grouped IE 
			 				string temp = ((ieList.find(((*grpPos)->getSubIe()))->second))->dataType();

          				bool subFlag = true;
          				int  cnt1 = 0;
							cout << " Grp SubIe " << (*grpPos)->getSubIe().c_str() << "\n" << "\n" ;
						
          				if(stringComparei(((ieList.find((*grpPos)->getSubIe())->second))->dataType(),
															"EG_GROUPED"))
          				{
							  cf.bl(1);
							  cf.add("      grpCnt1 = 0;");

							  cf.add("      ret = SGetSBuf(DFLT_REGION,DFLT_POOL,(Data **)&(gm" + msgName +\
							                           "Cb->ieProperties[ieCnt].groupedIe->ieProperties[grpCnt].groupedId) ,sizeof(LegGroupedIe));");
							  cf.add("      if( ret == ROK && (gm"+msgName+"Cb->ieProperties[ieCnt].groupedIea->ieProperties[grpCnt].groupedId)" +\
							  																																				"!= NULLP)");
							  cf.add("      {");
							  cf.bl(1);

							  cf.add("         ieProperties = &gm"+msgName+"Cb->ieProperties[ieCnt].groupedIea->ieProperties[grpCnt].groupedId;");
							  cf.add("         ret = SGetSBuf(DFLT_REGION,DFLT_POOL ,(Data **)(ieProperties),(sizeof(LegIeProperties)*(EG_" + msgName +\
							                      "_" + (*grpPos)->getSubIe() + (*grpPos)->getInstance() + (*grpPos)->getGrInst() + "_GRP_NMB_IES" + ")));");
							  cf.add("         if( ret == ROK && ieProperties != NULLP)");
							  cf.add("         {");
             				cf.bl(1);
             				// Loop through all Sub-grouped 
             			   list<SubIePtr> ::iterator subGrpPos;
             				for(subGrpPos = subGrpIeList.begin(); subGrpPos != subGrpIeList.end(); ++subGrpPos)
             				{
							   	//string temp = (*subGrpPos)->getMsgName();
									//cout << " Msg Name " << ((*subGrpPos)->getMsgName()).c_str()<< "   " << (*grpPos)->getMsgName() << "\n";
									//cout << " Group IE " << ((*subGrpPos)->getGroupedIe()).c_str()<< "   " << (*grpPos)->getSubIe() << "\n";
									//cout << " Sub group IE " << ((*subGrpPos)->getSubGroupedIe()).c_str()<< "   " << (*grpPos)->getGroupedIe() << "\n";
									//cout << " Sub group Inst " << ((*subGrpPos)->getSubGrInst()).c_str()<< "   " << (*grpPos)->getGrInst() << "\n";
									//cout << " group Inst " << ((*subGrpPos)->getGrInst()).c_str()<< "   " << (*grpPos)->getInstance() << "\n" << "\n" ;
                				if( stringComparei((*subGrpPos)->getMsgName(), (*grpPos)->getMsgName()) 
                   		   	&& stringComparei((*subGrpPos)->getGroupedIe(), (*grpPos)->getSubIe()) 
                   				&& stringComparei((*subGrpPos)->getSubGroupedIe(), (*grpPos)->getGroupedIe()) 
                   				&& stringComparei((*subGrpPos)->getSubGrInst(), (*grpPos)->getGrInst())
                   				&& stringComparei((*subGrpPos)->getGrInst(), (*grpPos)->getInstance()) )
                				{
                  				cnt1++;
                				}
             				}

								cout << " cnt1 " << cnt1 << "\n" << "\n" ;
             				// Loop through all Sub-grouped 
             				for(subGrpPos = subGrpIeList.begin(); subGrpPos != subGrpIeList.end(); ++subGrpPos)
             				{
                				if( stringComparei((*subGrpPos)->getMsgName(), (*grpPos)->getMsgName()) 
                   			&& stringComparei((*subGrpPos)->getGroupedIe(), (*grpPos)->getSubIe()) 
                   			&& stringComparei((*subGrpPos)->getSubGroupedIe(), (*grpPos)->getGroupedIe()) 
                   			&& stringComparei((*subGrpPos)->getSubGrInst(), (*grpPos)->getGrInst())
                   			&& stringComparei((*subGrpPos)->getGrInst(), (*grpPos)->getInstance()) )
                				{
              						cf.add("   egMakeAppChildIeEntry(&(gm" + msgName + 
												 "Cb->ieProperties[ieCnt].groupedIe->ieProperties[grpCnt].groupedIe), grpCnt1++, " 
               					       + ((ieList.find((*subGrpPos)->getSubIe()))->second)->name() + "," 
												 + (*subGrpPos)->getIeClass() + "," + (*subGrpPos)->getInstance() + ","  
												 + (*subGrpPos)->getIsList() + "," );
              						if(subFlag)
                   				{
            							cf.add("EG_" + msgName + "_" + (*subGrpPos)->getGroupedIe()+ 
													 (*subGrpPos)->getGrInst() + (*subGrpPos)->getSubGrInst() + 
													 		"_GRP_NMB_IES" + ");");
                      				cf.bl(1);
            							subFlag = false;
                      				ostringstream def;
                      				def.setf(ios_base::left, ios_base::adjustfield);
                      				def << "#define " <<  "EG_"  << msgName << "_" << (*grpPos)->getGroupedIe() 
													  << (*subGrpPos)->getGrInst() <<  (*subGrpPos)->getSubGrInst() 
													  <<"_GRP_NMB_IES" << " " << setw(10) << cnt1;
                      				hf.add(def);

              						}
              						else
         							{
            							cf.add( "0 );");
                      				cf.bl(1);
              						}
									} // seond level if comparision end 
			     				} // Sub Gropu For loop end 
				            cf.add("      }");
				            cf.add("   }");
							} //second level if end  till
                	} /* end of the finding of the entry */
             } /* end of for loop */
				 cf.add("}");
             cf.bl(1);      
				 cf.add("}");
          } /* end of if grouped */

          if (msgPtr->numIe() > i)
          {
             cf.add("   ieCnt++;");
          }
          cf.bl();
         }
         cf.add("} /* End of egMake" + intfPrefix + msgName + "GmEntry */");
   }
   
   // Make GM dictionary function
   cf.addFuncHeader("egMake" + intfPrefix + "GmDict",
                   string("This functions populates eGTP Messages in GM Dictionary"),
               string("EG_ROK"));
   cf.add("#ifdef ANSI");
   cf.add("PUBLIC S16 egMake" + intfPrefix + "GmDict");
   cf.add("(");
   cf.add("LegMsgEntry *gmEntry,");
   cf.add("U8        *nmbGmMsgs");
   cf.add(")");
   cf.add("#else");
   cf.add("PUBLIC S16 egMake" + intfPrefix + "GmDict(gmEntry,nmbGmMsgs)");
   cf.add("LegMsgEntry *gmEntry;");
   cf.add("U8        *nmbGmMsgs;");
   cf.add("#endif");
   cf.add("{");
   cf.add("   U8  gmMsgCount;                  /* Number of eGTP Messages inserted */");
   cf.add("   gmMsgCount = 0;");
   cf.bl();
   cf.add("   TRC2(egMake" + intfPrefix + "GmDict);");

   for (msgPos = gmList.begin(); msgPos != gmList.end(); ++msgPos)
   {
           string msgName = msgPos->first;
           cf.bl();
           cf.add("   /* Populating " + msgName + " GM Entry */");
           cf.add("   egMake" + intfPrefix + msgName + "GmEntry(&gmEntry[gmMsgCount]);");
           cf.add("   gmMsgCount++;");
   }

   cf.add("   *nmbGmMsgs = gmMsgCount;");
   cf.add("   RETVALUE(ROK);");
   cf.add("} /* End of geMake" + intfPrefix + "GmDict */");
   cf.bl(2);
   hf.bl(2);

   // Prepare .x file
   xf.bl(2);
   xf.add("EXTERN S16 egMakeIeDict ARGS((LegIeEntry *ieEntry, U8 *nmbIe, U16 *posIdx));");
   xf.add("EXTERN S16 egMake" + intfPrefix + "GmDict  ARGS((LegMsgEntry *gmEntry, U8 *nmbGmMsgs));");
   xf.bl(2);

   // Generate Sample Application files for sending & processing eGTP Messages and IEs

   OutFile abc("euacc" + file + ".c", "Sample source file for Generating & processing Commands");
   OutFile abx("euacc" + file + ".x", "Sample typedef file for Generating & processing Commands");
}

void OutFile::addHeader()
{
   // Put standard header by parsing this source file
   string name("egcodetool.cpp");
   

   ifstream thisFile(name.c_str());
   if (!thisFile)
   {
      cerr << "can't open  file for reading" << name << endl;
      throw 0;
   }
   
   while (!thisFile.eof())
   {
      char str[256];
      
      thisFile.getline(str,256);
      add(str);
           string line(str);
      if (line.find("**17*") != string::npos)
      {
         break;
      }
   }
   // Prepare to add file header
   bl(2);
   bsc();
   bl();
   add("    Name: " + desc);
   bl();
   add("    Type: C Source");
   bl();
   ostringstream descr;
   descr << "    Desc: " << header.str();
   add(descr);
   bl();
   add("    File: " + filename);
   bl();
   add("    Sid:      egcodetool.cpp@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:55 2015
   bl();
   add("    Prg: an");
   bl();
   bec();
   bl(2);
}

void OutFile::addFooter()
{
// Put standard footer by parsing this source file
   string name("egcodetool.cpp");
   
   ifstream thisFile(name.c_str());
   if (!thisFile)
   {
      cerr << "can't open  file for reading" << name << endl;
      throw 0;
   }
   int write = 0, end = 0;
   char eof[256] = "End ";

   strcat(eof, "of ");
   strcat(eof, "file:\0");

   string eofstr(eof);

   while (!thisFile.eof())
   {
      char str[256];

      thisFile.getline(str,256);
      string line(str);
      if (line.find(eof) != string::npos)
      {
         end++;
         if (end == 3)
         {
            string f("         " + eofstr + " " + filename);
            add(f);
            continue;
         }
      }  
      if (line.find("**30*") != string::npos)
      {
         write++;
      }
      if (write==2)
         add(str);
   }
}

void OutFile::addFuncHeader(string funcName, string descp, string ret)
{
   bsc();
   bl();
   add("   Func  : " + funcName);
   bl();
   add("   Desc  : " + descp);
   bl();
   add("   Ret   : " + ret);
   bl();
   add("   File  : " + filename);
   bl();
   bec();
   bl(2);
}

Ie::Ie(string& type, string& code, string& dataType, string& funcPtr, string& _minLen, string& _maxLen)
{
    ieType = type;
    ieCode = code;
    ieDataType = dataType;
    if (stringComparei(ieDataType, "FTEID"))
    {
      ieDataType = "EG_FTEID";
    }
    else if (stringComparei(ieDataType , "GROUPED"))
    {
      ieDataType = "EG_GROUPED";
    }
    else if (stringComparei(ieDataType, "UNSIGNED8"))
    {
      ieDataType = "EG_UNSIGNED_8";
    }
    else if (stringComparei(ieDataType, "UNSIGNED16"))
    {
      ieDataType = "EG_UNSIGNED_16";
    }
    else if (stringComparei(ieDataType, "UNSIGNED32"))
    {
      ieDataType = "EG_UNSIGNED_32";
    }
    else if (stringComparei(ieDataType, "STRING8"))
    {
      ieDataType = "EG_STRING_8";
    }
    else if (stringComparei(ieDataType, "STRING4"))
    {
      ieDataType = "EG_STRING_4";
    }
    else if (stringComparei(ieDataType, "STRING16"))
    {
      ieDataType = "EG_STRING_16";
    }
    else if (stringComparei(ieDataType, "STRING32"))
    {
      ieDataType = "EG_STRING_32";
    }
    else if (stringComparei(ieDataType, "STRING132"))
    {
      ieDataType = "EG_STRING_132";
    }
    else if (stringComparei(ieDataType, "STRING"))
    {
      ieDataType = "EG_STRING_MAX";
    }
    else if (stringComparei(ieDataType, "INDICATION"))
    {
      ieDataType = "EG_INDICATION";
    }
    else if (stringComparei(ieDataType, "PAA"))
    {
      ieDataType = "EG_PAA_IEDATA";
    }
    else if (stringComparei(ieDataType, "BEAR_QOS"))
    {
      ieDataType = "EG_BQOS_IEDATA";
    }
    else if (stringComparei(ieDataType, "FQOS"))
    {
      ieDataType = "EG_FQOS";
    }
    else if (stringComparei(ieDataType, "SERVING_NWK"))
    {
      ieDataType = "EG_SNETWORK";
    }
    else if (stringComparei(ieDataType, "ULI"))
    {
      ieDataType = "EG_ULI_DATA";
    }
    else if (stringComparei(ieDataType, "TRACE_INFO"))
    {
      ieDataType = "EG_TRC_INFO";
    }
    else if (stringComparei(ieDataType, "FTEID"))
    {
      ieDataType = "EG_FTEID";
    }
    else if (stringComparei(ieDataType, "BEAR_ID_LIST"))
    {
      ieDataType = "EG_BID_LST";
    }
    else if (stringComparei(ieDataType, "BEAR_FLAGS"))
    {
      ieDataType = "EG_BEARER_FLAG";
    }
    else if (stringComparei(ieDataType, "CAUSE"))
    {
      ieDataType = "EG_CAUSE";
    }
    else if (stringComparei(ieDataType, "PRIVATE_EXT"))
    {
      ieDataType = "EG_PVT_EXTN";
    }
    else if (stringComparei(ieDataType, "IP_ADDR"))
    {
      ieDataType = "EG_IP_ADDR";
    }
    else if (stringComparei(ieDataType, "GLOBAL_CN_ID"))
    {
      ieDataType = "EG_GBL_CN_ID";
    }
    else if (stringComparei(ieDataType, "S103PDNFWINFO"))
    {
      ieDataType = "EG_S103_PDN_FW_INFO";
    }
    else if (stringComparei(ieDataType, "S1UDATAFW"))
    {
      ieDataType = "EG_S1U_DATA_FW";
    }
    else if (stringComparei(ieDataType, "PDUNUM"))
    {
      ieDataType = "EG_PDUNUM";
    }
    else if (stringComparei(ieDataType, "GSMKEYTRIP"))
    {
      ieDataType = "EG_GSM_KEY_TRIP";
    }
    else if (stringComparei(ieDataType, "UMTSKEYCIPHQUIN"))
    {
      ieDataType = "EG_UMTS_KEY_CIPH_QUIN";
    }
    else if (stringComparei(ieDataType, "GSMKEYCIPHQUIN"))
    {
      ieDataType = "EG_GSM_KEY_CIPH_QUIN";
    }
    else if (stringComparei(ieDataType, "UMTSKEYQUIN"))
    {
      ieDataType = "EG_UMTS_KEY_QUIN";
    }
    else if (stringComparei(ieDataType, "EPSSECQUADQUIN"))
    {
      ieDataType = "EG_EPS_SEC_QUAD_QUIN";
    }
    else if (stringComparei(ieDataType, "UMTSKEYQUADQUIN"))
    {
      ieDataType = "EG_UMTS_KEY_QUAD_QUIN";
    }
    else if (stringComparei(ieDataType, "AUTH_QUIN"))
    {
      ieDataType = "EG_AUTH_QUIN";
    }
    else if (stringComparei(ieDataType, "AUTH_QUAD"))
    {
      ieDataType = "EG_AUTH_QUAD";
    }
    else if (stringComparei(ieDataType, "GUTI"))
    {
      ieDataType = "EG_GUTI";
    }
    else if (stringComparei(ieDataType, "CMP_REQ"))
    {
      ieDataType = "EG_CMP_REQ";
    }
    else if (stringComparei(ieDataType, "F_CONT"))
    {
      ieDataType = "EG_F_CONT";
    }
    else if (stringComparei(ieDataType, "F_CAUSE"))
    {
      ieDataType = "EG_F_CAUSE";
    }
    else if (stringComparei(ieDataType, "TRGTID"))
    {
      ieDataType = "EG_TRGTID";
    }
    else if (stringComparei(ieDataType, "CELLID"))
    {
      ieDataType = "EG_CELLID";
    }
    else if (stringComparei(ieDataType, "PKTFLOWID"))
    {
      ieDataType = "EG_PKTFLOWID";
    }
    else if (stringComparei(ieDataType, "PDN_CONN_SET_ID"))
    {
      ieDataType = "EG_PDN_CONN_SET_ID";
    }
    // Added New Ie data types 
    else if (stringComparei(ieDataType, "TIME_ZONE"))
    {
      ieDataType = "EG_TIME_ZONE";
    }
    else if (stringComparei(ieDataType, "TRACE_REF"))
    {
      ieDataType = "EG_TRC_REF";
    }
    else if (stringComparei(ieDataType, "RAB_CONTEXT"))
    {
      ieDataType = "EG_RAB_CONTEXT";
    }
    else if (stringComparei(ieDataType, "MBMS_SESS_DURATION"))
    {
      ieDataType = "EG_MBMS_SESS_DURATION";
    }
    else if (stringComparei(ieDataType, "MBMS_IP_MULT_DIST"))
    {
      ieDataType = "EG_MBMS_IP_MULT_DIST";
    }
    else if (stringComparei(ieDataType, "MBMS_IP_MULT_DIST"))
    {
      ieDataType = "EG_MBMS_IP_MULT_DIST";
    }
    else if (stringComparei(ieDataType, "UCI"))
    {
      ieDataType = "EG_UCI";
    }
    else if (stringComparei(ieDataType, "SRC_ID"))
    {
      ieDataType = "EG_SRC_ID";
    }
    else if (stringComparei(ieDataType, "AMBR"))
    {
      ieDataType = "EG_AMBR";
    }
    else if (stringComparei(ieDataType, "CSGINFOREPACT"))
    {
      ieDataType = "EG_CSG_INFO_REP_ACT";
    }
    else
    {
      cerr << "Invalid IEDataType in " << type << endl;
      throw 0;
    }

    ieFuncPtr  = funcPtr;
    minLen = _minLen;
    maxLen = _maxLen;
    defName = "EG_" + type + "_IETYPE";
}

Message::Message(string& _name, string& _msgCode, string& _fncPtr)
{
   ieList.empty();

   defName = "EG_" + intfPrefix + '_' + _name + "_CMD_CODE";
   for_each(defName.begin(), defName.end(), hdefine);

   msgCode = _msgCode;

} // end of message constructor

void Ie::addVal(EnumElem& enumElem)
{
   enumQ.push_back(enumElem);
}

MessageIe::MessageIe(string& _name, string& _class, string& _type, string& _pos, string& _instance, string& _isList)
{
   name = _name;
   ieClass = _class;
   if (stringComparei(ieClass, "M"))
   {
      ieClass = "EG_IE_MANDATORY";
   }
   else if (stringComparei(ieClass, "O"))
   {
      ieClass = "EG_IE_OPTIONAL";
   }
   else if (stringComparei(ieClass, "C"))
   {
      ieClass = "EG_IE_CONDITIONAL";
   }
   // Added one more Ie class as per new spec 8.6.0
   else if (stringComparei(ieClass, "CO"))
   {
      ieClass = "EG_IE_CONDITIONAL_OPTIONAL";
   }
   else
   {
      cerr << "Invalid IEClass in " << name << endl;
      throw 0;
   }

   ieType = _type;
   pos    = _pos;
   instance = _instance;
	isList = _isList;

} // end of constructor

SubIe::SubIe(string& _subIe, string& _msgName, string& _groupedIe, string& _subGroupedIe, string& _ieClass, string& _grInst, string& _subGrpInst, string& _instance, string& _isList)
{
   subIe          = _subIe;
   msgName        = _msgName;
   groupedIe      = _groupedIe;
   subGroupedIe   = _subGroupedIe;

   ieClass     = _ieClass;
   if (stringComparei(ieClass, "M"))
   {
      ieClass = "EG_IE_MANDATORY";
   }
   else if (stringComparei(ieClass, "O"))
   {
      ieClass = "EG_IE_OPTIONAL";
   }
   else if (stringComparei(ieClass, "C"))
   {
      ieClass = "EG_IE_CONDITIONAL";
   }
   // Added one more Ie class as per new spec 8.6.0
   else if (stringComparei(ieClass, "CO"))
   {
      ieClass = "EG_IE_CONDITIONAL_OPTIONAL";
   }
   else
   {
      cerr << "Invalid IEClass in " << msgName << endl;
      throw 0;
   }

   grInst      = _grInst;
   subGrpInst = _subGrpInst;
   instance    = _instance;
	isList = _isList;

} // end of constructor

/********************************************************************30**

         End of file:     egcodetool.cpp@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:55 2015

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      an                1. Initial Release
/main/2      ---      kchitanya         1. initial for egtp release 1.2
/main/3      ---      pmacharla         Initial for eGTP release 2.1
*********************************************************************91*/
