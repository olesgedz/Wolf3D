/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:21:30 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 21:34:41 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_swap_double(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void			ft_swap_int_here(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void		ft_init_sort(t_sort_helper *s, t_wolf *w)
{
	s->gap = w->map.sprites_count;
	s->swapped = 0;
	s->i = -1;
	s->j = 0;
}

void			ft_comb_sort(t_wolf *w)
{
	t_sort_helper s;

	ft_init_sort(&s, w);
	while (s.gap > 1 || s.swapped)
	{
		s.gap = (s.gap * 10) / 13;
		if (s.gap == 9 || s.gap == 10)
			s.gap = 11;
		s.gap < 1 ? s.gap = 1 : 0;
		s.swapped = 0;
		while (++s.i < w->map.sprites_count - s.gap)
		{
			s.j = s.i + s.gap;
			if (w->map.sprite_distance[s.i] < w->map.sprite_distance[s.j])
			{
				ft_swap_double(&w->map.sprite_distance[s.i],
				&w->map.sprite_distance[s.j]);
				ft_swap_int_here(&w->map.sprite_order[s.i],
				&w->map.sprite_order[s.j]);
				s.swapped = 1;
			}
		}
	}
}
