// Most of this is taken from various tutorials on YouTube that
// were modified to fit whatever I needed from it. It's very
// likely that this code will no longer be maintained or
// compile in [CURRENT YEAR], so take this more as a learning
// thing rather than something serious.
//
// Requires SDL2 to compile, installation instructions here:
// https://wiki.libsdl.org/SDL2/Installation
//
// - Noctilia Grah, 2026
//
// DESCRIPTION:
// Main snake code
//

#include <stdio.h> // used for printing to console
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h> // graphics/sound/input library

#include "snakegame.h"
#include "snakedefs.h"

#include "r_main.h"

#include "p_user.h"




//
// DrawSnake
// TODO: This is probably broken, also move it to a different file
//
void DrawSnake(SDL_Surface* window_surface,
               SnakeElement* snake)
{
    if (snake != NULL)
{
        SNAKE(snake->x, snake->y);
        DrawSnake(window_surface,
                  snake->next_element);
}

}




//
// ResetApple
// TODO: Rewrite this so it doesn't give me pain to look at
//
void ResetApple(SnakeElement *snake_pointer,
                Apple *apple_pointer)
{


    // if a valid position is available
    bool valid_position = false;
    while (!valid_position)
        {

            // make the new apple's position random
            apple_pointer->x = columns * ((double) rand() / RAND_MAX);
            apple_pointer->y = rows * ((double) rand() / RAND_MAX);

            valid_position = true;

            // check the snake's head
            if (apple_pointer->x == snake_pointer->x &&
                apple_pointer->y == snake_pointer->y)
                {
                    valid_position = false;
                    continue;
                }
            snake_pointer = snake_pointer->next_element;
        }
}


//
// DrawApple
// TODO: Move to a different file
//
void DrawApple(SDL_Surface* window_surface,
               Apple* apple_pointer)
{
    if (apple_pointer != NULL)
    {
    APPLE(apple_pointer->x,apple_pointer->y);
    DrawApple(window_surface, apple_pointer->next_element);
    }
}




//
// InputBuffering
//
// HACKHACK: pressing L/R at the same time as U/D will often cause the
// snake to move back into itself if the first input is the perpendicular
// to the current movement axis and if the parallel input is opposite of
// the current direction. For example, if the snake is moving left and
// you press right and up/down on the same frame, the snake will go back
// into itself if the up/down input is registered first and the right
// input is registered second.
//
// The solution? Hold onto the 2nd input a player gives for a certain
// frame and override the input on the next frame with it, preferably
// holding onto the new overridden input to use on the next frame as well.
// Originally I thought this would be a very shoddy method, but it ended
// up being so elegant that the implementation was pretty much perfect
// on my first attempt. It even had the side effect of adding proper input
// buffering, hence the name.
//
// This requires some setup in other areas, though, specifically in the
// game loop, meaning this won't scale up well unless the stuff in those
// places get moved somewhere else.
//
void InputBuffering(InputBuffer *input_buffer1,
                    InputBuffer *input_buffer2,
                    InputBuffer *discard_buffer,
                    Direction *direction_pointer)
{

    if (input_buffer1->x == I_BUFFER_INIT &&
        input_buffer1->y == I_BUFFER_INIT)
        {
        input_buffer1->x = direction_pointer->dx;
        input_buffer1->y = direction_pointer->dy;
        }
    else if (input_buffer2->x == I_BUFFER_INIT &&
            input_buffer2->y == I_BUFFER_INIT)
            {
        input_buffer2->x = direction_pointer->dx;
        input_buffer2->y = direction_pointer->dy;
        }
    else
        {
        discard_buffer->x = direction_pointer->dx;
        discard_buffer->y = direction_pointer->dy;
        }

}




//
// GameLoop
// TODO: This is horrific!
//
int GameLoop()
{
    // ugly structs but putting it anywhere else breaks shit
    Direction direction = {0,0}; // x, y
    AppleLocation apple = {0,0}; // x, y
    SnakeElement snake = {INIT_X, INIT_Y,
        TAIL_INIT_X, TAIL_INIT_Y,
        NULL};

    SnakeElement *snake_pointer = &snake;
    Direction *direction_pointer = &direction;
    AppleLocation *apple_pointer = &apple;

    InputBuffer inpbf1 = {I_BUFFER_INIT,I_BUFFER_INIT};
    InputBuffer inpbf2 = {I_BUFFER_INIT,I_BUFFER_INIT};
    InputBuffer inpbfdsc = {I_BUFFER_INIT,I_BUFFER_INIT};

    InputBuffer *input_buffer1 = &inpbf1;
    InputBuffer *input_buffer2 = &inpbf2;
    InputBuffer *discard_buffer = &inpbfdsc;


    // new_segment prototype because the compiler is retarded
    SnakeElement *new_segment =
        (SnakeElement*)malloc(sizeof(SnakeElement));

    SDL_Rect override_rect = {0,0,window_width, window_height};

    bool is_growing = false;
    bool has_grown = false;
    bool gameOn = true;
    bool buffer_flush = false;


    // init video, timer (why?) & events
    // make the window
    // make the window surface
    SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER);
    SDL_Event event;

    SDL_Window* window =
    SDL_CreateWindow("Classic Snake",
                      SDL_WINDOWPOS_CENTERED,
                      SDL_WINDOWPOS_CENTERED,
                      window_width, window_height, window_flags);

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);

    // i don't know why but if this isn't here, everything breaks.
    ResetApple(snake_pointer, apple_pointer);
    // MAIN GAME LOOP
    while (gameOn)
    {

        // BUFFER_FLUSH, PART 1
        if (buffer_flush)
        {
            // copy input_buffer2 to input_buffer1
            input_buffer1->x = input_buffer2->x;
            input_buffer1->y = input_buffer2->y;

            // clear input_buffer2 if it isn't already empty
            if (input_buffer2->x != I_BUFFER_INIT &&
                input_buffer2->y != I_BUFFER_INIT)
                {
                input_buffer2->x = I_BUFFER_INIT;
                input_buffer2->y = I_BUFFER_INIT;
                }
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                {
                free(new_segment);
                new_segment = NULL;

                gameOn = false;
                }

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

            if (event.type == SDL_KEYDOWN)
            {
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
                    InputBuffering(input_buffer1, input_buffer2,
                                   discard_buffer, direction_pointer);
                }
                else
                {
                    direction.dx = DIR_RESET;
                    direction.dy = DIR_RESET;

                    if (event.key.keysym.sym == SDLK_LEFT)
                        direction.dx = DIR_LEFT;
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        direction.dx = DIR_RIGHT;
                    if (event.key.keysym.sym == SDLK_UP)
                        direction.dy = DIR_UP;
                    if (event.key.keysym.sym == SDLK_DOWN)
                        direction.dy = DIR_DOWN;
                    }
                }

            }


    // blank the screen before drawing the snake elements
    SDL_FillRect(window_surface, &override_rect, COLOR_BLACK);


    // if the snake eats the apple spawn the apple at a new
    // position set the is_growing flag to true so the snake
    // knows when to grow
    if (snake_pointer->x == apple.x && snake_pointer->y == apple.y)
        {
            ResetApple(snake_pointer,
                       apple_pointer);
            is_growing = true;
            has_grown  = true;
        }

    // BUFFER_FLUSH, PART 2
    // if input_buffer1 isn't empty, replace dx/dy with the buffer's values
    // then turn on the buffer_flush flag to drain the values again.
    // if input_buffer1 is empty, then we're done.
    if (input_buffer1->x != I_BUFFER_INIT &&
        input_buffer1->y != I_BUFFER_INIT)
        {
            direction.dx = input_buffer1->x;
            direction.dy = input_buffer1->y;
            buffer_flush = true;
        }
            else {
                    buffer_flush = false;

                    discard_buffer->x = I_BUFFER_INIT; // reset for safety
                    discard_buffer->y = I_BUFFER_INIT;
                 }
    P_MoveSnake(snake_pointer, direction_pointer, is_growing);

    // HACKHACK: set the growing to false so it doesn't occur every frame
    is_growing = false;

    DrawApple(window_surface, apple_pointer);
    DrawSnake(window_surface, &snake);
    R_DrawGrid(window_surface);

    SDL_UpdateWindowSurface(window);
    SDL_Delay(TICKRATE);

    }
}

int main()
{
    // simple hello world
    printf("Hello Snake\n");

    GameLoop();

}
