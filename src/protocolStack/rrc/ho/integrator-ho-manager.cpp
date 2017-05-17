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

#include "integrator-ho-manager.h"
#include "../../../device/NetworkNode.h"
#include "../../../device/UserEquipment.h"
#include "../../../device/ENodeB.h"
#include "../../../device/HeNodeB.h"
#include "../../../componentManagers/NetworkManager.h"
#include "../../../core/spectrum/bandwidth-manager.h"
#include "../../../phy/lte-phy.h"
#include "../../../utility/ComputePathLoss.h"

IntegratorHoManager::IntegratorHoManager() {
	m_target = NULL;
}

IntegratorHoManager::~IntegratorHoManager() {
	m_target = NULL;
}

bool IntegratorHoManager::CheckHandoverNeed(UserEquipment* ue) {
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

	// parameters
	double HOM = 6;
	double a = 0.25;

	double FDIF_threshold = HOM;


	// block for ENodeB
{
		std::vector<ENodeB*> *listOfNodes = NetworkManager::Init()->GetENodeBContainer();
		std::vector<ENodeB*>::iterator it;

		double RSRPDIF; // difference between target node and serving node
		double FRSRPDIF; // filter difference between target node and serving node


		ENodeB *probableNewTargetNode = (ENodeB*) targetNode;
		double probable_TXpower =
				10
						* log10(
								pow(10.,
										(probableNewTargetNode->GetPhy()->GetTxPower()
												- 30) / 10)
										/ probableNewTargetNode->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size());
		double probable_pathLoss = ComputePathLossForInterference(
				probableNewTargetNode, ue);
		double probable_RXpower = probable_TXpower - probable_pathLoss;

		// find the probableNewTargetNode with the highest power within Init()->GetENodeBContainer()
		for (it = listOfNodes->begin(); it != listOfNodes->end(); it++) {
			double it_TXpower =
					10
							* log10(
									pow(10.,
											((*it)->GetPhy()->GetTxPower() - 30)
													/ 10)
											/ (*it)->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size());
			double it_pathLoss = ComputePathLossForInterference((*it), ue);

			double it_RXpower = it_TXpower - it_pathLoss;

			if (it_RXpower > probable_RXpower) {
				probable_RXpower = it_RXpower;
				probableNewTargetNode = (*it);
			}

		}

		// CheckHandoverNeed process
		if (probableNewTargetNode->GetIDNetworkNode()
				!= targetNode->GetIDNetworkNode()) {

			// calculate the RSRP difference and filtered RSRP difference
			RSRPDIF = probable_RXpower - targetRXpower;
			FRSRPDIF = a * RSRPDIF + (1 - a) * probableNewTargetNode->GetFRSRPDIF();

			if (FRSRPDIF > FDIF_threshold)
			{
				targetRXpower = probable_RXpower;
				targetNode = probableNewTargetNode;

				probableNewTargetNode->ResetFRSRPDIF();
			}
			else
			{
				probableNewTargetNode->SetFRSRPDIF(FRSRPDIF);
			}

		}
}


// block for HeNodeB
{
	std::vector<HeNodeB*> *listOfNodes2 = NetworkManager::Init ()->GetHomeENodeBContainer();
	std::vector<HeNodeB*>::iterator it2;

	double RSRPDIF; // difference between target node and serving node
	double FRSRPDIF;// filter difference between target node and serving node


	HeNodeB *probableNewTargetNode = (HeNodeB*)targetNode;
	double probable_TXpower = 10
	* log10(
			pow(10.,
					(probableNewTargetNode->GetPhy()->GetTxPower()
							- 30) / 10)
			/ probableNewTargetNode->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size());
	double probable_pathLoss = ComputePathLossForInterference(
			probableNewTargetNode, ue);
	double probable_RXpower = probable_TXpower - probable_pathLoss;

	// find the probableNewTargetNode with the highest power within Init()->GetENodeBContainer()
	for (it2 = listOfNodes2->begin(); it2 != listOfNodes2->end(); it2++)
	{
		double it_TXpower = 10
		* log10(
				pow(10., ((*it2)->GetPhy()->GetTxPower() - 30) / 10)
				/ (*it2)->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size());
		double it_pathLoss = ComputePathLossForInterference((*it2), ue);

		double it_RXpower = it_TXpower - it_pathLoss;

		if (it_RXpower > probable_RXpower)
		{
			probable_RXpower = it_RXpower;
			probableNewTargetNode = (*it2);
		}

	}
	// CheckHandoverNeed process
			if (probableNewTargetNode->GetIDNetworkNode()
					!= targetNode->GetIDNetworkNode()) {

				// calculate the RSRP difference and filtered RSRP difference
				RSRPDIF = probable_RXpower - targetRXpower;
				FRSRPDIF = a * RSRPDIF + (1 - a) * probableNewTargetNode->GetFRSRPDIF();

				if (FRSRPDIF > FDIF_threshold)
				{
					targetRXpower = probable_RXpower;
					targetNode = probableNewTargetNode;

					probableNewTargetNode->ResetFRSRPDIF();
				}
				else
				{
					probableNewTargetNode->SetFRSRPDIF(FRSRPDIF);
				}

			}

}

if (ue->GetTargetNode()->GetIDNetworkNode() != targetNode->GetIDNetworkNode())
{
	m_target = targetNode;
	return true;
} else
{
	return false;
}
}
