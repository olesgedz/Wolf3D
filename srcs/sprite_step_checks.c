/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_step_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:58:27 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/14 18:02:40 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_forward_check(t_wolf *w, int i)
{
	if ((w->map.map[(int)(w->map.sprite[i]->x + 0.3) + (int)(w->map.sprite[i]->y) * w->map.map_w] == 0) && ((int)(w->map.sprite[i]->x + 0.3) != (int)w->pl.pos.x) && ((int)(w->map.sprite[i]->y) * w->map.map_w != ((int)w->pl.pos.y) * w->map.map_w))
	{
		w->map.map[(int)(w->map.sprite[i]->x) + (int)(w->map.sprite[i]->y) * w->map.map_w] = 0;
		w->map.sprite[i]->x += 0.3;
		w->map.map[(int)(w->map.sprite[i]->x) + (int)(w->map.sprite[i]->y) * w->map.map_w] = 21;
		return (1);
	}
	return (0);
}