#ifndef _APP_H
#define _APP_H

#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#define print(...) printf("[%s]: ", __func__); printf(__VA_ARGS__);

typedef struct app_t {
    bool running;
    int screen_width;
    int screen_height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    int grid_x;
    int grid_y;
    int grid_w;
    int grid_h;
} app_t;

#endif // _APP_H