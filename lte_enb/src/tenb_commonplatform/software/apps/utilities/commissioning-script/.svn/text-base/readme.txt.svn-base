This tool will be used for the short term field implementation by the Field Service team (for T2, TI).

Part of the script relies on being able to access an FTP server. This is for transferring operator certificates.
FileZilla is an example of a free FTP Server that can be downloaded for free and installed on a local machine.

The steps for using the script are.

1) Power up the FAP and wait for it too finish booting
2) telnet to the FAP using your favour telnet terminal program
3) Change directory
	cd /mnt/dbx
4) tftp the file off the FAP so it can be edited
	tftp -p -r commissioningScript <IP ADDRESS>
5) edit the file your PC and tftp it back on
	tftp -g -r commissioningScript <IP ADDRESS>
6) change the permissions of the script so that it can execute
	chmod +x commissioningScript
7) run the sc

8) Change the file permissions so that it is execuctable
9) Run the script
	./commissioningScript
	
10) Reboot or power cycle the fap if the script so that the settings take effect.	
	
Check the output of the script for any error messages.	
	

 