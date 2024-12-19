#pragma once

#include "entities/tile.h"
#include "entities/point.h"
#include <SDL2/SDL_render.h>
#include <stdlib.h>

struct Snake;
struct Point;
struct Tile;
struct RGB;

typedef struct Grid {
    struct Tile** tiles;
    int size;
} Grid;


Grid* grid_create(const int size);

void grid_draw(Grid* grid, SDL_Renderer* renderer);

void grid_free(Grid* grid);

void grid_update(Grid* grid, struct Snake* snake, struct Point* point, Uint32* delay, int* snake_collided);

void grid_colorize(Grid* grid, const int x, const int y, struct RGB rgb);

void grid_set_default_color(Grid* grid);

struct Tile* grid_get(Grid* grid, const int x, const int y);