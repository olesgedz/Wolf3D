

NAME = wolf3d

FLAGS = -g -O3
CC = gcc
LIBRARIES = -lft -L$(LIBFT_DIRECTORY) -F SDL2/Frameworks   -lSDL2 -L$(SDL_DIRECTORY) -lSDL2main -L$(SDL_DIRECTORY) -lSDL2-2.0.0 -L$(SDL_DIRECTORY)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(SDL_HEADERS)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/
SDL_HEADERS = include/

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = wolf3d.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

DIRECTORY =  $(shell pwd)
SDL_DIRECTORY = $(DIRECTORY)/lib

LIB_LIST =	libSDL2.a\
			libSDL2.la\
			libSDL2_test.la\
			libSDL2main.la\
			libSDL2-2.0.0.dylib\
			libSDL2.dylib\
			libSDL2_test.a\
			libSDL2main.a

SRCS_DIRECTORY = ./srcs/
SRCS_LIST = main.c\
			utilities.c\
			calculations.c\
			render.c\
			textures.c\
			steps_check.c\
			sound.c\
			events.c\
			floor.c\
			sprites.c\
			initialize.c\
			read_map.c\
			animation.c\
			walls.c\
			sort_sprites.c\

OBJS_DIRECTORY = objects/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))
SDL_LIBS = $(addprefix $(DIRECTORY)/lib, $(LIB_LIST))

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIRECTORY) $(OBJS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJS_DIRECTORY):
	@mkdir -p $(OBJS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJS_DIRECTORY) was created$(RESET)"

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

sdl:
	@echo "sad"
	cd SDL2; ./configure --prefix=$(DIRECTORY); make;
	$(MAKE) -sC $(DIRECTORY)/SDL2 install

$(SDL_LIBS):
	cd SDL2; ./configure --prefix=$(DIRECTORY); make;
	$(MAKE) -sC $(DIRECTORY)/SDL2 install

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
