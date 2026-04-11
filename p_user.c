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
// Snake movement code
//

#include <stddef.h>
#include <SDL2/SDL.h>

#include "snakegame.h"
#include "snakedefs.h"

//
// P_MoveSnake
// TODO: Make this less shit and less buggy
//
void P_MoveSnake(SnakeElement *snake_pointer,
                 Direction *direction_pointer,
                 Tail *tail_current,
                 bool is_growing)
{
    struct SnakeElement *current = snake_pointer;

    current->last_x = snake_pointer->x;
    current->last_y = snake_pointer->y;

    snake_pointer->x += direction_pointer->dx;
    snake_pointer->y += direction_pointer->dy;

    while (tail_current != NULL)
    {
        tail_current->x = current->last_x;
        tail_current->y = current->last_y;

        break;
    }

}
