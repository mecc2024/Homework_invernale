#include <ostream>
using std::ostream;
#include <iostream>
using std::endl;
#include "Boid.h"

// Helper functions for class Point
Point::Point(double x, double y) 
     :x{x}, y{y} 
{
}

// default constructor
const Point& default_position()
{
	static Point p{0,0};   
	return p;
}

Point::Point()
	 :x{default_position().get_x()},
	  y{default_position().get_y()}
{
}

// set x position
void Point::set_x(double x_pos){
	x = x_pos;
}

// set y position
void Point::set_y(double y_pos){
	y = y_pos;
}

// return x position
double Point::get_x() const{
    return x;
}

// return y position
double Point::get_y() const{
    return y;
}