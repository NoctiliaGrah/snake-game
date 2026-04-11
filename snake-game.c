// Most of this is taken from various tutorial on YouTube that
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
               SnakeElement* snake,
               Tail *tail_pointer)
{
    if (snake != NULL && tail_pointer != NULL)
{
        SNAKE(snake->x, snake->y);

        struct Tail *current = tail_pointer;
        while (current != NULL)
        {
            TAIL(current->x,  current->y);
            current = current->tail;
            continue;
        }
        DrawSnake(window_surface,
                  snake->next_element,
                  tail_pointer->tail);
}

}

//
// ResetApple
// TODO: Rewrite this so it isn't horrific
//
void ResetApple(SnakeElement *snake_pointer,
                Apple *apple_pointer,
                Tail *tail_pointer)
{


    // if the apple coordinates collide with the snake
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

            // check the snake's tail
            Tail *current = tail_pointer->tail;
            while (current != NULL)
                {
                if (apple_pointer->x == current->x &&
                    apple_pointer->y == current->y)
                    {
                        valid_position = false;
                        break;
                    }

                    current = current->tail;
                }
        }


}

//
// ResetApple
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
// TODO: This is ugly, fix it
//
int GameLoop()
{
    // ugly struct but putting it anywhere else
    // breaks things, i'll fix it later (never)
    SnakeElement snake = {5,5,4,4,4,4,NULL};
    Direction direction = {0,0};
    AppleLocation apple = {0,0};

    SnakeElement *snake_pointer = &snake;
    Direction *direction_pointer = &direction;
    AppleLocation *apple_pointer = &apple;

    Tail tail = {5,5,4,5,NULL};
    Tail *tail_pointer = &tail;



    ResetApple(snake_pointer, apple_pointer, tail_pointer);
    SDL_Rect override_rect = {0,0,window_width, window_height};

    bool is_growing = false;
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
                     window_width, window_height, 0);

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);

    // MAIN GAME LOOP
    while (gameOn)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                gameOn = false;

            if (event.type == SDL_KEYDOWN)
            {
                direction = (struct Direction) {0,0};
                    // garbage temporary implementation
                    if (event.key.keysym.sym == SDLK_LEFT)
                        direction.dx = -1;
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        direction.dx = 1;
                    if (event.key.keysym.sym == SDLK_UP)
                        direction.dy = -1;
                    if (event.key.keysym.sym == SDLK_DOWN)
                        direction.dy = 1;
            }
        }

        // blank the screen before drawing the snake elements
        SDL_FillRect(window_surface, &override_rect, COLOR_BLACK);


        // if the snake eats the apple
        if (snake_pointer->x == apple.x && snake_pointer->y == apple.y)
        {
            ResetApple(snake_pointer,
                       apple_pointer,
                       tail_pointer);
            is_growing = true;
        }

        P_MoveSnake(snake_pointer, direction_pointer, tail_pointer);
        DrawApple(window_surface, apple_pointer);
        DrawSnake(window_surface, &snake, &tail);
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

