/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:45:11 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/14 19:05:05 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "SDL2/SDL.h"
# include "SDL2/SDL_thread.h"
# include <pthread.h>
# include "libft.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# define WIN_W 1920
# define WIN_H 1080
# define TEX_W 64
# define TEX_H 64
# define TH_N 10
# define ONE_ANIM 20
# define FULL_ANIM ONE_ANIM * 4 - 4
# define TEXTURES_NUMBER 23

typedef struct s_wolf	t_wolf;

typedef struct		s_sort_helper
{
	int		gap;
	int		i;
	int		j;
	char	swapped;
}					t_sort_helper;

typedef struct		s_fill
{
	t_list	*lst;
	char	**split;
	int		x;
	int		y;
	int		sprites_count;
}					t_fill;

typedef struct		s_coords
{
	double	x;
	double	y;
}					t_coords;

typedef struct		s_sprite
{
	double	x;
	double	y;
	int		texture;
}					t_sprite;

typedef	struct		s_rectangle
{
	t_coords	size;
	t_coords	coords;
}					t_rectangle;

typedef struct		s_anim
{
	int			start_animation;
	int			frame;
	t_rectangle	pframe;
	t_coords	place;
	int			frames;
}					t_anim;

typedef struct		s_player
{
	t_coords	pos;
	t_coords	dir;
	t_coords	plane;
	t_coords	raydir;
	t_coords	side_dist;
	t_coords	delta_dist;
	double		old_dirx;
	double		oldplanex;
	double		camerax;
	double		wall_dist;
	int			stepx;
	int			stepy;
	int			side;
}					t_player;

typedef struct		s_sdl
{
	int					m_running;
	SDL_Window			*m_window;
	SDL_Renderer		*m_renderer;
	Uint32				*text_buf;
	SDL_Texture			*tex;
	SDL_Surface			**textures;
	SDL_AudioSpec		*wav_spec;
	Uint32				*wav_length;
	Uint8				**wav_buffer;
	SDL_AudioDeviceID	*audio_device;
	unsigned char		i;

}					t_sdl;

typedef struct		s_square
{
	double	x;
	double	y;
	double	z;
}					t_square;

typedef struct		s_map
{
	int			map_w;
	int			map_h;
	int			*map;
	int			x;
	int			y;
	int			sprites_count;
	t_sprite	**sprite;
	int			*sprite_order;
	double		*sprite_distance;
}					t_map;

typedef struct		s_const
{
	double	crs;
	double	srs;
	double	mcrs;
	double	msrs;
	double	camera_x_cnst;
	int		half_height;
}					t_const;

typedef struct		s_floor
{
	double	xwall;
	double	ywall;
	double	cur_dst;
	double	weight;
	double	cur_x;
	double	cur_y;
	int		text_x;
	int		text_y;
}					t_floor;

typedef struct		s_sprite_stats
{
	t_coords	pos;
	t_coords	transform;
	double		inv_det;
	int			screen_x;
	int			height;
	int			width;
	int			draw_starty;
	int			draw_startx;
	int			draw_endy;
	int			draw_endx;
	int			tex_x;
	int			tex_y;
}					t_sprite_stats;

typedef struct		s_time
{
	Uint32			time;
	Uint32			old_time;
	Uint32			frame_time;
	Uint32			sound_old_time;
	Uint32			sound_time;
	Uint32			change_of_time;
	Uint32			play_time;
	Uint32			sound_sum_time;
	unsigned char	flag;
}					t_time;

struct				s_wolf
{
	t_anim			anim;
	t_player		pl;
	t_map			map;
	t_sprite_stats	spr;
	t_floor			flr;
	t_time			t;
	t_const			c;
	SDL_Surface		*weapon_texture;
	t_sdl			*sdl;
	void			*tex_col;
	double			*z_buffer;
	unsigned char	arr[5];
	double			ms;
	double			rs;
	double			wall_hit;
	Uint32			color;
	int				fd;
	int				x;
	int				y;
	int				hit;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				texture_num;
	int				text_x;
	int				text_y;
	int				temp;
	int				stripe;
	int				i;
};

typedef struct		s_thread_args
{
	t_player	pl;
	t_map		map;
	t_floor		flr;
	t_sdl		*sdl;
	void		*tex_col;
	double		*z_buffer;
	double		wall_hit;
	double		camera_x_cnst;
	Uint32		color;
	int			y;
	int			hit;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			texture_num;
	int			text_x;
	int			text_y;
	int			temp;
	int			half_height;
}					t_thread_args;

typedef struct		s_thread
{
	t_thread_args	w;
	int				x;
	int				x2;
}					t_thread;

/*
** Utilities.c
*/
int					ft_error(char *reason);
void				*ft_safe_malloc(size_t size);
int					ft_cleanup(t_list **lst);
void				ft_clean_all(t_wolf *w);
SDL_Surface			*ft_sdl_load_bmp(char *str);
int					ft_check_line(char *str);
/*
** initialize.c
*/
t_sdl				*ft_init_sdl(t_sdl *sdl);
int					ft_init_anim(t_wolf *wolf);
void				ft_init_wolf(t_wolf *wolf);
void				ft_we_need_more_init(t_wolf *w);
void				ft_ver_line(int x, int start, int end,
						int color, t_sdl *game);
void				*ft_start_wolf(void *args);
void				game_draw_pixel(t_sdl *sdl, int x, int y, uint32_t c);
void				ft_draw_screen(t_wolf *w);
void				ft_load_texture(t_wolf *w);
void				ft_comb_sort(t_wolf *f);
void				ft_swap_double(double *a, double *b);
/*
** steps_check.c
*/
int					ft_step_forward_check(t_wolf *w, unsigned char flag);
int					ft_step_back_check(t_wolf *w, unsigned char flag);
void				ft_load_sound(t_wolf *w);
void				ft_init_sound(t_wolf *w);
/*
** events.c
*/
void				ft_use_events(t_wolf *w);
void				ft_handle_events(t_wolf *w);
/*
** floor.c
*/
void				ft_get_floor_coordinates(t_thread *a);
void				ft_draw_floor(t_thread *a);
/*
** sprites.c
*/
void				ft_draw_sprites(t_wolf *w);
void				ft_calculate_sprites(t_wolf *w);
void				ft_show_sprites(t_wolf *w);
void				ft_transform_sprites(t_wolf *w);
void				ft_multithreading(t_wolf *w);
void				ft_init_multi_wolf(t_thread_args *w, t_wolf *head);
void				ft_load_textures(t_wolf *wolf);
/*
** read_map.c
*/
void				ft_read_file(int fd, t_map *m);
int					ft_get_lines(int fd, t_list **lst);
void				ft_get_map(t_map *m, int map_w, int map_h);
int					ft_fill_map(t_map *m, t_list *list);
void				ft_fill_sprites(t_map *m);
/*
** animation.c
*/
void				ft_draw_animation(t_wolf *w);
void				ft_animation_play(t_wolf *w);
/*
** render.c
*/
void				ft_render(t_wolf *wolf);
/*
** walls.c
*/
void				ft_ray_dir_calculations(t_thread *a);
void				ft_wall_hit(t_thread *a);
void				ft_wall_draw_start(t_thread *a);
void				ft_draw_walls(t_thread *a);
/*
** sound.c
*/
void				ft_play_shot(t_wolf *w);
/*
** sort_sprites.c
*/
void				ft_swap_double(double *a, double *b);
void				ft_swap_int_here(int *a, int *b);
void				ft_comb_sort(t_wolf *w);
#endif
