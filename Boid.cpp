#include <ostream>
using std::ostream;
using namespace std;
#include <iostream>
#include <random>
using std::rand;
#include <cmath>
#include "Boid.h"

#define MINSPEED 1
#define MAXSPEED 10

// Helper functions for class Boid
Boid::Boid(Point position, Velocity vectvelocity_vector)
    :pos{position}, vel{vectvelocity_vector}
{
}

// Default constructor
Boid::Boid()
    :pos{0,0},
     vel{MINSPEED,MINSPEED}
{
}

// return position
Point Boid::position() const
{
    return pos;
}

// Position update
void Boid::pos_update(){
	pos.set_x(pos.get_x() + vel.get_vx());
	pos.set_y(pos.get_y() + vel.get_vy());
}

// Operators
ostream& operator<<(ostream& os, const Point& p)
{
	return os << p.get_x() << ' ' << p.get_y();
}

ostream& operator<<(ostream& os, const Boid& b)
{
	return os << b.position();
}