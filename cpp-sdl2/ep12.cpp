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
    if (init(WINDOW, RENDERER, "Coding Math - Ep. 12", WIDTH, HEIGHT))
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

    particle p(WIDTH / 2, HEIGHT / 2, 3, randf() * PI * 2);
    p.radius = 80;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            quit = is_quit(e);
        }
        SDL_SetRenderDrawColor(RENDERER, 0x33, 0x33, 0x33, 0xff);
        SDL_RenderClear(RENDERER);

        p.update();
        if (p.position.x + p.radius < 0)
            p.position.x = WIDTH + p.radius;
        if (p.position.x - p.radius > WIDTH)
            p.position.x = -p.radius;
        if (p.position.y + p.radius < 0)
            p.position.y = HEIGHT + p.radius;
        if (p.position.y - p.radius > HEIGHT)
            p.position.y = -p.radius;

        filledCircleRGBA(RENDERER, p.position.x, p.position.y, p.radius, 0xe8, 0x61, 0x00, 0xff);

        SDL_RenderPresent(RENDERER);
        SDL_Delay(15);
    }
}
