

NAME = WOLF



#echo $(sdl2-config --cflags --libs)

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
DIRECTORY =  $(shell pwd)
LIBFT = libft/libft.a
#$(shell cd SDL2; sh configure --prefix=$(DIRECTORY))

#  args = %W[--prefix=#{prefix} --without-x]
#  system "./configure", *args
#    system "make", "install"

#$(MAKE) -sC $(DIRECTORY)/SDL2 uninstall
#$(MAKE) -sC $(DIRECTORY)/SDL2 install
LIB_DIR = lib/
all: $(LIBFT)
	gcc main.c $(LIBFT) -I libft/includes   -F SDL2/Frameworks   -lSDL2 -L$(LIB_DIR) -lSDL2main -L$(LIB_DIR) -lSDL2-2.0.0 -L$(LIB_DIR) -I include/ -o $(NAME)

sdl:
	@echo "sad"
	cd SDL2; ./configure --prefix=$(DIRECTORY); make;
	$(MAKE) -sC $(DIRECTORY)/SDL2 install

$(LIBFT):
	$(MAKE) -sC libft/
