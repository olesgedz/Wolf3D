/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:44:34 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/09 14:57:06 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init_wolf(t_wolf *w)
{
	w->pl.pos.x = 2;
	w->pl.pos.y = 2;
	w->pl.dir.x = -1;
	w->pl.dir.y = 0;
	w->pl.plane.x = 0;
	w->pl.plane.y = 0.66;
	w->hit = 0;
	w->x = -1;
	w->ms = 0.3;
	w->rs = 0.05;
	w->c.crs = cos(w->rs);
	w->c.srs = sin(w->rs);
	w->c.mcrs = cos(- w->rs);
	w->c.msrs = sin(- w->rs);
	w->c.half_height = (WIN_H >> 1);
	w->c.camera_x_cnst = 2 / (double)WIN_W;
}

void	ft_start_wolf(t_wolf *w)
{
	w->x = -1;
	while (++w->x < WIN_W)
	{
		w->pl.camerax = w->x * w->c.camera_x_cnst - 1;
		w->pl.raydir.x = w->pl.dir.x + w->pl.plane.x * w->pl.camerax;
		w->pl.raydir.y = w->pl.dir.y + w->pl.plane.y * w->pl.camerax;
		w->map.x = (int)w->pl.pos.x;
		w->map.y = (int)w->pl.pos.y;
		w->pl.delta_dist.x = fabs(1 / w->pl.raydir.x);
		w->pl.delta_dist.y = fabs(1 / w->pl.raydir.y);
		w->hit = 0;
		if (w->pl.raydir.x < 0)
		{
			w->pl.stepx = -1;
			w->pl.side_dist.x = (w->pl.pos.x - w->map.x) * w->pl.delta_dist.x;
		}
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
			if (w->map.map[w->map.x + w->map.y * w->map.map_w] > 0)
				w->hit = 1;
		}
		if (w->pl.side == 0)
			w->pl.wall_dist = (w->map.x - w->pl.pos.x + ((1 - w->pl.stepx) >> 1)) / w->pl.raydir.x;
		else
			w->pl.wall_dist = (w->map.y - w->pl.pos.y + ((1 - w->pl.stepy) >> 1)) / w->pl.raydir.y;
		w->line_height = (int)(WIN_H / w->pl.wall_dist);
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
		//FLOOR CASTING
		//4 different wall directions possible
		if (w->pl.side == 0 && w->pl.raydir.x > 0)
		{
			w->floorx_w = w->map.x;
			w->floory_w = w->map.y + w->wall_hit;
		}
		else if (w->pl.side == 0 && w->pl.raydir.x < 0)
		{
			w->floorx_w = w->map.x + 1.0;
			w->floory_w = w->map.y + w->wall_hit;
		}
		else if (w->pl.side == 1 && w->pl.raydir.y > 0)
		{
			w->floorx_w = w->map.x + w->wall_hit;
			w->floory_w = w->map.y;
		}
		else
		{
			w->floorx_w = w->map.x + w->wall_hit;
			w->floory_w = w->map.y + 1.0;
		}
		w->dist_wall = w->pl.wall_dist;
		w->dist_player = 0.0;
		if (w->draw_end < 0) //becomes < 0 when the integer overflows
			w->draw_end = WIN_H;
		//draw the floor from drawEnd to the bottom of the screen
		w->y = w->draw_end;
		while (w->y < WIN_H)
		{
			w->current_dist = WIN_H / (2.0 * w->y - WIN_H);
			w->weight = (w->current_dist - w->dist_player) / (w->dist_wall - w->dist_player);
			w->current_floorx = w->weight * w->floorx_w + (1.0 - w->weight) * w->pl.pos.x;
			w->current_floory = w->weight * w->floory_w + (1.0 - w->weight) * w->pl.pos.y;
			w->floor_text_x = (int)(w->current_floorx * TEX_W) % TEX_W;
			w->floor_text_y = (int)(w->current_floory * TEX_H) % TEX_H;
			//draw floor
			w->tex_col = &((Uint8*)(w->sdl->textures[2]->pixels))[TEX_W * 3 * w->floor_text_y + w->floor_text_x * 3];
			w->color = *(Uint32*)(w->tex_col);
			w->color = (w->color >> 2) & 8355711;
			w->sdl->text_buf[w->x + (w->y * WIN_W)] = w->color;
			//draw ceiling
			w->tex_col = &((Uint8*)(w->sdl->textures[1]->pixels))[TEX_W * 3 * w->floor_text_y + w->floor_text_x * 3];
			w->color = *(Uint32*)(w->tex_col);
			w->sdl->text_buf[w->x + ((WIN_H - w->y) * WIN_W)] = w->color;
			w->y++;
		}
		//ft_draw_screen(w);
		// if (w->map.map[w->map.x + w->map.y * w->map.map_w])
		// {
		// 	if (w->map.map[w->map.x + w->map.y * w->map.map_w] == 1)
		// 		w->color = 0xafceff;
		// 	else if (w->map.map[w->map.x + w->map.y * w->map.map_w] == 2)
		// 		w->color = 0x00FFF0;
		// 	else if (w->map.map[w->map.x + w->map.y * w->map.map_w] == 3)
		// 		w->color = 0xF000FF;
		// 	else
		// 		w->color = 0xFF00FF;
		// }
		// if (w->pl.side ==1)
		// 	w->color = w->color >> 1;
		// ft_ver_line(w->x, w->draw_start, w->draw_end, w->color, w->sdl);
	}
}
