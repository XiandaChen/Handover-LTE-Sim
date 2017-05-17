/*
 * SortEnodesListAccordingReceivedPower.h
 *
 *  Created on: 2015. 1. 8.
 *      Author: chen
 */

#ifndef SORTENODESLISTACCORDINGRECEIVEDPOWER_H_
#define SORTENODESLISTACCORDINGRECEIVEDPOWER_H_

// added file, 20150108
// to sort the list of eNBs according to the power strength UE detects from each eNB
// the new list is used to make handover decision with A3-event sequentially
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
#include "GetTargetReceivedPowerFromEnode.h"
#include "math.h"

std::vector<ENodeB*> * SortEnodesListAccordingReceivedPower (UserEquipment* ue, std::vector<ENodeB*> *listOfNodes)
{
	std::vector<ENodeB*>::iterator it;
	std::vector<ENodeB*>::iterator jt;
	ENodeB* temp;
	for (it = listOfNodes->begin(); it != listOfNodes->end(); it++)
	{
		for (jt = (listOfNodes->end() - 1); jt >= (it + 1); jt--)
		{
			if (GetTargetReceivedPowerFromEnode(ue, *jt) < GetTargetReceivedPowerFromEnode(ue, *(jt-1)))
			{
				temp = *jt;
				*jt =  *(jt-1);
				*(jt-1) = temp;
			}
		}
	}
	return listOfNodes;
}



#endif /* SORTENODESLISTACCORDINGRECEIVEDPOWER_H_ */
