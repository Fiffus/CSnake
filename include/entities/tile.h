#pragma once

#include "entities/snake.h"
#include "SDL2/SDL.h"

#define TILE_WIDTH 50
#define TILE_HEIGHT 50

#define DEFAULT_RGB (RGB) { \
    .r = 35, \
    .g = 35, \
    .b = 35, \
}
#define POINT_RGB (RGB) { \
    .r = 210, \
    .g = 210, \
    .b = 40, \
}
#define SNAKE_HEAD_RGB (RGB) { \
    .r = 60, \
    .g = 60, \
    .b = 230, \
}
#define SNAKE_BODY_RGB (RGB) { \
    .r = 60, \
    .g = 60, \
    .b = 180, \
}

typedef struct RGB {
    int r;
    int g;
    int b;
} RGB;


typedef struct Tile {
    int x, y;
    int w, h;
    RGB* rgb;
} Tile;


Tile* tile_create(const int x, const int y, const int w, const int h, const RGB rgb);

void tile_free(Tile* tile);

void tile_colorize(Tile* tile, RGB rgb);

void tile_draw(Tile *tile, SDL_Renderer* renderer);