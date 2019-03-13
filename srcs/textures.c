/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:28:24 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 16:29:41 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    ft_load_textures(t_wolf *w)
{
	w->weapon_texture = ft_safe_malloc(sizeof(SDL_Surface));
	w->weapon_texture = ft_sdl_load_bmp("Textures/pistol.bmp");
	w->sdl->textures = ft_safe_malloc(sizeof(SDL_Surface *) * 23);
	w->sdl->textures[0] = ft_sdl_load_bmp("Textures/bluestone.bmp");
	w->sdl->textures[1] = ft_sdl_load_bmp("Textures/greystone.bmp");
	w->sdl->textures[2] = ft_sdl_load_bmp("Textures/wood.bmp");
	w->sdl->textures[3] = ft_sdl_load_bmp("Textures/grey1.bmp");
	w->sdl->textures[4] = ft_sdl_load_bmp("Textures/eagle.bmp");
	w->sdl->textures[5] = ft_sdl_load_bmp("Textures/wood.bmp");
	w->sdl->textures[6] = ft_sdl_load_bmp("Textures/bluestone.bmp");
	w->sdl->textures[7] = ft_sdl_load_bmp("Textures/colorstone.bmp");
	w->sdl->textures[8] = ft_sdl_load_bmp("Textures/barrel.bmp");
	w->sdl->textures[9] = ft_sdl_load_bmp("Textures/pillar.bmp");
	w->sdl->textures[10] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[11] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[12] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[13] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[14] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[15] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[16] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[17] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[18] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[19] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[20] = ft_sdl_load_bmp("Textures/greenlight.bmp");
	w->sdl->textures[21] = ft_sdl_load_bmp("Textures/pillar.bmp");
	w->sdl->textures[22] = ft_sdl_load_bmp("Textures/barrel.bmp");
}