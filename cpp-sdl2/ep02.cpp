#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

#include "helpers.h"

const int WIDTH = 1280;
const int HEIGHT = 720;
SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

void loop();

int main(int argc, char* args[])
{
    if (init(WINDOW, RENDERER, "Coding Math - Ep. 2", WIDTH, HEIGHT))
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

    double angle;
    int x;
    int y;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            quit = is_quit(e);
        }
        SDL_SetRenderDrawColor(RENDERER, 0x33, 0x33, 0x33, 0xff);
        SDL_RenderClear(RENDERER);

        angle = 0.00;
        while (angle < (3.14 * 2))
        {
            x = angle * 200;
            y = (sin(angle) * 200) + (HEIGHT / 2);
            rectangleColor(RENDERER, x, y, x + 5, y + 5, 0xff0000ff);
            angle += 0.01;
        }

        SDL_RenderPresent(RENDERER);
        SDL_Delay(15);
    }
}
