/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:29:36 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/11 17:36:05 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    ft_use_events(t_wolf *w)
{
    if (w->arr[0] == 1)
    {
        w->sdl->i = 1;
		ft_load_sound(w);
		if (ft_step_forward_check(w, 1))
			w->pl.pos.x += w->pl.dir.x * w->ms;
		if (ft_step_forward_check(w, 0))
			w->pl.pos.y += w->pl.dir.y * w->ms;
    }
    if (w->arr[1] == 1)
    {
        if (ft_step_back_check(w, 1))
			w->pl.pos.x -= w->pl.dir.x * w->ms;
		if (ft_step_back_check(w, 0))
			w->pl.pos.y -= w->pl.dir.y * w->ms;
    }
    if (w->arr[2] == 1)
    {
        w->pl.old_dirx = w->pl.dir.x;
        w->pl.dir.x = w->pl.dir.x * w->c.crs - w->pl.dir.y * w->c.srs;
        w->pl.dir.y = w->pl.old_dirx * w->c.srs + w->pl.dir.y * w->c.crs;
        w->pl.oldplanex = w->pl.plane.x;
        w->pl.plane.x = w->pl.plane.x * w->c.crs - w->pl.plane.y * w->c.srs;
        w->pl.plane.y = w->pl.oldplanex * w->c.srs + w->pl.plane.y * w->c.crs;
    }
    if (w->arr[3] == 1)
    {
        w->pl.old_dirx = w->pl.dir.x;
        w->pl.dir.x = w->pl.dir.x * w->c.mcrs - w->pl.dir.y * w->c.msrs;
        w->pl.dir.y = w->pl.old_dirx * w->c.msrs + w->pl.dir.y * w->c.mcrs;
        w->pl.oldplanex = w->pl.plane.x;
        w->pl.plane.x = w->pl.plane.x	* w->c.mcrs - w->pl.plane.y * w->c.msrs;
        w->pl.plane.y = w->pl.oldplanex * w->c.msrs + w->pl.plane.y * w->c.mcrs;
    }
    if(w->arr[4] == 1)
    {
        w->sdl->i = 0;
        ft_load_sound(w);
        w->anim.start_animation  = 1;
    }
}