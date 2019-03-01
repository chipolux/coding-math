#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

const int WIDTH = 400;
const int HEIGHT = 400;
const char* TITLE = "Coding Math - Ep. 5";

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

void draw_arrow(int x, int y, double angle)
{
    // 2d rotation matrix:
    //   x1 = x * cos(a) - y * sin(a)
    //   y1 = x * sin(a) + y * cos(a)
    double ca = cos(angle);
    double sa = sin(angle);
    int x1 = (0 * ca - 20 * sa) + x;
    int y1 = (0 * sa + 20 * ca) + y;
    int x2 = (10 * ca - 10 * sa) + x;
    int y2 = (10 * sa + 10 * ca) + y;
    int x3 = (-10 * ca - 10 * sa) + x;
    int y3 = (-10 * sa + 10 * ca) + y;
    int x4 = (0 * ca + 20 * sa) + x;
    int y4 = (0 * sa - 20 * ca) + y;

    thickLineRGBA(RENDERER, x1, y1, x4, y4, 3, 0xe8, 0x61, 0x00, 0xff);
    thickLineRGBA(RENDERER, x2, y2, x1, y1, 3, 0xe8, 0x61, 0x00, 0xff);
    thickLineRGBA(RENDERER, x3, y3, x1, y1, 3, 0xe8, 0x61, 0x00, 0xff);
}

void loop()
{
    bool quit = false;
    SDL_Event e;

    double center_x = WIDTH / 2;
    double center_y = HEIGHT / 2;
    double speed = 0.03;

    double angle = 0;
    double mouse_angle = 0;
    int mouse_x;
    int mouse_y;
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
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(RENDERER, 0x33, 0x33, 0x33, 0xff);
        SDL_RenderClear(RENDERER);

        angle += speed;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        // 5.1 Static Arrow
        mouse_angle = atan2(mouse_y - center_y, mouse_x - center_x) - (3.14 / 2);
        draw_arrow(center_x, center_y, mouse_angle);

        // 5.2 Mobile Arrow
        x = cos(angle) * 100 + center_x;
        y = sin(angle) * 100 + center_y;
        mouse_angle = atan2(mouse_y - y, mouse_x - x) - (3.14 / 2);
        draw_arrow(x, y, mouse_angle);

        SDL_RenderPresent(RENDERER);
    }
}
