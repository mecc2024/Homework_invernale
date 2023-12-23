#ifndef BOID_H
#define BOID_H
#include <ostream>

// Point class to define the position of boids
class Point
{
private:
    double x; // coordinata x
    double y; // coordinata y

public:
    Point(double x, double y);
    Point();

    // const members: can't modify the object
    double get_x() const;
    double get_y() const;

    // setter
    void set_x(double x);
    void set_y(double y);
};

// Velocity class to define boid's velocity
class Velocity
{
private:
    double vx; //x-velocity
    double vy; //y-velocity
public:
    // constructors
    Velocity(double vx, double vy);
    Velocity();

    // const members: can't modify the object
    double get_vx() const;
    double get_vy() const;
	double magnitude() const;
	double direction() const;

    // setter
    void set_vx(double x);
    void set_vy(double y);
};

// Boid class to define the boid entity
class Boid
{
private:
    Point pos;
    Velocity vel;
public:
    Boid(Point pos,Velocity vel);
    Boid();

    // const members: can't modify the object
	Point position() const;
	Velocity vector() const;

    // position update
    void pos_update();
};

// Operators
std::ostream& operator<<(std::ostream& os, const Point& p);
std::ostream& operator<<(std::ostream& os, const Velocity& v);
std::ostream& operator<<(std::ostream& os, const Boid& b);

#endif