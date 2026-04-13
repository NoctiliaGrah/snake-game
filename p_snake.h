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
// User movement/responding to inputs
//

#ifndef __P_SNAKE__
#define __P_SNAKE__


void P_MoveSnake(SnakeElement *snake_pointer, Direction *direction_pointer,
                 bool is_growing);

void P_InputBuffers(InputBuffer *input_buffer1, InputBuffer *input_buffer2,
                    InputBuffer *discard_buffer, Direction *direction_pointer);

void P_FlushBuffers1(InputBuffer *input_buffer1, InputBuffer *input_buffer2,
                     bool *buffer_flush);

void P_FlushBuffers2(InputBuffer *input_buffer1, InputBuffer *discard_buffer,
                     Direction *direction_pointer, bool *buffer_flush);



#endif
