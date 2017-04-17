#!/usr/bin/perl -w
use strict;
my $DATE = `date '+%m-%d-%y'`;
chomp $DATE;
package Createbasedirectory;

##################################################################################
# createdir function is use for copying the files from vobs to local Release dir
##################################################################################

sub createdir(@)
{
	my ( $VIEW_NAME , $LABEL , $CREATE_COMPILE_DIR_PATH , $PRODUCT ) = @_;
	chomp $VIEW_NAME ; chomp $LABEL ; chomp $CREATE_COMPILE_DIR_PATH ; chomp $PRODUCT; 
	print "Changing the CONFIG-SPEC to $LABEL\n";
   	my $srcPath = "/msbublds01/tbuild/Release_Build/".$LABEL."_".$DATE.".txt";
	chomp $srcPath;
   	system ( "rm -f $srcPath" );
   	print "============== SET THE CONFIG-SPEC TO THE GIVEN LABEL 1  =============== \n";
   	open (FH, ">$srcPath") or die "Can not open the file name $!";
   	print FH "element * $LABEL \n";
   	close FH;
   	system ("cleartool setcs -tag $VIEW_NAME $srcPath");
   	print "*********************Config-Spec Details*********************** \n";
   	system ("cleartool catcs -tag $VIEW_NAME");
 	my $Directorypath = "/msbublds01/tbuild/Release_Build/".$LABEL;
	chomp $Directorypath;
	print "getting code base for the label $LABEL\n";
	print "$CREATE_COMPILE_DIR_PATH /view/$VIEW_NAME $Directorypath -c -PKG\n";
	if ($PRODUCT =~ /BRDCM_TDD/){
	system ("$CREATE_COMPILE_DIR_PATH -v /view/$VIEW_NAME -c -m TDD -PKG $Directorypath");
	}
	elsif ($PRODUCT =~ /BRDCM_FDD/){
	system ("$CREATE_COMPILE_DIR_PATH /view/$VIEW_NAME $Directorypath -c FDD -PKG");
	}
	elsif ($PRODUCT =~ /T2200_TDD/) {
	system ("$CREATE_COMPILE_DIR_PATH -v /view/$VIEW_NAME -c -m TDD -PKG $Directorypath");
	} else
	{
		system ("$CREATE_COMPILE_DIR_PATH /view/$VIEW_NAME $Directorypath -c -PKG");
	}
	system ("chmod 777 -R $Directorypath");
}
1;
