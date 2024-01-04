#include <ostream>
using std::ostream;
#include <iostream>
#include <random>
using std::rand;
#include <cmath>
#include <mutex>
#include "Boid.h"

const float MINSPEED = 0.0;
const float MAXSPEED = 5;

const float LEFTMARGIN = 0.0;
const float RIGHTMARGIN = 500.0;
const float BOTTOMMARGIN = 0.0;
const float TOPMARGIN = 500.0;

// Helper functions for class Boid
Boid::Boid(Point position, Velocity velocity_vector)
    :pos{position}, vel{velocity_vector}
{
}

// Default constructor
Boid::Boid()
    :pos{static_cast<float>(rand()) / RAND_MAX * RIGHTMARGIN, static_cast<float>(rand()) / RAND_MAX * TOPMARGIN},
     vel{static_cast<float>(rand()) / RAND_MAX * MAXSPEED, static_cast<float>(rand()) / RAND_MAX * MAXSPEED}
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

// Costruttore di copia
Boid::Boid(const Boid& other)
    : pos(other.pos), vel(other.vel)
{
}

// Costruttore di spostamento
Boid::Boid(Boid&& other)
    : pos(std::move(other.pos)), vel(std::move(other.vel))
{
}

// Assegnazione di copia
Boid& Boid::operator=(const Boid& other)
{
    if (this != &other) {
        pos = other.pos;
        vel = other.vel;
    }
    return *this;
}

// Assegnazione di spostamento
Boid& Boid::operator=(Boid&& other)
{
    if (this != &other) {
        pos = std::move(other.pos);
        vel = std::move(other.vel);
    }
    return *this;
}

// Separation function
void Boid::separation(const std::vector<Boid>& all_boids, float avoidfactor, float d_sep) {
    float close_dx = 0.0;
    float close_dy = 0.0;

    for (const Boid& other_boid : all_boids) {
        if (&other_boid != this) {
            float distance = sqrt(pow(pos.get_x() - other_boid.position().get_x(), 2) +
                                  pow(pos.get_y() - other_boid.position().get_y(), 2));

            if (distance < d_sep) {
                close_dx += pos.get_x() - other_boid.position().get_x();
                close_dy += pos.get_y() - other_boid.position().get_y();
            }
        }
    }

    vel.set_vx(vel.get_vx() + close_dx * avoidfactor);
    vel.set_vy(vel.get_vy() + close_dy * avoidfactor);
}

// Alignment function
void Boid::alignment(const std::vector<Boid>& all_boids, float alignfactor, float d_ca) {
    float xvel_avg = 0.0;
    float yvel_avg = 0.0;
    int close_boids = 0;

    for (const Boid& other_boid : all_boids) {
        if (&other_boid != this) {
            float distance = sqrt(pow(pos.get_x() - other_boid.position().get_x(), 2) +
                                  pow(pos.get_y() - other_boid.position().get_y(), 2));

            if (distance < d_ca) {
                xvel_avg += other_boid.vel.get_vx();  // Utilizza vel invece di vector()
                yvel_avg += other_boid.vel.get_vy();  // Utilizza vel invece di vector()
                close_boids++;
            }
        }
    }

    if (close_boids > 0) {
        xvel_avg /= close_boids;
        yvel_avg /= close_boids;
        vel.set_vx(vel.get_vx() + (xvel_avg - vel.get_vx()) * alignfactor);
        vel.set_vy(vel.get_vy() + (yvel_avg - vel.get_vy()) * alignfactor);
    }
}

// Cohesion function
void Boid::cohesion(const std::vector<Boid>& all_boids, float centeringfactor, float d_ca) {
    float xpos_avg = 0.0;
    float ypos_avg = 0.0;
    int neighboring_boids = 0;

    for (const Boid& other_boid : all_boids) {
        if (&other_boid != this) {
            float distance = sqrt(pow(pos.get_x() - other_boid.position().get_x(), 2) +
                                  pow(pos.get_y() - other_boid.position().get_y(), 2));

            if (distance < d_ca) {
                xpos_avg += other_boid.position().get_x();
                ypos_avg += other_boid.position().get_y();
                neighboring_boids++;
            }
        }
    }

    if (neighboring_boids > 0) {
        xpos_avg = xpos_avg / neighboring_boids;
        ypos_avg = ypos_avg / neighboring_boids;
        vel.set_vx(vel.get_vx() + (xpos_avg - pos.get_x()) * centeringfactor);
        vel.set_vy(vel.get_vy() + (ypos_avg - pos.get_y()) * centeringfactor);
    }
}

// Funzione per gestire i bordi dello schermo
void Boid::handleScreenBorders(float left_margin, float right_margin, float bottom_margin, float top_margin, float turn_factor) {
    if (pos.get_x() < left_margin) {
        vel.set_vx(vel.get_vx() + turn_factor);
    }
    if (pos.get_x() > right_margin) {
        vel.set_vx(vel.get_vx() - turn_factor);
    }
    if (pos.get_y() > bottom_margin) {
        vel.set_vy(vel.get_vy() - turn_factor);
    }
    if (pos.get_y() < top_margin) {
        vel.set_vy(vel.get_vy() + turn_factor);
    }
}

// Funzione per limitare la velocità
void Boid::limitSpeed(float min_speed, float max_speed) {
    float speed = sqrt((vel.get_vx() * vel.get_vx()) + (vel.get_vy() * vel.get_vy()));

    if (speed > max_speed) {
        vel.set_vx((vel.get_vx() / speed) * max_speed);
        vel.set_vy((vel.get_vy() / speed) * max_speed);
    }

    if (speed < min_speed) {
        vel.set_vx((vel.get_vx() / speed) * min_speed);
        vel.set_vy((vel.get_vy() / speed) * min_speed);
    }
}

