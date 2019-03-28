#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

#include "helpers.h"

const int WIDTH = 400;
const int HEIGHT = 400;
SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

void loop();

int main(int argc, char* args[])
{
    if (init(WINDOW, RENDERER, "Coding Math - Ep. 5", WIDTH, HEIGHT))
    {
        loop();
    }

    close(WINDOW);
    return 0;
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
            quit = is_quit(e);
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
        SDL_Delay(15);
    }
}
