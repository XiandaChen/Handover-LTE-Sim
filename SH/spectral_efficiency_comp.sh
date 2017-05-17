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

# params 1 MINUSERS, 2 MAXUSERS, 3 INTERVAL, 4 FILENAME, 5 FILE, 6 NUMSIM,  7 TYPE, 8 FILE_NAME_PLOT,

FILE=$5   #OUTPUT FILE NAME
NUMSIM=$6  #SIMULATIONS NUMBER
FILENAME=$4   # SIMULATION TYPE NAME
COUNT=1
CELS=19       # NUMBER OF CELLS
TOTALNAME=""

NBUE=$1 #Number of UE's
# variables for values

HOTYPE1=1
HOTYPE4=4

bandwidth=10000000 # setear en el archivo compute_spectral_efficiency
time=100 # setear en el archivocompute_spectral_efficiency

until [ $NBUE -gt $2 ]; do
	COUNT=1
	until [ $COUNT -gt $NUMSIM ]; do
	TOTALNAME=$FILE"_"$COUNT"_"$FILENAME"_3kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"

	grep -i "^RX" $TOTALNAME |grep -iv "AM RLC"  | awk '{print $8+5}'  > tmp
	grep -i "^RX" $TOTALNAME |grep -i "AM RLC"  | awk '{print $4+5}'  >> tmp
	./compute_spectral_efficiency.sh tmp  >> temporal
	rm tmp
	 let COUNT=COUNT+1
	done
       ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 3kmph_HOType1_spectral_$8_$7.xlsx
	rm temporal


	COUNT=1
        until [ $COUNT -gt $NUMSIM ]; do
        TOTALNAME=$FILE"_"$COUNT"_"$FILENAME"_30kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"

        grep -i "^RX" $TOTALNAME |grep -iv "AM RLC"  | awk '{print $8+5}'  > tmp
        grep -i "^RX" $TOTALNAME |grep -i "AM RLC"  | awk '{print $4+5}'  >> tmp
        ./compute_spectral_efficiency.sh tmp  >> temporal
        rm tmp
         let COUNT=COUNT+1
        done
       ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 30kmph_HOType1_spectral_$8_$7.xlsx
        rm temporal

	COUNT=1
        until [ $COUNT -gt $NUMSIM ]; do
        TOTALNAME=$FILE"_"$COUNT"_"$FILENAME"_120kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE1"HO"".sim"

        grep -i "^RX" $TOTALNAME |grep -iv "AM RLC"  | awk '{print $8+5}'  > tmp
        grep -i "^RX" $TOTALNAME |grep -i "AM RLC"  | awk '{print $4+5}'  >> tmp
        ./compute_spectral_efficiency.sh tmp  >> temporal
        rm tmp
         let COUNT=COUNT+1
        done
       ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 120kmph_HOType1_spectral_$8_$7.xlsx
        rm temporal


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	COUNT=1
        until [ $COUNT -gt $NUMSIM ]; do
        TOTALNAME=$FILE"_"$COUNT"_"$FILENAME"_3kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE4"HO"".sim"

        grep -i "^RX" $TOTALNAME |grep -iv "AM RLC"  | awk '{print $8+5}'  > tmp
        grep -i "^RX" $TOTALNAME |grep -i "AM RLC"  | awk '{print $4+5}'  >> tmp
        ./compute_spectral_efficiency.sh tmp  >> temporal
        rm tmp
         let COUNT=COUNT+1
        done
       ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 3kmph_HOType4_spectral_$8_$7.xlsx
        rm temporal


        COUNT=1
        until [ $COUNT -gt $NUMSIM ]; do
        TOTALNAME=$FILE"_"$COUNT"_"$FILENAME"_30kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE4"HO"".sim"

        grep -i "^RX" $TOTALNAME |grep -iv "AM RLC"  | awk '{print $8+5}'  > tmp
        grep -i "^RX" $TOTALNAME |grep -i "AM RLC"  | awk '{print $4+5}'  >> tmp
        ./compute_spectral_efficiency.sh tmp  >> temporal
        rm tmp
         let COUNT=COUNT+1
        done
       ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 30kmph_HOType4_spectral_$8_$7.xlsx
        rm temporal

        COUNT=1
        until [ $COUNT -gt $NUMSIM ]; do
        TOTALNAME=$FILE"_"$COUNT"_"$FILENAME"_120kmph_"$NBUE"UE"$CELS"CELL"$HOTYPE4"HO"".sim"

        grep -i "^RX" $TOTALNAME |grep -iv "AM RLC"  | awk '{print $8+5}'  > tmp
        grep -i "^RX" $TOTALNAME |grep -i "AM RLC"  | awk '{print $4+5}'  >> tmp
        ./compute_spectral_efficiency.sh tmp  >> temporal
        rm tmp
         let COUNT=COUNT+1
        done
       ./compute_average.sh temporal | awk '{print "'$NBUE' "$1}' >> 120kmph_HOType4_spectral_$8_$7.xlsx
        rm temporal
#START ANOTHER ALGORITHM
#
#-----> Add code here
#
#END ANOTHER ALGORITHM
 let NBUE=NBUE+$3
done

#echo PF  >> results_$8_$7.ods
#echo Users Value  >> results_$8_$7.ods
#	grep  " " PF_Y1_$8_$7.dat  >> results_$8_$7.ods
#echo MLWDF  >> results_$8_$7.ods
#echo Users Value  >> results_$8_$7.ods
#	grep  " " MLWDF_Y1_$8_$7.dat  >> results_$8_$7.ods
#echo EXP-PF  >> results_$8_$7.ods
#echo Users Value  >> results_$8_$7.ods
#	grep  " " EXPPF_Y1_$8_$7.dat  >> results_$8_$7.ods

#./Graph1.sh $7_$8 PF_Y1_$8_$7.dat MLWDF_Y1_$8_$7.dat EXPPF_Y1_$8_$7.dat Cell-Spectral-Efficiency Users Spectral-Efficiency[bpsS]

#rm PF_Y1_$8_$7.dat 
#rm MLWDF_Y1_$8_$7.dat 
#rm EXPPF_Y1_$8_$7.dat 
echo  SPECTRAL EFFICIENCY REPORT FINISHED!! 





