#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

#include "vector.h"
#include "particle.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "Coding Math - Ep. 11";

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
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN && !e.key.repeat)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE: quit = true; break;
                }
            }
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
