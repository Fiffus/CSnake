#include "entities/tile.h"
#include <SDL2/SDL_render.h>

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

Tile* tile_create(const int x, const int y, const int w, const int h, RGB rgb) {
    Tile* tile = (Tile*)malloc(sizeof(Tile));

    tile->x = x;
    tile->y = y;
    tile->w = w;
    tile->h = h;

    tile_colorize(tile, rgb);

    return tile;
}

void tile_free(Tile* tile) {
    if (tile == NULL) {
        return;
    }

    if (tile->rgb) {
        free(tile->rgb);
    }
    
    free(tile);
}

void tile_colorize(Tile* tile, RGB rgb) {
    RGB* _rgb = (RGB*)malloc(sizeof(RGB));
    _rgb->r = rgb.r;
    _rgb->g = rgb.g;
    _rgb->b = rgb.b;
    tile->rgb = _rgb;
}

void tile_draw(Tile *tile, SDL_Renderer* renderer) {
    if (tile == NULL) {
        return;
    }

    SDL_Rect rect = {
        .x = tile->x*tile->w, .y = tile->y*tile->h,
        .w = tile->w, .h = tile->h,
    };

    SDL_SetRenderDrawColor(renderer, tile->rgb->r, tile->rgb->g, tile->rgb->b, 255);
    SDL_RenderFillRect(renderer, &rect);
}