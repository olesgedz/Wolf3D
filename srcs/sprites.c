/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 21:36:49 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/14 23:57:25 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
/*
** sort sprites from far to close
*/

int		ft_sprite_move(t_wolf *w, t_sprite *sprite, double x, double y)
{

		if (((w->map.map[(int)(sprite->x + x) + (int)((sprite->y + y) * w->map.map_w)]) == 0 ||
		(w->map.map[(int)(sprite->x + x) + (int)((sprite->y + y) * w->map.map_w)]) == 22))																						//if ((((int)(sprite->x + x) != (int)w->pl.pos.x) && ((int)(sprite->y + y) * w->map.map_w != ((int)w->pl.pos.y) * w->map.map_w)))
		{
			w->map.map[(int)(sprite->x) + (int)(sprite->y) * w->map.map_w] = 0;
			sprite->x += x;
			sprite->y += y;
			w->map.map[(int)(sprite->x) + (int)(sprite->y) * w->map.map_w] = 21;
			return (1);
		}
		return (0);
}
// void	ft_shenanigans(t_wolf *w)
// {
// 	int			i;
// 	static int	frames = 0;
// 	int			r;
// 	frames++;
// 	i = -1;
// 	while (++i <  w->map.sprites_count && frames == 10)
// 	{
// 		r = rand() % 4;
// 		if (w->map.sprite[i]->texture == 22 && r == 1)
// 		{
// 			if (!ft_sprite_move(w, w->map.sprite[i], 0.3, 0))
// 				r++ ;
// 		}
// 		if(w->map.sprite[i]->texture == 22 && r == 2)
// 		{
// 			if (!ft_sprite_move(w, w->map.sprite[i], -0.3, 0))
// 				r++ ;
// 		}
// 		if(w->map.sprite[i]->texture == 22 && r == 3)
// 		{
// 		if (!ft_sprite_move(w, w->map.sprite[i], 0, 0.3))
// 				r++ ;
// 		}
// 		if(w->map.sprite[i]->texture == 22 && r == 4)
// 		{
// 			ft_sprite_move(w, w->map.sprite[i], 0, -0.3);
// 		}
// 	}
// 	frames == 10 ? frames = 0 : 0;
// }

void		ft_chase_player(t_wolf *w)
{
	int			i;
	static int	frames = 0;
	double x;
	double y;
	frames++;
	i = -1;
	while (++i <  w->map.sprites_count && frames == 2)
	{
		x = 0;
		y = 0;
		if (w->map.sprite[i]->texture == 22)
		{
			// if(w->map.sprite[i]->x < w->pl.pos.x)
			// 	x+=1.3;
			// else
			// 	x-=1.3;
			// if (w->map.sprite[i]->y < w->pl.pos.y)
			// 	y+=1.3;
			// else
			// 	y-=1.3;
			x = 0.5;
			y = 0.5;
			ft_sprite_move(w, w->map.sprite[i], x, y);
		}
	}
	frames == 2 ? frames = 0 : 0;
}

void	ft_draw_sprites(t_wolf *w)
{
	int	i;

	i = -1;
	while (++i < w->map.sprites_count)
	{
		w->map.sprite_ord[i] = i;
		w->map.spr_dst[i] = ((w->pl.pos.x - w->map.sprite[i]->x) *
		(w->pl.pos.x - w->map.sprite[i]->x) + (w->pl.pos.y -
		w->map.sprite[i]->y) * (w->pl.pos.y - w->map.sprite[i]->y));
	}
	ft_comb_sort(w);
	ft_transform_sprites(w);
}

/*
** after sorting the sprites, do the projection and draw them
** transform sprite with the inverse camera matrix
** [ planeX   dirX ] -1                                     [ dirY      -dirX ]
** [               ]       =  1/(planeX*dirY-dirX*planeY) * [                 ]
** [ planeY   dirY ]                                        [ -planeY  planeX ]
** calculate height of the sprite on screen
** using "transformY" instead of the real distance prevents fisheye
** calculate lowest and highest pixel to fill in current stripe
** calculate width of the sprite
*/

void	ft_calculate_sprites(t_wolf *w)
{
	w->spr.pos.x = w->map.sprite[w->map.sprite_ord[w->i]]->x - w->pl.pos.x;
	w->spr.pos.y = w->map.sprite[w->map.sprite_ord[w->i]]->y - w->pl.pos.y;
	w->spr.inv_det = 1.0 / (w->pl.plane.x * w->pl.dir.y -
	w->pl.dir.x * w->pl.plane.y);
	w->spr.transform.x = w->spr.inv_det * (w->pl.dir.y *
	w->spr.pos.x - w->pl.dir.x * w->spr.pos.y);
	w->spr.transform.y = w->spr.inv_det * (-w->pl.plane.y *
	w->spr.pos.x + w->pl.plane.x * w->spr.pos.y);
	w->spr.screen_x = (int)((WIN_W >> 1) * (1 + w->spr.transform.x
	/ w->spr.transform.y));
	w->spr.height = abs((int)(WIN_H / w->spr.transform.y));
	w->spr.draw_starty = (-w->spr.height >> 1) + (WIN_H >> 1);
	if (w->spr.draw_starty < 0)
		w->spr.draw_starty = 0;
	w->spr.draw_endy = (w->spr.height >> 1) + (WIN_H >> 1);
	if (w->spr.draw_endy >= WIN_H)
		w->spr.draw_endy = WIN_H - 1;
	w->spr.width = abs((int)(WIN_H / w->spr.transform.y));
	w->spr.draw_startx = (-w->spr.width >> 1) + w->spr.screen_x;
	if (w->spr.draw_startx < 0)
		w->spr.draw_startx = 0;
	w->spr.draw_endx = (w->spr.width >> 1) + w->spr.screen_x;
	if (w->spr.draw_endx >= WIN_W)
		w->spr.draw_endx = WIN_W - 1;
}

/*
** loop through every vertical stripe of the w->map.sprite on screen
** the conditions in the if are:
** 1) it's in front of camera plane so you don't see things behind you
** 2) it's on the screen (left)
** 3) it's on the screen (right)
** 4) ZBuffer, with perpendicular distance
** for every pixel of the current stripe
** get current color from the texture
** paint pixel if it isn't black, black is the invisible color
*/

void	ft_show_sprites(t_wolf *w)
{
	w->stripe = w->spr.draw_startx;
	while (w->stripe < w->spr.draw_endx)
	{
		w->spr.tex_x = (int)(w->stripe - ((-w->spr.width >> 1) +
		w->spr.screen_x)) * TEX_W / w->spr.width;
		if (w->spr.transform.y > 0 && w->stripe > 0
		&& w->stripe < WIN_W && w->spr.transform.y < w->z_buffer[w->stripe])
		{
			w->y = w->spr.draw_starty;
			while (w->y < w->spr.draw_endy)
			{
				w->temp = w->y - (WIN_H >> 1) + (w->spr.height >> 1);
				w->spr.tex_y = ((w->temp * TEX_H) / w->spr.height);
				w->tex_col = &((Uint8*)(w->sdl->textures[w->map.sprite
				[w->map.sprite_ord[w->i]]->texture]->pixels))[TEX_W *
				3 * w->spr.tex_y + w->spr.tex_x * 3];
				w->color = *(Uint32*)(w->tex_col);
				if ((w->color & 0x00FFFFFF) != 0)
					w->sdl->text_buf[w->stripe + (w->y * WIN_W)] = w->color;
				w->y++;
			}
		}
		w->stripe++;
	}
}

void	ft_transform_sprites(t_wolf *w)
{
	//ft_shenanigans(w);
	ft_chase_player(w);
	w->i = -1;
	while (++w->i < w->map.sprites_count)
	{
		ft_calculate_sprites(w);
		ft_show_sprites(w);
	}
}
