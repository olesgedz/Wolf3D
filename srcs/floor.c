/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 21:24:47 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/15 23:31:01 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** 4 different wall directions possible
*/

void	ft_get_floor_coordinates(t_thread *a)
{
	if (a->w.pl.side == 0 && a->w.pl.raydir.x > 0)
	{
		a->w.flr.xwall = a->w.map.x;
		a->w.flr.ywall = a->w.map.y + a->w.wall_hit;
	}
	else if (a->w.pl.side == 0 && a->w.pl.raydir.x < 0)
	{
		a->w.flr.xwall = a->w.map.x + 1.0;
		a->w.flr.ywall = a->w.map.y + a->w.wall_hit;
	}
	else if (a->w.pl.side == 1 && a->w.pl.raydir.y > 0)
	{
		a->w.flr.xwall = a->w.map.x + a->w.wall_hit;
		a->w.flr.ywall = a->w.map.y;
	}
	else
	{
		a->w.flr.xwall = a->w.map.x + a->w.wall_hit;
		a->w.flr.ywall = a->w.map.y + 1.0;
	}
	if (a->w.draw_end < 0)
		a->w.draw_end = WIN_H;
}

/*
** draw the floor from draw_end to the bottom of the screen
*/

void	ft_draw_floor(t_thread *a)
{
	a->w.y = a->w.draw_end;
	while (a->w.y < WIN_H - 1)
	{
		a->w.flr.cur_dst = WIN_H / (2.0 * a->w.y - WIN_H);
		a->w.flr.weight = a->w.flr.cur_dst / a->w.pl.wall_dist;
		a->w.flr.cur_x = a->w.flr.weight * a->w.flr.xwall +
		(1.0 - a->w.flr.weight) * a->w.pl.pos.x;
		a->w.flr.cur_y = a->w.flr.weight * a->w.flr.ywall +
		(1.0 - a->w.flr.weight) * a->w.pl.pos.y;
		a->w.flr.text_x = (int)(a->w.flr.cur_x * TEX_W) % TEX_W;
		a->w.flr.text_y = (int)(a->w.flr.cur_y * TEX_H) % TEX_H;
		a->w.tex_col = &((Uint8*)(a->w.sdl->textures[18]->pixels))[TEX_W * 3 *
		a->w.flr.text_y + a->w.flr.text_x * 3];
		a->w.color = *(Uint32*)(a->w.tex_col);
		a->w.color = (a->w.color >> 2) & 8355711;
		a->w.sdl->text_buf[a->x + (a->w.y * WIN_W)] = a->w.color;
		a->w.tex_col = &((Uint8*)(a->w.sdl->textures[19]->pixels))[TEX_W * 3 *
		a->w.flr.text_y + a->w.flr.text_x * 3];
		a->w.color = *(Uint32*)(a->w.tex_col);
		a->w.sdl->text_buf[a->x + ((WIN_H - a->w.y) * WIN_W)] = a->w.color;
		a->w.y++;
	}
}
