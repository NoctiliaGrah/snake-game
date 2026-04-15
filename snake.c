//
// Requires SDL2 to compile, installation instructions here:
// https://wiki.libsdl.org/SDL2/Installation
//
// Noctilia Grah, 2026
//
// DESCRIPTION:
// Game loop.
//

#include <stdio.h> // used for printing to console
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h> // graphics/sound/input library

#include "snakegame.h"
#include "snakedefs.h"

#include "r_main.h"
#include "r_snake.h"
#include "r_apple.h"

#include "p_snake.h"
#include "p_apple.h"




//
// GameLoop
// TODO: This is horrific!
//
void GameLoop()
{
Direction direction = {0, 0}; // x, y
Apple apple = {0, 0, NULL}; // x, y, next_element
SnakeElement snake = {INIT_X, INIT_Y, TAIL_INIT_X, TAIL_INIT_Y, NULL};

Direction *direction_pointer = &direction;
AppleLocation *apple_pointer = &apple;
SnakeElement *snake_pointer = &snake;

InputBuffer inpbf1 = {I_BUFFER_INIT,I_BUFFER_INIT};
InputBuffer inpbf2 = {I_BUFFER_INIT,I_BUFFER_INIT};
InputBuffer inpbfdsc = {I_BUFFER_INIT,I_BUFFER_INIT};

InputBuffer *input_buffer1 = &inpbf1;
InputBuffer *input_buffer2 = &inpbf2;
InputBuffer *discard_buffer = &inpbfdsc;

SDL_Rect override_rect = {0,0,window_width, window_height};

bool is_growing = false;
bool has_grown = false;
bool game_on = true;
bool buffer_flush_flag = false;



// video & event init
SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER);

SDL_Window* window =
SDL_CreateWindow("Snake",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                 window_width,window_height,window_flags);
SDL_Surface* window_surface = SDL_GetWindowSurface(window);

// i don't know why but if this isn't here, everything breaks
P_ResetApple(snake_pointer, apple_pointer);

    while (game_on)
    {
        P_FlushBuffers1(input_buffer1, input_buffer2, &buffer_flush_flag);
        P_ProcessInput(direction_pointer, input_buffer1, input_buffer2,
                       discard_buffer, &game_on, &has_grown);
        if (snake_pointer->x == apple.x && snake_pointer->y == apple.y)
            {
                P_ResetApple(snake_pointer, apple_pointer);
                is_growing = true;
                has_grown  = true;
            }
        P_FlushBuffers2(input_buffer1, discard_buffer,
                        direction_pointer,
                        &buffer_flush_flag);
        P_Collide(snake_pointer, &game_on);
        P_MoveSnake(snake_pointer, direction_pointer, is_growing);

        is_growing = false;

        // RENDERING
        SDL_FillRect(window_surface, &override_rect, COLOR_BLACK);

        R_DrawApple(window_surface, apple_pointer);
        R_DrawSnake(window_surface, &snake);
        R_DrawGrid(window_surface);
        SDL_UpdateWindowSurface(window);

        SDL_Delay(TICKRATE);
    }
}




int main()
{
    // simple hello world
    printf("Hello Snake!\n");

    GameLoop();
    return 0;
}

