/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:45:11 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/11 21:54:28 by lsandor-         ###   ########.fr       */
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

typedef struct s_sprite
{
	double x;
	double y;
	int texture;
}				t_sprite;

typedef	struct	s_rectangle
{
	t_coords size;
	t_coords coords;
} t_rectangle;


typedef struct s_anim
{
	int start_animation;
	int frame;
	t_rectangle pframe;
	t_coords place;
	int frames;
} t_anim;

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
		SDL_AudioSpec *wav_spec;
		Uint32 *wav_length;
		Uint8 **wav_buffer;
		SDL_AudioDeviceID *audio_device;
		unsigned char i;

}	t_sdl;

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
	int sprites_count;
	t_sprite **sprite;
	int	*sprite_order;
	double *sprite_distance;
}					t_map;

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

typedef struct s_sprite_stats
{
	t_coords pos;
	t_coords transform;
	double inv_det;
	int screen_x;
	int height;
	int width;
	int draw_starty;
	int draw_startx;
	int draw_endy;
	int draw_endx;
	int tex_x;
	int tex_y;
}				t_sprite_stats;
typedef struct	s_time
{
	Uint32 time;
	Uint32 old_time;
	double frame_time;
	Uint32 sound_old_time;
	Uint32 sound_time;
	Uint32 change_of_time;
	Uint32 play_time[2];
	Uint32 sound_sum_time[2];
}				t_time;

typedef struct	s_wolf
{
	t_map map;
	t_sdl	*sdl;
	t_player pl;
	t_const c;
	t_floor flr;
	t_sprite_stats spr;
	t_time t;
	t_anim anim;
	unsigned char arr[5];
	void	*tex_col;
	double z_buffer[WIN_W];
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
	int stripe;
	int i;
}				t_wolf;


//Utilities.c
int		ft_error(char *reason);
void	*ft_safe_malloc(size_t size);
//first.c
void    ft_init_wolf(t_wolf *wolf);
void    ft_ver_line(int x, int start, int end, int color, t_sdl *game);
void    ft_start_wolf(t_wolf *w);
//void ft_image_set_pixel(t_sdl *game,  int x, int y, int color);
//void	sdl_draw_pixel(t_sdl *sdl, int x, int y, int c);
void	game_draw_pixel(t_sdl *sdl, int x, int y, uint32_t c);
void	ft_draw_screen(t_wolf *w);
void    ft_load_textures(t_wolf *w);
void	ft_comb_sort(t_wolf *f);
void 	ft_swap_double(double *a, double *b);
// steps_check
int ft_step_forward_check(t_wolf *w, unsigned char flag);
int	ft_step_back_check(t_wolf *w, unsigned char flag);
void    ft_load_sound(t_wolf *w);
void ft_init_sound(t_wolf *w);
//events.c
void    ft_use_events(t_wolf *w);
//floor.c
void    ft_get_floor_coordinates(t_wolf *w);
void    ft_draw_floor(t_wolf *w);
//sprites.c
void    ft_draw_sprites(t_wolf *w);
void    ft_calculate_sprites(t_wolf *w);
void    ft_show_sprites(t_wolf *w);
void    ft_transform_sprites(t_wolf *w);