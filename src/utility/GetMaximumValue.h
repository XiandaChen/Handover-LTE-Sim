/*
 * GetMaximumValue.h
 *
 *  Created on: 2015. 1. 4.
 *      Author: chen
 */

#ifndef GETMAXIMUMVALUE_H_
#define GETMAXIMUMVALUE_H_

// added file, 20150104
// to get the maximum value in an array
static double GetMaximumValue(double * org) {
	double max = org[0];
	for (int i = 1; i < sizeof(org); i++) {
		if (max < org[i])	max = org[i];
	}

	return max;
}

#endif /* GETMAXIMUMVALUE_H_ */
