# snake-game
A very unfinished version of Snake written in C using SDL2 for graphics.

TODO:
- Fix the movement to not allow for the snake to go back into itself when moving perpendicular to and then opposite of the current direction in quick succession.
- Fix the apple respawn code to also check if it intersects any of the new snake segments.
- Implement a proper tick system so the movement speed isn't tied to the frame rate.
- Move the fuctions for drawing the snake & the apple on-screen into their own individual files.

# Building
This requires SDL2, instructions on how to install it can be found here:

https://wiki.libsdl.org/SDL2/Installation


After that, just type ``make`` in your terminal. If you're on Windows, good luck to you I guess.
