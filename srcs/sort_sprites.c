/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:21:30 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/14 19:37:25 by lsandor-         ###   ########.fr       */
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

void			ft_comb_sort(t_wolf *w)
{
	t_sort_helper s;

	s.gap = w->map.sprites_count;
	s.swapped = 0;
	while (s.gap > 1 || s.swapped)
	{
		s.gap = (s.gap * 10) / 13;
		if (s.gap == 9 || s.gap == 10)
			s.gap = 11;
		s.gap < 1 ? s.gap = 1 : 0;
		s.swapped = 0;
		s.i = -1;
		s.j = 0;
		while (++s.i < w->map.sprites_count - s.gap)
		{
			s.j = s.i + s.gap;
			if (w->map.spr_dst[s.i] < w->map.spr_dst[s.j])
			{
				ft_swap_double(&w->map.spr_dst[s.i], &w->map.spr_dst[s.j]);
				ft_swap_int_here(&w->map.sprite_ord[s.i],
				&w->map.sprite_ord[s.j]);
				s.swapped = 1;
			}
		}
	}
}
