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
    if (init(WINDOW, RENDERER, "Coding Math - Ep. 4", WIDTH, HEIGHT))
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

    double center_x = WIDTH / 2;
    double center_y = HEIGHT / 2;
    double speed = 0.03;
    int radius = 100;
    int x_radius = 100;
    int y_radius = 175;
    double x_speed = 0.05;
    double y_speed = 0.06;
    int obj_count = 10;
    double slice = (2 * 3.14) / obj_count;

    int draw = 0;
    double angle = 0;
    double x_angle = 0;
    double y_angle = 0;
    int x;
    int y;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            quit = is_quit(e);
            if (e.type == SDL_KEYDOWN && !e.key.repeat && e.key.keysym.sym == SDLK_RETURN)
            {
                draw = (draw + 1) % 5;
            }
        }
        SDL_SetRenderDrawColor(RENDERER, 0x33, 0x33, 0x33, 0xff);
        SDL_RenderClear(RENDERER);

        angle += speed;
        x_angle += x_speed;
        y_angle += y_speed;

        switch (draw)
        {
            case 0: {
                // 4.1 Circular
                stringRGBA(RENDERER, 10, 10, "4.1 Circular", 0xe8, 0x61, 0x00, 0xff);
                x = center_x + (cos(angle) * radius);
                y = center_y + (sin(angle) * radius);
                filledCircleRGBA(RENDERER, x, y, 10, 0xe8, 0x61, 0x00, 0xff);
                break;
            }
            case 1: {
                // 4.2 Elliptical
                stringRGBA(RENDERER, 10, 10, "4.2 Elliptical", 0xe8, 0x61, 0x00, 0xff);
                x = center_x + (cos(angle) * x_radius);
                y = center_y + (sin(angle) * y_radius);
                filledCircleRGBA(RENDERER, x, y, 10, 0xe8, 0x61, 0x00, 0xff);
                break;
            }
            case 2: {
                // 4.3 Lissajous
                stringRGBA(RENDERER, 10, 10, "4.3 Lissajous", 0xe8, 0x61, 0x00, 0xff);
                x = center_x + (cos(x_angle) * radius);
                y = center_y + (sin(y_angle) * radius);
                filledCircleRGBA(RENDERER, x, y, 10, 0xe8, 0x61, 0x00, 0xff);
                break;
            }
            case 3: {
                // 4.4 Layout
                stringRGBA(RENDERER, 10, 10, "4.4 Layout", 0xe8, 0x61, 0x00, 0xff);
                for (int i = 0; i <= obj_count; i++)
                {
                    x = center_x + (cos(i * slice) * radius);
                    y = center_y + (sin(i * slice) * radius);
                    filledCircleRGBA(RENDERER, x, y, 10, 0xe8, 0x61, 0x00, 0xff);
                }
                break;
            }
            case 4: {
                // 4.5 Animated Layout
                stringRGBA(RENDERER, 10, 10, "4.5 Animated Layout", 0xe8, 0x61, 0x00, 0xff);
                for (int i = 0; i <= obj_count; i++)
                {
                    x = center_x + (cos(i * slice + angle) * (100 * cos(angle)));
                    y = center_y + (sin(i * slice + angle) * (100 * cos(angle)));
                    filledCircleRGBA(RENDERER, x, y, 10, 0xe8, 0x61, 0x00, 0xff);
                }
                break;
            }
        }

        SDL_RenderPresent(RENDERER);
        SDL_Delay(15);
    }
}
