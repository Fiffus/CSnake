#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "entities/tile.h"
#include "entities/snake.h"
#include "entities/grid.h"
#include "entities/point.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"


#define GRID_SIZE 20
#define WIN_WIDTH GRID_SIZE*TILE_WIDTH
#define WIN_HEIGHT GRID_SIZE*TILE_HEIGHT


int main() {
    srand(time(0));

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        return 1;
    }

    if (TTF_Init() < 0) {
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Snake", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WIN_WIDTH, WIN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("resources/fonts/inter.ttf", 128);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface_message;
    SDL_Texture* message;
    SDL_Rect* message_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    int message_width = 400;
    int message_height = 140;
    message_rect->x = WIN_WIDTH/2-message_width/2;
    message_rect->y = WIN_HEIGHT/2-message_height/2;
    message_rect->w = message_width;
    message_rect->h = message_height;

    int quit = 0;
    int lost = 0;
    int won = 0;
    Uint32 delay = SDL_GetTicks();

    SDL_Event event;

    Grid* grid = grid_create(GRID_SIZE);
    Snake* snake = snake_create(GRID_SIZE);
    Point* point = point_create(snake, GRID_SIZE);

    while (!quit) {

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    point_relocate(point, snake, GRID_SIZE);
                    snake_reset(snake, GRID_SIZE);
                    grid_set_default_color(grid);
                    won = 0;
                    lost = 0;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (!won && !lost) {
            grid_update(grid, snake, point, &delay, &lost);

            won = snake->size == GRID_SIZE*GRID_SIZE-1;

            if (won) {
                surface_message = TTF_RenderText_Solid(font, "You won!", white); 
                message = SDL_CreateTextureFromSurface(renderer, surface_message);
            }

            if (lost) {
                surface_message = TTF_RenderText_Solid(font, "You lost!", white);
                message = SDL_CreateTextureFromSurface(renderer, surface_message);
            }
        }

        grid_draw(grid, renderer);

        if (won) {
            SDL_RenderCopy(renderer, message, NULL, message_rect);
        }

        if (lost) {
            SDL_RenderCopy(renderer, message, NULL, message_rect);
        }
        
        SDL_RenderPresent(renderer);
    }
    
    grid_free(grid);
    point_free(point);
    snake_free(snake);

    free(message_rect);
    SDL_DestroyTexture(message);
    free(surface_message);
    free(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
