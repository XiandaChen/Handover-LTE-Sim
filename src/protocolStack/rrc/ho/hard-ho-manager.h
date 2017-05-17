/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010,2011,2012,2013 TELEMATICS LAB, Politecnico di Bari
 *
 *  Created on: 2013. 4. 2.
 *      Author: chen
 */

#ifndef HARD_HO_MANAGER_H_
#define HARD_HO_MANAGER_H_

#include "ho-manager.h"

// added file, 20141230
class HardHoManager: public HoManager {
public:
	HardHoManager();
	virtual ~HardHoManager();

	virtual bool CheckHandoverNeed (UserEquipment* ue);
};


#endif /* HARD_HO_MANAGER_H_ */
