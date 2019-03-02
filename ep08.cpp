#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

#include "vector.h"
#include "particle.h"

const int WIDTH = 400;
const int HEIGHT = 400;
const char* TITLE = "Coding Math - Ep. 8";

SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

bool init(const char* title);
void close();
void loop();

int main(int argc, char* args[])
{
    if (init(TITLE))
    {
        loop();
    }

    close();
    return 0;
}

bool init(const char* title)
{
    bool success = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed to initialize SDL:" << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        WINDOW = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (WINDOW == nullptr)
        {
            std::cout << "Failed to create window:" << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (RENDERER == nullptr)
            {
                std::cout << "Failed to create renderer:" << SDL_GetError() << std::endl;
            }
            else
            {
                SDL_RenderSetLogicalSize(RENDERER, WIDTH, HEIGHT);
            }
        }
    }

    return success;
}

void close()
{
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();
}

double randf()
{
    return (double)rand() / (double)RAND_MAX;
}

void loop()
{
    bool quit = false;
    SDL_Event e;

    /* vec2 pos(100, 100); */
    /* vec2 vel(0, 0, 3, 0.5235); */
    /* particle par(0, 0, 3, 0.5235); */

    particle pars[100];
    for (int i = 0; i < 100; i++)
    {
        pars[i] = particle(WIDTH / 2, HEIGHT / 2, (randf() * 4) + 1, randf() * 3.14 * 2);
    }

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(RENDERER, 0x33, 0x33, 0x33, 0xff);
        SDL_RenderClear(RENDERER);

        SDL_RenderPresent(RENDERER);
        SDL_Delay(15);
    }
}
