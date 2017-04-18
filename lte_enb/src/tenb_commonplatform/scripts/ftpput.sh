FTP_USER=$2
FTP_PASSWORD=$4
FILE_TRANSFER_METHOD=$6

DestinationPath=${8}
SourceFileName=${9}
RETRY_COUNT=1
MAX_RETRY_COUNT=4
PassKey=/root/.ssh/id_rsa

str=`printf $7 | sed 's/.*\/\///g'`
FTP_SERVER=`printf $str | sed 's/:80.*//g'`

while [ $RETRY_COUNT != $MAX_RETRY_COUNT ]
do

# -n : No auto-login upon initial connection
# -v verbose : verbose option forces ftp to show all responses from the remote
# server, as well as report on data transfer statistics.

if [ $FILE_TRANSFER_METHOD = "FTP" ]
then
   echo "File transfer through FTP"
   /usr/bin/ftp -n -v <<EOF 2> /mnt/tmp/ftp_error.log
   open $FTP_SERVER
   user $FTP_USER $FTP_PASSWORD
   cd $DestinationPath
   put $SourceFileName
   bye
EOF
fi
 
if [ $FILE_TRANSFER_METHOD = "SCP" ]
then
   echo "File transfer through SCP"
   scp -i $PassKey ./$SourceFileName $FTP_USER@$FTP_SERVER:$DestinationPath 2> /mnt/tmp/sftp_error.log
fi 

if [ $FILE_TRANSFER_METHOD = "SFTP" ]
  then
    echo "File transfer through SFTP"
    sftp -oConnectTimeout=20  -b /dev/fd/0 $FTP_SERVER <<EOF 2> /mnt/tmp/ftp_error.log
    cd $DestinationPath
    put $SourceFileName
    bye
EOF
fi

     # Check Log File Exist Before Validation Start
     if [ -f "/mnt/tmp/ftp_error.log" ]
     then
         if [ -s "/mnt/tmp/ftp_error.log" ]
         then
	      echo "FTP Connection Status: Fail"
              RETRY_COUNT=$(($RETRY_COUNT+1))
              echo "Retry FTP Connection:- $RETRY_COUNT"
              if [ $RETRY_COUNT -eq $MAX_RETRY_COUNT ]
              then
                 echo "Maximum Retry count Reached"
              else
                 sleep 150   
              fi
         else
     	      echo "FTP Connection Status: Success"
              RETRY_COUNT=$MAX_RETRY_COUNT   
         fi
     else
        echo "File ftp_error.log doesn't exist" 
           RETRY_COUNT=$MAX_RETRY_COUNT   
     fi
done
