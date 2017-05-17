/*
 * dihat-ho-manager.cpp
 *
 *  Created on: 2015. 1. 2.
 *      Author: chen
 */

/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010,2011,2012,2013 TELEMATICS LAB, Politecnico di Bari
 *
 * This file is part of LTE-Sim
 *
 * LTE-Sim is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation;
 *
 * LTE-Sim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LTE-Sim; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Francesco Capozzi <f.capozzi@poliba.it>
 */

#include "dihat-ho-manager.h"
#include "../../../device/NetworkNode.h"
#include "../../../device/UserEquipment.h"
#include "../../../device/ENodeB.h"
#include "../../../device/HeNodeB.h"
#include "../../../componentManagers/NetworkManager.h"
#include "../../../core/spectrum/bandwidth-manager.h"
#include "../../../phy/lte-phy.h"
#include "../../../utility/ComputePathLoss.h"

// added file, 20150102

DihatHoManager::DihatHoManager()
{
	m_target = NULL;
}

DihatHoManager::~DihatHoManager()
{
	m_target = NULL;
}

bool DihatHoManager::CheckHandoverNeed(UserEquipment* ue)
{
	NetworkNode *targetNode = ue->GetTargetNode();

	double TXpower =
			10
					* log10(
							pow(10.,
									(targetNode->GetPhy()->GetTxPower() - 30)
											/ 10)
									/ targetNode->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size());
	double pathLoss = ComputePathLossForInterference(targetNode, ue);
	double targetRXpower = TXpower - pathLoss;

	double probable_TXpower = 0.0;
	double probable_pathLoss = 0.0;
	double probable_RXpower = 0.0;

	double it_TXpower = 0.0;
	double it_pathLoss = 0.0;
	double it_RXpower = 0.0;

	double HOM = 2;
	double TTT_threshold = 0.16;

	double FDIF_threshold = HOM;
	double alfa = 0.01 / TTT_threshold;		// alfa = Tm/Tu = TTI/TTT

	std::vector<ENodeB*> *listOfNodes =
			NetworkManager::Init()->GetENodeBContainer();
	std::vector<ENodeB*>::iterator it;

	double RSRPDIF;			// difference between target node and serving node
	double FRSRPDIF;// filter difference between target node and serving node

	double HOMDIF;// HOMDIF = (RSRPT(t) - RSRPS(t) - HOM) - (RSRPT(t-1) - RSRPS(t-1) - HOM)
	double FHOMDIF;			// filtered HOMDIF
	double ratio;			// ratio = filtered_HOMDIF(t) / filtered_HOMDIF(t-1)

	/*
	 ENodeB *probableNewTargetNode = (*(listOfNodes->begin()));
	 */

	ENodeB *probableNewTargetNode = (ENodeB*) targetNode;
	probable_TXpower =
			10
					* log10(
							pow(10.,
									(probableNewTargetNode->GetPhy()->GetTxPower()
											- 30) / 10)
									/ probableNewTargetNode->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size());
	probable_pathLoss = ComputePathLossForInterference(probableNewTargetNode,
			ue);
	probable_RXpower = probable_TXpower - probable_pathLoss;

	// find the probableNewTargetNode with the highest power within Init()->GetENodeBContainer()
	for (it = listOfNodes->begin(); it != listOfNodes->end(); it++)
	{
		it_TXpower =
				10
						* log10(
								pow(10.,
										((*it)->GetPhy()->GetTxPower() - 30)
												/ 10)
										/ (*it)->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size());
		it_pathLoss = ComputePathLossForInterference((*it), ue);

		it_RXpower = it_TXpower - it_pathLoss;

		if (it_RXpower > probable_RXpower)
		{
			probable_RXpower = it_RXpower;
			probableNewTargetNode = (*it);
		}

	}

	// CheckHandoverNeed process
	if (probableNewTargetNode->GetIDNetworkNode()
			!= targetNode->GetIDNetworkNode())
	{

		// calculate the RSRP difference and filtered RSRP difference
		RSRPDIF = probable_RXpower - targetRXpower;
		FRSRPDIF = alfa * RSRPDIF
				+ (1 - alfa) * probableNewTargetNode->GetFRSRPDIF();

		// if event A3 condition is satisfied,
		if (FRSRPDIF > FDIF_threshold)// if (probable_RXpower >= targetRXpower + HOM)
		{

			if (probableNewTargetNode->GetTTTcounter() == 0)
			{
				// if current probableNewTargetNode is the first time to be potential targetNode,
				// then add m_TTTcounter in probableNewTargetNode and set ue's m_previousProbableNewTargetNode to be probableNewTargetNode

				probableNewTargetNode->AddTTTcounter();
				ue->SetPreviousProbableNewTargetNode(probableNewTargetNode);
			}
			else if (ue->GetIDofPreviousProbableNewTargetNode()
					== probableNewTargetNode->GetIDNetworkNode())
			{
				// if current probableNewTargetNode is not the first time to be potential targetNode,
				// then we should guarantee that current probableNewTargetNode is the same with previous probableNewTargetNode,
				// so that we add m_TTTcounter in probableNewTargetNode
				// otherwise, we should do third part

				probableNewTargetNode->AddTTTcounter();
				ue->SetPreviousProbableNewTargetNode(probableNewTargetNode);
			}
			else
			{
				// if current probableNewTargetNode is not the same with previous probableNewTargetNode,
				// then we should reset m_TTTcounter in previous probableNewTargetNode to be zero

				ue->GetPreviousProbableNewTargetNode()->ResetTTTcounter();
				probableNewTargetNode->AddTTTcounter();
				ue->SetPreviousProbableNewTargetNode(probableNewTargetNode);
			}

			HOMDIF = probable_RXpower - targetRXpower - HOM;
			FHOMDIF = alfa * HOMDIF
					+ (1 - alfa) * probableNewTargetNode->GetFHOMDIF1();

			if (probableNewTargetNode->GetTTTcounter() == 0)
			{
				probableNewTargetNode->SetHOMDIF(HOMDIF);
				probableNewTargetNode->SetFHOMDIF2(
						probableNewTargetNode->GetFHOMDIF1());
				probableNewTargetNode->SetFOMDIF1(FHOMDIF);

				ratio = 0.0;
			}
			else
			{
				ratio = FHOMDIF
						/ (alfa * probableNewTargetNode->GetHOMDIF()
								+ (1 - alfa)
										* probableNewTargetNode->GetFHOMDIF2());

				probableNewTargetNode->SetHOMDIF(HOMDIF);
				probableNewTargetNode->SetFHOMDIF2(
						probableNewTargetNode->GetFHOMDIF1());
				probableNewTargetNode->SetFOMDIF1(FHOMDIF);
			}

			if (((FHOMDIF > alfa * HOM) && ratio > alfa)
					|| probableNewTargetNode->GetTTTcounter() >= TTT_threshold)
			{
				targetRXpower = probable_RXpower;
				targetNode = probableNewTargetNode;
			}

		}
		else
		{
			probableNewTargetNode->ResetTTTcounter();
		}
	}

	if (ue->GetTargetNode()->GetIDNetworkNode()
			!= targetNode->GetIDNetworkNode())
	{
		m_target = targetNode;
		for (it = listOfNodes->begin(); it != listOfNodes->end(); it++)
		{
			(*it)->ResetTTTcounter();
		}
		return true;
	}
	else
	{
		return false;
	}

}

