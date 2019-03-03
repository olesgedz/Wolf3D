

NAME = WOLF



#echo $(sdl2-config --cflags --libs)

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

all:
	gcc main.c $(SDL_CFLAGS) $(SDL_LDFLAGS) -o $(NAME)
