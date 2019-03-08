/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:45:21 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/08 21:50:03 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// void	ft_draw_screen(t_wolf *w)
// {
// 	int y;
// 	int x;
// 	y = -1;
// 	while (++y < WIN_H)
// 	{
// 		x = -1;
// 		while (++x < WIN_W)
// 		//	w->sdl->text_buf[x + (y * WIN_W)] = w->buf[y][x];
// 	}
// }

void	ft_ver_line(int x, int start, int end, int color, t_sdl *sdl)
{
	int y;
	y = start;
	while (y++ < end)
		sdl->text_buf[x + (y * WIN_W)] = color;
	if (start > 0)
	{
		y = 0;
		while (y <= start)
		{
			sdl->text_buf[x + (y * WIN_W)] = 0x152f99;
			y++;
		}
	}
	if (end < WIN_H)
	{
		y = end;
		while (y < WIN_H)
		{
			sdl->text_buf[x + (y * WIN_W)] = 0x9995a0;
			y++;
		}
	}
}


// void	sdl_draw_pixel(t_sdl *sdl, int x, int y, int c)
// {
// 	sdl->text_buf[x + (y * WIN_W)] = c;
// }


void	game_draw_pixel(t_sdl *sdl, int x, int y, uint32_t c)
{
   sdl->text_buf[x + (y * WIN_W)] = c;
}
