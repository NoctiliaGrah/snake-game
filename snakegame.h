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
// Structs, Structs, and more structs.
//

// I have no idea why i'm doing most of this stuff
// like this, if you're using this as a reference,
// use something better.

#ifndef __SNAKEGAME__
#define __SNAKEGAME__

#include <stddef.h>

// STRUCTS
typedef struct SnakeElement SnakeElement;
typedef struct Snake Snake;
typedef struct Apple Apple;

typedef struct SnakeElement
{
    int x, y;
    int last_x, last_y;
    SnakeElement *next_element; // null if it's the last element
} SnakeElement;

typedef struct Apple
{
    int x, y;
    Apple *next_element;
} AppleLocation;

typedef struct Direction
{
    int dx, dy;
} Direction;

typedef struct InputBuffer
{
    int x, y;
} InputBuffer;



extern bool is_growing;

#endif
