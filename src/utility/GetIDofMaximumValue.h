/*
 * GetIDofMaxValue.h
 *
 *  Created on: 2015. 1. 4.
 *      Author: chen
 */

#ifndef GETIDOFMAXVALUE_H_
#define GETIDOFMAXVALUE_H_

// added file, 20150104
// to get ID of the maximum value in an array
static int
GetIDofMaximumValue(double * org) {
	int key = 0;
	double max = org[0];
	for (int i = 1; i < sizeof(org); i++) {
		if (max < org[i])
		{
			max = org[i];
			key = i;
		}
	}

	return key;
}


#endif /* GETIDOFMAXVALUE_H_ */
