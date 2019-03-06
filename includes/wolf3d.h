#include "SDL2/SDL.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

#define WIN_H 780
#define WIN_W 780

typedef struct s_player
{
	float x;
	float y;
	float angle;
} 				t_player;


typedef struct s_game
{
		int				m_bRunning;
		SDL_Window		*m_pWindow;
		SDL_Renderer	*m_pRenderer;

}	t_game;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct		s_square
{
	double		x;
	double		y;
	double		z;
}					t_square;

typedef struct		s_map
{
	int			map_w;
	int			map_h;
	t_square	**squares;
}					t_map;

typedef struct			s_line
{
	t_point		start;
	t_point		end;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
}						t_line;

typedef struct	s_wolf
{
	t_map map;
	t_game *game;
	t_player player;
	int	fd;
}				t_wolf;


//Utilities.c
int			ft_error(char *reason);