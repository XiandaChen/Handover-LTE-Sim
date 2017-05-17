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


#include "handover-entity.h"
#include "../../../device/NetworkNode.h"
#include "../../../device/UserEquipment.h"
#include "ho-manager.h"
#include "position-based-ho-manager.h"
#include "power-based-ho-manager.h"
#include "dihat-ho-manager.h"			// added, DIHAT scheme used for EURASIP journal
#include "integrator-ho-manager.h"		// added, 20141230, Integrator handover implementation
#include "nch-ho-manager.h"				// added, 20141230, NCH handover implementation
#include "hard-ho-manager.h"			// added, 20141230, 3GPP standard ho scheme


HandoverEntity::HandoverEntity()
{
  m_device = NULL;

  // added, 20141230
   m_hoManager = new DihatHoManager ();				// DIHAT handover implementation
  // m_hoManager = new SinrThresholdHoManager ();	// NCH handover implementation
  // m_hoManager = new IntegratorHoManager ();		// Integrator handover implementation 
  // m_hoManager = new HardHoManager ();			// Standard HARD handover implementation

}

HandoverEntity::~HandoverEntity()
{
  m_device = 0;
  delete m_hoManager;
}

void
HandoverEntity::SetDevice (NetworkNode* d)
{
  m_device = d;
}

NetworkNode*
HandoverEntity::GetDevice ()
{
  return m_device;
}

void
HandoverEntity::SetHoManager (HoManager *h)
{
  m_hoManager = h;
}

HoManager*
HandoverEntity::GetHoManager (void)
{
  return m_hoManager;
}


bool
HandoverEntity::CheckHandoverNeed (UserEquipment* ue)
{
  return GetHoManager ()->CheckHandoverNeed (ue);
}
