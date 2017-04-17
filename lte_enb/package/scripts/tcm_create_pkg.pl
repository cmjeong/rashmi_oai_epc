#!/usr/bin/perl -w
use strict;
use File::Path;
use File::Copy::Recursive qw(fcopy rcopy dircopy fmove rmove dirmove);
use File::Copy;
use File::Basename;
my $PATCHDIR = "/clearcase/rtr";
my $BUILDDIR = "/msbublds01/tbuild/Release_Build";
my $INCGENS = $ENV{'INCGENS'};
my $PRODUCT = $ENV{'PRODUCT'};
my $PART_NUMBER = $ENV{'PART_NUMBER'};
my $RELEASE_TYPE = $ENV{'RELEASE_TYPE'};
my $RELEASE_VERSION = $ENV{'RELEASE_VERSION'};
my $NEXT_LABEL = $ENV{'NEXT_LABEL'};
my @INCGENS_LIST = split (',',$INCGENS);
chomp $NEXT_LABEL;chomp @INCGENS_LIST;chomp $PRODUCT;
chomp $PATCHDIR;chomp $BUILDDIR;chomp $PART_NUMBER;

CreateLibsPatchDir();
CopyingLibs();
cleancompliation();
CreatePkg();
CreatetarPkg();

sub CreatetarPkg
{
	foreach (@INCGENS_LIST)
	{
		my $GEN = $_;;
        	chomp $GEN;
        	my $RELTARNAME = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$RELEASE_VERSION;
        	chomp $RELTARNAME;
        	if (chdir "$PATCHDIR/$PART_NUMBER/$GEN/next/" != 0)
        	{
               	 	print "Swtiching to $PATCHDIR/$PART_NUMBER/$GEN/next directory\n";
                	system ("tar -cvzf $RELTARNAME.tar.gz $RELTARNAME");
        	}
        	else
        	{
                	print "$PATCHDIR/$PART_NUMBER/$GEN/next\n";
                	print "Please Check the Release Directory\n";
                	exit;
        	}
	}
}

sub cleancompliation
{
	print "starting clean the *.o *obj files\n";
	if ($PRODUCT =~ /T2200_FDD/)
	{
		if (chdir "$BUILDDIR/$NEXT_LABEL/src/ltephy/mindSpeed/lowercore/transcede_libs" == 0)
		{
			print "$BUILDDIR/$NEXT_LABEL/src/ltephy/mindSpeed/lowercore/transcede_libs exit\n";
			exit;
		}
		else
		{
			system ("./clean.sh | tee $BUILDDIR/$NEXT_LABEL/transcede_libsclean.log");
		}
		if (chdir "$BUILDDIR/$NEXT_LABEL/src/ltephy/mindSpeed/lowercore/ltert" == 0)
		{
			print "$BUILDDIR/$NEXT_LABEL/src/ltephy/mindSpeed/lowercore/ltert exit\n";
			exit;
		}
		else
		{
			system ("./t2k.sh xclean | tee $BUILDDIR/$NEXT_LABEL/ltertclean.log");
		}
  	 	if (chdir "$BUILDDIR/$NEXT_LABEL/src/enbapp/build" == 0 )
		{
  		 	print "$BUILDDIR/$NEXT_LABEL/enbapp/builddir doesnt exits\n";
  		 	exit;
  		 }
   		else
   		{
     	 		system ( "make t2k_clean | tee $BUILDDIR/$NEXT_LABEL/t2k_clean.log");
			my @NEXT_LABEL_HIDDEN = `find $BUILDDIR/$NEXT_LABEL -name ".*"`;
   			foreach my $files ( @NEXT_LABEL_HIDDEN )
   			{
         			print $files;
      	   			chomp $files;
        	 		system (" rm -rf $files ");
			}
			my @NEXT_LABEL_OBJ = `find $BUILDDIR/$NEXT_LABEL -name "obj"`;
			foreach my $NEXT_LABEL_OBJfiles ( @NEXT_LABEL_OBJ )
			{
				print $NEXT_LABEL_OBJfiles;
				chomp $NEXT_LABEL_OBJfiles;
				system (" rm -rf $NEXT_LABEL_OBJfiles ");
   			}
		}
	}
	if ($PRODUCT =~ /T2200_TDD/)
	{
  	 	if (chdir "$BUILDDIR/$NEXT_LABEL/src/enbapp/build" == 0 )
		{
  		 	print "$BUILDDIR/$NEXT_LABEL/enbapp/builddir doesnt exits\n";
  		 	exit;
  		 }
   		else
   		{
     	 		system ( "make clean | tee $BUILDDIR/$NEXT_LABEL/t2kdd_clean_all.log");
			my @NEXT_LABEL_HIDDEN = `find $BUILDDIR/$NEXT_LABEL -name ".*"`;
   			foreach my $files ( @NEXT_LABEL_HIDDEN )
   			{
         			print $files;
      	   			chomp $files;
        	 		system (" rm -rf $files ");
			}
			my @NEXT_LABEL_OBJ = `find $BUILDDIR/$NEXT_LABEL -name "obj"`;
			foreach my $NEXT_LABEL_OBJfiles ( @NEXT_LABEL_OBJ )
			{
				print $NEXT_LABEL_OBJfiles;
				chomp $NEXT_LABEL_OBJfiles;
				system (" rm -rf $NEXT_LABEL_OBJfiles ");
   			}
		}
	}
	elsif ($PRODUCT =~ /BRDCM_FDD/)
	{
  	 	if (chdir "$BUILDDIR/$NEXT_LABEL/src/enbapp/build" == 0 )
		{
  		 	print "$BUILDDIR/$NEXT_LABEL/enbapp/builddir doesnt exits\n";
  		 	exit;
  		 }
   		else
   		{
     	 		system ( "make bcclean_all | tee $BUILDDIR/$NEXT_LABEL/bcclean_all.log");
			my @NEXT_LABEL_HIDDEN = `find $BUILDDIR/$NEXT_LABEL -name ".*"`;
   			foreach my $files ( @NEXT_LABEL_HIDDEN )
   			{
      			   	print $files;
         			chomp $files;
         			system (" rm -rf $files ");
			}
			my @NEXT_LABEL_OBJ = `find $BUILDDIR/$NEXT_LABEL -name "obj"`;
			foreach my $NEXT_LABEL_OBJfiles ( @NEXT_LABEL_OBJ )
			{
				print $NEXT_LABEL_OBJfiles;
				chomp $NEXT_LABEL_OBJfiles;
				system (" rm -rf $NEXT_LABEL_OBJfiles ");
   			}
		}
		
	}
	elsif ($PRODUCT =~ /T3300_TDD/)
	{
  	 	if (chdir "$BUILDDIR/$NEXT_LABEL/src/enbapp/build" == 0 )
		{
  		 	print "$BUILDDIR/$NEXT_LABEL/enbapp/builddir doesnt exits\n";
  		 	exit;
  		 }
   		else
   		{
     	 		system ( "make make t33h_clean_all | tee $BUILDDIR/$NEXT_LABEL/make t33h_clean_all.log");
			my @NEXT_LABEL_HIDDEN = `find $BUILDDIR/$NEXT_LABEL -name ".*"`;
   			foreach my $files ( @NEXT_LABEL_HIDDEN )
   			{
      			   	print $files;
         			chomp $files;
         			system (" rm -rf $files ");
			}
			my @NEXT_LABEL_OBJ = `find $BUILDDIR/$NEXT_LABEL -name "obj"`;
			foreach my $NEXT_LABEL_OBJfiles ( @NEXT_LABEL_OBJ )
			{
				print $NEXT_LABEL_OBJfiles;
				chomp $NEXT_LABEL_OBJfiles;
				system (" rm -rf $NEXT_LABEL_OBJfiles ");
   			}
		}
		
	}
	elsif ($PRODUCT =~ /T3300_FDD/)
	{
  	 	if (chdir "$BUILDDIR/$NEXT_LABEL/src/enbapp/build" == 0 )
		{
  		 	print "$BUILDDIR/$NEXT_LABEL/enbapp/builddir doesnt exits\n";
  		 	exit;
  		 }
   		else
   		{
     	 		system ( "make make t33h_clean_all | tee $BUILDDIR/$NEXT_LABEL/make t33h_clean_all.log");
			my @NEXT_LABEL_HIDDEN = `find $BUILDDIR/$NEXT_LABEL -name ".*"`;
   			foreach my $files ( @NEXT_LABEL_HIDDEN )
   			{
      			   	print $files;
         			chomp $files;
         			system (" rm -rf $files ");
			}
			my @NEXT_LABEL_OBJ = `find $BUILDDIR/$NEXT_LABEL -name "obj"`;
			foreach my $NEXT_LABEL_OBJfiles ( @NEXT_LABEL_OBJ )
			{
				print $NEXT_LABEL_OBJfiles;
				chomp $NEXT_LABEL_OBJfiles;
				system (" rm -rf $NEXT_LABEL_OBJfiles ");
   			}
		}
		
	}
	elsif ($PRODUCT =~ /BRDCM_TDD/)
	{
  	 	if (chdir "$BUILDDIR/$NEXT_LABEL/src/enbapp/build" == 0 )
		{
  		 	print "$BUILDDIR/$NEXT_LABEL/enbapp/builddir doesnt exits\n";
  		 	exit;
  		 }
   		else
   		{
     	 		system ( "make clean | tee $BUILDDIR/$NEXT_LABEL/bcclean_all.log");
			my @NEXT_LABEL_HIDDEN = `find $BUILDDIR/$NEXT_LABEL -name ".*"`;
   			foreach my $files ( @NEXT_LABEL_HIDDEN )
   			{
      			   	print $files;
         			chomp $files;
         			system (" rm -rf $files ");
			}
			my @NEXT_LABEL_OBJ = `find $BUILDDIR/$NEXT_LABEL -name "obj"`;
			foreach my $NEXT_LABEL_OBJfiles ( @NEXT_LABEL_OBJ )
			{
				print $NEXT_LABEL_OBJfiles;
				chomp $NEXT_LABEL_OBJfiles;
				system (" rm -rf $NEXT_LABEL_OBJfiles ");
   			}
		}
		
	}
	elsif ($PRODUCT =~ /PAL_FDD/)
	{
  	 	if (chdir "$BUILDDIR/$NEXT_LABEL/src/enbapp/build" == 0 )
		{
  		 	print "$BUILDDIR/$NEXT_LABEL/enbapp/builddir doesnt exits\n";
  		 	exit;
  		}
   		else
   		{
     	 		system ( "make lnxclean_all | tee $BUILDDIR/$NEXT_LABEL/lnxcleanl.log");
			my @NEXT_LABEL_HIDDEN = `find $BUILDDIR/$NEXT_LABEL -name ".*"`;
   			foreach my $files ( @NEXT_LABEL_HIDDEN )
   			{
         			chomp $files;
         			system (" rm -rf $files ");
			}
			my @NEXT_LABEL_OBJ = `find $BUILDDIR/$NEXT_LABEL -name "obj"`;
			foreach my $NEXT_LABEL_OBJfiles ( @NEXT_LABEL_OBJ )
			{
				print $NEXT_LABEL_OBJfiles;
				chomp $NEXT_LABEL_OBJfiles;
				system (" rm -rf $NEXT_LABEL_OBJfiles ");
			}
		}
	}
   system ("rm -rf $BUILDDIR/$NEXT_LABEL/src/tenb_commonplatform/software/libs/common/include/boost");	
   system ("rm -rf $BUILDDIR/$NEXT_LABEL/src/mt/security/*");	
   system ("rm -rf $BUILDDIR/$NEXT_LABEL/src/lteremapp/libs/i686-linux/*");	
   system ("rm -rf $BUILDDIR/$NEXT_LABEL/src/lteremapp/libs/mipsel-unknown-linux-gnu/*");	
   system ("rm -rf $BUILDDIR/$NEXT_LABEL/src/lteremapp/libs/arm-none-linux-gnueabi/*");
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
		mkpath(["$PATCHDIR/$PART_NUMBER/$GEN/next"], "{ verbose => 1}");
		mkpath(["$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/"], "{ verbose => 1}");
		mkpath(["$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/src"], "{ verbose => 1}");
		mkpath(["$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/docs"], "{ verbose => 1}");
	}
}

sub CopyingLibs
{
	foreach (@INCGENS_LIST)
	{
		my $GEN = $_;
		chomp $GEN;
		my $RELDIRNAME = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$RELEASE_VERSION;
      		chomp $RELDIRNAME;
		print "$BUILDDIR/$NEXT_LABEL/bin/rsys\n";
		dircopy ("$BUILDDIR/$NEXT_LABEL/bin","$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/bin") or die "Failed to copy files under Directory $BUILDDIR/$NEXT_LABEL/bin $!";
		dircopy ("$BUILDDIR/$NEXT_LABEL/libs","$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/libs/") or die "Failed to copy files under Directory $BUILDDIR/$NEXT_LABEL/libs $!";
		if (-d "$BUILDDIR/$NEXT_LABEL/bsp")
		{
			dircopy ("$BUILDDIR/$NEXT_LABEL/bsp","$PATCHDIR/$PART_NUMBER/$GEN/next/$RELDIRNAME/bsp/") or die "Failed to copy files under Directory $BUILDDIR/$NEXT_LABEL/bsp $!";
		}
	}
}

sub CreatePkg
{
	
	foreach my $GEN (@INCGENS_LIST)
	{
		chomp $GEN;
		my $RELDIRNAME = $PART_NUMBER."_".$GEN."_".$RELEASE_TYPE."_".$RELEASE_VERSION;
  	   	chomp $RELDIRNAME;
		my $SRCPATH = $PATCHDIR."/".$PART_NUMBER."/".$GEN."/next/".$RELDIRNAME."/src";
		my $DOCSPATH = $PATCHDIR."/".$PART_NUMBER."/".$GEN."/next/".$RELDIRNAME."/docs";
  	 	chomp $SRCPATH ;chomp $DOCSPATH;
		my $PRODUCT_CONFIG = $BUILDDIR."/".$NEXT_LABEL."/package/build/".$PRODUCT.".cmd.".$GEN;
		chomp $PRODUCT_CONFIG;
		open (AD,$PRODUCT_CONFIG) or die "Not able to open $PRODUCT_CONFIG $!";
		my @listofdir = <AD>;
		my @PRODUCT_PREFIX;
		my @docslist;
		foreach (@listofdir)
		{
			if (grep (/dir / ,$_))
			{
				my @soccmdstring = split (' ' , $_);
				my $product = $soccmdstring[1];
				my $prdprefix = $soccmdstring[2];
				chomp $product ;chomp $prdprefix;
				my $prdcmdfile = $BUILDDIR."/".$NEXT_LABEL."/package/build/".$prdprefix.".cmd";
				chomp $prdcmdfile;
				mkpath(["$SRCPATH/$product"], "{ verbose => 1}");
				open (ND,$prdcmdfile) or die "Not able to find $prdcmdfile file $!\n";
				my @cmdfilecontain = <ND>;
				close (ND);
				foreach (@cmdfilecontain)
				{
					my $filelist = $_;
					chomp $filelist;
					if (grep (/file /,$filelist))
					{
						my @file = split (' ' , $filelist);
						my $filename = $file[1];
						chomp $filename;
						my $i = dirname($filename);
						my $length = length $i;
						if ($length != 1)
						{
							mkpath(["$SRCPATH/$product/$i"], "{ verbose => 1}");
							copy ("$BUILDDIR/$NEXT_LABEL/src/$product/$filename" , "$SRCPATH/$product/$filename") or die "Failed to copy file $BUILDDIR/$NEXT_LABEL/src/$product/$filename $!\n";
						}
						else
						{
							copy ("$BUILDDIR/$NEXT_LABEL/src/$product/$filename" , "$SRCPATH/$product/") or die "Failed to copy file $BUILDDIR/$NEXT_LABEL/src/$product/$filename $!\n";
						}
					}
					elsif (grep (/dir/, $filelist))
					{
						my @dir = split (' ' , $filelist);
						my $dirname = $dir[1];
						chomp $dirname;
						dircopy ("$BUILDDIR/$NEXT_LABEL/src/$product/$dirname" , "$SRCPATH/$product/$dirname") or die "Failed to copy dir $BUILDDIR/$NEXT_LABEL/src/$product/$dirname $!";		
					}
				}
			}
			if (grep (/file / ,$_))
			{
				my @filepath = split (' ' ,$_);
				my $filename = $filepath[1];
				chomp $filename;
				my $i = dirname($filename);
				my $length = length $i;
				if ($length != 1)
				{
					mkpath(["$SRCPATH/$i"], "{ verbose => 1}");
					copy ("$BUILDDIR/$NEXT_LABEL/src/$filename" , "$SRCPATH/$filename") or die "Failed to copy file $BUILDDIR/$NEXT_LABEL/src/$filename $!";		
				}
				else
				{
					copy ("$BUILDDIR/$NEXT_LABEL/src/$filename" , "$SRCPATH/$filename") or die "Failed to copy file $BUILDDIR/$NEXT_LABEL/src/$filename $!";		
				}
			}

			if (grep(/docs/ , $_))
			{
				my @DocsName = split (' ' , $_);
				chomp $DocsName[1];
				push (@docslist , $DocsName[1]);
			}
		}
		foreach (@docslist)
		{
			my $docs = $_ ;
			copy ("$BUILDDIR/$NEXT_LABEL/docs/$docs" , "$DOCSPATH/") or die "Failed to copy files under Directory $BUILDDIR/$NEXT_LABEL/docs/$docs $!";	
		}
}
}
