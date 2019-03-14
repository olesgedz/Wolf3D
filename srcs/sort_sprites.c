/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:21:30 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/14 18:57:34 by lsandor-         ###   ########.fr       */
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

void	ft_comb_sort(t_wolf *w)	
{	
	int gap;	
	char swapped;	
	int i;	
	int j;	

 	gap =  w->map.sprites_count;	
	swapped = 0;	
	while (gap > 1 || swapped)	
	{	
		gap = (gap * 10) / 13;	
		if (gap == 9 || gap == 10)	
			gap = 11;	
		if (gap < 1)	
			gap = 1;	
		swapped = 0;	
		i = -1;	
		j = 0;	
		while(++i <  w->map.sprites_count - gap)	
		{	
			j = i + gap;	
			if (w->map.sprite_distance[i] < w->map.sprite_distance[j])	
			{	
				ft_swap_double(&w->map.sprite_distance[i], &w->map.sprite_distance[j]);	
				ft_swap_int_here(&w->map.sprite_order[i], &w->map.sprite_order[j]);	
				swapped = 1;	
			}	
		}	
	}	
}	
