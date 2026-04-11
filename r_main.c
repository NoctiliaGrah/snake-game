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
// Main render functions.
//

#include <stdio.h> // used for printing to console
#include <SDL2/SDL.h> // low-level graphics/sound/input library

#include "snakedefs.h"




//
// R_DrawGrid
//
int R_DrawGrid(SDL_Surface* window_surface)
{
    // x, y, width, height
    SDL_Rect row_line = {0,0,640,line_width};
    SDL_Rect column_line = {0,0,line_width,window_height};

    for (row_line.y = 0;
         row_line.y < window_height;
         row_line.y += cell_size)
         SDL_FillRect(window_surface, &row_line, GRID_COLOR);

    for (column_line.x = 0;
         column_line.x < window_width;
         column_line.x += cell_size)
         SDL_FillRect(window_surface, &column_line, GRID_COLOR);

}




//
// R_FillCell
// I don't know why this is a function and I don't know a better way.
//
void R_FillCell(SDL_Surface* window_surface, int x, int y, Uint32 color)
{
    SDL_Rect rect = {x*cell_size, y*cell_size, cell_size, cell_size};
    SDL_FillRect(window_surface, &rect, color);
}
