//
// Requires SDL2 to compile, installation instructions here:
// https://wiki.libsdl.org/SDL2/Installation
//
// Noctilia Grah, 2026
//
// DESCRIPTION:
// Snake movement code
//
// DESCRIPTION:
// Main render functions.
//

#include <stdio.h> // used for printing to console
#include <SDL2/SDL.h> // low-level graphics/sound/input library

#include "snakedefs.h"
#include "snakegame.h"



//
// R_DrawGrid
//
void R_DrawGrid(SDL_Surface* window_surface)
{
    // x, y, width, height
    SDL_Rect row_line = {0,0,window_width,line_width};
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
//
void R_FillCell(SDL_Surface* window_surface, int x, int y, Uint32 color)
{
    SDL_Rect rect = {x*cell_size, y*cell_size, cell_size, cell_size};
    SDL_FillRect(window_surface, &rect, color);
}
