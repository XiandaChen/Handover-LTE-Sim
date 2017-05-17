/*
 * ComputerNormalizedValue.h
 *
 *  Created on: 2015. 1. 2.
 *      Author: chen
 */

#ifndef COMPUTERNORMALIZEDVALUE_H_
#define COMPUTERNORMALIZEDVALUE_H_

// added file, 20150102
// calculate the square root of sum of sqrt value of each element
#include <math.h>
#include <vector>
static double
ComputerNormalizedValue (double * org)
{
	double temp = 0;
	for (int i = 0; i < sizeof(org); i++)
	{
		temp += pow(org[i], 2);
	}
	double normalizedValue = sqrt(temp);

	return normalizedValue;
}


#endif /* COMPUTERNORMALIZEDVALUE_H_ */
