CC = cc

all: final

final: snake.c
	$(CC) snake.c r_main.c p_snake.c p_apple.c r_snake.c r_apple.c -o snake -g `sdl2-config --cflags --libs`

snake-game.o: snake.c r_main.c p_user.c r_snake.c r_apple.c
	$(CC) -c snake.c

r_apple.o: r_apple.c r_apple.h
	$(CC) -c r_apple.c

r_snake.o: r_snake.c r_snake.h
	$(CC) -c r_snake.c

r_main.o: r_main.c r_main.h
	$(CC) -c r_main.c

p_apple.o: p_apple.c snakegame.h
	$(CC) -c p_apple.c

p_snake.o: p_snake.c snakedefs.h snakegame.h p_snake.h
	$(CC) -c p_snake.c
