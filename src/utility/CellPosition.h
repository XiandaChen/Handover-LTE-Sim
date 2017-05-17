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
 * Author: Giuseppe Piro <g.piro@poliba.it>
 */


#ifndef CELLPOSITION_H_
#define CELLPOSITION_H_

#include "../core/cartesianCoodrdinates/CartesianCoordinates.h"
#include <math.h>

static double cellPosition[19][2] = {

		//Radius = 500 m

		//Center
		{0., 0.},				// cellID = 0

		//First Loop
		{0.,866.},				// cellID = 1
		{-750.,433.},			// cellID = 2
		{-750,-433},			// cellID = 3
		{0.,-866.},				// cellID = 4
		{750.,-433.},			// cellID = 5
		{750.,433.},			// cellID = 6

		//Second Loop
		{0.,1732.},				// cellID = 7
		{-750.,1299.},				// cellID = 8
		{-1500.,866.},				// cellID = 9
		{-1500.,0.},				// cellID = 10
		{-1500.,-866.},				// cellID = 11
		{-750.,-1299.},				// cellID = 12
		{0.,-1732},				// cellID = 13
		{750.,-1299.},				// cellID = 14
		{1500.,-866.},				// cellID = 15
		{1500.,0},				// cellID = 16
		{1500.,866.},				// cellID = 17
		{750.,1299.},				// cellID = 18
};

// coordinates for Pico-cells
static double PicoCellPosition[72][2] = {

		//Macro-Radius = 500 m

		  // first loop
		  {0, 433.01},						// IDPicocell = 1100
		  {-375, 216.50},					// IDPicocell = 1101
		  {-375, -216.50},					// IDPicocell = 1102
		  {0, -433.},						// IDPicocell = 1103
		  {375, -216.50},					// IDPicocell = 1104
		  {375, 216.50},					// IDPicocell = 1105

		  // second loop
		  {-375, 649.51},					// IDPicocell = 1106
		  {-750, 0},						// IDPicocell = 1107
		  {-375, -649.51},					// IDPicocell = 1108
		  {375, -649.51},					// IDPicocell = 1109
		  {750, 0},							// IDPicocell = 1110
		  {375, 649.51},					// IDPicocell = 1111

		  // third loop
		  {0, 1299.},						// IDPicocell = 1112
		  {-375, 1082.5},					// IDPicocell = 1113
		  {-750, 866.02},					// IDPicocell = 1114
		  {-1125, 649.51},					// IDPicocell = 1115
		  {-1125,  216.50},					// IDPicocell = 1116
		  {-1125, -216.50},					// IDPicocell = 1117
		  {-1125, -649.51},					// IDPicocell = 1118
		  {-750, -866.02},					// IDPicocell = 1119
		  {-375, -1082.5},					// IDPicocell = 1120
		  {0, -1299.},						// IDPicocell = 1121
		  {375, -1082.5},					// IDPicocell = 1122
		  {750, -866.02},					// IDPicocell = 1123
		  {1125, - 649.51},					// IDPicocell = 1124
		  {1125, - 216.50},					// IDPicocell = 1125
		  {1125, 216.50},					// IDPicocell = 1126
		  {1125, 649.51},					// IDPicocell = 1127
		  {750, 866.02},					// IDPicocell = 1128
		  {375, 1082.5},					// IDPicocell = 1129

		  // fourth loop
		  {-375, 1515.5},					// IDPicocell = 1130
		  {-1125, 1082.5},					// IDPicocell = 1131
		  {-1500, 433.01},					// IDPicocell = 1132
		  {-1500,  -433.01},				// IDPicocell = 1133
		  {-1125, -1082.5},					// IDPicocell = 1134
		  {-375, -1515.5},					// IDPicocell = 1135
		  {375, -1515.5},					// IDPicocell = 1136
		  {1125, -1082.5},					// IDPicocell = 1137
		  {1500, -433.01},					// IDPicocell = 1138
		  {1500, 433.01},					// IDPicocell = 1139
		  {1125, 1082.5},					// IDPicocell = 1140
		  {375, 1515.5},					// IDPicocell = 1141

		  // fifth loop
		  {0,  2165.1},						// IDPicocell = 1142
		  {-375, 1948.6},					// IDPicocell = 1143
		  {-750, 1732.1},					// IDPicocell = 1144
		  {-1125, 1515.5},					// IDPicocell = 1145
		  {-1500, 1299.},					// IDPicocell = 1146
		  {-1875, 1082.5},					// IDPicocell = 1147
		  {-1875, 649.51},					// IDPicocell = 1148
		  {-1875, 216.50},					// IDPicocell = 1149
		  {-1875, -216.50},					// IDPicocell = 1150
		  {-1875, -649.51},					// IDPicocell = 1151
		  {-1875, -1082.5},					// IDPicocell = 1152
		  {-1500, -1299.},					// IDPicocell = 1153
		  {-1125, -1515.5},					// IDPicocell = 1154
		  {-750, -1732.1},					// IDPicocell = 1155
		  {-375, -1948.6},					// IDPicocell = 1156
		  {0, -2165.1},						// IDPicocell = 1157
		  {375, -1948.6},					// IDPicocell = 1158
		  {750, -1732.1},					// IDPicocell = 1159
		  {1125, -1515.5},					// IDPicocell = 1160
		  {1500, -1299.},					// IDPicocell = 1161
		  {1875, -1082.5},					// IDPicocell = 1162
		  {1875, -649.51},					// IDPicocell = 1163
		  {1875, -216.50},					// IDPicocell = 1164
		  {1875, 216.50},					// IDPicocell = 1165
		  {1875, 649.51},					// IDPicocell = 1166
		  {1875, 1082.5},					// IDPicocell = 1167
		  {1500, 1299.},					// IDPicocell = 1168
		  {1125, 1515.5},					// IDPicocell = 1169
		  {750, 1732.1},					// IDPicocell = 1170
		  {375, 1948.6},					// IDPicocell = 1171
};

static double
GetMaxDistanceFromCenter (int nbCell, double radius)
{
  double maxPosition;

  switch (nbCell)
    {
      case 1:
        maxPosition = radius;
        break;
      case 7:
    	maxPosition = (radius * (sqrt(3)/2)) * 3;
    	break;
      case 19:
    	maxPosition = (radius * (sqrt(3)/2)) * 5;
    	break;
      default:
    	maxPosition = radius;
    	break;
    }
  return maxPosition;
}

static CartesianCoordinates
GetCartesianCoordinatesForCell (int idCell, double radius)
{
  double x;
  double y;

  switch (idCell)
    {
      case 0:
    	  x = 0;
    	  y = 0;
    	  break;

      case 1:
    	  x = 0;
    	  y = radius * sqrt(3);
          break;

      case 2:
    	  x = - (radius + (radius/2));
    	  y = radius * (sqrt(3)/2);
          break;

      case 3:
    	  x = - (radius + (radius/2));
    	  y = - (radius * (sqrt(3)/2));
          break;

      case 4:
    	  x = 0;
    	  y = - (radius * sqrt(3));
          break;

      case 5:
    	  x = radius + (radius/2);
    	  y = - (radius * (sqrt(3)/2));
          break;

      case 6:
    	   x = radius + (radius/2);
    	   y = radius * (sqrt(3)/2);
           break;

      case 7:
    	   x = 0;
    	   y = 2 * (radius * sqrt(3));
          	  break;

      case 8:
    	   x = - (radius + (radius/2));
    	   y = 3 * (radius * (sqrt(3)/2));
          	  break;

      case 9:
    	   x = - (3 * radius);
    	   y = radius * sqrt(3);
          	  break;

      case 10:
    	  x = - (3 * radius);
    	  y = 0;
          break;

      case 11:
    	   x = - (3 * radius);
    	   y = - (radius * sqrt(3));
          	  break;

      case 12:
    	  x = - (radius + (radius/2));
    	   y = - (3 * (radius * (sqrt(3)/2)));
          	  break;

      case 13:
    	   x = 0;
    	   y = - (2 * (radius * sqrt(3)));
           break;

      case 14:
    	  x = radius + (radius/2);
    	  y = - (3 * (radius * (sqrt(3)/2)));
          break;

      case 15:
    	   x = 3 * radius;
    	   y = - (radius * sqrt(3));
           break;

      case 16:
    	  x = 3 * radius;
    	  y = 0;
          break;

      case 17:
    	   x = 3 * radius;
    	   y = radius * sqrt(3);
           break;

      case 18:
    	  x = radius + (radius/2);
    	  y = 3 * (radius * (sqrt(3)/2));
		  break;


    }

  CartesianCoordinates coordinates;
  coordinates.SetCoordinates(x,y);
  return coordinates;
}

static double
GetTopology_Border (void)
{
  int nbCell = NetworkManager::Init()->GetNbCell();

  switch (nbCell)
    {
      case 1:
    	  return (NetworkManager::Init()->GetCellByID (0)->GetRadius () * 1000);
    	  break;
      case 7:
    	  return ((2.6 * NetworkManager::Init()->GetCellByID (0)->GetRadius ()) * 1000);
    	  break;
      case 19:
          return ((4. * NetworkManager::Init()->GetCellByID (0)->GetRadius ()) * 1000);
          break;
      default:
    	  return 1000.0;
    	  break;
    }
}

#endif /* CELLPOSITION_H_ */
