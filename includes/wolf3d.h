#include "SDL2/SDL.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

#define WIN_W 1366
#define WIN_H 768
#define TEX_W 64
#define TEX_H 64

typedef struct s_coords
{
	double x;
	double y;
}				t_coords;

typedef struct s_player
{
	t_coords pos;
	t_coords dir;
	t_coords plane;
	t_coords raydir;
	t_coords side_dist;
	t_coords delta_dist;
	double old_dirx;
	double oldplanex;
	double camerax;
	double wall_dist;
	int stepx;
	int stepy;
	int side;
} 				t_player;


typedef struct s_sdl
{
		int				m_bRunning;
		SDL_Window		*m_pWindow;
		SDL_Renderer	*m_pRenderer;

}	t_sdl;

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
	int			*map;
	int x;
	int y;
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

typedef struct s_const
{
	double crs;
	double srs;
	double mcrs;
	double msrs;
	int half_height;
}				t_const;

typedef struct	s_wolf
{
	t_map map;
	t_sdl	game;
	t_player pl;
	t_const c;
	int	fd;
	int x;
	int hit;
	int line_height;
	int draw_start;
	int draw_end;
	double ms;
	double rs;
	int color;
}				t_wolf;


//Utilities.c
int		ft_error(char *reason);
//first.c
void    ft_init_wolf(t_wolf *wolf);
void    ft_ver_line(int x, int start, int end, int color, t_sdl *game);
void    ft_start_wolf(t_wolf *w);
void ft_image_set_pixel(t_sdl *game,  int x, int y, int color);
