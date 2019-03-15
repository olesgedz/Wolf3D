/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 23:42:38 by jblack-b          #+#    #+#             */
/*   Updated: 2019/03/15 23:43:47 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			ft_ray_dir_calculations_helper(t_thread *a)
{
	if (a->w.pl.stepx == -1)
		a->w.pl.side_dist.x =\
		(a->w.pl.pos.x - a->w.map.x) * a->w.pl.delta_dist.x;
	else
	{
		a->w.pl.stepx = 1;
		a->w.pl.side_dist.x =\
		(a->w.map.x + 1.0 - a->w.pl.pos.x) * a->w.pl.delta_dist.x;
	}
	if (a->w.pl.raydir.y < 0)
	{
		a->w.pl.stepy = -1;
		a->w.pl.side_dist.y =\
		(a->w.pl.pos.y - a->w.map.y) * a->w.pl.delta_dist.y;
	}
	else
	{
		a->w.pl.stepy = 1;
		a->w.pl.side_dist.y =\
		(a->w.map.y + 1.0 - a->w.pl.pos.y) * a->w.pl.delta_dist.y;
	}
}

void				ft_ray_dir_calculations(t_thread *a)
{
	a->w.pl.camerax = a->x * a->w.camera_x_cnst - 1;
	a->w.pl.raydir.x = a->w.pl.dir.x + a->w.pl.plane.x * a->w.pl.camerax;
	a->w.pl.raydir.y = a->w.pl.dir.y + a->w.pl.plane.y * a->w.pl.camerax;
	a->w.map.x = (int)a->w.pl.pos.x;
	a->w.map.y = (int)a->w.pl.pos.y;
	a->w.pl.delta_dist.x = fabs(1 / a->w.pl.raydir.x);
	a->w.pl.delta_dist.y = fabs(1 / a->w.pl.raydir.y);
	a->w.pl.stepx = a->w.pl.raydir.x < 0 ? -1 : 0;
	ft_ray_dir_calculations_helper(a);
}
