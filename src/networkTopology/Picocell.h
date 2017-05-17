/*
 * Picocell.h
 *
 *  Created on: 2014. 12. 23.
 *      Author: chen
 */


// added file, 20141223
// add Pico-cell
#ifndef PICOCELL_H_
#define PICOCELL_H_

#include "Cell.h"

class Picocell : public Cell {
public:
	Picocell();
	Picocell(int idCell,
		 double radius,
		 double minDistance,
		 double X,
		 double Y);
	virtual ~Picocell();

};


#endif /* PICOCELL_H_ */
