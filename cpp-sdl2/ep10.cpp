#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include <algorithm>

#include "vector.h"
#include "particle.h"
#include "helpers.h"

const int WIDTH = 800;
const int HEIGHT = 600;
SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

const Sint16 BODY_X[] = {16,  2,  2,   5,  -4,  -6, -6, -4,  5, 2, 2, 16};
const Sint16 BODY_Y[] = { 0, -4, -7, -10, -12, -10, 10, 12, 10, 7, 4,  0};

const Sint16 FLAME_X[] = {-6, -12, -9, -15, -9, -12, -6};
const Sint16 FLAME_Y[] = {-6,  -5, -2,   0,  2,   5,  6};

void loop();

int main(int argc, char* args[])
{
    if (init(WINDOW, RENDERER, "Coding Math - Ep. 10", WIDTH, HEIGHT))
    {
        loop();
    }

    close(WINDOW);
    return 0;
}

void draw_ship(const particle& p, const double angle, const bool thrusting)
{
    // 2d rotation matrix:
    //   x1 = x * cos(a) - y * sin(a)
    //   y1 = x * sin(a) + y * cos(a)
    double ca = cos(angle);
    double sa = sin(angle);

    if (thrusting)
    {
        int fs = sizeof(FLAME_X)/sizeof(FLAME_X[0]);
        Sint16 fx[fs];
        Sint16 fy[fs];
        for (int i = 0; i < fs; i++)
        {
            fx[i] = p.position.x + (FLAME_X[i] * ca - FLAME_Y[i] * sa);
            fy[i] = p.position.y + (FLAME_X[i] * sa + FLAME_Y[i] * ca);
        }
        polygonRGBA(RENDERER, fx, fy, fs, 0xff, 0x00, 0x00, 0xff);
    }

    int bs = sizeof(BODY_X)/sizeof(BODY_X[0]);
    Sint16 bx[bs];
    Sint16 by[bs];
    for (int i = 0; i < bs; i++)
    {
        bx[i] = p.position.x + (BODY_X[i] * ca - BODY_Y[i] * sa);
        by[i] = p.position.y + (BODY_X[i] * sa + BODY_Y[i] * ca);
    }
    polygonRGBA(RENDERER, bx, by, bs, 0xe8, 0x61, 0x00, 0xff);
}

void loop()
{
    bool quit = false;
    SDL_Event e;

    particle ship(WIDTH / 2, HEIGHT / 2);
    vec2 thrust(0, 0);
    double angle = 0;
    int turning = 0;
    bool thrusting = false;
    char vel_str[] = "Velocity: 00.00";

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            quit = is_quit(e);
            if (e.type == SDL_KEYDOWN && !e.key.repeat)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_LEFT: turning = -1; break;
                    case SDLK_RIGHT: turning = 1; break;
                    case SDLK_UP: thrusting = true; break;
                }
            }
            else if (e.type == SDL_KEYUP && !e.key.repeat)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_LEFT: turning = 0; break;
                    case SDLK_RIGHT: turning = 0; break;
                    case SDLK_UP: thrusting = false; break;
                }
            }
        }
        SDL_SetRenderDrawColor(RENDERER, 0x33, 0x33, 0x33, 0xff);
        SDL_RenderClear(RENDERER);

        angle += 0.05 * turning;
        thrust.set_angle(angle);
        if (thrusting) { thrust.set_length(0.1); }
        else { thrust.set_length(0); }
        ship.accelerate(thrust);
        ship.velocity.set_length(std::min(15.0, ship.velocity.get_length()));
        ship.update();
        if (ship.position.x < 0)
            ship.position.x = WIDTH;
        if (ship.position.x > WIDTH)
            ship.position.x = 0;
        if (ship.position.y < 0)
            ship.position.y = HEIGHT;
        if (ship.position.y > HEIGHT)
            ship.position.y = 0;
        draw_ship(ship, angle, thrusting);

        sprintf(vel_str, "Velocity: %5.2f", ship.velocity.get_length());
        stringRGBA(RENDERER, 10, 10, vel_str, 0xe8, 0x61, 0x00, 0xff);

        SDL_RenderPresent(RENDERER);
        SDL_Delay(15);
    }
}
