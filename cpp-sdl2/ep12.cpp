#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include <vector>

#include "vector.h"
#include "particle.h"
#include "helpers.h"

const int WIDTH = 1280;
const int HEIGHT = 720;
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

void wrapping(particle &p)
{
    stringRGBA(RENDERER, 10, 10, "12.1 Wrapping", 0xe8, 0x61, 0x00, 0xff);

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
}

void removal(std::vector<particle> &ps)
{
    stringRGBA(RENDERER, 10, 10, "12.2 Removal", 0xe8, 0x61, 0x00, 0xff);

    for (particle &p : ps)
    {
        p.update();
        filledCircleRGBA(RENDERER, p.position.x, p.position.y, p.radius, 0xe8, 0x61, 0x00, 0xff);
    }

    for (auto it = ps.begin(); it != ps.end();)
    {
        particle &p = *it;
        if (p.position.x - p.radius > WIDTH ||
            p.position.x + p.radius < 0 ||
            p.position.y - p.radius > HEIGHT ||
            p.position.y + p.radius < 0)
        {
            std::cout << "Erasing: " << p << std::endl;
            ps.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void loop()
{
    bool quit = false;
    int draw = 0;
    int draw_count = 2;
    SDL_Event e;

    particle p(WIDTH / 2, HEIGHT / 2, 3, randf() * PI * 2);
    p.radius = 80;

    std::vector<particle> ps;
    for (int i = 0; i < 100; i++)
    {
        ps.push_back(particle(WIDTH / 2, HEIGHT / 2, randf() * 5 + 2, randf() * PI * 2));
        ps[i].radius = 10;
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
                    case SDLK_RETURN: {
                        draw = (draw + 1) % draw_count;
                        std::cout << "Now drawing " << draw << std::endl;
                        break;
                    }
                    case SDLK_r: {
                        std::cout << "Resetting..." << std::endl;
                        break;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(RENDERER, 0x33, 0x33, 0x33, 0xff);
        SDL_RenderClear(RENDERER);

        switch (draw)
        {
            case 0: wrapping(p); break;
            case 1: removal(ps); break;
        }

        SDL_RenderPresent(RENDERER);
        SDL_Delay(15);
    }
}
