/*
 * penb-lte-phy.h
 *
 *  Created on: 2014. 12. 23.
 *      Author: chen
 */

#ifndef PENB_LTE_PHY_H_
#define PENB_LTE_PHY_H_

// added file, 20141223
// add the PHY component of Pico, TxPower=30dBm
#include "lte-phy.h"
class IdealControlMessage;

class PenbLtePhy :public LtePhy {
public:
	PenbLtePhy();
	virtual ~PenbLtePhy();

	virtual void DoSetBandwidthManager (void);

	virtual void StartTx (PacketBurst* p);
	virtual void StartRx (PacketBurst* p, TransmittedSignal* txSignal);

	virtual void SendIdealControlMessage (IdealControlMessage *msg);
	virtual void ReceiveIdealControlMessage (IdealControlMessage *msg);

    void ReceiveReferenceSymbols (NetworkNode* n, TransmittedSignal* s);

};

#endif /* PENB_LTE_PHY_H_ */
