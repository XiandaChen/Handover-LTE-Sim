/*
 * GetMinimumValue.h
 *
 *  Created on: 2015. 1. 4.
 *      Author: chen
 */

#ifndef GETMINIMUMVALUE_H_
#define GETMINIMUMVALUE_H_

// added file, 20150104
// to get the minimum value in an array
static double GetMinimumValue(double * org) {
	double mini = org[0];
	for (int i = 1; i < sizeof(org); i++) {
		if (mini > org[i])	mini = org[i];
	}

	return mini;
}



#endif /* GETMINIMUMVALUE_H_ */
