//
// Requires SDL2 to compile, installation instructions here:
// https://wiki.libsdl.org/SDL2/Installation
//
// Noctilia Grah, 2026
//
// DESCRIPTION:
// Apple behavior

#include <stddef.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "snakegame.h"
#include "snakedefs.h"




//
// P_ResetApple
// FIXME: Merge with P_Collision & this is horrifically inefficient
//
void P_ResetApple(SnakeElement *snake_pointer, Apple *apple_pointer)
{
SnakeElement *current_node = snake_pointer;

    bool valid_position = false;
    while (!valid_position)
    {
        apple_pointer->x = ROW * ((double) rand() / RAND_MAX);
        apple_pointer->y = COLUMN * ((double) rand() / RAND_MAX);

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
