/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:45:32 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 16:42:07 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf3d.h"

SDL_Surface* ft_sdl_load_bmp(char *str)
{
	SDL_Surface *texture;
	texture = SDL_LoadBMP(str);
	if (texture == NULL)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
	return(texture);
}

int			ft_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
	return (1);
}

void	*ft_safe_malloc(size_t size)
{
	void *p = malloc(size);
	if (!p)
	{
		perror("Malloc allocation failed.");
		exit(EXIT_FAILURE);
	}
	return (p);
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

int				ft_cleanup(t_list **lst)
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_memdel(&(*lst)->content);
		ft_memdel((void **)lst);
		*lst = next;
	}
	return (0);
}

void		ft_clean_all(t_wolf *w)
{
	SDL_CloseAudioDevice(w->sdl->audio_device[0]);
	SDL_FreeWAV(w->sdl->wav_buffer[0]);
	SDL_CloseAudioDevice(w->sdl->audio_device[1]);
	SDL_FreeWAV(w->sdl->wav_buffer[1]);
	free(w->sdl->wav_buffer);
	free(w->sdl->wav_spec);
	free(w->sdl->wav_length);
	free(w->sdl->audio_device);
	free(w->sdl->textures);
	free(w->sdl->text_buf);
	if (w->map.sprites_count > 0)
	{
		free(w->map.sprite_order);
		free(w->map.sprite_distance);
		free(w->map.sprite);
	}
	free(w->map.map);
	SDL_DestroyWindow(w->sdl->m_pWindow);
	SDL_DestroyRenderer(w->sdl->m_pRenderer);
	SDL_Quit();
}