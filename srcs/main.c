/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:45:04 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 22:09:57 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			main(int argc, char **argv)
{
	t_wolf wolf;

	if (argc != 2)
		ft_error("Usage:./wolf3d map");
	if ((wolf.fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("Error: invalid file");
	ft_read_file(wolf.fd, &wolf.map);
	wolf.sdl = ft_init_sdl(wolf.sdl);
	ft_init_wolf(&wolf);
	ft_load_textures(&wolf);
	ft_init_sound(&wolf);
	ft_init_anim(&wolf);
	while (wolf.sdl->m_bRunning)
	{
		ft_render(&wolf);
		ft_handle_events(&wolf);
		ft_use_events(&wolf);
	}
	ft_clean_all(&wolf);
	return (0);
}
