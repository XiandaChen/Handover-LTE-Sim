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
 * Author: Giuseppe Piro <g.piro@poliba.it>
 */

#ifndef USEREQUIPMENT_H_
#define USEREQUIPMENT_H_

// added, 20150102
#include "../core/cartesianCoodrdinates/CartesianCoordinates.h"

#include "NetworkNode.h"

// added, 20150106, for Sinr-threshold-scheme
#include "../phy/ue-lte-phy.h"

class ENodeB;
class Gateway;
class CqiManager;


class UserEquipment: public NetworkNode {
public:
	UserEquipment();
	UserEquipment(int idElement, double posx, double posy, Cell *cell,
			NetworkNode* target, bool handover, Mobility::MobilityModel model);
	UserEquipment(int idElement, double posx, double posy, int speed,
			double speedDirection, Cell *cell, NetworkNode* target,
			bool handover, Mobility::MobilityModel model);

	virtual ~UserEquipment();

	void SetTargetNode(NetworkNode *n);
	NetworkNode* GetTargetNode(void);

	void UpdateUserPosition(double time);

	void SetCqiManager(CqiManager *cm);
	CqiManager* GetCqiManager(void);

	void
	SetIndoorFlag(bool flag);
	bool
	IsIndoor(void);

	//Debug
	void Print(void);

	// added, 20141230
	NetworkNode* GetPreviousProbableNewTargetNode(void) {
		return m_previousProbableNewTargetNode;
	}
	void SetPreviousProbableNewTargetNode(NetworkNode* pnode) {
		m_previousProbableNewTargetNode = pnode;
	}
	int GetIDofPreviousProbableNewTargetNode(void) {
		return m_previousProbableNewTargetNode->GetIDNetworkNode();
	}

	// added, 20150102
	CartesianCoordinates* GetPreviousAbsolutePosition(void) {
		return m_previouseAbsolutePosition;
	}
	void SetPreviousAbsolutePosition(CartesianCoordinates * coordinate) {
		m_previouseAbsolutePosition = coordinate;
	}


	// added, 20150106
	UeLtePhy * GetUeLtePhy ()
	{
		return m_ueLtePhy;
	}

private:
	NetworkNode* m_targetNode;
	CqiManager *m_cqiManager;

	bool m_isIndoor;

	double m_timePositionUpdate;

	// added, 20141230
	NetworkNode* m_previousProbableNewTargetNode;// store previous-time-instance probableNewTargetNode,
	// if current-time-instance probableNewTargetNode is no the same with previous-time-instance
	// probableNewTargetNode, and then we should reset m_TTTcounter in previous probableNewTargetNode to zero

	// added, 20150102
	// record the previous position of UE for calculating the angle of eNB-prePostion-curPosition
	CartesianCoordinates *m_previouseAbsolutePosition;


	// added, 20150106
	// the UeLtePhy instance, to get the m_measuredSinr to calculate the effective-SINR, which is used in SINR-threshold scheme
	UeLtePhy * m_ueLtePhy;
};

#endif /* USEREQUIPMENT_H_ */
