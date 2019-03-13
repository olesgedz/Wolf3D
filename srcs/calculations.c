/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:44:34 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 20:50:00 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_multithreading(t_wolf *w)
{
	int			x;
	int			xx;
	pthread_t	threads[TH_N];
	t_thread	args[TH_N];

	x = -1;
	xx = 0;
	while (++x < TH_N)
	{
		args[x].x = xx;
		args[x].x2 = xx + ((WIN_W / TH_N));
		ft_init_multi_wolf(&args[x].w, w);
		pthread_create(&threads[x], NULL, ft_start_wolf, (void*)&args[x]);
		xx += (WIN_W / TH_N);
	}
	x = -1;
	while (++x < TH_N)
		pthread_join(threads[x], NULL);
	w->pl.pos.x = args[x - 1].w.pl.pos.x;
	w->pl.pos.y = args[x - 1].w.pl.pos.y;
	w->pl.plane.x = args[x - 1].w.pl.plane.x;
	w->pl.plane.y = args[x - 1].w.pl.plane.y;
	w->pl.dir.x = args[x - 1].w.pl.dir.x;
	w->pl.dir.y = args[x - 1].w.pl.dir.y;
	ft_draw_sprites(w);
}

void		*ft_start_wolf(void *w)
{
	t_thread *args;

	args = (t_thread*)w;
	while (args->x < args->x2)
	{
		ft_ray_dir_calculations(args);
		ft_wall_hit(args);
		ft_wall_draw_start(args);
		ft_draw_walls(args);
		ft_get_floor_coordinates(args);
		ft_draw_floor(args);
		args->x++;
	}
	return (NULL);
}
