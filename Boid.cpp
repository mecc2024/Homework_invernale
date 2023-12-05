#include <ostream>
using std::ostream;
#include <iostream>
using std::cerr;
using std::endl;
#include <random>
using std::rand;
#include <cmath>
#include "Boid.h"

#define MINSPEED 1;
#define MAXSPEED 10;

// Helper functions for class Boid
const Point& default_position()
{
	static Point p{0,0};   // randon position in a 50x50 square
	return p;
}

const Velocity& default_velocity()
{
	static Velocity v{0,0};   // default speed equal to (1,1)
	return v;
}

Boid::Boid(Point position, Velocity vectvelocity_vector)
    :pos{position}, vel{vectvelocity_vector}
{
}

Boid::Boid()
    :pos{default_position().get_x(),default_position().get_y()},
     vel{default_velocity().get_vx(),default_velocity().get_vy()}
{
}

// return position
Point Boid::position() const
{
    return pos;
}

// return velocity
Velocity Boid::vector() const
{
    return vel;
}

// Operators
ostream& operator<<(ostream& os, const Point& p)
{
	return os << '(' << p.get_x()
		<< ',' << p.get_y() << ')';
}

ostream& operator<<(ostream& os, const Velocity& v)
{
	return os << '(' << v.magnitude()
		<< ',' << v.direction() << ')';
}

ostream& operator<<(ostream& os, const Boid& b)
{
	return os << "Position: " << b.position()
		<< ", Velocity: " << b.vector() << endl;
}