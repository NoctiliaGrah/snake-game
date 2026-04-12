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
// Snake movement code
//

#include <stddef.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "snakegame.h"
#include "snakedefs.h"

//
// P_MoveSnake
// TODO: There's probably a better way to do this
//
void P_MoveSnake(SnakeElement *head,
                 Direction *direction_pointer,
                 bool is_growing)
{
    // save the head's old position, move the head based
    // on direction, and move the rest of the body
    head->last_x = head->x;
    head->last_y = head->y;
    head->x += direction_pointer->dx;
    head->y += direction_pointer->dy;

    SnakeElement *current = head->next_element;

    int temp_x = head->last_x;
    int temp_y = head->last_y;

    // pointer to the last node
    SnakeElement *tail_node = head;

    while (current != NULL)
    {
        // save this segment's current position, move
        // it to the old position of the segment in
        // front of it, then update the temporary
        // variable for the next segment & track the
        // last node we touch
        current->last_x = current->x;
        current->last_y = current->y;

        current->x = temp_x;
        current->y = temp_y;

        temp_x = current->last_x;
        temp_y = current->last_y;

        tail_node = current;
        current = current->next_element;
    }

    if (is_growing == true)
    {
        //printf("is_growing, memory allocated\n"); // old debug code
        // allocate memory for the new segment
        SnakeElement *new_segment =
        (SnakeElement*)malloc(sizeof(SnakeElement));

        if (new_segment != NULL)
        {
            // put the new segment at the old
            // position of the last segment
            new_segment->x = temp_x;
            new_segment->y = temp_y;
            new_segment->last_x = temp_x;
            new_segment->last_y = temp_y;
            //current->next_element = new_segment;
            new_segment->next_element = NULL;

            tail_node->next_element = new_segment;
        }
    }
}
