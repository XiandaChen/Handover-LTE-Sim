/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010,2011,2012 TELEMATICS LAB, Politecnico di Bari
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

#include "../channel/LteChannel.h"
#include "../phy/enb-lte-phy.h"
#include "../phy/ue-lte-phy.h"
#include "../core/spectrum/bandwidth-manager.h"
#include "../networkTopology/Cell.h"
#include "../protocolStack/packet/packet-burst.h"
#include "../protocolStack/packet/Packet.h"
#include "../core/eventScheduler/simulator.h"
#include "../flows/application/InfiniteBuffer.h"
#include "../flows/application/VoIP.h"
#include "../flows/application/CBR.h"
#include "../flows/application/TraceBased.h"
#include "../device/IPClassifier/ClassifierParameters.h"
#include "../flows/QoS/QoSParameters.h"
#include "../flows/QoS/QoSForEXP.h"
#include "../flows/QoS/QoSForFLS.h"
#include "../flows/QoS/QoSForM_LWDF.h"
#include "../componentManagers/FrameManager.h"
#include "../utility/seed.h"
#include "../utility/RandomVariable.h"
#include "../phy/wideband-cqi-eesm-error-model.h"
#include "../phy/simple-error-model.h"
#include "../channel/propagation-model/macrocell-urban-area-channel-realization.h"
#include "../load-parameters.h"
#include "../protocolStack/mac/packet-scheduler/dl-pf-packet-scheduler.h"
#include "../protocolStack/mac/packet-scheduler/log-rule-downlink-packet-scheduler.h"
#include <queue>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <iostream>

//nbRNs = num di pico celle
//nbCells  num di macro celle

static void MacroWithPico(double cellRadius, int nbCells, int nbRNs,
		int relay_ptx, double relay_position, int nbUEs, int nbVoip,
		int nbVideo, int nbBe, int videoBitRate, int format_video,
		int sched_type, double MAX_DELAY) {

	std::cout << "cellRadius " << cellRadius << std::endl;
	std::cout << "nbCells " << nbCells << std::endl;
	std::cout << "nbRNs " << nbRNs << std::endl;
	std::cout << "relay_ptx " << relay_ptx << std::endl;
	std::cout << "relay_position " << relay_position << std::endl;
	std::cout << "nbUEs " << nbUEs << std::endl;
	std::cout << "nbVoip " << nbVoip << std::endl;
	std::cout << "nbVideo " << nbVideo << std::endl;
	std::cout << "nbBe " << nbBe << std::endl;
	std::cout << "videoBitRate " << videoBitRate << std::endl;
	std::cout << "format_video " << format_video << std::endl;
	std::cout << "sched_type " << sched_type << std::endl;
	std::cout << "MAX_DELAY " << MAX_DELAY << std::endl;

	/* SIMUALTION PARAMETERS */
	double bandwidth = 10; //MHz
	int clusterSize = 1;
	double duration = 50;
	double flow_duration = 40;
	cellRadius = cellRadius / 1000.; // Km
	relay_position = relay_position / 100.;

	srand(time(NULL));
	//srand(1);

	// CREATE COMPONENT MANAGERS
	Simulator *simulator = Simulator::Init();
	FrameManager *frameManager = FrameManager::Init();
	NetworkManager* networkManager = NetworkManager::Init();
	FlowsManager* flowsManager = FlowsManager::Init();

	// SET SCHEDULING ALLOCATION SCHEME
	ENodeB::DLSchedulerType downlink_scheduler_type;
	switch (sched_type) {
	case 1:
		downlink_scheduler_type = ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR;
		std::cout << "Scheduler PF " << std::endl;
		break;
	case 2:
		downlink_scheduler_type = ENodeB::DLScheduler_TYPE_MLWDF;
		std::cout << "Scheduler MLWDF " << std::endl;
		break;
	case 3:
		downlink_scheduler_type = ENodeB::DLScheduler_TYPE_EXP;
		std::cout << "Scheduler EXP " << std::endl;
		break;
	case 4:
		downlink_scheduler_type = ENodeB::DLScheduler_TYPE_FLS;
		std::cout << "Scheduler FLS " << std::endl;
		break;
	case 5:
		downlink_scheduler_type = ENodeB::DLScheduler_EXP_RULE;
		std::cout << "Scheduler EXP_RULE " << std::endl;
		break;
	case 6:
		downlink_scheduler_type = ENodeB::DLScheduler_LOG_RULE;
		std::cout << "Scheduler LOG RULE " << std::endl;
		break;
	default:
		downlink_scheduler_type = ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR;
		std::cout << "Scheduler default " << std::endl;
		break;
	}

//create cells
	std::vector<Cell*> *cells = new std::vector<Cell*>;
	for (int i = 0; i < nbCells; i++) {
		CartesianCoordinates center = GetCartesianCoordinatesForCell(i,
				cellRadius * 1000.);

		Cell *c = new Cell(i, cellRadius, 0.035, center.GetCoordinateX(),
				center.GetCoordinateY());
		cells->push_back(c);
		networkManager->GetCellContainer()->push_back(c);

		std::cout << "Created Cell, id " << c->GetIdCell() << ", position: "
				<< c->GetCellCenterPosition()->GetCoordinateX() << " "
				<< c->GetCellCenterPosition()->GetCoordinateY() << std::endl;
	}

	std::vector<BandwidthManager*> spectrums = RunFrequencyReuseTechniques(
			nbCells, clusterSize, bandwidth);

//Create GW
	Gateway *gw = new Gateway();
	networkManager->GetGatewayContainer()->push_back(gw);

//create eNBs
	std::vector<ENodeB*> *eNBs = new std::vector<ENodeB*>;
	for (int i = 0; i < nbCells; i++) {
		ENodeB* enb = new ENodeB(i, cells->at(i));
		enb->GetPhy()->SetDlChannel(new LteChannel());
		enb->GetPhy()->SetUlChannel(new LteChannel());
//enb->SetDLScheduler (ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR);
		enb->GetPhy()->SetBandwidthManager(spectrums.at(i));

		std::cout << "\n***\nCreated enb, id " << enb->GetIDNetworkNode()

		<< ", cell id " << enb->GetCell()->GetIdCell() << ", position: "
				<< enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateX()
				<< " "
				<< enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateY()
				<< " , channels id "
				<< enb->GetPhy()->GetDlChannel()->GetChannelId() << " "
				<< enb->GetPhy()->GetUlChannel()->GetChannelId() << std::endl;

		enb->GetPhy()->GetBandwidthManager()->Print();

		networkManager->GetENodeBContainer()->push_back(enb);
		eNBs->push_back(enb);
	}

//create pico nodes
	int idRn = 1100;

	double angles_4_RNs[4] = { 1 * (3.14 / 3.0), 2 * (3.14 / 3.0), 4
			* (3.14 / 3.0), 5 * (3.14 / 3.0) };
	double angles_2_RNs[19] = { 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1,
			0, 1, 0 };

	for (int i = 0; i < nbCells; i++) { // ci sono 19 macrocelle e per ognuna di queste, 4 picocelle
		for (int j = 0; j < nbRNs; j++) {

			ENodeB* enb = networkManager->GetENodeBByID(i);

// compute relay position
			double angle;
			double x;
			double y;
			if (nbRNs == 6) {
				angle = j * (3.14 / 3.0);
				x = relay_position * (cellRadius * 1000) * cos(angle);
				y = relay_position * (cellRadius * 1000) * sin(angle);
			}
			if (nbRNs == 4) {
				angle = angles_4_RNs[j];
				x = relay_position * (cellRadius * 1000) * cos(angle);
				y = relay_position * (cellRadius * 1000) * sin(angle);
			}
			if (nbRNs == 2) {
				angle = ((3.14 / 2) * angles_2_RNs[i]) + (j * 3.14);
				x = relay_position * (cellRadius * 1000) * cos(angle);
				y = relay_position * (cellRadius * 1000) * sin(angle);
			}

			double absolute_x =
					x
							+ enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateX();
			double absolute_y =
					y
							+ enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateY();

//RelayNode *rn = new RelayNode (idRn, networkManager->GetCellByID (i), absolute_x, absolute_y);

//CREATE PICO CELLS
			ENodeB *rn = new ENodeB(idRn, networkManager->GetCellByID(i),
					absolute_x, absolute_y);
			rn->SetNodeType(NetworkNode::TYPE_PICO_NODE);

			rn->GetPhy()->SetDlChannel(new LteChannel());
			rn->GetPhy()->SetUlChannel(new LteChannel());
			rn->GetPhy()->SetTxPower(relay_ptx);

			rn->GetPhy()->SetBandwidthManager(spectrums.at(i));

			networkManager->GetENodeBContainer()->push_back(rn);

			std::cout << "\n***\nCreated eNB for PICO, id "
					<< rn->GetIDNetworkNode() << ", cell id "
					<< rn->GetCell()->GetIdCell()

//<< ", DeNB " << rn->GetTargetEnb ()->GetIDNetworkNode ()
					<< ", position: "
					<< rn->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateX()
					<< " "
					<< rn->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateY()
					<< " , channels id "
					<< rn->GetPhy()->GetDlChannel()->GetChannelId() << " "
					<< rn->GetPhy()->GetUlChannel()->GetChannelId()
					<< std::endl;
			rn->GetPhy()->GetBandwidthManager()->Print();

			idRn++;
		}
	}

//*********************************************************************
// SET PACKET SCHEDULING STRATEGY
	std::vector<ENodeB*> *nodes = networkManager->GetENodeBContainer();
	std::vector<ENodeB*>::iterator it;
	if (sched_type == 1) {
		std::cout << "SELECTED PF SCHEDULER" << std::endl;
		for (it = nodes->begin(); it != nodes->end(); it++) {
			ENodeB *n = (*it);
			EnbMacEntity *mac =
					(EnbMacEntity*) n->GetProtocolStack()->GetMacEntity();
			DL_PF_PacketScheduler* sched = new DL_PF_PacketScheduler();
			sched->SetMacEntity(mac);
			mac->SetDownlinkPacketScheduler(sched);
		}
	}
	if (sched_type == 6) {
		std::cout << "SELECTED LOG RULE SCHEDULER" << std::endl;
		for (it = nodes->begin(); it != nodes->end(); it++) {
			ENodeB *n = (*it);
			EnbMacEntity *mac =
					(EnbMacEntity*) n->GetProtocolStack()->GetMacEntity();
			LogRuleDownlinkPacketScheduler * sched =
					new LogRuleDownlinkPacketScheduler();
			sched->SetMacEntity(mac);
			mac->SetDownlinkPacketScheduler(sched);
		}
	}

//*********************************************************************

	//Define Application Container
	int nbCell = 1;
	VoIP VoIPApplication[nbVoip * nbCell * nbUEs];
	TraceBased VideoApplication[nbVideo * nbCell * nbUEs];
	InfiniteBuffer BEApplication[nbBe * nbCell * nbUEs];
	int voipApplication = 0;
	int videoApplication = 0;
	int cbrApplication = 0;
	int beApplication = 0;
	int destinationPort = 101;
	int applicationID = 0;

	int maxXY = cellRadius * 1000;
	//Create UEs
	int idUE = nbCells;
	for (int i = 0; i < nbUEs; i++) {
		//ue's random position
		double posX = (double) rand() / RAND_MAX;
		posX = 0.95 * (((2 * cellRadius * 1000) * posX) - (cellRadius * 1000));
		double posY = (double) rand() / RAND_MAX;
		posY = 0.95 * (((2 * cellRadius * 1000) * posY) - (cellRadius * 1000));
		double speedDirection = GetRandomVariable(360.) * ((2. * 3.14) / 360.);
		int speed = 3;

		UserEquipment* ue = new UserEquipment(idUE, posX, posY, speed,
				speedDirection, cells->at(0), eNBs->at(0), 0, //handover false!
				Mobility::CONSTANT_POSITION);

		NetworkManager::Init()->SelectTargetNode(ue);
		while (ue->GetTargetNode()->GetCell()->GetIdCell() != 0) {
			posX = (double) rand() / RAND_MAX;
			posX = 0.95
					* (((2 * cellRadius * 1000) * posX) - (cellRadius * 1000));
			posY = (double) rand() / RAND_MAX;
			posY = 0.95
					* (((2 * cellRadius * 1000) * posY) - (cellRadius * 1000));
			ue->GetMobilityModel()->GetAbsolutePosition()->SetCoordinates(posX,
					posY);
			NetworkManager::Init()->SelectTargetNode(ue);
		}

		std::cout << "Created UE - id " << idUE << " position " << posX << " "
				<< posY << ", cell " << ue->GetCell()->GetIdCell()
				<< ", target enb " << ue->GetTargetNode()->GetIDNetworkNode()
				<< std::endl;

		ue->GetMobilityModel()->GetAbsolutePosition()->Print();
		ue->GetPhy()->SetDlChannel(
				ue->GetTargetNode()->GetPhy()->GetDlChannel());
		ue->GetPhy()->SetUlChannel(
				ue->GetTargetNode()->GetPhy()->GetUlChannel());

		FullbandCqiManager *cqiManager = new FullbandCqiManager();
		cqiManager->SetCqiReportingMode(CqiManager::PERIODIC);
		cqiManager->SetReportingInterval(1);
		cqiManager->SetDevice(ue);
		ue->SetCqiManager(cqiManager);

		WidebandCqiEesmErrorModel *errorModel = new WidebandCqiEesmErrorModel();
		ue->GetPhy()->SetErrorModel(errorModel);

		networkManager->GetUserEquipmentContainer()->push_back(ue);

		// register ue to the base station
		NetworkNode* target = ue->GetTargetNode();
		((ENodeB*) target)->RegisterUserEquipment(ue);
		// define the channel realization
		MacroCellUrbanAreaChannelRealization* c =
				new MacroCellUrbanAreaChannelRealization(target, ue);
		c->SetChannelType(ChannelRealization::CHANNEL_TYPE_PED_A);
		target->GetPhy()->GetDlChannel()->GetPropagationLossModel()->AddChannelRealization(
				c);

		// CREATE DOWNLINK APPLICATION FOR THIS UE
		double start_time = 0.1 + GetRandomVariable(5.);
		double duration_time = start_time + flow_duration;

		// *** voip application
		for (int j = 0; j < nbVoip; j++) {
			// create application
			VoIPApplication[voipApplication].SetSource(gw);
			VoIPApplication[voipApplication].SetDestination(ue);
			VoIPApplication[voipApplication].SetApplicationID(applicationID);
			VoIPApplication[voipApplication].SetStartTime(start_time);
			VoIPApplication[voipApplication].SetStopTime(duration_time);

			// create qos parameters
			if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_FLS) {
				QoSForFLS *qos = new QoSForFLS();
				qos->SetMaxDelay(MAX_DELAY);
				if (MAX_DELAY == 0.1) {
					std::cout << "Target Delay = 0.1 s, M = 9" << std::endl;
					qos->SetNbOfCoefficients(9);
				} else if (MAX_DELAY == 0.08) {
					std::cout << "Target Delay = 0.08 s, M = 7" << std::endl;
					qos->SetNbOfCoefficients(7);
				} else if (MAX_DELAY == 0.06) {
					std::cout << "Target Delay = 0.06 s, M = 5" << std::endl;
					qos->SetNbOfCoefficients(5);
				} else if (MAX_DELAY == 0.04) {
					std::cout << "Target Delay = 0.04 s, M = 3" << std::endl;
					qos->SetNbOfCoefficients(3);
				} else {
					std::cout << "ERROR: target delay is not available"
							<< std::endl;
					return;
				}

				VoIPApplication[voipApplication].SetQoSParameters(qos);
			} else if (downlink_scheduler_type
					== ENodeB::DLScheduler_TYPE_EXP) {
				QoSForEXP *qos = new QoSForEXP();
				qos->SetMaxDelay(MAX_DELAY);
				VoIPApplication[voipApplication].SetQoSParameters(qos);
			} else if (downlink_scheduler_type
					== ENodeB::DLScheduler_TYPE_MLWDF) {
				QoSForM_LWDF *qos = new QoSForM_LWDF();
				qos->SetMaxDelay(MAX_DELAY);
				VoIPApplication[voipApplication].SetQoSParameters(qos);
			} else {
				QoSParameters *qos = new QoSParameters();
				qos->SetMaxDelay(MAX_DELAY);
				VoIPApplication[voipApplication].SetQoSParameters(qos);
			}

			//create classifier parameters
			ClassifierParameters *cp = new ClassifierParameters(
					gw->GetIDNetworkNode(), ue->GetIDNetworkNode(), 0,
					destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
			VoIPApplication[voipApplication].SetClassifierParameters(cp);

			std::cout << "CREATED VOIP APPLICATION, ID " << applicationID
					<< std::endl;

			//update counter
			destinationPort++;
			applicationID++;
			voipApplication++;
		}

		// *** video application
		for (int j = 0; j < nbVideo; j++) {
			// create application
			VideoApplication[videoApplication].SetSource(gw);
			VideoApplication[videoApplication].SetDestination(ue);
			VideoApplication[videoApplication].SetApplicationID(applicationID);
			VideoApplication[videoApplication].SetStartTime(start_time);
			VideoApplication[videoApplication].SetStopTime(duration_time);

			//string video_trace("");
			//string video_trace ("side_by_side_");
			//string video_trace ("FS_l_depth_");
			//string video_trace ("FS_lr_view_");
			//string video_trace ("highway_H264_");
			//string video_trace ("mobile_H264_");

			string video_trace;
			// side_by_side --> 1
			// FS_l_view --> 2
			// FS_lr_depth --> 3

			switch (format_video) {
			case 1: {
				video_trace = "side_by_side_H264_";
				std::cout << "		selected side_by_side " << video_trace.c_str()
						<< std::endl;
				break;
			}
			case 2: {
				video_trace = "FS_l_depth_H264_";
				std::cout << "		selected FS_l_depth " << video_trace.c_str()
						<< std::endl;
				break;
			}
			case 3: {
				video_trace = "FS_lr_view_H264_";
				std::cout << "		selected FS_lr_view " << video_trace.c_str()
						<< std::endl;
				break;
			}
			default: {
				video_trace = "side_by_side_H264_";
				std::cout << "		selected side_by_side default "
						<< video_trace.c_str() << std::endl;
				break;
			}
			}

			switch (videoBitRate) {
			case 200: {
				string _file(
						path + "src/flows/application/Trace/"
								+ video_trace.c_str() + "200k.dat");
				VideoApplication[videoApplication].SetTraceFile(_file);
				std::cout << "		selected video @ 200k " << std::endl;
				break;
			}
			case 400: {
				string _file(
						path + "src/flows/application/Trace/"
								+ video_trace.c_str() + "400k.dat");
				VideoApplication[videoApplication].SetTraceFile(_file);
				std::cout << "		selected video @ 400k" << std::endl;
				break;
			}
			case 600: {
				string _file(
						path + "src/flows/application/Trace/"
								+ video_trace.c_str() + "600k.dat");
				VideoApplication[videoApplication].SetTraceFile(_file);
				std::cout << "		selected video @ 600k" << std::endl;
				break;
			}
			case 800: {
				string _file(
						path + "src/flows/application/Trace/"
								+ video_trace.c_str() + "800k.dat");
				VideoApplication[videoApplication].SetTraceFile(_file);
				std::cout << "		selected video @ 800k" << std::endl;
				break;
			}
			case 1000: {
				string _file(
						path + "src/flows/application/Trace/"
								+ video_trace.c_str() + "1000k.dat");
				VideoApplication[videoApplication].SetTraceFile(_file);
				std::cout << "		selected video @ 1000k" << std::endl;
				break;
			}
			default: {
				string _file(
						path + "src/flows/application/Trace/"
								+ video_trace.c_str() + "200k.dat");
				VideoApplication[videoApplication].SetTraceFile(_file);
				std::cout << "		selected video @ 200k as default" << std::endl;
				break;
			}
			}

			// create qos parameters
			if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_FLS) {
				QoSForFLS *qos = new QoSForFLS();
				qos->SetMaxDelay(MAX_DELAY);
				if (MAX_DELAY == 0.1) {
					std::cout << "Target Delay = 0.1 s, M = 9" << std::endl;
					qos->SetNbOfCoefficients(9);
				} else if (MAX_DELAY == 0.08) {
					std::cout << "Target Delay = 0.08 s, M = 7" << std::endl;
					qos->SetNbOfCoefficients(7);
				} else if (MAX_DELAY == 0.06) {
					std::cout << "Target Delay = 0.06 s, M = 5" << std::endl;
					qos->SetNbOfCoefficients(5);
				} else if (MAX_DELAY == 0.04) {
					std::cout << "Target Delay = 0.04 s, M = 3" << std::endl;
					qos->SetNbOfCoefficients(3);
				} else {
					std::cout << "ERROR: target delay is not available"
							<< std::endl;
					return;
				}
				VideoApplication[videoApplication].SetQoSParameters(qos);
			} else if (downlink_scheduler_type
					== ENodeB::DLScheduler_TYPE_EXP) {
				QoSForEXP *qos = new QoSForEXP();
				qos->SetMaxDelay(MAX_DELAY);
				VideoApplication[videoApplication].SetQoSParameters(qos);
			} else if (downlink_scheduler_type
					== ENodeB::DLScheduler_TYPE_MLWDF) {
				QoSForM_LWDF *qos = new QoSForM_LWDF();
				qos->SetMaxDelay(MAX_DELAY);
				VideoApplication[videoApplication].SetQoSParameters(qos);
			} else {
				QoSParameters *qos = new QoSParameters();
				qos->SetMaxDelay(MAX_DELAY);
				VideoApplication[videoApplication].SetQoSParameters(qos);
			}

			//create classifier parameters
			ClassifierParameters *cp = new ClassifierParameters(
					gw->GetIDNetworkNode(), ue->GetIDNetworkNode(), 0,
					destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
			VideoApplication[videoApplication].SetClassifierParameters(cp);

			std::cout << "CREATED VIDEO APPLICATION, ID " << applicationID
					<< std::endl;

			//update counter
			destinationPort++;
			applicationID++;
			videoApplication++;
		}

		// *** be application
		for (int j = 0; j < nbBe; j++) {
			// create application
			BEApplication[beApplication].SetSource(gw);
			BEApplication[beApplication].SetDestination(ue);
			BEApplication[beApplication].SetApplicationID(applicationID);
			BEApplication[beApplication].SetStartTime(start_time);
			BEApplication[beApplication].SetStopTime(duration_time);

			// create qos parameters
			QoSParameters *qosParameters = new QoSParameters();
			BEApplication[beApplication].SetQoSParameters(qosParameters);

			//create classifier parameters
			ClassifierParameters *cp = new ClassifierParameters(
					gw->GetIDNetworkNode(), ue->GetIDNetworkNode(), 0,
					destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
			BEApplication[beApplication].SetClassifierParameters(cp);

			std::cout << "CREATED BE APPLICATION, ID " << applicationID
					<< std::endl;

			//update counter
			destinationPort++;
			applicationID++;
			beApplication++;
		}

		idUE++;

	}

	simulator->SetStop(duration);
	simulator->Run();

}
