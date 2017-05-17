/*
 * GetTargetReceivedPower.h
 *
 *  Created on: 2015. 1. 8.
 *      Author: chen
 */

#ifndef GETTARGETRECEIVEDPOWER_H_
#define GETTARGETRECEIVEDPOWER_H_

// added file, 20150108
// to get the power UE detects for a eNB
#include "../device/NetworkNode.h"
#include "../device/UserEquipment.h"
#include "../device/ENodeB.h"
#include "../phy/lte-phy.h"
#include "ComputePathLoss.h"

static double GetTargetReceivedPowerFromEnode(UserEquipment* ue, ENodeB *targetNode)
{
	double TXpower =
			10
					* log10(
							pow(10.,
									(targetNode->GetPhy()->GetTxPower() - 30)
											/ 10)
									/ targetNode->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size());
	double pathLoss = ComputePathLossForInterference(targetNode, ue);
	double targetRXpower = TXpower - pathLoss;

	return targetRXpower;
}

#endif /* GETTARGETRECEIVEDPOWER_H_ */
