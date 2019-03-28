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
bool init(SDL_Window* &window, SDL_Renderer* &renderer, const char* title, const int width, const int height)
{
    bool success = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed to initialize SDL:" << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            std::cout << "Failed to create window:" << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr)
            {
                std::cout << "Failed to create renderer:" << SDL_GetError() << std::endl;
            }
            else
            {
                SDL_RenderSetLogicalSize(renderer, width, height);
            }
        }
    }

    return success;
}

void close(SDL_Window* &window)
{
    SDL_DestroyWindow(window);
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
