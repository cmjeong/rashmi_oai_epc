#!/usr/bin/perl -w
use strict;
use lib '/opt/script/ReleaseScript//';
use Compilation;
use File::Path;
use File::Copy::Recursive qw(fcopy rcopy dircopy fmove rmove dirmove);
my $BASEDIR = "/msbublds01/tbuild/Release_Build/";
my $NEXT_LABEL = $ENV{'NEXT_LABEL'};
my $PRODUCT = $ENV{'PRODUCT'};
chomp $BASEDIR;
if ( $PRODUCT eq ""){
   print "Error: PRODUCT must not be blank\n";
   print "Please Enter the PRODUCT in your buildENV file\n";
   exit;
}
if ( $NEXT_LABEL eq ""){
   print "Error: NEXT_LABELmust not be blank\n";
   print "Please Enter the NEXT_LABEL in your buildENV file\n";
   exit;
}
my $BUILD_DIR = $BASEDIR.$NEXT_LABEL;
chomp $BUILD_DIR;
if ($PRODUCT =~ /T2200_FDD/)
{
	Compilation::T2200_FDD_Compliation($BUILD_DIR);
}
elsif ($PRODUCT =~ /T3300_FDD/)
{
	Compilation::T3300_FDD_Compliation($BUILD_DIR);
}
elsif ($PRODUCT =~ /T3300_TDD/)
{
	Compilation::T3300_TDD_Compliation($BUILD_DIR);
}
elsif ($PRODUCT =~ /T2200_TDD/)
{
	Compilation::T2200_TDD_Compliation($BUILD_DIR);
}
elsif ($PRODUCT =~ /BRDCM_FDD/)
{
	Compilation::BRDCM_FDD_Compliation($BUILD_DIR);
}
elsif ($PRODUCT =~ /BRDCM_TDD/)
{
	Compilation::BRDCM_TDD_Compliation($BUILD_DIR);
}
elsif ($PRODUCT =~ /PAL_FDD/)
{
	Compilation::PAL_FDD_Compliation($BUILD_DIR);
}
else
{
	print "Please Enter Correct Product Name\n";
	exit;
}
