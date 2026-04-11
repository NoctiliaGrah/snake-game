CC = cc

all: final

final: snake-game.c r_main.c p_user.c
	$(CC) snake-game.c r_main.c p_user.c -o snake -g `sdl2-config --cflags --libs`

snake-game.o: snake-game.c r_main.c p_user.c
	$(CC) -c snake-game.c

r_main.o: r_main.c r_main.h
	$(CC) -c r_main.c

p_user.o: p_user.c snakedefs.h snakegame.h
	$(CC) -c p_user.c
