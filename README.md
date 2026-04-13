# snake-game
A very unfinished version of Snake written in C using SDL2 for graphics.

TODO:
- Game restart
- Snake collision with self/walls
- Player fail/death state
- Player win state (i.e. all attempts for a new apple position have failed)
- Round the cell size to a multiple of 8 (temporary)
- Implement a proper tick system so the movement speed isn't tied to the frame rate.
# Building
This requires SDL2, instructions on how to install it can be found here:

https://wiki.libsdl.org/SDL2/Installation


After that, just type ``make`` in your terminal. I don't know if this will work on Windows or MacOS.
