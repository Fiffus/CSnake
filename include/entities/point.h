#pragma once

#include "utils.h"
#include "entities/grid.h"

struct Grid;
struct Snake;
typedef struct Point {
    int y, x;
} Point;


Point* point_create(struct Snake* snake, const int grid_size);

void point_free(Point* point);

void point_relocate(Point* point, struct Snake* snake, const int grid_size);

void point_colorize(Point* point, struct Grid* grid);