#include "entities/snake.h"
#include "utils.h"
#include "SDL2/SDL.h"
#include <time.h>


Snake* snake_create(const int grid_size) {
    Snake* snake = (Snake*)malloc(sizeof(Snake));

    Position* head = (Position*)malloc(sizeof(Position));
    head->x = rand_range(0, grid_size-1);
    head->y = rand_range(0, grid_size-1);
    snake->head = head;

    snake->body = (Position**)malloc(sizeof(Position*)*grid_size*grid_size-1); // head not included
    for (int i = 0; i < grid_size*grid_size-1; i++) {
        snake->body[i] = (Position*)malloc(sizeof(Position*));
    }

    snake->direction = 'n';
    snake->prev_direction = 'n';
    snake->size = 0;

    return snake;
}

void snake_change_direction(Snake* snake) {
    const Uint8* state = SDL_GetKeyboardState(0);

    if (state[SDL_SCANCODE_W]) {
        if ((snake->direction != 'b' && snake->prev_direction != 'b') || snake->size == 0) 
            snake->direction = 't';
    } else if (state[SDL_SCANCODE_A]) {
        if ((snake->direction != 'r' && snake->prev_direction != 'r') || snake->size == 0)
            snake->direction = 'l';
    } else if (state[SDL_SCANCODE_S]) {
        if ((snake->direction != 't' && snake->prev_direction != 't') || snake->size == 0)
            snake->direction = 'b';
    } else if (state[SDL_SCANCODE_D]) {
        if ((snake->direction != 'l' && snake->prev_direction != 'l') || snake->size == 0)
            snake->direction = 'r';
    }
}

void snake_move(Snake* snake, Grid* grid, int* collided) {
    switch (snake->direction) {
        case 'n': 
            return;
        case 't':
            if (snake->head->y - 1 > -1) {
                if (snake_collided_with_self(snake, 0, -1)) {
                    *collided = 1;
                    break;
                }
                snake->head->y--;
                break;
            }
            *collided = snake_collided_with_wall(snake, grid->size);
            break;
        case 'l':
            if (snake->head->x - 1 > -1) {
                 if (snake_collided_with_self(snake, -1, 0)) {
                    *collided = 1;
                    break;
                }
                snake->head->x--;
                break;
            }
            *collided = snake_collided_with_wall(snake, grid->size);
            break;
        case 'b':
            if (snake->head->y + 1 < grid->size) {
                 if (snake_collided_with_self(snake, 0, 1)) {
                    *collided = 1;
                    break;
                }
                snake->head->y++;
                break;
            }
            *collided = snake_collided_with_wall(snake, grid->size);
            break;
        case 'r':
            if (snake->head->x + 1 < grid->size) {
                 if (snake_collided_with_self(snake, 1, 0)) {
                    *collided = 1;
                    break;
                }
                snake->head->x++;
                break;
            }
            *collided = snake_collided_with_wall(snake, grid->size);
            break;
    }
}

void snake_free(Snake* snake) {
    free(snake->head);
    for (int i = 0; i < snake->size; i++) {
        free(snake->body[i]);
    }
    free(snake->body);
    free(snake);
}

void snake_consume(Snake* snake, Point* point, const int grid_size) {
    if (snake->head->x == point->x && snake->head->y == point->y) {
        point_relocate(point, snake, grid_size);
        snake->size++;
    }
}

void snake_track_body(Snake* snake) {
    for (int i = snake->size; i > 0; i--) {
        snake->body[i]->x = snake->body[i-1]->x;
        snake->body[i]->y = snake->body[i-1]->y;
    }
    snake->body[0]->x = snake->head->x;
    snake->body[0]->y = snake->head->y;
}

void snake_update(Snake* snake, Point* point, Grid* grid, Uint32* delay, int* collided) {
    snake_change_direction(snake);

    if (*delay < SDL_GetTicks()) {
        snake_track_body(snake);
        snake_move(snake, grid, collided);
        *delay = SDL_GetTicks()+150;
        snake->prev_direction = snake->direction;
    }
    
    snake_colorize(snake, grid);
    snake_consume(snake, point, grid->size);
}

void snake_colorize(Snake* snake, Grid* grid) {
    for (int i = 0; i < snake->size; i++) {
        int row = snake->body[i]->y;
        int col = snake->body[i]->x;
        
        grid_colorize(grid, col, row, SNAKE_BODY_RGB);
    }
    grid_colorize(grid, snake->head->x, snake->head->y, SNAKE_HEAD_RGB);
}

void snake_reset(Snake* snake, int grid_size) {
    for (int i = 0; i < snake->size; i++) {
        snake->body[i]->x = 0;
        snake->body[i]->y = 0;
    }
    snake->size = 0;
    snake->head->x = rand_range(0, grid_size-1);
    snake->head->y = rand_range(0, grid_size-1);
    snake->direction = 'n';
    snake->prev_direction = 'n';
}

int snake_collided_with_self(Snake* snake, int move_x, int move_y) {
    for (int i = 0; i < snake->size; i++) {
        if (
            (snake->head->x+move_x) == snake->body[i]->x && \
            (snake->head->y+move_y) == snake->body[i]->y
        ) {
            return 1;
        }
    }
    return 0;
}

int snake_collided_with_wall(Snake* snake, int grid_size) {
    switch (snake->direction) {
        case 'n': 
            return 0;
        case 't':
            return snake->head->y == 0;
        case 'l':
            return snake->head->x == 0;
        case 'b':
            return snake->head->y == grid_size - 1;
        case 'r':
            return snake->head->x == grid_size - 1;
    }
    return 0;
}