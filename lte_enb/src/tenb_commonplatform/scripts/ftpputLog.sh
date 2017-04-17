#PARAMETER Values will be get update from OAM configured parameters      

FTP_SERVER=HERE_VALUE_WILL_GET_UPDATE_FROM_OAM_DONT_DELETE
FTP_USER=HERE_VALUE_WILL_GET_UPDATE_FROM_OAM_DONT_DELETE
FTP_PASSWORD=HERE_VALUE_WILL_GET_UPDATE_FROM_OAM_DONT_DELETE
FILE_TRANSFER_METHOD=HERE_VALUE_WILL_GET_UPDATE_FROM_OAM_DONT_DELETE
DESTINATION_PATH=HERE_VALUE_WILL_GET_UPDATE_FROM_OAM_DONT_DELETE
FTP_TRACE_LOCATION=HERE_VALUE_WILL_GET_UPDATE_FROM_OAM_DONT_DELETE
                       
###################################################################################
#                                                                                    #
#   usage                                                                            #
#		                                                                     #
#   . ./ftpputLog UsrName Pwd FTP_method FTPServer RemoteDir LocalFileName (6 args)  #
#                               ==> Providing all information about trace file and   #
#                                   FTP username location and all necessary info     #
#   . ./ftpputLog traceLocation ==> Argument could be either one directry of file    #
#                                   First it will search for this location in OAM    #
#                                   configured TRACE_LOCATION if it is not there     #
#                                   then it will search from root                    #
#   . ./ftpputLog traceLocation ==> It will upload all trace files from OAM          #
#                                   cofigured Trace Location                         #
######################################################################################


######################################################################################
#                                                                                    #
#     Global variables                                                               #
#                                                                                    #
######################################################################################
RETRY_COUNT=1
INCREMENTER=1
MAX_RETRY_COUNT=2
PassKey=/root/.ssh/id_rsa

DIR=""
#####################################################################################
#                                                                                   #
#    This functon wll receive one file path and return File name from that          #
#####################################################################################
extractFileName()
{
   pathString="$1"
   fileName=${pathString##*/}
   echo "$fileName"
}

#####################################################################################
#                                                                                   #
#    This functon wll receive one file path and return directory path from that     #
#####################################################################################
extractDirName()
{
   pathString="$1"
   fileName=$(extractFileName $1)
   dirName=${pathString%%$fileName}
   echo "$dirName"
}
#####################################################################################
#                                                                                   #
# This function to check whether All parametrs configued or not                     #
#####################################################################################


isConfigurationCompleate()
{
    result=0;
    if [ "$FTP_USER" = "None" ] || [ "$FTP_PASSWORD" = "None" ] ; then
        result=1;
    fi
    if [ "$FILE_TRANSFER_METHOD"  = "None" ] || [ "$DESTINATION_PATH"  = "None" ] ; then
       result=1;
    fi
    if [ "$SOURCE_DIR"  = "None" ] || [ "$FTP_SERVER" = "None" ] ; then 
       result=1;
    fi
   echo $result
}

#######################################################################################
#                                                                                     #
#       Function to upload Log files into remote location                             #
#                                                                                     #
#######################################################################################


uploadTrace()
{
   RETRY_COUNT=0;
   while [ $RETRY_COUNT != $MAX_RETRY_COUNT ]
   do
   rm -rf ftp_error.log

      # -n : No auto-login upon initial connection
      # -v verbose : verbose option forces ftp to show all responses from the remote
      # server, as well as report on data transfer statistics.
      if [ $FILE_TRANSFER_METHOD = "FTP" ]
         then
            echo "File transfer through FTP"
            /usr/bin/ftp -n -v <<EOF 2> ftp_error.log
            open $FTP_SERVER
            user $FTP_USER $FTP_PASSWORD
            cd $DESTINATION_PATH
            put $SOURCE_FILE
            bye
EOF
      fi
      if [ $FILE_TRANSFER_METHOD = "SCP" ]
         then
            echo "File transfer through SCP"
      scp -i /root/.ssh/id_rsa  $SOURCE_FILE $FTP_SERVER:$DESTINATION_PATH 2> ftp_error.log
      fi 

      if [ $FILE_TRANSFER_METHOD = "SFTP" ]
          then
              echo "File transfer through SFTP"
              sftp -oConnectTimeout=20  -b /proc/self/fd/0 $FTP_SERVER <<EOF 2> ftp_error.log
              cd $DESTINATION_PATH
              put $SOURCE_FILE
              bye

EOF
              return
      fi

      # Check Log File Exist Before Validation Start
       if [ -f "ftp_error.log" ]
          then
             if [ -s "ftp_error.log" ]
                then
                   echo "$FILE_TRANSFER_METHOD Connection Status: Fail";
                   RETRY_COUNT=$((RETRY_COUNT + INCREMENTER))
                   echo "Retry FTP Connection:- $RETRY_COUNT"
                   if [ $RETRY_COUNT -eq $MAX_RETRY_COUNT ]
                      then
                         echo "Maximum Retry count Reached"
                      else
                         sleep 150   
                   fi
                   else
                      echo "$FILE_TRANSFER_METHOD Connection Status: Success"
                      RETRY_COUNT=$MAX_RETRY_COUNT   
             fi
              else
                 echo "File ftp_error.log doesn't exist" 
                 RETRY_COUNT=$MAX_RETRY_COUNT   
       fi
done
}

##############################################################################################################
#                                                                                                            #
#      Main function                                                                                         #
##############################################################################################################
   configConmpleate=$(isConfigurationCompleate)
   if [ "$configConmpleate" = "0" ] ; then
if [ $# -ne 6 ] ; then
   
   if [ $# -ne 1 ] && [ $# -ne 0 ]; then 
      return
   fi
   # parameters not provided while involking script 
   # Extracting parameters from local file localFile

   #search keys

   if [ $# -eq 1 ] ; then
       traceLocation=$FTP_TRACE_LOCATION/$1
FTP_TRACE_LOCATION=$traceLocation
   ## first search the given trace location is in configured TRACE_LOC ( configured via OAM)

#       if [ -d $traceLocation ] ; then
#          FTP_TRACE_LOCATION=$traceLocation
#       elif [ -f $traceLocation ] ;  then
#          FTP_TRACE_LOCATION=$traceLocation
## else search the given trace location is  out side of OAM configured trace location
#      elif [ -d $1 ] ; then # if the argument is  a directry we need to pass the entire directry
#           FTP_TRACE_LOCATION=$1
#       elif [ -f $1 ] ; then
#           FTP_TRACE_LOCATION=$1 # if the argument is a file then that file should be in path
#       else
#           FTP_TRACE_LOCATION=$SOURCE_DIR$1 # (SOURCE_DIR) and take that file 
#      fi
   fi
else
#Parameters provided while involking So Reading Arguments
   FTP_USER=$1
   FTP_PASSWORD=$2
   FILE_TRANSFER_METHOD=$3
   DESTINATION_PATH=$5
   FTP_TRACE_LOCATION=$6
   MAX_RETRY_COUNT=4
   PassKey=/root/.ssh/id_rsa
   str=`printf $4 | sed 's/.*\/\///g'`
   FTP_SERVER=`printf $str | sed 's/:80.*//g'`
   SOURCE_FILE=$SOURCE_DIR
fi

         if [ -d $FTP_TRACE_LOCATION ] ; then

            echo "need to parse all files and send"
            allFiles="$FTP_TRACE_LOCATION/*"
            
            cd $FTP_TRACE_LOCATION
            echo "" >ftp_error.log
           idx=0;
            for i in $allFiles
            do
            SOURCE_FILE=$(extractFileName $i)
               echo $SOURCE_FILE
               uploadTrace
            done
            cd -
         else

            dirName=$(extractDirName $FTP_TRACE_LOCATION)
            fileName=$(extractFileName $FTP_TRACE_LOCATION)
            cd $dirName
              echo "" >ftp_error.log
            echo "#$dirName# #$fileName#"

            SOURCE_FILE=$fileName
            uploadTrace
            cd -
            pwd
         fi

   if [ $# -eq 0 ] ; then
      # need to search for core file
      cd /root
      corePath=`find . -name core*`
      if [ -n "$corePath" ] ; then
         echo "core generated #$corePath#"
         dirName=$(extractDirName $corePath)
         fileName=$(extractFileName $corePath)
         cd $dirName
         echo "" >ftp_error.log
         echo "path #$dirName#"

         SOURCE_FILE=$fileName
         uploadTrace
      fi
cd -
   fi

fi
