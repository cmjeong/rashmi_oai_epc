#!/usr/bin/perl
use strict;

#====================================================
#List of modules which are used in this script
#===================================================
use lib '/opt/script/ReleaseScript/';
use File::Spec;
use File::Path;
use File::Copy::Recursive qw(fcopy rcopy dircopy fmove rmove dirmove);
use File::Copy;
use Createbasedirectory; 
my $VIEW_NAME;

#====================================================
# get all the value from buildENV
#===================================================
my $DEV_BRANCH = $ENV{'DEV_BRANCH'};
my $NEXT_LABEL = $ENV{'NEXT_LABEL'};
my $INCGENS = $ENV{'INCGENS'};
my $CREATE_COMPILE_DIR_PATH = $ENV{'CREATE_COMPILE_DIR_PATH'};
my $VOBS_PATH = $ENV{'VOBS_PATH'};
my $PRODUCT = $ENV{'PRODUCT'};
my $PART_NUMBER = $ENV{'PART_NUMBER'};
my $RELEASE_DIR = $ENV{'RELEASE_DIR'};
my $RELEASE_TYPE = $ENV{'RELEASE_TYPE'};
my $RELEASE_VERSION = $ENV{'RELEASE_VERSION'};
chomp $DEV_BRANCH;chomp $NEXT_LABEL;chomp $INCGENS;chomp $CREATE_COMPILE_DIR_PATH;
chomp $VOBS_PATH;chomp $PRODUCT;chomp $PART_NUMBER;chomp $RELEASE_DIR;
chomp $RELEASE_TYPE; chomp $RELEASE_VERSION;
#==================================================
# verify the input from buildENV
#==================================================
#verify the DEV branch name enter or not
if ($DEV_BRANCH eq ""){
	print "Error: DEV BRANCH must not be blank\n";
	print "Please Enter the DEV BRANCH in your buildENV file\n";
	exit 1;
}

#verify the label name enter or not 
if ($NEXT_LABEL eq ""){
	print "Error: LABEL NAME must not be blank\n";
	print "Please Enter the Correct LABEL NAME in your buildENV file\n";
	print "For Example LB_TeNB_T2200_REL_FDD_GA2.0_GPR_01\n";
	exit 1;
}
#verify the INCGENG are mention or not 
if ( $INCGENS eq ""){
	print "Error: INCGENS must not be blank\n";
	print "Please Enter the GENS in your buildENV file\n";
	exit;
}
#verify the CREATE_COMPILE_DIR_PATH is mention or not 
if ( $CREATE_COMPILE_DIR_PATH eq ""){
	print "Error: CREATE_COMPILE_DIR_PATH must not be blank\n";
	print "Please Enter the CREATE_COMPILE_DIR_PATH in your buildENV file\n";
	exit;
}
#verify the VOBS_PATH is mention or not 
if ( $VOBS_PATH eq ""){
	print "Error: VOBS_PATH must not be blank\n";
	print "Please Enter the list of vobs in your buildENV file\n";
	exit;
}

#verify the PRODUCT is mention or not 
if ( $PRODUCT eq ""){
	print "Error: PRODUCT must not be blank\n";
	print "Please Enter the PRODUCT in your buildENV file\n";
	exit;
}
#verify the RELEASE_DIR is mention or not 
if ( $RELEASE_DIR eq ""){
	print "Error: RELEASE_DIR must not be blank\n";
	print "Please Enter the RELEASE_DIR in your buildENV file\n";
	exit;
}
#verify the RELEASE TYPE is mention or not 
if ( $RELEASE_TYPE eq ""){
	print "Error: RELEASE_TYPE must not be blank\n";
	print "Please Enter the RELEASE_TYPE in your buildENV file\n";
	exit;
}
#verify the RELEASE VERSION is mention or not 
if ( $RELEASE_VERSION eq ""){
	print "Error: RELEASE_VERSION must not be blank\n";
	print "Please Enter the RELEASE_VERSION in your buildENV file\n";
	exit;
}

# verify the part number enter or not 

if ( $PART_NUMBER !~ /^\d{7}$/ ){
	print "Error Product Part Number must have 7 digits\n";
	print "Please Enter the Correct Part Number in your buildENV file\n";
	exit 1;
}

# verify the view is set or not

my @viewCheck = `cleartool pwv`;
if( $viewCheck[1] =~ /Set view: \*\* NONE \*\*/ ){
   print "Please set the view before running validation script\n\n";
   exit 0;
	}
else{
	my @pwv = split (' ' , $viewCheck[1]);
	$VIEW_NAME = $pwv[2];
}
chomp $VIEW_NAME;

#split the GEN 00,01,02 to 00 01 02

my @INCGENS_option = split (',',$INCGENS);
chomp @INCGENS_option;


if ($NEXT_LABEL ne "")
{
	my @vobpath = split (',' , $VOBS_PATH );
	foreach my $path (@vobpath)
	{
		chomp $path ;
		if ($path eq "")
		{
			print "Error: VOBS_PATH in buildENV is not correct\n";
			print "Please Enter the Correct VOBS PATH in your buildENV file\n";
			print "For Example /vobs/core_prd/gprs/,/vobs/core_prd/cm/,/vobs/core_prd/voip/,/vobs/TeNB/\n";
				exit 1 ;
		}
		else
		{
			if (chdir "$path" == 0)
			{
				print "Error: VOBS_PATH in buildENV is not correct\n";
				print "Please Enter the Correct VOBS PATH in your buildENV file\n";
				print "For Example /vobs/core_prd/gprs/,/vobs/core_prd/cm/,/vobs/core_prd/voip/,/vobs/TeNB/\n";
				exit 1 ;
			}
			else
			{
				`cleartool desc lbtype:$NEXT_LABEL 2>/dev/null`;
				if ($? ne "0")
				{
					print "label type $NEXT_LABEL is not find in vob:$path \n";
					exit 1;
				}
			}		
		}
	}
}
	
###########################################################################
#verification is completed
############################################################################	

print "creating the code base on mention label\n";

#calling Createbasedirectory.pm for copying the code base from vobs to Release directory

if ($NEXT_LABEL ne "")
{
	Createbasedirectory::createdir ( $VIEW_NAME , $NEXT_LABEL , $CREATE_COMPILE_DIR_PATH , $PRODUCT );
}

