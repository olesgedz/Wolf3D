/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:44:34 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/08 22:39:23 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init_wolf(t_wolf *w)
{
	w->pl.pos.x = 10;
	w->pl.pos.y = 5;
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
	w->textures = malloc(sizeof(int) * 64 * 64);
}

void	ft_start_wolf(t_wolf *w)
{
	#define texWidth 64
	#define texHeight 64
	w->x = -1;
	for(int x = 0; x < texWidth; x++)
	for(int y = 0; y < texHeight; y++)
	{
		int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
		int ycolor = y * 256 / texHeight;
		int xycolor = y * 128 / texHeight + x * 128 / texWidth;
		w->textures[texWidth * y + x]  = 65536 * 192 * (x % 16 && y % 16);
	}
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

		 int texNum = w->map.map[w->map.x + w->map.y * w->map.map_w] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (w->pl.side == 0) 
		wallX = w->pl.pos.y + w->pl.wall_dist * w->pl.raydir.y;
      else
	  	wallX = w->pl.pos.x + w->pl.wall_dist * w->pl.raydir.x;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)texWidth);
      if(w->pl.side == 0 && w->pl.raydir.x > 0) texX = texWidth - texX - 1;
      if(w->pl.side == 1 && w->pl.raydir.y < 0) texX = texWidth - texX - 1;
		// if (w->pl.side == 1)
		// 	w->color = (w->color >> 1) & 0b1111110111111101111111;
		// ft_ver_line(w->x, w->draw_start, w->draw_end, w->color, w->sdl);

		for(int y = w->draw_start; y<w->draw_end; y++)
		{
			int d = y * 256 - WIN_H * 128 + w->line_height * 128;  //256 and 128 factors to avoid floats
			// TODO: avoid the division to speed this up
			int texY = ((d * texHeight) / w->line_height) / 256;
			Uint32 color = w->textures[texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(w->pl.side == 1)
				color = (color >> 1) & 8355711;
        	game_draw_pixel(w->sdl, w->x, y, color);
      	}
    }
}
