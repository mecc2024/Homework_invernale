#include <ostream>
#include <iostream>
using std::endl;
#include <cmath>
#include "Boid.h"

#define MINSPEED 1
#define MAXSPEED 10

// Helper functions for class Velocity
Velocity::Velocity(double x_velocity, double y_velocity)
        :vx{x_velocity}, vy{y_velocity}
{
    if (vx < MINSPEED)
        vx = MINSPEED;
}

const Velocity& default_velocity()
{
	static Velocity v{MINSPEED,MINSPEED};   
	return v;
}

Velocity::Velocity()
        :vx{default_velocity().get_vx()},
         vy{default_velocity().get_vy()}
{
}

// set x velocity
void Velocity::set_vx(double x_vel){
	vx = x_vel;
}

// set y velocity
void Velocity::set_vy(double y_vel){
	vy = y_vel;
}

// return vx
double Velocity::get_vx() const{
    return vx;
}

// return vy
double Velocity::get_vy() const{
    return vy;
}

// return magnitude
double Velocity::magnitude() const
{
	return sqrt(vx*vx + vy*vy);
}

// return direction
double Velocity::direction() const
{
	if(vx == 0)
		return 0;
	else
		return atan(vy/vx);
}