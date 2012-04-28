//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
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