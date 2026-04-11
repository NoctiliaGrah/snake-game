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
// Main render stuff
//

#ifndef __R_MAIN__
#define __R_MAIN__




int R_DrawGrid(SDL_Surface* window_surface);

void R_FillCell(SDL_Surface* window_surface,
              int x, int y, Uint32 color);



#endif
