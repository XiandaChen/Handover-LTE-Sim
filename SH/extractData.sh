FILE="Sim"   #OUTPUT FILE NAME
NUMSIM=5  #Number of simulations
FILENAME="MultiCellWithBorderPicos"   # SIMULATION TYPE NAME
# modified
CELS=19       # NUMBER OF CELLS
MINUSERS=1
INTERVAL=1
MAXUSERS=5

# params of LTE-SIM MULTICEL
RADIUS=0.5 # Radius in Km
NBVOIP=1  # Number of Voip Flows
NBVIDEO=0 #Number of Video
NBBE=0 # Number of Best Effort Flows
NBCBR=0 #Number of CBR flows
#Scheduler Type PF=1, MLWDF=2 EXP= 3
SCHED_TYPE=1    # SCHEDULER TYPE
FRAME_STRUCT=1  # FDD or TDD
MAXDELAY=0.1
VIDEOBITRATE=128

TOTALNAME3_HO=""
TOTALNAME30_HO=""
TOTALNAME120_HO=""
TOTALNAME200_HO=""
TOTALNAME300_HO=""

# 1 stands for standard hard ho, 2 stands for SINR-threshold scheme, 3 stands for the proposed
HOTYPE=1

echo Start running simulation!


echo SIMULATION FINISHIED!
echo CREATING RESULTS REPORT!



# params 1 MINUSERS, 2 MAXUSERS, 3 INTERVAL, 4 FILENAME, 5 FILE, 6 NUMSIM,  7 TypeFlow, 8 Graphic_name

# result shells
./packet_loss_ratio.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VOIP Packet-Loss-Ratio
./goodput_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VOIP System-T
./delay_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VOIP Average-Packet-Delay
#./spectral_efficiency_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM Spectral-Efficiency Spec-Eff
#./fairnessIndex_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM  VIDEO Fairness-Index
#./fairnessIndex_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM  VOIP Fairness-Index
#./fairnessIndex_comp.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM  INF_BUF Fairness-Index
./average_HOs.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VOIP Average-Handover-per-Second
./average_HOs_differentType.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VOIP Average-Handover-of-different-hoType
./mean_time_between_ho.sh $MINUSERS $MAXUSERS $INTERVAL $FILENAME $FILE $NUMSIM VOIP MeanTime-between-HO



