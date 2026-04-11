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

#ifndef __P_USER__
#define __P_USER__


void P_MoveSnake(SnakeElement *snake_pointer,
                 Direction *direction_pointer,
                 Tail *tail_current);


#endif
