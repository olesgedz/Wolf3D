/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:28:24 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/08 21:40:26 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    ft_load_textures(t_wolf *w)
{
	w->sdl->textures = malloc(sizeof(SDL_Surface *) * 1);
	w->sdl->textures[0] = SDL_LoadBMP("Textures/10.bmp");
}