#include <ostream>
#include <iostream>
using std::endl;
#include <cmath>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "Boid.h"

const float MINSPEED = 0.0;
const float MAXSPEED = 5;

// Helper functions for class Velocity
Velocity::Velocity(float x_velocity, float y_velocity)
        :vx{x_velocity}, vy{y_velocity}
{
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
void Velocity::set_vx(float x_vel){
	vx = x_vel;
}

// set y velocity
void Velocity::set_vy(float y_vel){
	vy = y_vel;
}

// return vx
float Velocity::get_vx() const{
    return vx;
}

// return vy
float Velocity::get_vy() const{
    return vy;
}