#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

#include "vector.h"
#include "particle.h"
#include "helpers.h"

const int WIDTH = 1280;
const int HEIGHT = 900;
SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

void loop();

int main(int argc, char* args[])
{
    if (init(WINDOW, RENDERER, "Coding Math - Ep. 9", WIDTH, HEIGHT))
    {
        loop();
    }

    close(WINDOW);
    return 0;
}

void reset_particle(particle& p)
{
    p.set_position(WIDTH / 2, WIDTH / 3);
    p.set_velocity((randf() * 5) + 2, randf() * 3.14 * 2);
}

void loop()
{
    bool quit = false;
    SDL_Event e;

    int draw = 0;
    vec2 gravity(0, 0.1);
    particle p(0, HEIGHT, 10, -1.5707);
    particle pars1[100];
    for (int i = 0; i < 100; i++)
    {
        pars1[i] = particle(WIDTH / 2, HEIGHT / 3, (randf() * 5) + 2, randf() * 3.14 * 2);
    }
    particle pars2[100];
    for (int i = 0; i < 100; i++)
    {
        pars2[i] = particle(WIDTH / 2, HEIGHT / 3, (randf() * 5) + 2, randf() * 3.14 * 2, 0.1);
    }

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            quit = is_quit(e);
            if (e.type == SDL_KEYDOWN && !e.key.repeat)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_RETURN: draw = (draw + 1) % 3; break;
                    case SDLK_r: {
                        p.set_position(0, HEIGHT);
                        p.set_velocity(10, -1.5707);
                        for (int i = 0; i < 100; i++)
                        {
                            reset_particle(pars1[i]);
                            reset_particle(pars2[i]);
                        }
                        break;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(RENDERER, 0x33, 0x33, 0x33, 0xff);
        SDL_RenderClear(RENDERER);

        switch (draw)
        {
            case 0: {
                // 9.1 Ball
                stringRGBA(RENDERER, 10, 10, "9.1 Ball", 0xe8, 0x61, 0x00, 0xff);
                p.accelerate(vec2(0.1, 0.1));
                p.update();
                filledCircleRGBA(RENDERER, p.position.x, p.position.y, 5, 0xe8, 0x61, 0x00, 0xff);
                break;
            }
            case 1: {
                // 9.2 Fireworks
                stringRGBA(RENDERER, 10, 10, "9.2 Fireworks", 0xe8, 0x61, 0x00, 0xff);
                for (int i = 0; i < 100; i++)
                {
                    pars1[i].accelerate(vec2(0.0, 0.1));
                    pars1[i].update();
                    filledCircleRGBA(RENDERER, pars1[i].position.x, pars1[i].position.y, 5, 0xe8, 0x61, 0x00, 0xff);
                }
                break;
            }
            case 2: {
                // 9.3 Fireworks 2
                stringRGBA(RENDERER, 10, 10, "9.3 Fireworks 2", 0xe8, 0x61, 0x00, 0xff);
                for (int i = 0; i < 100; i++)
                {
                    pars2[i].update();
                    filledCircleRGBA(RENDERER, pars2[i].position.x, pars2[i].position.y, 5, 0xe8, 0x61, 0x00, 0xff);
                }
                break;
            }
        }

        SDL_RenderPresent(RENDERER);
        SDL_Delay(15);
    }
}
