//
// Requires SDL2 to compile, installation instructions here:
// https://wiki.libsdl.org/SDL2/Installation
//
// Noctilia Grah, 2026
//
// DESCRIPTION:
// Defines
//

#ifndef __SNAKEDEFS__
#define __SNAKEDEFS__

#include "snakegame.h"


// window
#define window_width 640
#define window_height 480
#define window_flags 0
// cells
#define cell_size 40
#define line_width 1

#define ROW window_width/cell_size
#define COLUMN window_height/cell_size

// colors
#define GRID_COLOR 0x1f1f1f1f
#define COLOR_WHITE 0xffffffff
#define COLOR_RED 0x00ff0000
#define COLOR_GREEN 0x0000ff00
#define COLOR_BLACK 0x00000000

// game specific defines
#define SNAKE(x,y) R_FillCell(window_surface,x,y,COLOR_WHITE)
#define APPLE(x,y) R_FillCell(window_surface,x,y,COLOR_RED)


#define TICKRATE 100

// init snake position & direction
#define INIT_X 5
#define INIT_Y 5
#define TAIL_INIT_X 4
#define TAIL_INIT_Y 4
#define DIR_RESET 0

// HACKHACK: These are here to make magic numbers go away, but it
// kinda sucks because of the underlying values just being -1 & 1.
// I don't want to put in the effort to redo the movement code yet
// so this is what I'm stuck with for right now.
#define DIR_LEFT -1
#define DIR_RIGHT 1
#define DIR_UP -1
#define DIR_DOWN 1

#define I_BUFFER_INIT 2 // input buffer init/empty value






#endif
