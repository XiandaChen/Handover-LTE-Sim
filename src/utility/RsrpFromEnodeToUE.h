/*
 * RsrpFromEnodeToUE.h
 *
 *  Created on: 2015. 1. 2.
 *      Author: chen
 */

#ifndef RSRPFROMENODETOUE_H_
#define RSRPFROMENODETOUE_H_


// added file, 20150102
// function to obtain the RSRP of UE from eNode
#include "../device/ENodeB.h"
#include "../device/UserEquipment.h"
#include "../utility/ComputePathLoss.h"
#include "math.h"

static double
ComputeRSRPBetweenUEandEnodeB (UserEquipment* ue, ENodeB* enb)
{
	double TXpower = 10
			* log10(
					pow(10., (enb->GetPhy()->GetTxPower() - 30) / 10)
							/ enb->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size());
	double pathLoss = ComputePathLossForInterference(enb, ue);
	double targetRXpower = TXpower - pathLoss;

	return targetRXpower;
}


#endif /* RSRPFROMENODETOUE_H_ */
