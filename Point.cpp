#include <ostream>
using std::ostream;
#include <iostream>
using std::cerr;
using std::endl;
#include "Boid.h"

// Helper functions for class Point
Point::Point(int x, int y) :x{x}, y{y} {}

// default constructor
const Point& default_position()
{
	static Point p{0,0};   // randon position in a 50x50 square
	return p;
}

Point::Point()
	:x{default_position().get_x()},
	 y{default_position().get_y()}
{
}

int Point::get_x() const{
    return x;
}

int Point::get_y() const{
    return y;
}