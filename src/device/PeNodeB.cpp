/*
 * PeNodeB.cpp
 *
 *  Created on: 2014. 12. 23.
 *      Author: chen
 */


// added file, 20141223
// add PeNodeB device
#include "NetworkNode.h"
#include "UserEquipment.h"
#include "PeNodeB.h"		// added, 2014126
#include "../networkTopology/Picocell.h"		// added, 20141226
#include "../phy/penb-lte-phy.h"		// added, 20141226
#include "Gateway.h"
#include "../protocolStack/mac/packet-scheduler/packet-scheduler.h"
#include "../protocolStack/mac/packet-scheduler/mt-uplink-packet-scheduler.h"
#include "../protocolStack/mac/packet-scheduler/dl-pf-packet-scheduler.h"
#include "../protocolStack/mac/packet-scheduler/dl-mlwdf-packet-scheduler.h"
#include "../protocolStack/mac/packet-scheduler/dl-exp-packet-scheduler.h"
#include "../protocolStack/mac/packet-scheduler/dl-fls-packet-scheduler.h"
#include "../protocolStack/mac/packet-scheduler/exp-rule-downlink-packet-scheduler.h"
#include "../protocolStack/mac/packet-scheduler/log-rule-downlink-packet-scheduler.h"
#include "../protocolStack/mac/packet-scheduler/enhanced-uplink-packet-scheduler.h"
#include "../protocolStack/mac/packet-scheduler/roundrobin-uplink-packet-scheduler.h"
#include "../phy/enb-lte-phy.h"
#include "../core/spectrum/bandwidth-manager.h"
#include "../protocolStack/packet/packet-burst.h"
PeNodeB::PeNodeB (int idElement,
		Picocell *cell)
{
  SetIDNetworkNode (idElement);
  SetNodeType(NetworkNode::TYPE_PICO_NODE);
  SetCell (cell);

  double pos_X = cell->GetCellCenterPosition()->GetCoordinateX();
  double pos_Y = cell->GetCellCenterPosition()->GetCoordinateY();

  CartesianCoordinates *position = new CartesianCoordinates(pos_X, pos_Y);
  Mobility* m = new ConstantPosition ();
  m->SetAbsolutePosition (position);
  SetMobilityModel (m);

  CreateUserEquipmentRecords();

  PenbLtePhy *phy = new PenbLtePhy ();
  phy->SetDevice(this);
  SetPhy (phy);

  ProtocolStack *stack = new ProtocolStack (this);
  SetProtocolStack (stack);

  Classifier *classifier = new Classifier ();
  classifier->SetDevice (this);
  SetClassifier (classifier);
}

PeNodeB::~PeNodeB()
{
  Destroy ();
  DeleteUserEquipmentRecords ();
}

