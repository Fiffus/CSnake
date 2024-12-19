#include "entities/point.h"
#include <stdlib.h>


Point* point_create(Snake* snake, const int grid_size) {
    Point* point = (Point*)malloc(sizeof(Point));

    point_relocate(point, snake, grid_size);

    return point;
}

void point_free(Point* point) {
    if (!point) {
        return;
    }

    free(point);
}

void point_relocate(Point* point, Snake* snake, const int grid_size) {
    int x = rand_range(0, grid_size-1);
    int y = rand_range(0, grid_size-1);

    
    if (snake->head->x == x && snake->head->y == y) {
        point_relocate(point, snake, grid_size);
        return;
    }

    int spawned_in_snake = 0;
    for (int i = 0; i < snake->size; i++) {
        if (snake->body[i]->x == x && snake->body[i]->y == y) {
            spawned_in_snake = 1;
            break;
        }
    }

    if (spawned_in_snake) {
        point_relocate(point, snake, grid_size);
        return;
    }

    point->x = x;
    point->y = y;
}

void point_colorize(Point* point, Grid* grid) {
    grid_colorize(grid, point->x, point->y, POINT_RGB);
}