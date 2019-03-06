

NAME = wolf3d



#echo $(sdl2-config --cflags --libs)

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
DIRECTORY =  $(shell pwd)
LIBFT = libft/libft.a
DIRECTORY_COMP = $(addsuffix $(shell pwd), /SDL_library)
#$(shell cd SDL2; sh configure --prefix=$(DIRECTORY))

#  args = %W[--prefix=#{prefix} --without-x]
#  system "./configure", *args
#    system "make", "install"

#$(MAKE) -sC $(DIRECTORY)/SDL2 uninstall
#$(MAKE) -sC $(DIRECTORY)/SDL2 install
LIB_DIR = SDL_library/lib
all: $(LIBFT)
	gcc main.c $(LIBFT) -I libft/includes   -F SDL2/Frameworks   -lSDL2 -L$(LIB_DIR)   -I include/ -o $(NAME)

sdl: $(DIRECTORY_COMP)
	@echo "sad"
	cd SDL2; ./configure --prefix=$(DIRECTORY)/SDL_library; make;
	$(MAKE) -sC $(DIRECTORY)/SDL2 install

$(DIRECTORY_COMP):
	mkdir -p SDL_library
$(LIBFT):
	$(MAKE) -sC libft/
