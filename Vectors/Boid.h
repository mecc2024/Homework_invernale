#ifndef BOID_H
#define BOID_H
#include <ostream>
#include <vector>
#include <mutex>

// Point class to define the position of boids
class Point
{
private:
    float x; // coordinata x
    float y; // coordinata y

public:
    Point(float x, float y);
    Point();

    // const members: can't modify the object
    float get_x() const;
    float get_y() const;

    // setter
    void set_x(float x);
    void set_y(float y);
};

// Velocity class to define boid's velocity
class Velocity
{
private:
    float vx; //x-velocity
    float vy; //y-velocity
public:
    // constructors
    Velocity(float vx, float vy);
    Velocity();

    // const members: can't modify the object
    float get_vx() const;
    float get_vy() const;
	float magnitude() const;
	float direction() const;

    // setter
    void set_vx(float x);
    void set_vy(float y);
};

// Boid class to define the boid entity
class Boid
{
private:
    Point pos;
    Velocity vel;
    std::mutex myMutex_;
public:
    Boid(Point pos,Velocity vel);
    Boid();

    // const members: can't modify the object
	Point position() const;
	Velocity vector() const;

    // Costruttore di copia
    Boid(const Boid& other);

    // Costruttore di spostamento
    Boid(Boid&& other);
    
    // Assegnazione di copia
    Boid& operator=(const Boid& other);

    // Assegnazione di spostamento
    Boid& operator=(Boid&& other);

    // position update
    void pos_update();

    // alignment, cohesion and separation functions 
    void separation(const std::vector<Boid>& otherBoids, float avoidfactor, float d_sep);
    void alignment(const std::vector<Boid>& otherBoids, float alignfactor, float d_ca);
    void cohesion(const std::vector<Boid>& otherBoids, float centeringfactor, float d_ca);

    // screen borders and speed limits
    void handleScreenBorders(float left_margin, float right_margin, float bottom_margin, float top_margin, float turn_factor);
    void limitSpeed(float min_speed, float max_speed);

};

// Operators
std::ostream& operator<<(std::ostream& os, const Point& p);
std::ostream& operator<<(std::ostream& os, const Velocity& v);
std::ostream& operator<<(std::ostream& os, const Boid& b);

#endif