#!/usr/bin/perl -w
use strict;
use File::Path;
use File::Copy::Recursive qw(fcopy rcopy dircopy fmove rmove dirmove);
use File::Copy;
use File::Basename;
my $PATCHDIR = "/clearcase/rtr";
my $Date=`date '+%m/%d/%y'`;
my $BUILDDIR = "/msbublds01/tbuild/Release_Build/";
my $INCGENS = $ENV{'INCGENS'};
my $PRODUCT = $ENV{'PRODUCT'};
my $PART_NUMBER = $ENV{'PART_NUMBER'};
my $RELEASE_DIR = $ENV{'RELEASE_DIR'};
my $VERSION = $ENV{'VERSION'};
my $RELEASE_TYPE = $ENV{'RELEASE_TYPE'};
my $RELEASE_VERSION = $ENV{'RELEASE_VERSION'};
my $PREVRELEASE_VERSION = $ENV{'PREVRELEASE_VERSION'};
my $NEXT_LABEL = $ENV{'NEXT_LABEL'};
my @INCGENS_LIST = split (',',$INCGENS);
chomp @INCGENS_LIST;chomp $PRODUCT;
chomp $PATCHDIR;chomp $BUILDDIR;chomp $PART_NUMBER;

CreateLibsPatchDir();
CopyLibsDocsBin();
Create_crnt_structure();
Create_Src_Patch();
CreatetarPatch();

sub CreatetarPatch
{
	foreach (@INCGENS_LIST)
	{
       	 	my $GEN = $_;;
        	chomp $GEN;
        	my $RELTARNAME = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$RELEASE_VERSION;
        	chomp $RELTARNAME;
        	if (chdir "$PATCHDIR/$PART_NUMBER/$GEN/gpr_pat/" != 0)
        	{
                	print "Swtiching to $BUILDDIR/$PART_NUMBER/$GEN/gpr_pat directory\n";
                	system ("tar -cvzf $RELTARNAME.tar.gz $RELTARNAME");
        	}
        	else
        	{
                	print "$BUILDDIR/$PART_NUMBER/$GEN/gpr_pat\n";
                	print "Please Check the Release Directory\n";
                	exit;
        	}
	}
}

sub CopyLibsDocsBin
{
	foreach (@INCGENS_LIST)
	{
		my $GEN = $_;
		chomp $GEN;
		my $RELDIRNAME = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$RELEASE_VERSION;
      		chomp $RELDIRNAME;
		dircopy ("$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/bin" , "$PATCHDIR/$PART_NUMBER/$GEN/gpr_pat/$RELDIRNAME/bin") or die "Failed to copy dir $PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/bin $!";
		dircopy ("$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/docs" , "$PATCHDIR/$PART_NUMBER/$GEN/gpr_pat/$RELDIRNAME/docs") or die "Failed to copy dir $PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/docs $!";
		dircopy ("$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/libs" , "$PATCHDIR/$PART_NUMBER/$GEN/gpr_pat/$RELDIRNAME/libs") or die "Failed to copy dir $PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/libs $!";
		if (-d "$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/bsp")
		{
			dircopy ("$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/bsp" , "$PATCHDIR/$PART_NUMBER/$GEN/gpr_pat/$RELDIRNAME/bsp") or die "Failed to copy dir $PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/bsp $!";
		}
	}
}
sub CreateLibsPatchDir
{
	foreach (@INCGENS_LIST)
	{
		my $GEN = $_;
		chomp $GEN;
		my $RELDIRNAME = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$RELEASE_VERSION;
      		chomp $RELDIRNAME;
		mkpath(["$PATCHDIR/$PART_NUMBER"], "{ verbose => 1}");
		mkpath(["$PATCHDIR/$PART_NUMBER/$GEN/gpr_pat"], "{ verbose => 1}");
		mkpath(["$PATCHDIR/$PART_NUMBER/$GEN/crnt"], "{ verbose => 1}");
		mkpath(["$PATCHDIR/$PART_NUMBER/$GEN/gpr_pat/$RELDIRNAME/"], "{ verbose => 1}");
		mkpath(["$PATCHDIR/$PART_NUMBER/$GEN/gpr_pat/$RELDIRNAME/src"], "{ verbose => 1}");
	}
}

sub Create_crnt_structure
{
	foreach my $GEN (@INCGENS_LIST)
	{
		chomp $GEN;
		my $PREVRELDIRNAMETARFile = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$PREVRELEASE_VERSION.".tar.gz";
		my $PREVRELDIRNAME = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$PREVRELEASE_VERSION;
		copy ("$RELEASE_DIR/$PART_NUMBER/$VERSION/$GEN/crnt/$PREVRELDIRNAMETARFile" , "$PATCHDIR/$PART_NUMBER/$GEN/crnt/") or die "Failed to copy dir $RELEASE_DIR/$PART_NUMBER/$VERSION/$GEN/crnt/$PREVRELDIRNAMETARFile  $!";
		system ("tar -xzvf $PATCHDIR/$PART_NUMBER/$GEN/crnt/$PREVRELDIRNAMETARFile -C $PATCHDIR/$PART_NUMBER/$GEN/crnt/")
	}
	
	
}

sub Create_Src_Patch
{
	foreach my $GEN (@INCGENS_LIST)
	{
		chomp $GEN;
		my $RELDIRNAME = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$RELEASE_VERSION;
		my $PREVRELDIRNAME = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$PREVRELEASE_VERSION;
  	 	chomp $RELDIRNAME; chomp $PREVRELDIRNAME;
		my $PATCHPATH = $PATCHDIR."/".$PART_NUMBER."/".$GEN."/gpr_pat/".$RELDIRNAME."/src/";
   		chomp $PATCHPATH ;
		my $PRODUCT_CONFIG = $BUILDDIR.$NEXT_LABEL."/package/build/".$PRODUCT.".cmd.".$GEN;
		chomp $PRODUCT_CONFIG;
		open (AD,$PRODUCT_CONFIG) or die "Not able to open $PRODUCT_CONFIG $!";
		my @listofdir = <AD>;
		my @PATCH_REQ_DIR;
		my @PRODUCT_PREFIX;
		foreach (@listofdir)
		{
			if (grep (/dir / ,$_))
			{
				my @DirName = split (' ' , $_);
				my $PATCH_REQ_DIR = $DirName[1];
				my $PRODUCT_PREFIX = $DirName[2];
				my $PRODUCT_PATCH_REQ = $DirName[3];
				chomp $PATCH_REQ_DIR;
				chomp $PRODUCT_PREFIX ;
				chomp $PRODUCT_PATCH_REQ;
				my @chxfile;
				if ($PRODUCT_PATCH_REQ =~ /yes/ )
				{
					my $prevdir;my $nextdir;
					$nextdir = "$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/src/$PATCH_REQ_DIR";
					$prevdir = "$PATCHDIR/$PART_NUMBER/$GEN/crnt/$PREVRELDIRNAME/src/$PATCH_REQ_DIR";
					chomp $prevdir ; 
					chomp $nextdir;
					my $patchname;
					$patchname = $PATCHPATH.$PATCH_REQ_DIR."_".$PART_NUMBER.$GEN."_"."$RELEASE_TYPE"."_"."$RELEASE_VERSION"."_pat";
					chomp $patchname;
					my @changefile;
					print "`diff --brief -r $prevdir $nextdir`\n";
					my @allfiles = `diff --brief -r $prevdir $nextdir`;
					foreach my $x (@allfiles)
					{
						if ( $x =~ /differ/ )
						{
							my @splitpathdiff = split ( ' and ', $x);
							my @y = split m!(/)!, $splitpathdiff[0];
							chomp $y[$#y];
							push ( @changefile , $y[$#y] ) ;
						}
						else
						{
							my @splitpath = split ( ': ' , $x );
							chomp $splitpath[1];
							push ( @changefile , $splitpath[1]) ;
						}
					}
					if ($#changefile >=  0)
      					{
						print "creating patch between $prevdir and $nextdir\n";
			     	    		open (FH, "> $patchname") or die "Can not open file $!";
			        	   	print FH "=============================================================================== \n";
        			    		print FH "\t\t\t   Software Patch Form \n";
			            		print FH "\t\t\tTrillium software from Radisys \n";
			            		print FH "=============================================================================== \n";
			           		print FH " \n";
			            		print FH "Previous Version   :    $PREVRELEASE_VERSION                                        \n";
			            		print FH "Date               :    $Date                                       \n";
			            		print FH "Next Version       :    $RELEASE_VERSION                                           \n";
			            		print FH "Filenames          :                                                   \n\n";
			               		for (my $i=0,my $j=1; $i<=$#changefile; $i++,$j++)
			               		{
							print FH "\t\t\t\t $j. $changefile[$i]\n";
                  				}
			            		print FH "============================================================================== \n";
			            		close FH;
			            		open (PF, ">>$patchname") or die "Can not open patch file $PATCH_REQ_DIR $!";
			            		print "\n";print "CREATING PATCH FOR PARENT CRNT ...... \n";print "\n";
						#chdir ("$PATCHDIR/$PART_NUMBER/$GEN/crnt/$RELDIRNAME/src/");
						chdir ("$PATCHDIR/$PART_NUMBER/$GEN/crnt/$PREVRELDIRNAME/src/");
						print "$PATCHDIR/$PART_NUMBER/$GEN/crnt/$PREVRELDIRNAME/src/\n";
			            		#print "diff -cN -r $PATCH_REQ_DIR/ $nextdir/\n";exit;
			            		print PF `diff -cN -r $PATCH_REQ_DIR/ $nextdir/\n`;
			            		print PF "================================================================================= \n";
			            		close PF;
			      		}
				}
				else
				{
					dircopy ("$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/src/$PATCH_REQ_DIR" , "$PATCHDIR/$PART_NUMBER/$GEN/gpr_pat/$RELDIRNAME/src/$PATCH_REQ_DIR") or die "Failed to copy dir $PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/src/$PATCH_REQ_DIR $!";
				}
					
			
			}
		}
	}
}
