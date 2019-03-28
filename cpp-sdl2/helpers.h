#ifndef HELPERS_H
#define HELPERS_H

#include <SDL2/SDL.h>
#include <math.h>


// Math Helpers
#define PI 3.141592653589793

double randf()
{
    return (double)rand() / (double)RAND_MAX;
}


// SDL2 Helpers
SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

bool init(const char* title, const int WIDTH, const int HEIGHT)
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

bool is_quit(const SDL_Event &e)
{
    if (e.type == SDL_QUIT)
    {
        return true;
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
    {
        return true;
    }
    return false;
}

#endif  // HELPERS_H
