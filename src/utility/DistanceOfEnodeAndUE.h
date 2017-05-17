/*
 * DistanceOfEnodeAndUE.h
 *
 *  Created on: 2015. 1. 2.
 *      Author: chen
 */

#ifndef DISTANCEOFENODEANDUE_H_
#define DISTANCEOFENODEANDUE_H_

// added file, 20150102
// function to obtain the distance between UE and eNodes
#include "../device/ENodeB.h"
#include "../device/UserEquipment.h"
#include "math.h"

// obtain the distance between UE-at-currentPosition and eNB
static double
ComputeDistanceBetweenUEandEnodeB (UserEquipment* ue, ENodeB* enb)
{
	// line of eNB-position and UE-current
	double dist = sqrt((double) pow((ue->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateX() - enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateX()), 2)
						+ pow((ue->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateY() - enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateY()), 2)
						+ pow((ue->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateZ() - enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateZ()), 2));
	return dist;
}


#endif /* DISTANCEOFENODEANDUE_H_ */
