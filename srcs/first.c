/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:44:34 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/09 20:51:02 by lsandor-         ###   ########.fr       */
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
	
	t_sprite sprite[SPRITES_NUM] =
	{
		{20.5, 11.5, 10},
		{18.5,4.5, 10},
		{10.0,4.5, 10},
		{10.0,12.5, 10},
		{3.5, 6.5, 10},
		{3.5, 20.5,10},
		{3.5, 14.5,10},
		{14.5,20.5,10},
		{18.5, 10.5, 9},
		{18.5, 11.5, 9},
		{18.5, 12.5, 9},
		{21.5, 1.5, 8},
		{15.5, 1.5, 8},
		{16.0, 1.8, 8},
		{16.2, 1.2, 8},
		{3.5,  2.5, 8},
		{9.5, 15.5, 8},
		{10.0, 15.1, 8},
		{10.5, 15.8, 8},
	};
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
		w->z_buffer[w->x] = w->pl.wall_dist;
		//FLOOR CASTING
		//4 different wall directions possible
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
		if (w->draw_end < 0) //becomes < 0 when the integer overflows
			w->draw_end = WIN_H;
		//draw the floor from drawEnd to the bottom of the screen
		w->y = w->draw_end;
		while (w->y < WIN_H)
		{
			w->flr.cur_dst = WIN_H / (2.0 * w->y - WIN_H);
			w->flr.weight = w->flr.cur_dst/ w->pl.wall_dist;
			w->flr.cur_x = w->flr.weight * w->flr.xwall + (1.0 - w->flr.weight) * w->pl.pos.x;
			w->flr.cur_y = w->flr.weight * w->flr.ywall + (1.0 - w->flr.weight) * w->pl.pos.y;
			w->flr.text_x = (int)(w->flr.cur_x * TEX_W) % TEX_W;
			w->flr.text_y = (int)(w->flr.cur_y * TEX_H) % TEX_H;
			//draw floor
			w->tex_col = &((Uint8*)(w->sdl->textures[2]->pixels))[TEX_W * 3 * w->flr.text_y + w->flr.text_x * 3];
			w->color = *(Uint32*)(w->tex_col);
			w->color = (w->color >> 2) & 8355711;
			w->sdl->text_buf[w->x + (w->y * WIN_W)] = w->color;
			//draw ceiling
			w->tex_col = &((Uint8*)(w->sdl->textures[1]->pixels))[TEX_W * 3 * w->flr.text_y + w->flr.text_x * 3];
			w->color = *(Uint32*)(w->tex_col);
			w->sdl->text_buf[w->x + ((WIN_H - w->y) * WIN_W)] = w->color;
			w->y++;
		}
	}
		//SPRITE CASTING
		//sort sprites from far to close
		int i = -1;
		while (++i < SPRITES_NUM)
		{
			w->sprite_order[i] = i;
			w->sprite_distance[i] = ((w->pl.pos.x - sprite[i].x) * (w->pl.pos.x - sprite[i].x) + (w->pl.pos.y - sprite[i].y) * (w->pl.pos.y - sprite[i].y));
		}
		ft_comb_sort(w);
		
		//after sorting the sprites, do the projection and draw them
		i = -1;
		while (++i < SPRITES_NUM)
		{
			w->spr.pos.x = sprite[w->sprite_order[i]].x - w->pl.pos.x;
			w->spr.pos.y = sprite[w->sprite_order[i]].y - w->pl.pos.y;
		}
		//transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]
		w->spr.inv_det = 1.0 / (w->pl.plane.x * w->pl.dir.y - w->pl.dir.x * w->pl.plane.y);
		w->spr.transform.x = w->spr.inv_det * (w->pl.dir.y * w->spr.pos.x - w->pl.dir.x * w->spr.pos.y);
		w->spr.transform.y = w->spr.inv_det * (-w->pl.plane.y * w->spr.pos.x + w->pl.plane.x * w->spr.pos.y);
		w->spr.screen_x = (int)((WIN_W >> 1) * (1 + w->spr.transform.x / w->spr.transform.y));
		//calculate height of the sprite on screen
		w->spr.height = abs((int)(WIN_H / w->spr.transform.y)); //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		w->spr.draw_starty = (- w->spr.height / 2) + (WIN_H >> 1);
		if (w->spr.draw_starty < 0)
			w->spr.draw_starty = 0;
		w->spr.draw_endy = (w->spr.height / 2) + (WIN_H >> 1);
		if (w->spr.draw_endy >= WIN_H)
			w->spr.draw_endy = WIN_H - 1;
		//w->spr.draw_endy = w->spr.draw_endy >= WIN_H ? WIN_H - 1 : w->spr.draw_endy;
		//calculate width of the sprite
		w->spr.width = abs((int)(WIN_H / w->spr.transform.y));
		w->spr.draw_startx = (-w->spr.width / 2) + w->spr.screen_x;
		if (w->spr.draw_startx < 0)
			w->spr.draw_startx = 0;
		w->spr.draw_endx = (w->spr.width >> 1) + w->spr.screen_x;
		if (w->spr.draw_endx >= WIN_W)
			w->spr.draw_endx = WIN_W - 1;
		//loop through every vertical stripe of the sprite on screen
		w->stripe = w->spr.draw_startx;
		while (w->stripe < w->spr.draw_endx)
		{
			w->spr.tex_x = (int)(256 * (w->stripe - (-w->spr.width / 2 + w->spr.screen_x)) * TEX_W / w->spr.width) / 256;
			//the conditions in the if are:
        	//1) it's in front of camera plane so you don't see things behind you
        	//2) it's on the screen (left)
        	//3) it's on the screen (right)
        	//4) ZBuffer, with perpendicular distance
			if (w->spr.transform.y > 0 && w->stripe > 0 && w->stripe < WIN_W && w->spr.transform.y < w->z_buffer[w->stripe])
			{
				w->y = w->spr.draw_starty;
				while (w->y < w->spr.draw_endy) //for every pixel of the current stripe
				{
					w->temp = (w->y << 8) - (WIN_H << 7) + (w->spr.height << 7);
					w->spr.tex_y = (((w->temp * TEX_H) / w->spr.height)	 >> 8);
					//get current color from the texture
					w->tex_col = &((Uint8*)(w->sdl->textures[sprite[w->sprite_order[i]].texture]->pixels))[TEX_W * 3 * w->spr.tex_y + w->spr.tex_x * 3];
					//paint pixel if it isn't black, black is the invisible color
					w->color = *(Uint32*)(w->tex_col);
					if ((w->color & 0x00FFFFFF) != 0)
						w->sdl->text_buf[w->stripe + (w->y * WIN_W)] = w->color; //paint pixel if it isn't black, black is the invisible color
					w->y++;
				}	
			}
			w->stripe++;
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
