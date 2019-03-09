/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:45:32 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/09 21:41:54 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf3d.h"

int			ft_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
	return (1);
}

void 	ft_swap_double(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
void	ft_swap_int_here(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_comb_sort(t_wolf *w)
{
	int gap;
	char swapped;
	int i;
	int j;

	gap = SPRITES_NUM;
	swapped = 0;
	while (gap > 1 || swapped)
	{
		//shrink factor 1.3
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swapped = 0;
		i = -1;
		j = 0;
		while(++i < SPRITES_NUM - gap)
		{
			j = i + gap;
			if (w->sprite_distance[i] < w->sprite_distance[j])
			{
				ft_swap_double(&w->sprite_distance[i], &w->sprite_distance[j]);
				//printf("DO SWAPA: 1:%d 2:%d\n",w->sprite_order[i], w->sprite_order[j]);
				ft_swap_int_here(&w->sprite_order[i], &w->sprite_order[j]);
				//printf("POSLE SWAPA: 1:%d 2:%d\n",w->sprite_order[i], w->sprite_order[j]);
				swapped = 1;
			}
		}
	}
}