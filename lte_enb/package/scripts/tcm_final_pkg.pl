#!/usr/bin/perl -w
my $BASEDIR = "/clearcase/rtr/";
my $CRNT_LABEL = $ENV{'CRNT_LABEL'};
my $NEXT_LABEL = $ENV{'NEXT_LABEL'};
my $INCGENS = $ENV{'INCGENS'};
my $PRODUCT = $ENV{'PRODUCT'};
my $PART_NUMBER = $ENV{'PART_NUMBER'};
my $RELEASE_TYPE = $ENV{'RELEASE_TYPE'};
my $RELEASE_VERSION = $ENV{'RELEASE_VERSION'};
chomp $BASEDIR; chomp $NEXT_LABEL; chomp $INCGENS; chomp $PRODUCT;
chomp $PART_NUMBER; chomp $RELEASE_TYPE; chomp $RELEASE_VERSION;
my @INCGENS_option = split (',',$INCGENS);
chomp @INCGENS_option;
print "Please Provide Below input\n";
print " Its a Code Drop yes/no ??\n";
$Input = <STDIN>;
chomp $Input;
my $Type;
if ($Input =~ /yes/)
{
	$Type = "next";
}
else
{
	$Type = "gpr_pat";
}
foreach (@INCGENS_option)
{
	my $GEN = $_;;
	chomp $GEN;
	my $RELTARNAME = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$RELEASE_VERSION;
	chomp $RELTARNAME;
	if (chdir "$BASEDIR/$PART_NUMBER/$GEN/$Type/" != 0)
	{
		print "Swtiching to $BASEDIR/$PART_NUMBER/$GEN/$Type directory\n";
		system ("tar -cvzf $RELTARNAME.tar.gz $RELTARNAME");
	}
	else
	{
		print "$BASEDIR/$PART_NUMBER/$GEN/Type\n";
		print "Please Check the Release Directory\n";
		exit;
	}
}
