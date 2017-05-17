/*
 * GetTargetENodeUsingMCDM.h
 *
 *  Created on: 2015. 1. 5.
 *      Author: chen
 */

#ifndef GETTARGETENODEUSINGMCDM_H_
#define GETTARGETENODEUSINGMCDM_H_

#include "../device/ENodeB.h"
#include "../device/UserEquipment.h"
#include "../componentManagers/NetworkManager.h"
#include "AngleOfEnodeAndUE.h"
#include "DistanceOfEnodeAndUE.h"
#include "RsrpFromEnodeToUE.h"
#include "SinrOfUEFromSpecificEnode.h"
#include "ComputerNormalizedValue.h"
#include "GetMaximumValue.h"
#include "GetMinimumValue.h"
#include "GetIDofMaximumValue.h"
#include "math.h"

// added file, 20150103
// obtain the ID number of the target eNB using the Multi-Criteria Decision Making (TOPSIS)
static int
GetTargetENodeUaingMCDM(UserEquipment* ue, double * weight)
{
	std::vector<ENodeB*> *listOfNodes =
					NetworkManager::Init()->GetENodeBContainer();
	std::vector<ENodeB*>::iterator it;

	// angle vector, containing the angles of eNB-UEprePosition-UEcurPosition
	double angles[91] = { 0 };
	// distance vector, containing the distances of eNB and UE-at-current-Position
	double dists[91] = { 0 };
	// SINR vector, containing the SINRs of UE (after position update, namely at current position) received from eNBs
	double sinrs[91] = { 0 };
	// RSRP vector, containing the RSRPs of UE (after position update, namely at current position) received from eNBs
	double rsrps[91] = { 0 };
	int index = 0;
	for (it = listOfNodes->begin(); it != listOfNodes->end(); it++) {
		angles[index] = ComputeAngleBetweenUEandEnodeB(ue, *it);
		dists[index] = ComputeDistanceBetweenUEandEnodeB(ue, *it);
		sinrs[index] = ComputeSINRBetweenUEandEnodeB(ue, *it);
		rsrps[index] = ComputeRSRPBetweenUEandEnodeB(ue, *it);

		++index;
	}

	// construct the normalized decision matrix
	// normalized angle vector
	double anglesNor[91] = { 0 };
	// normalized distance vector
	double distsNor[91] = { 0 };
	// normalized SINR vector
	double sinrsNor[91] = { 0 };
	// normalized RSRP vector
	double rsrpsNor[91] = { 0 };
	double normalAnlge = ComputerNormalizedValue(angles);
	double normalDist = ComputerNormalizedValue(dists);
	double normalSinr = ComputerNormalizedValue(sinrs);
	double normalRsrp = ComputerNormalizedValue(rsrps);
	for (int i = 0; i < 91; i++) {
		anglesNor[i] = (double) angles[i] / normalAnlge;
		distsNor[i] = (double) dists[i] / normalDist;
		sinrsNor[i] = (double) sinrs[i] / normalSinr;
		rsrpsNor[i] = (double) rsrps[i] / normalRsrp;
	}

	// multiple each normalized value by weight wi
	// weighted normalization
	double anglesWei[91] = { 0 };
	double distsWei[91] = { 0 };
	double sinrsWei[91] = { 0 };
	double rsrpsWei[91] = { 0 };
	for (int i = 0; i < 91; i++) {
		anglesWei[i] = anglesNor[i] * weight[0];
		distsWei[i] = distsNor[i] * weight[1];
		sinrsWei[i] = sinrsNor[i] * weight[2];
		rsrpsWei[i] = rsrpsNor[i] * weight[3];
	}

	// determine the ideal solution
	double idealSolution[4] = { 0 };
	idealSolution[0] = GetMinimumValue(anglesWei);
	idealSolution[1] = GetMinimumValue(distsWei);
	idealSolution[2] = GetMaximumValue(sinrsWei);
	idealSolution[3] = GetMaximumValue(rsrpsWei);

	// determine the negative ideal solution
	double nidealSolution[4] = { 0 };
	nidealSolution[0] = GetMaximumValue(anglesWei);
	nidealSolution[1] = GetMaximumValue(distsWei);
	nidealSolution[2] = GetMinimumValue(sinrsWei);
	nidealSolution[3] = GetMinimumValue(rsrpsWei);

	// determine separation from ideal solution
	double idealSeparation[91] = { 0 };
	for (int i = 0; i < 91; i++) {
		idealSeparation[i] = sqrt(
				pow((anglesWei[i] - idealSolution[0]), 2)
						+ pow((distsWei[i] - idealSolution[1]), 2)
						+ pow((sinrsWei[i] - idealSolution[2]), 2)
						+ pow((rsrpsWei[i] - idealSolution[3]), 2));
	}
	// determine separation from negative ideal solution
	double nidealSeparation[91] = { 0 };
	for (int i = 0; i < 91; i++) {
		nidealSeparation[i] = sqrt(
				pow((anglesWei[i] - nidealSolution[0]), 2)
						+ pow((distsWei[i] - nidealSolution[1]), 2)
						+ pow((sinrsWei[i] - nidealSolution[2]), 2)
						+ pow((rsrpsWei[i] - nidealSolution[3]), 2));
	}

	// calculate the relative closeness to the ideal solution
	double reCloss[91] = { 0 };
	for (int i = 0; i < 91; i++) {
		reCloss[i] = nidealSeparation[i]
				/ (nidealSeparation[i] + idealSeparation[i]);
	}

	// get the ID of the eNB which has the highest value of relative clossness
	int newTarget = GetIDofMaximumValue(reCloss);

	return newTarget;
}

#endif /* GETTARGETENODEUSINGMCDM_H_ */
