# Copyright (c) 2010 
# 
# This file is part of LTE-Sim
# LTE-Sim is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation;
# 
# LTE-Sim is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with LTE-Sim; if not, see <http://www.gnu.org/licenses/>.
#
# Author: Mauricio Iturralde <mauricio.iturralde@irit.fr, mauro@miturralde.com>

# params 1 MINUSERS, 2 MAXUSERS, 3 INTERVAL, 4 FILENAME, 5 FILE, 6 NUMSIM, 7 TYPE FLOW, 8 FILE_NAME_PLOT

FILE=$5   # OUTPUT FILE NAME
NUMSIM=$6  # SIMULATIONS NUMBER
FILENAME=$4   # SIMULATION TYPE NAME
CELS=19       # NUMBER OF CELLS

TOTALNAME3=""
TOTALNAME30=""
TOTALNAME120=""
TOTALNAME200=""
TOTALNAME300=""

# 75 second for a simulation round
time=75

	# bash until loop
HOTYPE1=1	# Stands for the standard Hard HO
HOTYPE2=2	# Stands for the SINR-threshold HO
HOTYPE3=3	# Stands for the Proposed HO 

        # GRAPHIC FOR 3kmph of the standard Hard HO
        COUNT=1
	NBUE=$1
	until [ $NBUE -gt $2 ]; do
		COUNT=1
		until [ $COUNT -gt $NUMSIM ]; do
		TOTALNAME3=$FILE"_"$COUNT"_"$FILENAME"_3kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"
		grep "RX "$7   $TOTALNAME3  | awk '{print $1}'  > tmp
		grep "TX "$7   $TOTALNAME3  | awk '{print $1}'  >> tmp
		./compute_plr.sh tmp >> temporal
		rm tmp
		 let COUNT=COUNT+1
		done
		./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 3kmph_HOType1_$8_$7.xlsx
		rm temporal
	let NBUE=NBUE+$3
	done


       # GRAPHIC FOR 30kmph of the standard Hard HO
	COUNT=1
	NBUE=$1
	until [ $NBUE -gt $2 ]; do
		COUNT=1
                until [ $COUNT -gt $NUMSIM ]; do
                TOTALNAME30=$FILE"_"$COUNT"_"$FILENAME"_30kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"
                grep "RX "$7   $TOTALNAME30  | awk '{print $1}'  > tmp
                grep "TX "$7   $TOTALNAME30  | awk '{print $1}'  >> tmp
                ./compute_plr.sh tmp >> temporal
                rm tmp
                 let COUNT=COUNT+1
                done
                ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 30kmph_HOType1_$8_$7.xlsx
                rm temporal
	let NBUE=NBUE+$3
        done


        # GRAPHIC FOR 120kmph of the standard Hard HO
	COUNT=1
	NBUE=$1
        until [ $NBUE -gt $2 ]; do
		COUNT=1
                until [ $COUNT -gt $NUMSIM ]; do
                TOTALNAME120=$FILE"_"$COUNT"_"$FILENAME"_120kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"
                grep "RX "$7   $TOTALNAME120  | awk '{print $1}'  > tmp
                grep "TX "$7   $TOTALNAME120  | awk '{print $1}'  >> tmp
                ./compute_plr.sh tmp >> temporal
                rm tmp
                 let COUNT=COUNT+1
                done
                ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 120kmph_HOType1_$8_$7.xlsx 
                rm temporal
	let NBUE=NBUE+$3
        done

        # GRAPHIC FOR 200kmph of the standard Hard HO
        COUNT=1
        NBUE=$1
        until [ $NBUE -gt $2 ]; do
                COUNT=1
                until [ $COUNT -gt $NUMSIM ]; do
                TOTALNAME200=$FILE"_"$COUNT"_"$FILENAME"_200kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"
                grep "RX "$7   $TOTALNAME200  | awk '{print $1}'  > tmp
                grep "TX "$7   $TOTALNAME200  | awk '{print $1}'  >> tmp
                ./compute_plr.sh tmp >> temporal
                rm tmp
                 let COUNT=COUNT+1
                done
                ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 200kmph_HOType1_$8_$7.xlsx 
                rm temporal
        let NBUE=NBUE+$3
        done

        # GRAPHIC FOR 120kmph of the standard Hard HO
        COUNT=1
        NBUE=$1
        until [ $NBUE -gt $2 ]; do
                COUNT=1
                until [ $COUNT -gt $NUMSIM ]; do
                TOTALNAME300=$FILE"_"$COUNT"_"$FILENAME"_300kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"
                grep "RX "$7   $TOTALNAME300  | awk '{print $1}'  > tmp
                grep "TX "$7   $TOTALNAME300  | awk '{print $1}'  >> tmp
                ./compute_plr.sh tmp >> temporal
                rm tmp
                 let COUNT=COUNT+1
                done
                ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 300kmph_HOType1_$8_$7.xlsx 
                rm temporal
        let NBUE=NBUE+$3
        done



# ./Graph1.sh $7_$8 PF_Y1_$8_$7.dat MLWDF_Y1_$8_$7.dat EXPPF_Y1_$8_$7.dat $7-Packet-Loss-Ratio Users PLR
 
# modified
##./Graph1.sh $7_$8 3kmph_HOType1_$8_$7.dat 3kmph_HOType2_$8_$7.dat 3kmph_HOType3_$8_$7.dat 3kmph_HOType4_$8_$7.dat\
##30kmph_HOType1_$8_$7.dat 30kmph_HOType2_$8_$7.dat 30kmph_HOType3_$8_$7.dat 30kmph_HOType4_$8_$7.dat\
##120kmph_HOType1_$8_$7.dat 120kmph_HOType2_$8_$7.dat 120kmph_HOType3_$8_$7.dat 120kmph_HOType4_$8_$7.dat\
##Packet-Loss-Ratio Users-per-Cell Packet-Loss-Ratio[%]


echo  PLR REPORT FINISHED!! 


