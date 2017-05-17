/*
 * nch-ho-manager.h
 *
 *  Created on: 2015. 1. 6.
 *      Author: chen
 */

#ifndef SINR_THRESHOLD_HO_MANAGER_H_
#define SINR_THRESHOLD_HO_MANAGER_H_

#include "ho-manager.h"

// added file, 20150106
// The implementation of the NCH (SINR-threshold) scheme -- "A Network Controlled Handover Mechanism and its Optimization in LTE- Heterogeneous Network"
class SinrThresholdHoManager: public HoManager {
public:
	SinrThresholdHoManager();
	virtual ~SinrThresholdHoManager();

	virtual bool CheckHandoverNeed (UserEquipment* ue);
};



#endif /* SINR_THRESHOLD_HO_MANAGER_H_ */
