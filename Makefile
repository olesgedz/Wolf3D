

NAME = WOLF



#echo $(sdl2-config --cflags --libs)

all:
	gcc main.c -I./sdl2/2.0.9/include/SDL2 -D_THREAD_SAFE -L./sdl2/2.0.9/lib -lSDL2 -o $(NAME)
