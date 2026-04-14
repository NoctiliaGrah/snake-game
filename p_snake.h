//
// Requires SDL2 to compile, installation instructions here:
// https://wiki.libsdl.org/SDL2/Installation
//
// Noctilia Grah, 2026
//
// DESCRIPTION:
// User movement/responding to inputs
//

#ifndef __P_SNAKE__
#define __P_SNAKE__


void P_MoveSnake(SnakeElement *snake_pointer, Direction *direction_pointer,
                 bool is_growing);

void P_Collide(SnakeElement *snake_pointer, bool *game_on_pointer);

// input buffering
void P_InputBuffers(InputBuffer *input_buffer1, InputBuffer *input_buffer2,
                    InputBuffer *discard_buffer, Direction *direction_pointer);

void P_FlushBuffers1(InputBuffer *input_buffer1, InputBuffer *input_buffer2,
                     bool *buffer_flush);

void P_FlushBuffers2(InputBuffer *input_buffer1, InputBuffer *discard_buffer,
                     Direction *direction_pointer, bool *buffer_flush);


#endif
