/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:44:34 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/11 22:26:18 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_ray_dir_calculations(t_wolf *w)
{
	w->pl.camerax = w->x * w->c.camera_x_cnst - 1;
	w->pl.raydir.x = w->pl.dir.x + w->pl.plane.x * w->pl.camerax;
	w->pl.raydir.y = w->pl.dir.y + w->pl.plane.y * w->pl.camerax;
	w->map.x = (int)w->pl.pos.x;
	w->map.y = (int)w->pl.pos.y;
	w->pl.delta_dist.x = fabs(1 / w->pl.raydir.x);
	w->pl.delta_dist.y = fabs(1 / w->pl.raydir.y);
	//could be a bug!
	w->pl.stepx = w->pl.raydir.x < 0 ? -1 : 0;
	if (w->pl.stepx == -1)
		w->pl.side_dist.x = (w->pl.pos.x - w->map.x) * w->pl.delta_dist.x;
	else
	{
		w->pl.stepx = 1;
		w->pl.side_dist.x = (w->map.x + 1.0 - w->pl.pos.x) * w->pl.delta_dist.x;
	}
	if (w->pl.raydir.y < 0)
	{
		w->pl.stepy = -1;
		w->pl.side_dist.y = (w->pl.pos.y - w->map.y) * w->pl.delta_dist.y;
	}
	else
	{
		w->pl.stepy = 1;
		w->pl.side_dist.y = (w->map.y + 1.0 - w->pl.pos.y) * w->pl.delta_dist.y;
	}
}

void	ft_wall_hit(t_wolf *w)
{
	w->hit = 0;
	while (w->hit == 0)
	{
		if (w->pl.side_dist.x < w->pl.side_dist.y)
		{
			w->pl.side_dist.x += w->pl.delta_dist.x;
			w->map.x += w->pl.stepx;
			w->pl.side = 0;
		}
		else
		{
			w->pl.side_dist.y += w->pl.delta_dist.y;
			w->map.y += w->pl.stepy;
			w->pl.side = 1;
		}
		if (w->map.map[w->map.x + w->map.y * w->map.map_w] > 0 && w->map.map[w->map.x + w->map.y * w->map.map_w] < 20)
			w->hit = 1;
	}
	if (w->pl.side == 0)
		w->pl.wall_dist = (w->map.x - w->pl.pos.x + ((1 - w->pl.stepx) >> 1)) / w->pl.raydir.x;
	else
		w->pl.wall_dist = (w->map.y - w->pl.pos.y + ((1 - w->pl.stepy) >> 1)) / w->pl.raydir.y;
	w->line_height = (int)(WIN_H / w->pl.wall_dist);
}

void	ft_wall_draw_start(t_wolf *w)
{
	w->draw_start = - (w->line_height >> 1) + w->c.half_height;
	if (w->draw_start < 0)
		w->draw_start = 0;
	w->draw_end = (w->line_height >> 1) + w->c.half_height;
	if (w->draw_end >= WIN_H)
		w->draw_end = WIN_H - 1;
	w->texture_num = w->map.map[w->map.x + w->map.y * w->map.map_w] - 1;
	if (w->pl.side == 0)
		w->wall_hit = w->pl.pos.y + w->pl.wall_dist * w->pl.raydir.y;
	else
		w->wall_hit = w->pl.pos.x + w->pl.wall_dist * w->pl.raydir.x;
	w->wall_hit -= floor(w->wall_hit);
	w->text_x = (int)(w->wall_hit * (double)(TEX_W));
	if (w->pl.side == 0 && w->pl.raydir.x > 0)
		w->text_x = TEX_W - w->text_x - 1;
	if (w->pl.side == 1 && w->pl.raydir.y < 0)
		w->text_x = TEX_W - w->text_x - 1;
}

void	ft_draw_walls(t_wolf *w)
{
	w->y = w->draw_start;
	while (w->y < w->draw_end)
	{
		w->temp = (w->y << 8) - (WIN_H << 7) + (w->line_height << 7);
		w->text_y = (((w->temp * TEX_H) / w->line_height) >> 8);
		w->tex_col = &((Uint8*)(w->sdl->textures[w->texture_num]->pixels))[TEX_H * 3 * w->text_y + w->text_x * 3];
		w->color = *(Uint32*)(w->tex_col);
		if (w->pl.side == 1)
			w->color = (w->color >> 1) & 8355711;
		w->sdl->text_buf[w->x + (w->y * WIN_W)] = w->color;
		w->y++;
	}
	w->z_buffer[w->x] = w->pl.wall_dist;
}

void	ft_start_wolf(t_wolf *w)
{
	w->x = -1;
	while (++w->x < WIN_W)
	{
		ft_ray_dir_calculations(w);
		ft_wall_hit(w);
		ft_wall_draw_start(w);
		ft_draw_walls(w);
		ft_get_floor_coordinates(w);
		ft_draw_floor(w);
	}
	ft_draw_sprites(w);
	//w->t.old_time = w->t.time;
	//w->t.time = SDL_GetTicks();
	//w->t.frame_time = (w->t.time - w->t.old_time) / 1000.0;
}
