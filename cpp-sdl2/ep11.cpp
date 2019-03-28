#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

#include "vector.h"
#include "particle.h"
#include "helpers.h"

const int WIDTH = 800;
const int HEIGHT = 600;
SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

void loop();

int main(int argc, char* args[])
{
    if (init(WINDOW, RENDERER, "Coding Math - Ep. 11", WIDTH, HEIGHT))
    {
        loop();
    }

    close(WINDOW);
    return 0;
}

void loop()
{
    bool quit = false;
    SDL_Event e;

    particle sun(WIDTH / 2, HEIGHT / 2);
    sun.mass = 20000;
    particle planet(WIDTH / 2 + 200, HEIGHT / 2, 10, -3.1415 / 2);

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            quit = is_quit(e);
        }
        SDL_SetRenderDrawColor(RENDERER, 0x33, 0x33, 0x33, 0xff);
        SDL_RenderClear(RENDERER);

        planet.gravitateTo(sun);
        planet.update();

        filledCircleRGBA(RENDERER, sun.position.x, sun.position.y, 20, 0xef, 0xcc, 0x00, 0xff);
        filledCircleRGBA(RENDERER, planet.position.x, planet.position.y, 10, 0x00, 0x93, 0xaf, 0xff);

        SDL_RenderPresent(RENDERER);
        SDL_Delay(15);
    }
}
