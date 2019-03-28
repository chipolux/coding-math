#ifndef PARTICLE_H
#define PARTICLE_H

#include <math.h>
#include "vector.h"

struct particle
{
    vec2 position;
    vec2 velocity;
    vec2 gravity;
    double mass;
    double radius;

    particle(double x=0, double y=0, double s=0, double d=0, double g=0, double m=1, double r=0)
    {
        position = vec2(x, y);
        velocity = vec2(0, 0, s, d);
        gravity = vec2(0, g);
        mass = m;
        radius = r;
    }

    void update() { velocity += gravity; position += velocity; }
    void accelerate(const vec2& acceleration) { velocity += acceleration; }
    void set_position(double x, double y) { position.x = x; position.y = y; }
    void set_velocity(double speed, double direction)
    {
        velocity.set_length(speed);
        velocity.set_angle(direction);
    }

    double angleTo(const particle& p)
    {
        return atan2(p.position.y - position.y, p.position.x - position.x);
    }

    double distanceTo(const particle& p)
    {
        double dx = p.position.x - position.x;
        double dy = p.position.y - position.y;
        return sqrt(dx * dx + dy * dy);
    }

    void gravitateTo(const particle& p)
    {
        vec2 grav = vec2(0, 0);
        double dist = distanceTo(p);
        grav.set_length(p.mass / (dist * dist));
        grav.set_angle(angleTo(p));
        velocity += grav;
    }
};

#endif  // PARTICLE_H
