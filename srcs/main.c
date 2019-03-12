/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:45:04 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/13 00:05:22 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sdl		*init(t_sdl *sdl)
{
	sdl = ft_memalloc(sizeof(t_sdl));
	sdl->text_buf = malloc(sizeof(uint32_t) * WIN_W * WIN_H);
	SDL_Init(SDL_INIT_AUDIO);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &sdl->m_pWindow, &sdl->m_pRenderer))
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
	sdl->tex =  SDL_CreateTexture(sdl->m_pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (!sdl->tex)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
	sdl->m_bRunning = 1;
	return (sdl);
}

void		ft_load_texture(t_wolf *w)
{
	w->weapon_texture = ft_safe_malloc(sizeof(SDL_Surface));
	if (!(w->weapon_texture = SDL_LoadBMP("Textures/pistol.bmp")))
		ft_error("Can't load an image");
}

void		ft_draw_animation(t_wolf *w)
{
	int x;
	int y;

	y = w->anim.place.y;
	while (y < w->anim.pframe.size.y + w->anim.place.y)
	{
		x = w->anim.place.x;
		while (x < w->anim.pframe.size.x + w->anim.place.x)
		{
			w->tex_col = &((Uint8*)(w->weapon_texture->pixels))[(int)(3 * w->weapon_texture->w * (y - (int)(w->anim.place.y) + w->anim.pframe.coords.y)\
			+ (x - (int)(w->anim.place.x) + w->anim.pframe.coords.x) * 3)];
			w->color = *(Uint32 *)w->tex_col;
			w->color &= 0xFFFFFF;
			if (w->color != 0xFF00FF)
				w->sdl->text_buf[x + (y * WIN_W)] = w->color;
			x++;
		}
		y++;
	}
}	

void		ft_animation_play(t_wolf *wolf)
{
	if (wolf->anim.start_animation == 1)
	{
		wolf->anim.frames++;
		if (wolf->anim.frames > 10 && wolf->anim.frames  % 10 == 0)
			wolf->anim.pframe.coords.x += 512;
		else
		{
			if (wolf->anim.frames > 45)
			{
				wolf->anim.start_animation = 0;
				wolf->anim.frames = 0;
				wolf->anim.pframe.coords.x = 0;
			}
		}
	}
}

void		ft_render(t_wolf *wolf)
{
	ft_animation_play(wolf);
	ft_bzero(wolf->sdl->text_buf, 4 * WIN_W * WIN_H);
	SDL_SetRenderDrawColor(wolf->sdl->m_pRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(wolf->sdl->m_pRenderer);
	ft_multithreading(wolf);
	ft_draw_animation(wolf);
	SDL_UpdateTexture(wolf->sdl->tex, 0, wolf->sdl->text_buf, WIN_W * 4);
	SDL_RenderCopy(wolf->sdl->m_pRenderer, wolf->sdl->tex, NULL, NULL);
	SDL_RenderPresent(wolf->sdl->m_pRenderer);
}

void		update()
{}

void		ft_handle_events(t_wolf *w)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		e.type == SDL_QUIT ? w->sdl->m_bRunning = 0 : 0;
		if (e.type == SDL_KEYDOWN)
		{
			e.key.keysym.scancode == SDL_SCANCODE_ESCAPE ? w->sdl->m_bRunning = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_W ? w->arr[0] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_S ? w->arr[1] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_A ? w->arr[2] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_D ? w->arr[3] = 1 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_SPACE ? w->arr[4] = 1 : 0;
		}
		if (e.type == SDL_KEYUP)
		{
			e.key.keysym.scancode == SDL_SCANCODE_W ? w->arr[0] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_S ? w->arr[1] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_A ? w->arr[2] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_D ? w->arr[3] = 0 : 0;
			e.key.keysym.scancode == SDL_SCANCODE_SPACE ? w->arr[4] = 0 : 0;
	 	}
	 }
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

static int				ft_cleanup(t_list **lst)
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




static	int	ft_fill_map(t_map *m, t_list *list)
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

int			ft_check_line(char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

static	int	ft_get_lines(int fd, t_list **lst)
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

static	void	ft_fill_sprites(t_map *m)
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

int			ft_init_anim(t_wolf *wolf)
{
	wolf->anim.start_animation = 0;
	wolf->anim.frame = 0;
	wolf->anim.pframe.size = (t_coords){512, 512};
	wolf->anim.pframe.coords = (t_coords){0, 0};
	wolf->anim.place = (t_coords){WIN_W/2 - 512/2, WIN_H - 512};
	wolf->anim.frames = 0;
	return (0);
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
	wolf.sdl = init(wolf.sdl);
	ft_load_textures(&wolf);
	ft_init_sound(&wolf);
	ft_load_texture(&wolf);
	ft_init_anim(&wolf);
	while(wolf.sdl->m_bRunning)
	{
		ft_render(&wolf);
		update();
		ft_handle_events(&wolf);
		ft_use_events(&wolf);
	}
	ft_clean_all(&wolf);
	return (0);
}
