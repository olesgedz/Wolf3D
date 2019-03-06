#include "SDL2/SDL.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

#define WIN_H 780
#define WIN_W 780

typedef struct s_player
{
	float x;
	float y;
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

typedef struct		s_vector
{
	double		x;
	double		y;
	double		z;
	int			color;
}					t_vector;
typedef struct		s_map
{
	int			width;
	int			height;
	int			depth_min;
	int			depth_max;
	t_vector	**vectors;
	double		*colors;
	int			ncolor;
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
/********

*******/
int			ft_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
	return (1);
}
