/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 21:24:47 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/11 21:30:32 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** 4 different wall directions possible
*/

void    ft_get_floor_coordinates(t_wolf *w)
{
	if (w->pl.side == 0 && w->pl.raydir.x > 0)
		{
			w->flr.xwall = w->map.x;
			w->flr.ywall = w->map.y + w->wall_hit;
		}
		else if (w->pl.side == 0 && w->pl.raydir.x < 0)
		{
			w->flr.xwall = w->map.x + 1.0;
			w->flr.ywall = w->map.y + w->wall_hit;
		}
		else if (w->pl.side == 1 && w->pl.raydir.y > 0)
		{
			w->flr.xwall = w->map.x + w->wall_hit;
			w->flr.ywall = w->map.y;
		}
		else
		{
			w->flr.xwall = w->map.x + w->wall_hit;
			w->flr.ywall = w->map.y + 1.0;
		}
		if (w->draw_end < 0)
			w->draw_end = WIN_H;
}

/*
** draw the floor from draw_end to the bottom of the screen
*/

void    ft_draw_floor(t_wolf *w)
{
	w->y = w->draw_end;
	while (w->y < WIN_H)
	{
		w->flr.cur_dst = WIN_H / (2.0 * w->y - WIN_H);
		w->flr.weight = w->flr.cur_dst/ w->pl.wall_dist;
		w->flr.cur_x = w->flr.weight * w->flr.xwall + (1.0 - w->flr.weight) * w->pl.pos.x;
		w->flr.cur_y = w->flr.weight * w->flr.ywall + (1.0 - w->flr.weight) * w->pl.pos.y;
		w->flr.text_x = (int)(w->flr.cur_x * TEX_W) % TEX_W;
		w->flr.text_y = (int)(w->flr.cur_y * TEX_H) % TEX_H;
		w->tex_col = &((Uint8*)(w->sdl->textures[2]->pixels))[TEX_W * 3 * w->flr.text_y + w->flr.text_x * 3];
		w->color = *(Uint32*)(w->tex_col);
		w->color = (w->color >> 2) & 8355711;
		w->sdl->text_buf[w->x + (w->y * WIN_W)] = w->color;
		w->tex_col = &((Uint8*)(w->sdl->textures[1]->pixels))[TEX_W * 3 * w->flr.text_y + w->flr.text_x * 3];
		w->color = *(Uint32*)(w->tex_col);
		w->sdl->text_buf[w->x + ((WIN_H - w->y) * WIN_W)] = w->color;
		w->y++;
	}
}