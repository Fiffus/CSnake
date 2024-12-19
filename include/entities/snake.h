#pragma once

#include "SDL2/SDL.h"
#include "entities/grid.h"
#include "entities/point.h"

struct Grid;
struct Point;

typedef struct Position {
    int x, y;
} Position;


typedef struct Snake {
    Position* head;
    Position** body;
    char direction;
    char prev_direction; // prevents bug that occurs when player selects too many directions in 1 interval
    int size;
} Snake;


Snake* snake_create(const int grid_size);

void snake_change_direction(Snake* snake);

void snake_move(Snake* snake, struct Grid* grid, int* collided);

void snake_free(Snake* snake);

void snake_consume(Snake* snake, struct Point* point, const int grid_size);

void snake_track_body(Snake* snake);

void snake_update(Snake* snake, struct Point* point, struct Grid* grid, Uint32* delay, int* collided);

void snake_colorize(Snake* snake, struct Grid* grid);

void snake_reset(Snake* snake, int grid_size);

int snake_collided_with_self(Snake* snake, int move_x, int move_y);

int snake_collided_with_wall(Snake* snake, int grid_size);