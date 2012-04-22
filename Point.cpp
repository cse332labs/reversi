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

ostream& operator<<(ostream& stream, const Point& point)
{
	stream << point.x_ << ", " << point.y_;

	return stream;
}