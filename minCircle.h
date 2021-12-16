/*
 * minCircle.h
 *
 * Author: 313361560 Shahar Rapp, 205866163 Ze'ev Binnes.
 */

#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

// you can add here additional methods
Circle findMinCircle(vector<Point> points);

#endif /* MINCIRCLE_H_ */
