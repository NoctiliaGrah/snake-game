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
// I genuinely have no idea what this is doing
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

    int temp_x = head->last_x; //the last place the head was
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
            new_segment->next_element = NULL;

            tail_node->next_element = new_segment;
        }
    }
}

//
// P_InputBuffers
//
// HACKHACK: pressing L/R at the same time as U/D will often cause the
// snake to move back into itself the first input is perpendicular to
// the current movement axis and if the parallel input is opposite of
// the current direction. For example, if the snake is moving left and
// you press right and up/down on the same frame, the snake will go
// back into itself if the up/down input is registered first and the
// right input is registered second.
//
// The solution? Hold onto the 2nd input a player gives for a specific
// frame and override the input on the next frame with it, preferably
// holding onto the new overridden input to use on the next frame as
// well. Originally I thought this would be a very shoddy method, but
// it ended up being so elegant that the implementation was pretty much
// perfect on my first attempt. It even had the side effect of adding
// basic input buffering implementation, hence the name here.
//
// Could the same idea be done with else ifs? Yeah. But I like this
// better, and getting input buffering along with it makes future
// implementation easier.
//
void P_InputBuffers(InputBuffer *input_buffer1,
                    InputBuffer *input_buffer2,
                    InputBuffer *discard_buffer,
                    Direction *direction_pointer)
{

   // printf("DEBUG: InputBuffering func start b1 = %d, %d init b2 = %d, %d init discard = %d, %d\n",
   //        input_buffer1->x, input_buffer1->y,
   //        input_buffer2->x, input_buffer2->y,
   //        discard_buffer->x, discard_buffer->y);

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

   //  printf("DEBUG: InputBuffering func end b1 = %d, %d init b2 = %d, %d init discard = %d, %d\n",
   //         input_buffer1->x, input_buffer1->y,
   //         input_buffer2->x, input_buffer2->y,
   //         discard_buffer->x, discard_buffer->y);

}

void P_FlushBuffers1(InputBuffer *input_buffer1,
                     InputBuffer *input_buffer2,
                     bool *buffer_flush_flag)
{
     //printf("DEBUG: buffer_flush1 buffer_flush_flag");

        // BUFFER_FLUSH, PART 1
        // copy input_buffer2 to input_buffer1
     if (*buffer_flush_flag)
        input_buffer1->x = input_buffer2->x;
        input_buffer1->y = input_buffer2->y;

       // printf("DEBUG: buffer_flush1 (transfer b2 -> b1) b1 = %d, %d b2 = %d, %d\n",
       //        input_buffer1->x, input_buffer1->y,
       //        input_buffer2->y, input_buffer2->y);

        // clear input_buffer2 if it isn't already empty
        if (input_buffer2->x != I_BUFFER_INIT &&
            input_buffer2->y != I_BUFFER_INIT)
        {
            input_buffer2->x = I_BUFFER_INIT;
            input_buffer2->y = I_BUFFER_INIT;
        }
}

void P_FlushBuffers2(InputBuffer *input_buffer1,
                     InputBuffer *discard_buffer,
                     Direction *direction_pointer,
                     bool *buffer_flush_flag)
{
    if (input_buffer1->x != I_BUFFER_INIT &&
        input_buffer1->y != I_BUFFER_INIT)
        {
        direction_pointer->dx = input_buffer1->x;
        direction_pointer->dy = input_buffer1->y;

        (*buffer_flush_flag) = true;

        //printf("DEBUG: buffer_flush2 (transfer b1 -> dir) b1 = %d, %d b2 = %d, %d\n",
        //       input_buffer1->x, input_buffer1->y,
        //       direction_pointer->dx, direction_pointer->dy);

        }
    else {
            (*buffer_flush_flag) = false;
            discard_buffer->x = I_BUFFER_INIT; // reset for safety
            discard_buffer->y = I_BUFFER_INIT;
            }
}
