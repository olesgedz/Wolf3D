/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:09:08 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 20:44:35 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_draw_animation(t_wolf *w)
{
	int x;
	int y;

	y = w->anim.place.y;
	while (y < w->anim.pframe.size.y + w->anim.place.y)
	{
		x = w->anim.place.x;
		while (x < w->anim.pframe.size.x + w->anim.place.x)
		{
			w->tex_col = &((Uint8*)(w->weapon_texture->pixels))[(int)(3 *
			w->weapon_texture->w * (y - (int)(w->anim.place.y) +
			w->anim.pframe.coords.y) + (x - (int)(w->anim.place.x) +
			w->anim.pframe.coords.x) * 3)];
			w->color = *(Uint32 *)w->tex_col;
			w->color &= 0xFFFFFF;
			if (w->color != 0xFF00FF)
				w->sdl->text_buf[x + (y * WIN_W)] = w->color;
			x++;
		}
		y++;
	}
}

void		ft_animation_play(t_wolf *w)
{
	if (w->anim.start_animation == 1)
	{
		w->anim.frames++;
		if (w->anim.frames && w->anim.frames % ONE_ANIM == 0)
			w->anim.pframe.coords.x += 512;
		else
		{
			if (w->anim.frames > FULL_ANIM)
			{
				w->anim.start_animation = 0;
				w->anim.frames = 0;
				w->anim.pframe.coords.x = 0;
				w->t.flag = 1;
			}
		}
	}
}
