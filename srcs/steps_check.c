/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 18:47:26 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/10 18:48:37 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int ft_step_forward_check(t_wolf *w, unsigned char flag)
{
	if (flag == 1)
	{
		w->temp = w->map.map[(int)(w->pl.pos.x + w->pl.dir.x * w->ms) + (int)w->pl.pos.y * w->map.map_w];
		if (!w->temp || w->temp  == 20)
			return (1);
	}
	else if (flag == 0)
	{
		w->temp = w->map.map[(int)(w->pl.pos.y + w->pl.dir.y * w->ms) * w->map.map_w + (int)w->pl.pos.x];
		if (!w->temp || w->temp  == 20)
			return (1);
	}
	return (0);
}

int	ft_step_back_check(t_wolf *w, unsigned char flag)
{
	if (flag == 1)
	{
		w->temp = w->map.map[(int)(w->pl.pos.x - w->pl.dir.x * w->ms) + (int)w->pl.pos.y * w->map.map_w];
		if (!w->temp || w->temp  == 20)
			return (1);
	}
	else if (flag == 0)
	{
		w->temp = w->map.map[(int)(w->pl.pos.y - w->pl.dir.y * w->ms) * w->map.map_w + (int)w->pl.pos.x];
		if (!w->temp || w->temp  == 20)
			return (1);
	}
	return (0);
}