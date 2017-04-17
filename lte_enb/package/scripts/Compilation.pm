#!/usr/bin/perl -w
use strict;
my $DATE = `date '+%m-%d-%y'`;
chomp $DATE;
package Compilation;
use File::Path;
use File::Copy::Recursive qw(fcopy rcopy dircopy fmove rmove dirmove);

sub T2200_FDD_Compliation(@)
{
	my ( $BUILD_DIR ) = @_;
	chomp $BUILD_DIR ;
	if (chdir "$BUILD_DIR/src/ltephy/mindSpeed/lowercore/transcede_libs" == 0 )
	{
		print "$BUILD_DIR/src/ltephy/mindSpeed/lowercore/transcede_libs dir doesnt exits\n";
		exit;
	}
	else
	{
		system ( "dos2unix *.sh");
		system ("chmod 777 *.sh");
		system ("rm -f clean ");
		system ("./clean.sh");
		system ("./build.sh");
	}
	if ( chdir "$BUILD_DIR/src/ltephy/mindSpeed/lowercore/ltert" == 0)
  	{
        print "directory $BUILD_DIR/src/ltephy/mindSpeed/lowercore/ltert doesn't exist\n";
        exit;
	}
	else
	{
		system ( "dos2unix *.sh");
		system ("chmod 777 *.sh");
		system ("./t2k.sh xclean");
   	system ("./t2k.sh");
	}
	if (chdir "$BUILD_DIR/src/enbapp/build" == 0 )
	{
		print "$BUILD_DIR/enbapp/build dir doesnt exits\n";
		exit;
	}
	else
	{
		print "Start compilation for product T2200_FDD\n";
		system (". $BUILD_DIR/src/enbapp/build/setVar.sh");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART OAM COMPILATION									\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t2k_clean_all");
		system ( "make t2k_oam &> $BUILD_DIR/msoambuild.log");
		`ls $BUILD_DIR/src/enbapp/build/rsys/bin/oam`;
		my $oamstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART REMAPP COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t2k_remapp &> $BUILD_DIR/remappbuild.log");
		`ls $BUILD_DIR/bin/rsys/bin/rem`;
		my $remappstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART REMLIB COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t2k_remlib &> $BUILD_DIR/rembuild.log");
		`ls $BUILD_DIR/libs/librem.a`;
		my $remstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART ENB COMPILATION									\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t2k_enb &> $BUILD_DIR/msenbbuild.log");
		`ls $BUILD_DIR/bin/rsys/bin/enodeb`;
		my $status = `echo $?`;
		#system ("make t2k_clean_all | tee $BUILD_DIR/t2k_clean_all.log");
		system ("make t2k_clean | tee $BUILD_DIR/t2k_clean_all.log");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART T2K_INT COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t2k_int &> $BUILD_DIR/t2k_intbuild.log");
		`ls $BUILD_DIR/bin/rsys_withoutoam/enodeb`;
		my $t2kstatus = `echo $?`;
		chomp $oamstatus;
	 	chomp $remappstatus;
		chomp $remstatus;
		chomp $status;
		chomp $t2kstatus;
		if ( $status != 0 or $remstatus != 0 or $oamstatus != 0 or $remappstatus != 0 or $t2kstatus != 0)
		{
			print "shipment compilation of all source code is failed\n";
	    	print "please check ... \n";
  	 		exit;
		}
		else
		{
			print "#################################################################################################\n";
			print "#################################################################################################\n";
			print "\t\t\t\t\t ALL THE COMPILATION IS PASSED								\n";
			print "#################################################################################################\n";
			print "#################################################################################################\n";
		}
	}
}


sub T3300_FDD_Compliation(@)
{
	my ( $BUILD_DIR ) = @_;
	chomp $BUILD_DIR ;
	if (chdir "$BUILD_DIR/src/ltephy/mindSpeed/lowercore/transcede_libs" == 0 )
	{
		print "$BUILD_DIR/src/ltephy/mindSpeed/lowercore/transcede_libs dir doesnt exits\n";
		exit;
	}
	else
	{
		system ( "dos2unix *.sh");
		system ("chmod 777 *.sh");
		system ("rm -f clean ");
		system ("./clean.sh");
		system ("./build.sh");
	}
	if ( chdir "$BUILD_DIR/src/ltephy/mindSpeed/lowercore/ltert" == 0)
  	{
        print "directory $BUILD_DIR/src/ltephy/mindSpeed/lowercore/ltert doesn't exist\n";
        exit;
	}
	else
	{
		system ( "dos2unix *.sh");
		system ("chmod 777 *.sh");
		system ("./t2k.sh xclean");
   		system ("./t2k.sh");
	}
	if (chdir "$BUILD_DIR/src/enbapp/build" == 0 )
	{
		print "$BUILD_DIR/enbapp/build dir doesnt exits\n";
		exit;
	}
	else
	{
		print "Start compilation for product T3300_FDD\n";
		system (". $BUILD_DIR/src/enbapp/build/setVar.sh");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART OAM COMPILATION									\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_clean_all");
		system ( "make t33h_oam &> $BUILD_DIR/msoambuild.log");
		`ls $BUILD_DIR/src/enbapp/build/rsys/bin/oam`;
		my $oamstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART RRM COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_rrm &> $BUILD_DIR/t33h_rrm.log");
		`ls $BUILD_DIR/bin/rsys/bin/rem`;
		my $remappstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART REMLIB COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_remlib &> $BUILD_DIR/rembuild.log");
		`ls $BUILD_DIR/libs/librem.a`;
		my $remstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART REMAPP COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_remapp &> $BUILD_DIR/t33h_remapp.log");
		`ls $BUILD_DIR/libs/librem.a`;
		my $remstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART ENB COMPILATION									\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_enb &> $BUILD_DIR/msenbbuild.log");
		`ls $BUILD_DIR/bin/rsys/bin/enodeb_net`;
		my $status = `echo $?`;
		`ls $BUILD_DIR/bin/rsys/bin/enodeb_radio`;
		my $radiostatus = `echo $?`;
		#system ("make t33h_clean_all | tee $BUILD_DIR/t33h_clean_all.log");
		system ("make t33h_clean | tee $BUILD_DIR/t33h_clean_all.log");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART T2K_INT COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_int &> $BUILD_DIR/t33h_intbuild.log");
		`ls $BUILD_DIR/bin/rsys_withoutoam/enodeb_net`;
		my $t2kstatus = `echo $?`;
		`ls $BUILD_DIR/bin/rsys_withoutoam/enodeb_radio`;
		my $t3kradiostatus = `echo $?`;
		chomp $oamstatus;
	 	chomp $remappstatus;
		chomp $remstatus;
		chomp $status;
		chomp $t2kstatus;
		chomp $t3kradiostatus;
		chomp $radiostatus ;
		if ( $status != 0 or $remstatus != 0 or $oamstatus != 0 or $remappstatus != 0 or $t2kstatus != 0 or $radiostatus != 0 or $t3kradiostatus != 0)
		{
			print "shipment compilation of all source code is failed\n";
	    		print "please check ... \n";
  	 		exit;
		}
		else
		{
			print "#################################################################################################\n";
			print "#################################################################################################\n";
			print "\t\t\t\t\t ALL THE COMPILATION IS PASSED								\n";
			print "#################################################################################################\n";
			print "#################################################################################################\n";
		}
	}
}



sub T2200_TDD_Compliation(@)
{
	my ( $BUILD_DIR ) = @_;
	chomp $BUILD_DIR ;
	if (chdir "$BUILD_DIR/src/enbapp/build" == 0 )
	{
		print "$BUILD_DIR/enbapp/build dir doesnt exits\n";
		exit;
	}
	else
	{
		print "Start compilation for product T2200_TDD\n";
		system (". $BUILD_DIR/src/enbapp/build/setVar.sh");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART OAM COMPILATION									\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		
		system ( "make t2ktdd_oam &> $BUILD_DIR/t2ktdd_oam.log");
		`ls $BUILD_DIR/src/enbapp/build/rsys/bin/oam`;
		my $oamstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART ENB COMPILATION									\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t2ktdd_enb_cnm &> $BUILD_DIR/t2ktdd_enb_cnm.log");
		`ls $BUILD_DIR/bin/rsys/bin/enodeb`;
		my $status = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART REMAPP COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t2ktdd_remapp &> $BUILD_DIR/t2ktdd_remapp.log");
		`ls $BUILD_DIR/bin/rsys/bin/rem`;
		my $remappstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART REMLIB COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t2ktdd_remlib &> $BUILD_DIR/t2ktdd_remlib.log");
		`ls $BUILD_DIR/libs/librem.a`;
		my $remstatus = `echo $?`;
		system ("make t2k_clean_all | tee $BUILD_DIR/t2k_clean_all.log");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART t2ktdd_rrm COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t2ktdd_rrm &> $BUILD_DIR/t2ktdd_rrm.log");
		`ls $BUILD_DIR/libs/librm.a`;
		my $t2kstatus = `echo $?`;
		system ("make t2k_clean_all | tee $BUILD_DIR/t2k_clean_all.log");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART t2ktdd_int COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t2ktdd_int &> $BUILD_DIR/t2ktdd_int.log");
		`ls $BUILD_DIR/bin/rsys_withoutoam/enodeb`;
		my $t2ktdd_int = `echo $?`;
		chomp $oamstatus;
	 	chomp $remappstatus;
		chomp $remstatus;
		chomp $status;
		chomp $t2kstatus;
		chomp $t2ktdd_int;
		if ( $status != 0 or $remstatus != 0 or $oamstatus != 0 or $remappstatus != 0 or $t2kstatus != 0 or $t2ktdd_int !=0  )
		{
			print "shipment compilation of all source code is failed\n";
	    	print "please check ... \n";
  	 		exit;
		}
		else
		{
			print "#################################################################################################\n";
			print "#################################################################################################\n";
			print "\t\t\t\t\t ALL THE COMPILATION IS PASSED								\n";
			print "#################################################################################################\n";
			print "#################################################################################################\n";
		}
	}
}
sub BRDCM_FDD_Compliation(@)
{
	my ( $BUILD_DIR ) = @_;
	chomp $BUILD_DIR ;
	if (chdir "$BUILD_DIR/src/enbapp/build" == 0 )
	{
		print "$BUILD_DIR/enbapp/build dir doesnt exits\n";
		exit;
	}
	else
	{
		print "Start compilation for product BRDCM_FDD\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART BroadCom COMPILATION without OAM							\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		
		my $brcmstatus = system ( "make bce2e -j &> $BUILD_DIR/bce2e.log");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART BroadCom Clean COMPILATION															  \n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make bcclean_all &> $BUILD_DIR/bcclean.log");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART BroadCom COMPILATION with OAM							\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		my $status = system ("make bce2e_oam_bld_all &> $BUILD_DIR/bce2e_oam_bld_all.log");
		chomp $status ;
		chomp $brcmstatus;
		if ( $status != 0 or $brcmstatus != 0 )
		{
			print "shipment compilation of all source code is failed\n";
	    	print "please check ... \n";
  	 		exit;
		}
		else
		{
			print "#################################################################################################\n";
			print "#################################################################################################\n";
			print "\t\t\t\t\t ALL THE COMPILATION IS PASSED								\n";
			print "#################################################################################################\n";
			print "#################################################################################################\n";
		}
	}
}

sub PAL_FDD_Compliation(@)
{
	my ( $BUILD_DIR ) = @_;
	chomp $BUILD_DIR ;
	if (chdir "$BUILD_DIR/src/enbapp/build" == 0 )
	{
		print "$BUILD_DIR/enbapp/build dir doesnt exits\n";
		exit;
	}
	else
	{
	
		print "Start compilation for product PAL_FDD\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART PAL FDD COMPILATION with OAM							\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		my $brcmstatus = system ( "make lnxsplit_oam -j &> $BUILD_DIR/lnxsplit_oam.log");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART PAL FDD Clean COMPILATION															  \n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make lnxclean_all &> $BUILD_DIR/lnxclean_all.log");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART PAL FDD COMPILATION without OAM							\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		my $status = system ("make lnxsplit &> $BUILD_DIR/lnxsplit.log");
		chomp $status ;
		chomp $brcmstatus;
		if ( $status != 0 or $brcmstatus != 0 )
		{
			print "shipment compilation of all source code is failed\n";
	    	print "please check ... \n";
  	 		exit;
		}
		else
		{
			print "#################################################################################################\n";
			print "#################################################################################################\n";
			print "\t\t\t\t\t ALL THE COMPILATION IS PASSED								\n";
			print "#################################################################################################\n";
			print "#################################################################################################\n";
		}
	}
}
sub T3300_TDD_Compliation(@)
{
	my ( $BUILD_DIR ) = @_;
	chomp $BUILD_DIR ;
	if (chdir "$BUILD_DIR/src/enbapp/build" == 0 )
	{
		print "$BUILD_DIR/enbapp/build dir doesnt exits\n";
		exit;
	}
	else
	{
		print "Start compilation for product T3300_FDD\n";
		system (". $BUILD_DIR/src/enbapp/build/setVar.sh");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART OAM COMPILATION									\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_clean_all");
		system ( "make t33h_oam &> $BUILD_DIR/msoambuild.log");
		`ls $BUILD_DIR/bin/rsys/bin/oam`;
		my $oamstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART ENB_CNM COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_enb_cnm &> $BUILD_DIR/cnmbuild.log");
		`ls $BUILD_DIR/bin/rsys/bin/enodeb_radio`;
		my $enodeb_radio = `echo $?`;
		`ls $BUILD_DIR/bin/rsys/bin/enodeb_net`;
		my $enodeb_net = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART REMAPP COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_remapp &> $BUILD_DIR/remappbuild.log");
		`ls $BUILD_DIR/libs/rem`;
		my $remstatus = `echo $?`;
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART REMLIB COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_remlib &> $BUILD_DIR/rembuild.log");
		`ls $BUILD_DIR/libs/librem.a`;
		my $remlibstatus = `echo $?`;
		#system ("make t33h_clean_all | tee $BUILD_DIR/t33h_clean_all.log");
		system ("make t33h_clean | tee $BUILD_DIR/t33h_clean_all.log");
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		print "\t\t\t\t\tSTART T2K_INT COMPILATION								\n";
		print "#################################################################################################\n";
		print "#################################################################################################\n";
		system ("make t33h_int &> $BUILD_DIR/t33h_intbuild.log");
		`ls $BUILD_DIR/bin/rsys_withoutoam/enodeb_net`;
		my $t2kstatus = `echo $?`;
		`ls $BUILD_DIR/bin/rsys_withoutoam/enodeb_radio`;
		my $t3kradiostatus = `echo $?`;
		chomp $oamstatus ; chomp $enodeb_radio; chomp $enodeb_net ; chomp $remstatus; chomp $remlibstatus ; chomp $t2kstatus ; chomp $t3kradiostatus;
		if ( $oamstatus != 0 or $enodeb_radio != 0 or $enodeb_net != 0 or $remstatus != 0 or $remlibstatus != 0 or $t2kstatus != 0 or $t3kradiostatus !=0)
		{
			print "shipment compilation of all source code is failed\n";
	    		print "please check ... \n";
  	 		exit;
		}
		else
		{
			print "#################################################################################################\n";
			print "#################################################################################################\n";
			print "\t\t\t\t\t ALL THE COMPILATION IS PASSED								\n";
			print "#################################################################################################\n";
			print "#################################################################################################\n";
		}
	}
}

