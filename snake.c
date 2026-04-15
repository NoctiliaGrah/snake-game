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

SnakeElement *new_segment =                  // new_segment prototype because
(SnakeElement*)malloc(sizeof(SnakeElement)); // the compiler is braindead

bool is_growing = false;
bool has_grown = false;
bool game_on = true;
bool buffer_flush_flag = false;

// video & event init
SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER);
SDL_Event event;
SDL_Window* window =
SDL_CreateWindow("Snake",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                 window_width,window_height,window_flags);
SDL_Surface* window_surface = SDL_GetWindowSurface(window);

// i don't know why but if this
// isn't here, everything breaks
P_ResetApple(snake_pointer, apple_pointer);

    while (game_on)
    {

        P_FlushBuffers1(input_buffer1, input_buffer2, &buffer_flush_flag);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                {
                    free(new_segment);
                    new_segment = NULL;

                    game_on = false;
                }


            if (event.type == SDL_KEYDOWN)
            {

                // TODO: Move this to its own file

                // HACKHACK: We need a way to tell if the snake
                // has eaten an apple yet and change the movement
                // to be free or locked accordingly. This is the
                // simplest implementation I could think of, but
                // it is very bad and ugly and horrible and not
                // at all scaleable in any way. Oh well!
                //
                // If the snake hasn't eaten an apple yet, let
                // it move freely, but if it has eaten one, don't
                // let it move in the direction opposite of where
                // it's currently moving.
                //
                // If a key for a specific direction is pressed
                // and if the snake isn't going in the opposite
                // direction, set the x/y to the right value and
                // and reset the perpendicular axis back to the
                // initial value.
                //
                // Secretly, the values for the directions are
                // just -1 and 1, with the reset being 0, but
                // don't let John know that or he will get mad!

                if (has_grown)
                {
                    if (event.key.keysym.sym == SDLK_LEFT &&
                        direction.dx != DIR_RIGHT)
                    {
                        direction.dx = DIR_LEFT;
                        direction.dy = DIR_RESET;
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT &&
                        direction.dx != DIR_LEFT)
                    {
                        direction.dx = DIR_RIGHT;
                        direction.dy = DIR_RESET;
                    }
                    if (event.key.keysym.sym == SDLK_UP &&
                        direction.dy != DIR_DOWN)
                    {
                        direction.dy = DIR_UP;
                        direction.dx = DIR_RESET;
                    }
                    if (event.key.keysym.sym == SDLK_DOWN &&
                        direction.dy != DIR_UP)
                    {
                        direction.dy = DIR_DOWN;
                        direction.dx = DIR_RESET;
                    }
                    P_InputBuffers(input_buffer1, input_buffer2,
                                   discard_buffer, direction_pointer);
                }
                else
                {
                    direction_pointer->dx = DIR_RESET;
                    direction_pointer->dy = DIR_RESET;
                    if (event.key.keysym.sym == SDLK_LEFT)
                    {
                        direction_pointer->dx = DIR_LEFT;
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT)
                    {
                        direction_pointer->dx = DIR_RIGHT;
                    }
                    if (event.key.keysym.sym == SDLK_UP)
                    {
                        direction_pointer->dy = DIR_UP;
                    }
                    if (event.key.keysym.sym == SDLK_DOWN)
                    {
                        direction_pointer->dy = DIR_DOWN;
                    }
                }
            }
        }
        

        if (snake_pointer->x == apple.x && snake_pointer->y == apple.y)
            {
                P_ResetApple(snake_pointer, apple_pointer);
                is_growing = true;
                has_grown  = true;
            }


        P_FlushBuffers2(input_buffer1, discard_buffer,
                        direction_pointer, &buffer_flush_flag);
        P_Collide(snake_pointer, &game_on);
        P_MoveSnake(snake_pointer, direction_pointer, is_growing);

        // HACKHACK: only here so it isn't true every frame
        is_growing = false;

        // clear the screen and render everthing
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

