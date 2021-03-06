# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/16 12:58:07 by jblack-b          #+#    #+#              #
#    Updated: 2019/03/16 13:30:17 by jblack-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
SDL_MAKE = $(DIRECTORY)/SDL2

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
			ray_calculation.c

OBJS_DIRECTORY = objects/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))
SDL_LIBS = $(addprefix $(DIRECTORY)/lib/, $(LIB_LIST))

LIBFT = libft/libft.a
LIBSDL_EXIST = 0
err = no

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIRECTORY) $(OBJS)
	$(foreach p,$(SDL_LIBS),$(if $(wildcard $(p)),,$(info $(p) does not exist!) $(MAKE) sdl))
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
	$(MAKE) -sC $(SDL_MAKE) install

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"
	@$(MAKE) -sC $(SDL_MAKE) clean
	@echo "$(SDL_MAKE): $(RED)object files were deleted$(RESET)"

dd:
	rm $(NAME)

fclean: clean
	@rm -r $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
	@rm -f $(DIRECTORY)/bin/sdl2-config
	@rm -f $(DIRECTORY)/lib/libSDL2.la
	@rm -f $(DIRECTORY)/lib/libSDL2main.la
	@rm -f $(DIRECTORY)/lib/libSDL2_test.la
	@rm -f $(DIRECTORY)/share/aclocal/sdl2.m4
	@rm -f $(DIRECTORY)/lib/pkgconfig/sdl2.pc
	@rm -f $(DIRECTORY)/lib/cmake/SDL2/sdl2-config.cmake
	@rm -rf lib bin share
	@echo "$(SDL_MAKE): $(RED)was unistalled$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all