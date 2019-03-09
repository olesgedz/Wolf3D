/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:45:11 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/09 15:18:13 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		Uint32		*text_buf;
		SDL_Texture	*tex;
		SDL_Surface **textures;

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
	double camera_x_cnst;
	int half_height;
}				t_const;

typedef struct	s_floor
{
	double xwall;
	double ywall;
	double cur_dst;
	double weight;
	double cur_x;
	double cur_y;
	int text_x;
	int text_y;
}				t_floor;

typedef struct	s_wolf
{
	t_map map;
	t_sdl	*sdl;
	t_player pl;
	t_const c;
	t_floor flr;
	void	*tex_col;
	double ms;
	double rs;
	double wall_hit;
	Uint32 color;
	int	fd;
	int x;
	int y;
	int hit;
	int line_height;
	int draw_start;
	int draw_end;
	int texture_num;
	int text_x;
	int text_y;
	int temp;
}				t_wolf;


//Utilities.c
int		ft_error(char *reason);
//first.c
void    ft_init_wolf(t_wolf *wolf);
void    ft_ver_line(int x, int start, int end, int color, t_sdl *game);
void    ft_start_wolf(t_wolf *w);
//void ft_image_set_pixel(t_sdl *game,  int x, int y, int color);
//void	sdl_draw_pixel(t_sdl *sdl, int x, int y, int c);
void	game_draw_pixel(t_sdl *sdl, int x, int y, uint32_t c);
void	ft_draw_screen(t_wolf *w);
void    ft_load_textures(t_wolf *w);
