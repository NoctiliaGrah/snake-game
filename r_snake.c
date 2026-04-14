//
// Requires SDL2 to compile, installation instructions here:
// https://wiki.libsdl.org/SDL2/Installation
//
// Noctilia Grah, 2026
//
// DESCRIPTION:
// Snake movement code
//
// DESCRIPTION:
// Snake rendering
//

#include <stdio.h> // used for printing to console
#include <SDL2/SDL.h> // graphics/sound/input library

#include "snakegame.h"
#include "snakedefs.h"

#include "r_main.h"




//
// R_DrawSnake
//
void R_DrawSnake(SDL_Surface* window_surface, SnakeElement* snake)
{
    if (snake != NULL)
    {
        SNAKE(snake->x, snake->y);
        R_DrawSnake(window_surface,
                    snake->next_element);
    }

}
