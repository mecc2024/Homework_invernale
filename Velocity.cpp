#include <ostream>
using std::ostream;
#include <iostream>
using std::cerr;
using std::endl;
#include <cmath>
#include "Boid.h"

#define MINSPEED 1
#define MAXSPEED 10

// Helper functions for class Velocity
Velocity::Velocity(int x_velocity,int y_velocity)
        :vx{x_velocity}, vy{y_velocity}
{
    if (vx < MINSPEED)
        vx = MINSPEED;

}

const Velocity& default_velocity()
{
	static Velocity v{0,0};   // default speed equal to (1,1)
	return v;
}

Velocity::Velocity()
        :vx{default_velocity().get_vx()},
         vy{default_velocity().get_vy()}
{
}

// return vx
int Velocity::get_vx() const{
    return vx;
}

// return vy
int Velocity::get_vy() const{
    return vy;
}

// return magnitude
double Velocity::magnitude() const
{
	return sqrt((vx*vx) + (vy*vy));
}

// return direction
double Velocity::direction() const
{
	if(vx == 0)
		return 0;
	else
		return atan(vy/vx);
}