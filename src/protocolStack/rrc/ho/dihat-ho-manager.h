/*
 * dihat-ho-manager.h
 *
 *  Created on: 2015. 1. 2.
 *      Author: chen
 */

#ifndef DIHAT_HO_MANAGER_H_
#define DIHAT_HO_MANAGER_H_

// added file, 20150102
// This is the implementation of DIHAT algorithm used in EURASIP journal
#include "ho-manager.h"

class DihatHoManager: public HoManager {
public:
	DihatHoManager();
	virtual ~DihatHoManager();

	virtual bool CheckHandoverNeed (UserEquipment* ue);
};


#endif /* DIHAT_HO_MANAGER_H_ */
