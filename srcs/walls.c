/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 20:45:52 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 21:43:41 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_ray_dir_calculations(t_thread *a)
{
	a->w.pl.camerax = a->x * a->w.camera_x_cnst - 1;
	a->w.pl.raydir.x = a->w.pl.dir.x + a->w.pl.plane.x * a->w.pl.camerax;
	a->w.pl.raydir.y = a->w.pl.dir.y + a->w.pl.plane.y * a->w.pl.camerax;
	a->w.map.x = (int)a->w.pl.pos.x;
	a->w.map.y = (int)a->w.pl.pos.y;
	a->w.pl.delta_dist.x = fabs(1 / a->w.pl.raydir.x);
	a->w.pl.delta_dist.y = fabs(1 / a->w.pl.raydir.y);
	a->w.pl.stepx = a->w.pl.raydir.x < 0 ? -1 : 0;
	if (a->w.pl.stepx == -1)
		a->w.pl.side_dist.x = (a->w.pl.pos.x - a->w.map.x) * a->w.pl.delta_dist.x;
	else
	{
		a->w.pl.stepx = 1;
		a->w.pl.side_dist.x = (a->w.map.x + 1.0 - a->w.pl.pos.x) * a->w.pl.delta_dist.x;
	}
	if (a->w.pl.raydir.y < 0)
	{
		a->w.pl.stepy = -1;
		a->w.pl.side_dist.y = (a->w.pl.pos.y - a->w.map.y) * a->w.pl.delta_dist.y;
	}
	else
	{
		a->w.pl.stepy = 1;
		a->w.pl.side_dist.y = (a->w.map.y + 1.0 - a->w.pl.pos.y) * a->w.pl.delta_dist.y;
	}
}

void	ft_wall_hit(t_thread *a)
{
	a->w.hit = 0;
	while (a->w.hit == 0)
	{
		if (a->w.pl.side_dist.x < a->w.pl.side_dist.y)
		{
			a->w.pl.side_dist.x += a->w.pl.delta_dist.x;
			a->w.map.x += a->w.pl.stepx;
			a->w.pl.side = 0;
		}
		else
		{
			a->w.pl.side_dist.y += a->w.pl.delta_dist.y;
			a->w.map.y += a->w.pl.stepy;
			a->w.pl.side = 1;
		}
		if (a->w.map.map[a->w.map.x + a->w.map.y * a->w.map.map_w] > 0 && a->w.map.map[a->w.map.x + a->w.map.y * a->w.map.map_w] < 20)
			a->w.hit = 1;
	}
	if (a->w.pl.side == 0)
		a->w.pl.wall_dist = (a->w.map.x - a->w.pl.pos.x + ((1 - a->w.pl.stepx) >> 1)) / a->w.pl.raydir.x;
	else
		a->w.pl.wall_dist = (a->w.map.y - a->w.pl.pos.y + ((1 - a->w.pl.stepy) >> 1)) / a->w.pl.raydir.y;
	a->w.line_height = (int)(WIN_H / a->w.pl.wall_dist);
}

void	ft_wall_draw_start(t_thread *a)
{
	a->w.draw_start = a->w.half_height - (a->w.line_height >> 1);
	a->w.draw_start < 0 ? a->w.draw_start = 0 : 0;
	a->w.draw_end = (a->w.line_height >> 1) + a->w.half_height;
	a->w.draw_end >= WIN_H ? a->w.draw_end = WIN_H - 1 : 0;
	a->w.texture_num = a->w.map.map[a->w.map.x + a->w.map.y * a->w.map.map_w] - 1;
	if (a->w.pl.side == 0)
		a->w.wall_hit = a->w.pl.pos.y + a->w.pl.wall_dist * a->w.pl.raydir.y;
	else
		a->w.wall_hit = a->w.pl.pos.x + a->w.pl.wall_dist * a->w.pl.raydir.x;
	a->w.wall_hit -= floor(a->w.wall_hit);
	a->w.text_x = (int)(a->w.wall_hit * (double)(TEX_W));
	if (a->w.pl.side == 0 && a->w.pl.raydir.x > 0)
		a->w.text_x = TEX_W - a->w.text_x - 1;
	if (a->w.pl.side == 1 && a->w.pl.raydir.y < 0)
		a->w.text_x = TEX_W - a->w.text_x - 1;
}

void	ft_draw_walls(t_thread *a)
{
	a->w.y = a->w.draw_start;
	while (a->w.y < a->w.draw_end)
	{
		a->w.temp = (a->w.y << 8) - (WIN_H << 7 ) + (a->w.line_height << 7);
		a->w.text_y = (((a->w.temp * TEX_H) / a->w.line_height) >> 8);
		a->w.tex_col = &((Uint8*)(a->w.sdl->textures[a->w.texture_num]->pixels))[TEX_H * 3 * a->w.text_y + a->w.text_x * 3];
		a->w.color = *(Uint32*)(a->w.tex_col);
		if (a->w.pl.side == 1)
			a->w.color = (a->w.color >> 1) & 8355711;
		a->w.sdl->text_buf[a->x + (a->w.y * WIN_W)] = a->w.color;
		a->w.y++;
	}
	a->w.z_buffer[a->x] = a->w.pl.wall_dist;
}
