# parameters 1 MINUSERS, 2 MAXUSERS, 3 INTERVAL, 4 FULENAME, 5 FILE, 6 NUMSIM, 7 FILE-NAME-PLOT

FILE=$5	#OUTPUT FULE NAME
NUMSIM=$6	#SIMULATIONS NUMBER
FILENAME=$4

TOTALNAME3=""
TOTALNAME30=""
TOTALNAME120=""
TOTALNAME200=""
TOTALNAME300=""

HOTYPE1=1       # Stands for the standard Hard HO
HOTYPE2=2       # Stands for the SINR-threshold HO
HOTYPE3=3       # Stands for the Proposed HO 

time=75


        # GRAPHIC FOR 3kmph of the standard Hard HO
        COUNT=1
        NBUE=$1
        until [ $NBUE -gt $2 ]; do
                COUNT=1
                until [ $COUNT -gt $NUMSIM ]; do
                TOTALNAME3=$FILE"_"$COUNT"_"$FILENAME"_3kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"
		grep "SUCCESSFUL_HANDOVER"   $TOTALNAME3  | awk '{print $4 $6}' > HOType1_HOMoment_3kmph_$FILE_$COUNT_"UE"_$NBUE_$8_$7.xlsx
                grep "SUCCESSFUL_HANDOVER"   $TOTALNAME3  | awk '{print $6}'  > tmp
                ./compute_meanTime.sh tmp >> temporal
                rm tmp
                 let COUNT=COUNT+1
                done
                ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 3kmph_HOType1_$8_$7.xlsx
                rm temporal
        let NBUE=NBUE+$3
        done

	# For 30kmph
        COUNT=1
        NBUE=$1
        until [ $NBUE -gt $2 ]; do
                COUNT=1
                until [ $COUNT -gt $NUMSIM ]; do
                TOTALNAME30=$FILE"_"$COUNT"_"$FILENAME"_30kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"
		grep "SUCCESSFUL_HANDOVER"   $TOTALNAME30  | awk '{print $4 $6}' > HOType1_HOMoment_30kmph_$FILE_$COUNT_"UE"_$NBUE_$8_$7.xlsx
                grep "SUCCESSFUL_HANDOVER"   $TOTALNAME30  | awk '{print $6}'  > tmp
                ./compute_meanTime.sh tmp >> temporal
                rm tmp
                 let COUNT=COUNT+1
                done
                ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 30kmph_HOType1_$8_$7.xlsx
                rm temporal
        let NBUE=NBUE+$3
        done


        # loop for 120kmph scenario
        COUNT=1
        NBUE=$1
        until [ $NBUE -gt $2 ]; do
                COUNT=1
                until [ $COUNT -gt $NUMSIM ]; do
                TOTALNAME120=$FILE"_"$COUNT"_"$FILENAME"_120kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"
		grep "SUCCESSFUL_HANDOVER"   $TOTALNAME120  | awk '{print $4 $6}' > HOType1_HOMoment_120kmph_$FILE_$COUNT_"UE"_$NBUE_$8_$7.xlsx
                grep "SUCCESSFUL_HANDOVER"   $TOTALNAME120  | awk '{print $6}'  > tmp
                ./compute_meanTime.sh tmp >> temporal
                rm tmp
                 let COUNT=COUNT+1
                done
                ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 120kmph_HOType1_$8_$7.xlsx
                rm temporal
        let NBUE=NBUE+$3
        done


        # loop for 200kmph scenario
        COUNT=1
        NBUE=$1
        until [ $NBUE -gt $2 ]; do
                COUNT=1
                until [ $COUNT -gt $NUMSIM ]; do
                TOTALNAME200=$FILE"_"$COUNT"_"$FILENAME"_200kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"
                grep "SUCCESSFUL_HANDOVER"   $TOTALNAME200  | awk '{print $4 $6}' > HOType1_HOMoment_200kmph_$FILE_$COUNT_"UE"_$NBUE_$8_$7.xlsx
                grep "SUCCESSFUL_HANDOVER"   $TOTALNAME200  | awk '{print $6}'  > tmp
                ./compute_meanTime.sh tmp >> temporal
                rm tmp
                 let COUNT=COUNT+1
                done
                ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 200kmph_HOType1_$8_$7.xlsx
                rm temporal
        let NBUE=NBUE+$3
        done


        # loop for 300kmph scenario
        COUNT=1
        NBUE=$1
        until [ $NBUE -gt $2 ]; do
                COUNT=1
                until [ $COUNT -gt $NUMSIM ]; do
                TOTALNAME300=$FILE"_"$COUNT"_"$FILENAME"_300kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"
		grep "SUCCESSFUL_HANDOVER"   $TOTALNAME300  | awk '{print $4 $6}' > HOType1_HOMoment_300kmph_$FILE_$COUNT_"UE"_$NBUE_$8_$7.xlsx
                grep "SUCCESSFUL_HANDOVER"   $TOTALNAME300  | awk '{print $6}'  > tmp
                ./compute_meanTime.sh tmp >> temporal
                rm tmp
                 let COUNT=COUNT+1
                done
                ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 300kmph_HOType1_$8_$7.xlsx
                rm temporal
        let NBUE=NBUE+$3
        done


echo  Average-Handover $7 REPORT FINISHED!!
