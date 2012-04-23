//Lab 4 - Nine Almonds and Magic Squares
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
// Point.h

#include "stdafx.h"

#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <ostream>

using namespace std;

// a struct that represents a simple cartesian point of unsigned ints (i.e. positive only).
struct Point{
	Point(unsigned int x, unsigned int y);
	Point();
	bool operator< (const Point&) const;
	void set(int x, int y);
	int x_;
	int y_;
};

ostream& operator<<(ostream& stream, const Point& point);

#endif