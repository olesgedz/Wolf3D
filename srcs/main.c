/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:45:04 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 16:13:32 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// we need to delete this funct
void					ft_printMap(t_map *map)
{
	int j = -1;
	int k = 0;
	while (++j < map->map_h)
	{
		k = -1;
		while (++k < map->map_w)
		{
			printf("%d ", map->map[j * map->map_w + k]);
		}
		printf("\n");
	}
	printf("SPRITES COUNT:%d\n",map->sprites_count);
	j = -1;
	while (++j < map->sprites_count)
	{
		printf("number:%d x:%f y:%f texture:%d\n", j, map->sprite[j]->x,map->sprite[j]->y,map->sprite[j]->texture);
	}
}

int			main(int argc, char **argv)
{
	t_wolf wolf;

	if (argc != 2)
		ft_error("Usage:./wolf3d map");
	if ((wolf.fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("Error: invalid file");
	ft_read_file(wolf.fd, &wolf.map);
	ft_printMap(&wolf.map);
	ft_init_wolf(&wolf);
	wolf.sdl = ft_init_sdl(wolf.sdl);
	ft_load_textures(&wolf);
	ft_init_sound(&wolf);
	ft_init_anim(&wolf);
	while(wolf.sdl->m_bRunning)
	{
		ft_render(&wolf);
		ft_handle_events(&wolf);
		ft_use_events(&wolf);
	}
	ft_clean_all(&wolf);
	return (0);
}