/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:28:24 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/09 14:53:40 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    ft_load_textures(t_wolf *w)
{
	w->sdl->textures = malloc(sizeof(SDL_Surface *) * 10);
	w->sdl->textures[0] = SDL_LoadBMP("Textures/bluestone.bmp");
	w->sdl->textures[1] = SDL_LoadBMP("Textures/greystone.bmp");
	w->sdl->textures[2] = SDL_LoadBMP("Textures/wood.bmp");
	w->sdl->textures[3] = SDL_LoadBMP("Textures/grey1.bmp");
	w->sdl->textures[4] = SDL_LoadBMP("Textures/eagle.bmp");
	w->sdl->textures[5] = SDL_LoadBMP("Textures/wood.bmp");
	w->sdl->textures[6] = SDL_LoadBMP("Textures/barrel.bmp");
	w->sdl->textures[7] = SDL_LoadBMP("Textures/colorstone.bmp");
	w->sdl->textures[8] = SDL_LoadBMP("Textures/greenlight.bmp");
	w->sdl->textures[9] = NULL;
}