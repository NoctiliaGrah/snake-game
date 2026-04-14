CC = gcc

SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)

CFLAGS = -Wall -Wextra $(SDL_CFLAGS)
LDFLAGS = $(SDL_LDFLAGS)

TARGET = snake

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(OBJS)  $(LDFLAGS) -o  $(TARGET)

%.o: %.c $(wildcard *.h)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean



