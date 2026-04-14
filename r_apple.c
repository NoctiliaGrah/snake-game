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
// R_DrawApple
//
void R_DrawApple(SDL_Surface* window_surface, Apple *apple_pointer)
{
    if (apple_pointer != NULL)
    {
        APPLE(apple_pointer->x,apple_pointer->y);
        R_DrawApple(window_surface, apple_pointer->next_element);
    }
}
