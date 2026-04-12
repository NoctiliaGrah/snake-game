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
// GameLoop
// TODO: This is horrific
//
int GameLoop()
{
    // ugly struct but putting it anywhere else
    // breaks things, i'll fix it later (never)
    SnakeElement snake = {INIT_X, INIT_Y,
                          TAIL_INIT_X, TAIL_INIT_Y,
                          NULL};
    Direction direction = {0,0}; // x, y
    AppleLocation apple = {0,0}; // x, y

    // used for parsing the values within these
    // structs to functions without using the
    // structs themselves.
    SnakeElement *snake_pointer = &snake;
    Direction *direction_pointer = &direction;
    AppleLocation *apple_pointer = &apple;

    // new_segment prototype because the compiler is retarded
    SnakeElement *new_segment =
        (SnakeElement*)malloc(sizeof(SnakeElement));

    SDL_Rect override_rect = {0,0,window_width, window_height};

    bool is_growing = false;
    bool has_grown = false;

    bool gameOn = true;

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

    // i don't know why but if it isn't here, everything breaks.
    ResetApple(snake_pointer, apple_pointer);
    // MAIN GAME LOOP
    while (gameOn)
    {
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

// FIXME: pressing L/R at the same time as U/D will often cause the
// snake to go back into itself due to both inputs being made before
// a frame is finished.
//
// SOLUTION: hold onto the second input for any given frame and override
// whatever input is being given on the frame afterwards, preferrably
// also holding onto that overridden input and using it for the next frame.
//
// this requires some finicking because you'll have to discard the second
// input of the overridden frame in order to not cause the bug to happen
// if these types of inputs happen two or more times in a row.

            // TODO: ^ that.

            if (event.type == SDL_KEYDOWN)
            {
                if (has_grown)
                {
                    //printf("DEBUG: has_grown init dx = %d, dy = %d\n",
                    //       direction.dx, direction.dy);
                    if (event.key.keysym.sym == SDLK_LEFT &&
                        direction.dx != DIR_RIGHT)
                    {
                        direction.dx = DIR_LEFT;
                        direction.dy = DIR_RESET;
                        //printf("DIR_LEFT, ");
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT &&
                        direction.dx != DIR_LEFT)
                    {
                        direction.dx = DIR_RIGHT;
                        direction.dy = DIR_RESET;
                        //printf("DIR_RIGHT, ");
                    }
                    if (event.key.keysym.sym == SDLK_UP &&
                        direction.dy != DIR_DOWN)
                    {
                        direction.dy = DIR_UP;
                        direction.dx = DIR_RESET;
                        //printf("DIR_UP, ");
                    }
                    if (event.key.keysym.sym == SDLK_DOWN &&
                        direction.dy != DIR_UP)
                    {
                        direction.dy = DIR_DOWN;
                        direction.dx = DIR_RESET;
                        //printf("DIR_DOWN, ");
                    }
                    //printf("DEBUG: has_grown final dx = %d, dy = %d\n",
                           //direction.dx, direction.dy);
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
    P_MoveSnake(snake_pointer, direction_pointer, is_growing);

    // HACKHACK: Unfortunately, I have to manually set the
    // is_growing flag to false after it gets set to true so
    // that it doesn't activate each frame. It's the easiest
    // way to do this, but I want something better. I don't
    // know if it's possible, though.
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
