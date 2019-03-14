/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:45:32 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/14 17:27:24 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface		*ft_sdl_load_bmp(char *str)
{
	SDL_Surface	*texture;

	texture = SDL_LoadBMP(str);
	if (texture == NULL)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
	return (texture);
}

int				ft_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
	return (1);
}

void			*ft_safe_malloc(size_t size)
{
	void *p;

	p = malloc(size);
	if (!p)
	{
		perror("Malloc allocation failed.");
		exit(EXIT_FAILURE);
	}
	return (p);
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

void			ft_clean_all(t_wolf *w)
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
	SDL_DestroyWindow(w->sdl->m_window);
	SDL_DestroyRenderer(w->sdl->m_renderer);
	SDL_Quit();
}
