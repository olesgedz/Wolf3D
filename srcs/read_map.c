/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:56:18 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 15:59:00 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_read_file(int fd, t_map *m)
{
	t_list	*lst;
	int rows;

	lst = NULL;
	rows = ft_get_lines(fd, &lst);
	ft_get_map(m ,ft_countwords(lst->content, ' '), ft_lstcount(lst));
	m->sprites_count = ft_fill_map(m, lst);
	if (m->sprites_count)
	{
		ft_fill_sprites(m);
		m->sprite_order = ft_safe_malloc(sizeof(int) * m->sprites_count);
		m->sprite_distance = ft_safe_malloc(sizeof(double) * m->sprites_count);
	}
}

int	ft_get_lines(int fd, t_list **lst)
{
	t_list	*temp;
	char	*line;
	int rows;
	int width;

	rows = 0;
	width = -1;
	while ((get_next_line(fd, &line)) > 0)
	{
		if (width == -1)
			width = (int)ft_countwords(line, ' ');
		else
		{
			if (width != (int)ft_countwords(line, ' '))
				ft_error("Map is not rectangular.");
		}
		if (!(temp = ft_lstnew(line, ft_strlen(line) + 1)))
			ft_error("Malloc allocation failed.");
		ft_lstadd(lst, temp);
		ft_strdel(&line);
		rows++;
	}
	ft_lstrev(lst);
	return (rows);
}

void			ft_get_map(t_map *m, int map_w, int map_h)
{
	m->map_w = map_w;
	m->map_h = map_h;
	m->map = (int*)ft_safe_malloc(sizeof(int) * map_w * map_h);
}

int	ft_fill_map(t_map *m, t_list *list)
{
	t_list	*lst;
	char	**split;
	int		x;
	int		y;
	int sprites_count;

	lst = list;
	y = -1;
	sprites_count = 0;
	while (++y < m->map_h)
	{
		if (!(split = ft_strsplit(lst->content, ' ')))
			ft_error("Malloc allocation failed.");
		x = -1;
		while (++x < m->map_w)
		{
			m->map[y * m->map_w + x] = ft_atoi(split[x]);
			if (m->map[y * m->map_w + x] >= 20 && m->map[y * m->map_w + x] <= 22)
				sprites_count++;
		}
		ft_2darrayclean(&split);
		lst = lst->next;
	}
	ft_cleanup(&list);
	return (sprites_count);
}

void	ft_fill_sprites(t_map *m)
{
	int x;
	int y;
	int sprite_number;
	m->sprite = ft_safe_malloc(sizeof(t_sprite *) * m->sprites_count);
	y = -1;
	sprite_number = 0;
	while (++y < m->map_h)
	{
		x = -1;
		while(++x < m->map_w)
		{
			if (m->map[y * m->map_w + x] >= 20 && m->map[y * m->map_w + x] <= 22)
			{
				m->sprite[sprite_number] = ft_safe_malloc(sizeof(t_sprite) * 1);
				m->sprite[sprite_number]->x = x == m->map_w ? x - 0.5 : x + 0.5;
				m->sprite[sprite_number]->y = y == m->map_h ? y - 0.5 : y + 0.5;
				m->sprite[sprite_number]->texture = m->map[y * m->map_w + x];
				sprite_number++;
			}
		}

	}
}