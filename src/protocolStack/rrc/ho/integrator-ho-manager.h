/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010,2011,2012,2013 TELEMATICS LAB, Politecnico di Bari
 *
 *  Created on: 2013. 4. 2.
 *      Author: chen
 */

#ifndef Integrator_HO_MANAGER_H_
#define Integrator_HO_MANAGER_H_

#include "ho-manager.h"

class IntegratorHoManager: public HoManager {
public:
	IntegratorHoManager();
	virtual ~IntegratorHoManager();

	virtual bool CheckHandoverNeed (UserEquipment* ue);
};


#endif /* Integrator_HO_MANAGER_H_ */
