/*
 * SinrOfUEFromSpecificEnode.h
 *
 *  Created on: 2015. 1. 2.
 *      Author: chen
 */

#ifndef SINROFUEFROMSPECIFICENODE_H_
#define SINROFUEFROMSPECIFICENODE_H_

// added file, 20150102
// function to obtain the SINR of UE from each eNode
#include "../device/ENodeB.h"
#include "../device/UserEquipment.h"
#include "../utility/ComputePathLoss.h"
#include "../phy/ue-lte-phy.h"
#include "../phy/enb-lte-phy.h"
#include "../phy/interference.h"
#include "math.h"

/*
 * Noise is computed as follows:
 *  - noise figure = 2.5
 *  - n0 = -174 dBm
 *  - sub channel bandwidth = 180 kHz
 *
 *  noise_db = noise figure + n0 + 10log10 (180000) - 30 = -148.95
 */
#define NOISE -148.95

static double ComputeSINRBetweenUEandEnodeB(UserEquipment* ue, ENodeB* enb) {
	// compute the received power of UE from enb
	double TXpower =
			10
					* log10(
							pow(10., (enb->GetPhy()->GetTxPower() - 30) / 10)
									/ enb->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size());
	double pathLoss = ComputePathLossForInterference(enb, ue);
	double targetRXpower = TXpower - pathLoss;

	//compute noise + interference
	double interference;
	if (enb->GetPhy()->GetInterference() != NULL) {
		interference = enb->GetPhy()->GetInterference()->ComputeInterference(ue);
	} else {
		interference = 0;
	}

	double noise_interference = 10.
			* log10(pow(10., NOISE / 10) + interference); // dB

	double SINR = (double)(targetRXpower / noise_interference);

	return SINR;
}

#endif /* SINROFUEFROMSPECIFICENODE_H_ */
