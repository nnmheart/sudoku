#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#include<assert.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

#include<app.h>
#include<sudoku.h>

app_t* app;
sudoku_t* sud;

void game_handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: 
                print("Received SDL_QUIT signal.\n");
                app->running = false;
                break;
            default:
                break;
        }
    }
}
void game_update(double dt) {
}

void game_render() {
    SDL_SetRenderDrawColor(app->renderer, 150, 150, 150, 255);
    SDL_RenderClear(app->renderer);

    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(
        app->renderer,
        &(SDL_Rect){
            .x = app->grid_x,
            .y = app->grid_y,
            .w = app->grid_w,
            .h = app->grid_h
        }
    );

    int cw = app->grid_w / 9;
    int ch = app->grid_h / 9;

    // Cells
    for (int cy = 0; cy < 9; cy++) {
        for (int cx = 0; cx < 9; cx++) {
            //cell_t cell = sud->grid[cy][cx];
            SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(
                app->renderer,
                &(SDL_Rect){
                    .x = app->grid_x + cx * cw,
                    .y = app->grid_y + cy * ch,
                    .w = cw,
                    .h = ch
                }
            );
        }
    }
    // Sub grid separators
    SDL_SetRenderDrawColor(app->renderer, 220, 220, 220, 255);
    // Horizontal
    SDL_RenderFillRect(
        app->renderer,
        &(SDL_Rect){
            .x = app->grid_x,
            .y = app->grid_y + 3 * ch - 1,
            .w = app->grid_w,
            .h = 2
        }
    );
    SDL_RenderFillRect(
        app->renderer,
        &(SDL_Rect){
            .x = app->grid_x,
            .y = app->grid_y + 6 * ch - 1,
            .w = app->grid_w,
            .h = 2
        }
    );
    // Vertical
    SDL_RenderFillRect(
        app->renderer,
        &(SDL_Rect){
            .x = app->grid_x + 3 * cw - 1,
            .y = app->grid_y,
            .w = 2,
            .h = app->grid_h
        }
    );
    SDL_RenderFillRect(
        app->renderer,
        &(SDL_Rect){
            .x = app->grid_x + 6 * cw - 1,
            .y = app->grid_y,
            .w = 2,
            .h = app->grid_h
        }
    );

    SDL_RenderPresent(app->renderer);
}

int main(int argc, char** argv) {
    app = (app_t*)malloc(sizeof(app_t));
    app->running = true;
    app->screen_width = 800;
    app->screen_height = 600;

    assert(SDL_Init(SDL_INIT_EVERYTHING) == 0);
    app->window = SDL_CreateWindow(
        "Sudoku", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        app->screen_width, app->screen_height, 
        0
    );
    assert(app->window != NULL);
    app->renderer = SDL_CreateRenderer(app->window, -1, 0);
    assert(app->renderer != NULL);
    assert(SDL_SetRenderDrawBlendMode(app->renderer, SDL_BLENDMODE_BLEND) == 0);
    print("Initialized application window and renderer.\n");
    assert(TTF_Init() == 0);
    app->font = TTF_OpenFont("./OpenSans-Regular.ttf", 24);
    assert(app->font != NULL);

    sud = sudoku_create();

    ////////////////////////////

    app->grid_x = app->screen_width * 0.1;
    app->grid_y = app->screen_height * 0.1;
    app->grid_w = app->screen_width * 0.5;
    app->grid_h = app->screen_height * 0.7;
    app->grid_w -= (app->grid_w % 9);
    app->grid_h -= (app->grid_h % 9);

    ///////////////////////////
    
    double last_tick = (double)SDL_GetTicks();
    double current_tick = (double)SDL_GetTicks();
    double delta_accum = 0.0;
    double frametime = 1.0 / 50.0;

    print("Entering the mainloop.\n");
    while (app->running) {
        current_tick = (double)SDL_GetTicks();
        delta_accum += (current_tick - last_tick) / 1000.0;
        last_tick = current_tick;
        
        game_handle_events();
        while (delta_accum >= frametime) {
            game_update(frametime);
            delta_accum -= frametime;
        }
        game_render();
    }

    return 0;
}