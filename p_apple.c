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
// Apple/fruit/whatever behavior
//

#include <stddef.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "snakegame.h"
#include "snakedefs.h"

//
// P_ResetApple
// FIXME: This is horrifically inefficient
//
void P_ResetApple(SnakeElement *snake_pointer, Apple *apple_pointer)
{
    SnakeElement *current_node = snake_pointer;

    bool valid_position = false;
    while (!valid_position)
    {
        apple_pointer->x = columns * ((double) rand() / RAND_MAX);
        apple_pointer->y = rows * ((double) rand() / RAND_MAX);

        while (current_node != NULL)
        {
            if (apple_pointer->x == current_node->x &&
                apple_pointer->y == current_node->y)
                {
                    valid_position = false;
                    current_node = snake_pointer; // reset
                    goto TryAgain;
                }
                current_node = current_node->next_element;
        }
        valid_position = true;
        TryAgain:;
    }
}

