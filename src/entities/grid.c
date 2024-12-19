#include "entities/grid.h"

#include "utils.h"

Grid* grid_create(const int size) {
    Grid* grid = (Grid*)calloc(sizeof(Grid), 1);
    grid->tiles = (Tile**)calloc(sizeof(Tile*), size * size);
    grid->size = size;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            Tile* tile = tile_create(
                col, row, 
                TILE_WIDTH, TILE_HEIGHT, 
                DEFAULT_RGB
            );
            grid->tiles[row*grid->size+col] = tile;
        }
    }

    return grid;
}

void grid_draw(Grid* grid, SDL_Renderer* renderer) {
    for (int row = 0; row < grid->size; row++) {
        for (int col = 0; col < grid->size; col++) {
            tile_draw(grid_get(grid, col, row), renderer);
        }
    }
}

void grid_free(Grid* grid) {
    if (!grid) {
        return;
    }

    if (grid->tiles) {
        for (int row = 0; row < grid->size; row++) {
            for (int col = 0; col < grid->size; col++) {
                Tile* tile = grid_get(grid, col, row);
                tile_free(tile);
            }
        }
        free(grid->tiles);
    }

    free(grid);
}

void grid_update(Grid* grid, Snake* snake, Point* point, Uint32* delay, int* snake_collided) {
    grid_set_default_color(grid);
    snake_update(snake, point, grid, delay, snake_collided);
    point_colorize(point, grid);
}

void grid_colorize(Grid* grid, const int x, const int y, RGB rgb) {
    free(grid->tiles[y*grid->size+x]->rgb);

    tile_colorize(grid->tiles[y*grid->size+x], rgb);
}

void grid_set_default_color(Grid* grid) {
    for (int row = 0; row < grid->size; row++) {
        for (int col = 0; col < grid->size; col++) {
            grid_colorize(grid, col, row, DEFAULT_RGB);
        }
    }
}

Tile* grid_get(Grid* grid, const int x, const int y) {
    return grid->tiles[(y * grid->size) + x];
}