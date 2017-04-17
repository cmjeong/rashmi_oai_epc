#!/bin/sh
ProtectedBranch='master'
TopLevelDir=`git rev-parse --show-toplevel`
BuildPath=$TopLevelDir/build/
BuildPathBrcm=$BuildPath/brcm
BuildPathIntel=$BuildPath/intel
AcceptancePath=$TopLevelDir/src/acceptance/
BuildTargetFile=$BuildPath/targetbuild.txt
CurrentBranch=$(git symbolic-ref HEAD | sed -e 's,.*/\(.*\),\1,')
AccChangedFile=( $( git diff $CurrentBranch origin/$CurrentBranch --name-only | awk -F"/"  '{print $NF}' ) )
Commits=`git log @{u}..`
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#echo "File Name is $BuildTargetFile \n Current Branch is $current_branch \n AnyCommit is $Commits \n"
#******************************************************************************************************
function Xta_Compilation {
	Applicationinfo=$1
	PlatformInfo=$2
	AcceptanceLayer=( egtpu-eg enbapp-wr ltemac-rg ltepdcp-pj lterlc-kw lterrc-nh lterrm-rm lteson-nl s1ap-sz sctp-sb tucl-hi x2ap-cz )
	for i in "${AcceptanceLayer[@]}"
	do
	        ProductName=`echo $i | awk -F"-" '{print $1}'`
		ChildPrefix=`echo $i | awk -F"-" '{print $2}'`
		if [ $ProductName = 'ltemac' ]; then
			echo "This is LTEMAC"
		else
			cd $AcceptancePath/$ProductName/
			( $(make -f $ChildPrefix\.mak BLDENV=lnx_acc >& ${ProductName}_${ChildPrefix}_build.log) )
			if [ "$?" != "0" ];then
				exit 1
			else
				exit 0
			fi
		fi
	done
}
function ResultAnalysis {
	AcceptancePath=$1
	ExecutableName=$2
	TotalCount=$3
	TestResultFile=testReport.txt
	cd $AcceptancePath
	rm -f $TestResultFile
	while true:
	do
		count=`cat $TestResultFile | wc -l`
                FailedCount=( $(cat $TestResultFile | awk '{print $11}') )
                TestResult=( $(cat $TestResultFile | awk '{print $1$2$3"\t"$9$10$11}') )
                if [[ $ExecutableName =~ /eg_/ ]]; then
                        if [ $count -eq $TotalCount ]; then
                                for failedtest in "${FailedCount[@]}"
                                do
                                        if [ $failedtest -gt 0 ]; then
                                                echo "\n" "Below Test Cases Are Failed" "\n"
                                                echo "$TestResult[@}"
                                                exit 1
                                        else
                                                echo "All Test Cases Are Passed For $j"
                                                exit 0
                                        fi
                                done
                        fi
                fi
	done
}
function Xta_Execution {
	Applicationinfo=$1
        PlatformInfo=$2
	EGTPRunningStatus="NOTDONE"
	MACRunningStatus="NOTDONE"
	PDCPunningStatus="NOTDONE"
	ENBRunningStatus="NOTDONE"
	RRCRunningStatus="NOTDONE"
	SONRunningStatus="NOTDONE"
	S1APRunningStatus="NOTDONE"
	RLOGRunningStatus="NOTDONE"
	SCTPRunningStatus="NOTDONE"
	TUCLRunningStatus="NOTDONE"
	X2ApRunningStatus="NOTDONE"
	RLCRunningStatus="NOTDONE"
	RRMRunningStatus="NOTDONE"
	for i in "${AccChangedFile[@]}"
	do 
		MatchFile=( $( grep $i $TopLevelDir/tools/AccFiles/*) )
		ModuleName=( $(echo $MatchFile | awk -F"/" '{print $NF}') )
		ActualModuleName=( $(echo $ModuleName | awk -F":" '{print $1}') )
		for j in "${ActualModuleName[@]}"
		do
			if [ $j == 'egtpu' ]; then
				if [ $EGTPRunningStatus != 'done' ]; then
				GroupCount=1
				BinaryName=eg_acc
				AcceptanceDir=$TopLevelDir/src/acceptance/$j
				cd $AcceptanceDir
				for grp in {1..3}; 
				do
					./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
				done
				ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
        	                EGTPRunningStatus=done
                	        fi
                	fi
			if [ $j == 'ltemac' ]; then
                                if [ $MACRunningStatus != 'done' ]; then
                                GroupCount=1
                                BinaryName=rg_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                MACRunningStatus=done
                                fi
                        fi
			if [ $j == 'ltepdcp' ]; then
                                if [ $PDCPunningStatus!= 'done' ]; then
                                GroupCount=1
                                BinaryName=pj_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                PDCPunningStatus=done
                                fi
                        fi
                        if [ $j == 'enbapp' ]; then
                                if [ $ENBRunningStatus != 'done' ]; then
                                GroupCount=1
                                BinaryName=wr_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                ENBRunningStatus=done
                                fi
                        fi
                        if [ $j == 'lterrc' ]; then
                                if [ $RRCRunningStatus != 'done' ]; then
                                GroupCount=1
                                BinaryName=nh_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                RRCRunningStatus=done
                                fi
                        fi
                        if [ $j == 'lterrm' ]; then
                                if [ $RRMRunningStatus != 'done' ]; then
                                GroupCount=1
                                BinaryName=rm_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                RRMRunningStatus=done
                                fi
                        fi
                        if [ $j == 'lteson' ]; then
                                if [ $SONRunningStatus != 'done' ]; then
                                GroupCount=1
                                BinaryName=nl_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                SONRunningStatus=done
                                fi
                        fi
                        if [ $j == 'rlog' ]; then
                                if [ $RLOGRunningStatus != 'done' ]; then
                                RLOGRunningStatus=done
                                GroupCount=1
                                BinaryName=rl_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                fi
                        fi
                        if [ $j == 's1ap' ]; then
                                if [ $S1ApRunningStatus != 'done' ]; then
                                S1APRunningStatus=done
                                GroupCount=1
                                BinaryName=sz_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                fi
                        fi
                        if [ $j == 'sctp' ]; then
                                if [ $SCTPRunningStatus != 'done' ]; then
                                SCTPRunningStatus=done
                                GroupCount=1
                                BinaryName=sb_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                fi
                        fi
                        if [ $j == 'tucl' ]; then
                                if [ $TUCLRunningStatus != 'done' ]; then
                                GroupCount=1
                                BinaryName=hi_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                TUCLRunningStatus=done
                                fi
                        fi
                        if [ $j == 'lterlc' ]; then
                                if [ $RLCRunningStatus != 'done' ]; then
                                GroupCount=1
                                BinaryName=rl_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                RLCRunningStatus=done
                                fi
                        fi
                        if [ $j == 'x2ap' ]; then
                                if [ $X2APRunningStatus != 'done' ]; then
                                GroupCount=1
                                BinaryName=cz_acc
                                AcceptanceDir=$TopLevelDir/src/acceptance/$j
                                cd $AcceptanceDir
                                for grp in {1..3};
                                do
                                        ./$BinaryName -g $grp -o ${BinaryName}_group_$grp.log 2>&1 &
                                done
                                ResultAnalysis $AcceptanceDir $BinaryName $GroupCount
                                X2APRunningStatus=done
                                fi
                        fi
			done
	done
	
}
function local_build {
	Applicationinfo=$1
	PlatformInfo=$2
	if [ $Applicationinfo = 'BRDCM' ]; then
		cd $BuildPathBrcm
		#WithOutOAM=$(make tenb MODE=${PlatformInfo} OAM_ENABLE=NO >& ${Applicationinfo}_${PlatformInfo}_build.log);
		( $(make tenb MODE=${PlatformInfo} OAM_ENABLE=NO >& ${Applicationinfo}_${PlatformInfo}_build.log) )
		#echo "$Applicationinfo With Out OAM Build Status is $?"
		if [ $? == 0 ]; then
			( $(make tenb MODE=${PlatformInfo} OAM_ENABLE=YES >& ${Applicationinfo}_${PlatformInfo}_build.log) )
			if [ $? == 0 ]; then
				echo "$Applicationinfo With and WithOut OAM Build Status is PASSED"
				Xta_Compilation $Applicationinfo $PlatformInfo
				Xta_Execution $Applicationinfo $PlatformInfo
			else 	
				echo "$Applicationinfo $PlatformInfo With OAM build is Failing ... Due to This push Opreation is also Failed"
				exit 1
			fi
		else 
			echo "$Applicationinfo $PlatformInfo WithOut OAM build is Failing ... Due to This push Opreation is also Failed"
			exit 1
		fi
	elif [ $Applicationinfo = 'T22' ]; then
		cd $BuildPathIntel
		#if [ $PlatformInfo = 'FDD' ]; then
		WithOutOAM=$(make tenb OAM_ENABLE=NO -j >& ${Applicationinfo}_${PlatformInfo}_build.log);
		echo "$Applicationinfo With Out OAM Build Status is $?"
		if [ "$WithOutOAM" == 0 ]; then
			WithOAMBuild=$(make tenb_oam OAM_ENABLE=YES -j >& ${Applicationinfo}_${PlatformInfo}_build.log);
			Xta_Compilation $Applicationinfo $PlatformInfo
			Xta_Execution $Applicationinfo $PlatformInfo
			if [ "$WithOAMBuild" == 0 ]; then
				exit 0
			else
				echo "$Applicationinfo $PlatformInfo With OAM build is Failing ... Due to This push Opreation is also Failed"
				exit 1
			fi
		else 
			echo "$Applicationinfo $PlatformInfo WithOut OAM build is Failing ... Due to This push Opreation is also Failed"
			exit 1
		fi
	elif [ $Applicationinfo = 'T33' ]; then
		cd $BuildPathIntel
                WithOutOAM=$(make tenb BOARD=T33H >& ${Applicationinfo}_${PlatformInfo}_build.log);
		echo "$Applicationinfo With Out OAM Build Status is $WithOutOAM"
                if [ "$WithOutOAM" == 0 ]; then
                        WithOAMBuild=$(make tenb_oam BOARD=T33H >& ${Applicationinfo}_${PlatformInfo}_build.log);
			Xta_Compilation $Applicationinfo $PlatformInfo
			Xta_Execution $Applicationinfo $PlatformInfo
                        if [ "$WithOAMBuild" == 0 ]; then
                                exit 0
                        else
                                echo "$Applicationinfo $PlatformInfo With OAM build is Failing ... Due to This push Opreation is also Failed"
                                exit 1
                        fi
                else
                        echo "$Applicationinfo $PlatformInfo WithOut OAM build is Failing ... Due to This push Opreation is also Failed"
                        exit 1
                fi
	else 
		echo "Unknown Option | OR | NOT Able to Find Specific Platform"
		exit 1
	fi
}
if [[ $CurrentBranch = $ProtectedBranch ]]; then
	echo "NOT Allowing to PUSH any thing Over Master Branch\n"
	exit 1;
else 
	echo "CURRENT BRANCH is ==> $CurrentBranch"
	while IFS= read -r line
	do 
		ApplicationName=`echo $line | cut -d' ' -f1`
		PlatformName=`echo $line | cut -d' ' -f2`
		case $ApplicationName in
			BRDCM)
				local_build $ApplicationName $PlatformName
				;;
			T22|T33)
				local_build $ApplicationName $PlatformName
				;;
			*)
				echo "Seems ... Never Expected this Option"
				;;
		esac
	done < "$BuildTargetFile"
fi
exit 0
