/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:25:55 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 16:07:47 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		*ft_init_sdl(t_sdl *sdl)
{
	sdl = ft_memalloc(sizeof(t_sdl));
	sdl->text_buf = malloc(sizeof(uint32_t) * WIN_W * WIN_H);
	SDL_Init(SDL_INIT_AUDIO);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &sdl->m_pWindow, &sdl->m_pRenderer))
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
	sdl->tex =  SDL_CreateTexture(sdl->m_pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (!sdl->tex)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
	sdl->m_bRunning = 1;
	return (sdl);
}
int			ft_init_anim(t_wolf *wolf)
{
	wolf->anim.start_animation = 0;
	wolf->anim.frame = 0;
	wolf->anim.pframe.size = (t_coords){512, 512};
	wolf->anim.pframe.coords = (t_coords){0, 0};
	wolf->anim.place = (t_coords){WIN_W/2 - 512/2, WIN_H - 512};
	wolf->anim.frames = 0;
	return (0);
}

void	ft_init_wolf(t_wolf *w)
{
	w->pl.pos.x = 5;
	w->pl.pos.y = 5;
	w->pl.dir.x = -1;
	w->pl.dir.y = 0;
	w->pl.plane.x = 0;
	w->pl.plane.y = 0.66;
	w->hit = 0;
	w->x = -1;
	w->ms = 0.03;
	w->rs = 0.015;
	w->c.crs = cos(w->rs);
	w->c.srs = sin(w->rs);
	w->c.mcrs = cos(- w->rs);
	w->c.msrs = sin(- w->rs);
	w->c.half_height = (WIN_H >> 1);
	w->c.camera_x_cnst = 2 / (double)WIN_W;
	w->z_buffer = ft_safe_malloc(sizeof(double) * WIN_W);
	w->t.flag = 1;
    ft_we_need_more_init(w);
}

void    ft_we_need_more_init(t_wolf *w)
{
    w->t.time = 0;
	w->t.old_time = 0;
	w->t.sound_old_time = 0;
	w->t.play_time = 1000;
	w->t.sound_sum_time = 0;
	w->arr[0] = 0;
	w->arr[1] = 0;
	w->arr[2] = 0;
	w->arr[3] = 0;
	w->arr[4] = 0;
}

void ft_init_multi_wolf(t_thread_args *w, t_wolf *head)
{
    w->sdl = head->sdl;
    w->map.map = head->map.map;
    w->map.sprite = head->map.sprite;
    w->map.sprite_order = head->map.sprite_order;
    w->map.sprite_distance = head->map.sprite_distance;
	w->map.map_w = head->map.map_w;
	w->map.map_h = head->map.map_w;
 	w->pl.pos.x = head->pl.pos.x;
	w->pl.pos.y = head->pl.pos.y;
	w->pl.dir.x = head->pl.dir.x;
	w->pl.dir.y = head->pl.dir.y;
	w->pl.plane.x = head->pl.plane.x;
	w->pl.plane.y = head->pl.plane.y;
	w->z_buffer = head->z_buffer;
	w->half_height = head->c.half_height;
	w->camera_x_cnst = head->c.camera_x_cnst;
}