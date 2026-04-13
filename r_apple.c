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
