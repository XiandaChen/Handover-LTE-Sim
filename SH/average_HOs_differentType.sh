# parameters 1 MINUSERS, 2 MAXUSERS, 3 INTERVAL, 4 FULENAME, 5 FILE, 6 NUMSIM, 7 FILE-NAME-PLOT

FILE=$5 #OUTPUT FULE NAME
NUMSIM=$6       #SIMULATIONS NUMBER
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
                grep "SUCCESSFUL_HANDOVER"   $TOTALNAME3  | awk '{print $1}'  > tmp
                ./compute_averageHO.sh tmp >> temporal
                rm tmp
                 let COUNT=COUNT+1
                done
                ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 3kmph_HOType1_$8_$7.xlsx
                rm temporal
        let NBUE=NBUE+$3
        done

