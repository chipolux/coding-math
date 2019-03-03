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

    int draw = 0;
    vec2 pos(100, 100);
    vec2 vel(0, 0, 3, 0.5235);
    particle par(0, 0, 3, 0.5235);

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
            else if (e.type == SDL_KEYDOWN && !e.key.repeat)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_RETURN: draw = (draw + 1) % 3; break;
                    case SDLK_r: {
                        pos.x = 100; pos.y = 100;
                        par.position.x = 100; par.position.y = 100;
                        for (int i = 0; i < 100; i++)
                        {
                            pars[i].position.x = 100; pars[i].position.y = 100;
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
                // 8.1 Velocity and Position
                stringRGBA(RENDERER, 10, 10, "8.1 Velocity and Position", 0xe8, 0x61, 0x00, 0xff);
                pos += vel;
                filledCircleRGBA(RENDERER, pos.x, pos.y, 20, 0xe8, 0x61, 0x00, 0xff);
                break;
            }
            case 1: {
                // 8.2 Particle
                stringRGBA(RENDERER, 10, 10, "8.2 Particle", 0xe8, 0x61, 0x00, 0xff);
                par.update();
                filledCircleRGBA(RENDERER, par.position.x, par.position.y, 20, 0xe8, 0x61, 0x00, 0xff);
                break;
            }
            case 2: {
                // 8.3 Particles
                stringRGBA(RENDERER, 10, 10, "8.3 Particles", 0xe8, 0x61, 0x00, 0xff);
                for (int i = 0; i < 100; i++)
                {
                    pars[i].update();
                    filledCircleRGBA(RENDERER, pars[i].position.x, pars[i].position.y, 20, 0xe8, 0x61, 0x00, 0xff);
                }
                break;
            }
        }

        SDL_RenderPresent(RENDERER);
        SDL_Delay(15);
    }
}
