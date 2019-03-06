#include "SDL2/SDL.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

#define WIN_H 768
#define WIN_W 1366

typedef struct s_player
{
	float x;
	float y;
<<<<<<< HEAD
	double dirX;
	double dirY;
	double planeX;
	double planeY;

	double time;
	double oldtime;
	double cameraX;
	double rayDirX;
	double rayDirY;
} t_player;
=======
	float angle;
} 				t_player;
>>>>>>> e56cc3b429a842e223dfafdfd04031a0462ef0eb


typedef struct s_game
{
		int				m_bRunning;
		SDL_Window		*m_pWindow;
		SDL_Renderer	*m_pRenderer;
		t_player		*player;
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
<<<<<<< HEAD
	ft_putendl(reason);
	exit(EXIT_FAILURE);
	return (1);
}
=======
	t_map map;
	t_game *game;
	t_player player;
	int	fd;
}				t_wolf;


//Utilities.c
int			ft_error(char *reason);
>>>>>>> e56cc3b429a842e223dfafdfd04031a0462ef0eb
