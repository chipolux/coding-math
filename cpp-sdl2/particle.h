#ifndef PARTICLE_H
#define PARTICLE_H

#include <math.h>
#include "vector.h"

struct particle
{
    vec2 position;
    vec2 velocity;
    vec2 gravity;

    particle(double x=0, double y=0, double s=0, double d=0, double g=0)
    {
        position = vec2(x, y);
        velocity = vec2(0, 0, s, d);
        gravity = vec2(0, g);
    }

    void update() { velocity += gravity; position += velocity; }
    void accelerate(const vec2& acceleration) { velocity += acceleration; }
    void set_position(double x, double y) { position.x = x; position.y = y; }
    void set_velocity(double speed, double direction)
    {
        velocity.set_length(speed);
        velocity.set_angle(direction);
    }
};

#endif  // PARTICLE_H
