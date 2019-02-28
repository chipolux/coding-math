#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

const int WIDTH = 400;
const int HEIGHT = 400;

SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

bool init(const char* title);
void close();
void loop();

int main(int argc, char* args[])
{
    if (init("Coding Math - Ep. 3"))
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
            RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
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

    double angle = 0;
    double offset = HEIGHT * 0.4;
    double speed = 0.05;
    int radius;
    int alpha;
    int x;
    int y;


    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(RENDERER, 0x33, 0x33, 0x33, 0xff);
        SDL_RenderClear(RENDERER);

        angle += speed;

        // 3.1 Oscillate
        x = WIDTH / 2;
        y = (HEIGHT / 2) + (sin(angle) * offset);
        radius = 20;
        filledCircleRGBA(RENDERER, x, y, radius, 0xe8, 0x61, 0x00, 0xff);

        // 3.2 Grow
        x = (WIDTH / 2) - 50;
        y = HEIGHT / 2;
        radius = 20 + (10 * sin(angle));
        filledCircleRGBA(RENDERER, x, y, radius, 0xe8, 0x61, 0x00, 0xff);

        // 3.3 Fade
        x = (WIDTH / 2) + 50;
        y = HEIGHT / 2;
        radius = 20;
        alpha = 127 + (127 * sin(angle));
        filledCircleRGBA(RENDERER, x, y, radius, 0xe8, 0x61, 0x00, alpha);

        SDL_RenderPresent(RENDERER);
        SDL_Delay(15);
    }
}
