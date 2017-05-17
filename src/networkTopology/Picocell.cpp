/*
 * Picocell.cpp
 *
 *  Created on: 2014. 12. 23.
 *      Author: chen
 */

/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010,2011,2012,2013 TELEMATICS LAB, Politecnico di Bari
 *
 * This file is part of LTE-Sim
 *
 * LTE-Sim is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation;
 *
 * LTE-Sim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LTE-Sim; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Francesco Capozzi <f.capozzi@poliba.it>
 */


// added file, 20141223
// add Pico-cell
#include "Picocell.h"

Picocell::Picocell()
{
}

Picocell::Picocell(int idCell,
	 double radius,
	 double minDistance,
	 double X,
	 double Y)
{
	  this->SetIdCell(idCell);
	  this->SetRadius(radius);
	  this->SetMinDistance(minDistance);
	  CartesianCoordinates *Position = new CartesianCoordinates(X,Y);
	  SetCellCenterPosition(Position);
}

Picocell::~Picocell()
{}




