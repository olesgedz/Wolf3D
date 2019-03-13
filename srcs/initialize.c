/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:25:55 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 14:33:59 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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