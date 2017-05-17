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

#ifndef NETWORKNODE_H_
#define NETWORKNODE_H_

#include <vector>
#include <cmath>
#include "../networkTopology/Cell.h"
#include "../networkTopology/Femtocell.h"
#include "../networkTopology/Picocell.h"   // added, 20141223
#include "IPClassifier/Classifier.h"
#include "../protocolStack/protocols/TransportProtocol.h"
#include "../mobility/Mobility.h"
#include "../mobility/RandomDirection.h"
#include "../mobility/RandomWalk.h"
#include "../mobility/RandomWaypoint.h"
#include "../mobility/ConstantPosition.h"
#include "../mobility/Manhattan.h"
#include "../protocolStack/protocol-stack.h"

class PacketBurst;
class LtePhy;

class NetworkNode {
public:
	enum NodeState {
		STATE_DETACHED, STATE_ACTIVE, STATE_IDLE
	};

	enum NodeType {
		TYPE_ENODEB, TYPE_UE, TYPE_GW, TYPE_HOME_BASE_STATION, TYPE_RELAY_NODE,

		// added, 20141223
		TYPE_PICO_NODE,
	};

private:
	int m_idNetworkNode;
	NodeState m_state;
	NodeType m_nodeType;

	Cell *m_cell;

	ProtocolStack *m_protocolStack;

	Classifier *m_classifier;

	LtePhy *m_phy;

	Mobility *m_mobility;

	//added, 20141230
	double m_TTTcounter;

	// added, 20141230
	double m_HOMDIF; //	HOMDIF(t-1) = RSRP_T(t-1) - RSRP_S(t-1) - HOM, m_HOMDIF indicates HOMDIF at (t-1) time instant
	double m_FHOMDIF1; //  FHOMDIF(t) = a * HOMDIF(t) + (1-a) * FHOMDIF(t-1), where a = Tm/Tu = TTI/TTT
					   //	m_FHOMDIF1 indicates FHOMDIF at (t-1) time instance
	double m_FHOMDIF2; //	m_FHOMDIF2 indicates FHOMDIF at (t-2) time instance

	// added, 20141230
	double m_RSRPDIF;		// m_RSRPDIF(t) = RSRP_T(t) - RSRP_S(t),
	// m_RSRPDIF indicates RSRP difference between target node and serving node at (t) time instant
	double m_FRSRPDIF;// m_FRSRPDIF(t) = a * FRSRPDIF(t) + (1-a) * FRSRPDIF(t-1), where a = Tm/Tu = TTI/TTT

public:
	NetworkNode();
	virtual ~NetworkNode();

	void Destroy();

	void SetIDNetworkNode(int id);
	int GetIDNetworkNode(void) const;

	void SetNodeType(NodeType type);
	NodeType GetNodeType(void) const;

	void SetNodeState(NodeState state);
	void MakeActive(void);
	NodeState GetNodeState(void) const;

	void SetCell(Cell *cell);
	Cell* GetCell(void);

	void SetProtocolStack(ProtocolStack *stack);
	ProtocolStack* GetProtocolStack(void) const;

	void SetClassifier(Classifier *classifier);
	Classifier* GetClassifier(void) const;

	void SetPhy(LtePhy *phy);
	LtePhy* GetPhy(void);

	void SetMobilityModel(Mobility* m);
	Mobility* GetMobilityModel(void);

	void SendPacketBurst(PacketBurst* p);
	void ReceivePacketBurst(PacketBurst* p);

	// added, 20141230
	void ResetTTTcounter(void) {
		m_TTTcounter = 0.0;
	}
	double GetTTTcounter(void) {
		return m_TTTcounter;
	}
	void AddTTTcounter(void) {
		m_TTTcounter += 0.001;
	}

	// added, 20141230
	void SetHOMDIF(double homdif) {
		m_TTTcounter = homdif;
	}
	double GetHOMDIF(void) {
		return m_TTTcounter;
	}
	void SetFOMDIF1(double fhomdif1) {
		m_FHOMDIF1 = fhomdif1;
	}
	double GetFHOMDIF1(void) {
		return m_FHOMDIF1;
	}
	void SetFHOMDIF2(double fhomdif2) {
		m_FHOMDIF2 = fhomdif2;
	}
	double GetFHOMDIF2(void) {
		return m_FHOMDIF2;
	}

	// added, 20141230
	void SetRSRPDIF(double rsrpdif) {
		m_RSRPDIF = rsrpdif;
	}
	double GetRSRPDIF(void) {
		return m_RSRPDIF;
	}
	void SetFRSRPDIF(double frsrpdif) {
		m_FRSRPDIF = frsrpdif;
	}
	double GetFRSRPDIF(void) {
		return m_FRSRPDIF;
	}
	void ResetFRSRPDIF(void)
	{
		m_FRSRPDIF = 0.0;
	}
};

#endif /* NETWORKNODE_H_ */
