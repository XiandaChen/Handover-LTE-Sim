/*
 * AngleOfEnodeandUE.h
 *
 *  Created on: 2015. 1. 2.
 *      Author: chen
 */

#ifndef ANGLEOFENODEANDUE_H_
#define ANGLEOFENODEANDUE_H_

// added file, 20150102
// the angle of UE and eNodes, unit in PI
#include "../device/ENodeB.h"
#include "../device/UserEquipment.h"
#include "math.h"

static double
ComputeAngleBetweenUEandEnodeB (UserEquipment* ue, ENodeB* enb)
{
	// line of UE-previous and eNB-position
	double linePpPe = sqrt((double) pow((enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateX() - ue->GetPreviousAbsolutePosition()->GetCoordinateX()), 2)
								+ pow((enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateY() - ue->GetPreviousAbsolutePosition()->GetCoordinateY()), 2)
								+ pow((enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateZ() - ue->GetPreviousAbsolutePosition()->GetCoordinateZ()), 2));

	// line of UE-previous and UE-current
	double linePpPc = sqrt((double) pow((ue->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateX() - ue->GetPreviousAbsolutePosition()->GetCoordinateX()), 2)
								+ pow((ue->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateY() - ue->GetPreviousAbsolutePosition()->GetCoordinateY()), 2)
								+ pow((ue->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateZ() - ue->GetPreviousAbsolutePosition()->GetCoordinateZ()), 2));

	// line of eNB-position and UE-current
	double linePePc = sqrt((double) pow((ue->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateX() - enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateX()), 2)
								+ pow((ue->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateY() - enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateY()), 2)
								+ pow((ue->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateZ() - enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateZ()), 2));


	// angle of eNB-position, UE-previous and UE-current
	double angle = acos(pow(linePpPe, 2) + pow(linePpPc, 2) - pow(linePePc, 2) / (2 * linePpPe * linePpPc)) * 180.0 / 3.14159265;

	return angle;

}


#endif /* ANGLEOFENODEANDUE_H_ */
