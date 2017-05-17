/*
 * PeNodeB.h
 *
 *  Created on: 2014. 12. 23.
 *      Author: chen
 */


// added file, 20141223
// add PeNodeB device
#ifndef PENODEB_H_
#define PENODEB_H_

#include "ENodeB.h"

class PeNodeB : public ENodeB {
public:

	PeNodeB (int idElement,
			Picocell *cell);

	virtual ~PeNodeB();

};


#endif /* PENODEB_H_ */
