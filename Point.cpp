//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// Point.cpp

#include "stdafx.h"
#include "point.h" 

// the definition for the constructor for a Point. 
Point::Point(unsigned int x, unsigned int y)
	: x_(x), y_(y) {}

//default constructor
Point::Point()
	:x_(0), y_(0){}

//overloaded operator for comparing points used for sorting & access. 
bool Point::operator< (const Point& p) const
{
	return( x_ < p.x_ ) || (( x_ == p.x_ ) && ( y_ < p.y_ ));
}

// sets the values of x_ and y_ to x and y
void Point :: set (int x, int y)
{
	x_ = x;
	y_ = y;
	return;
}

// prints out the Point by printing out x_,y_
ostream& operator<<(ostream& stream, const Point& point)
{
	stream << point.x_ << "," << point.y_;
	return stream;
}