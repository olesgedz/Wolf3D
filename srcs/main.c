
#include "wolf3d.h"

t_square			ft_square_at(t_map *map, int x, int y)
{
	return (*map->squares[y * map->map_w + x]);
}


t_color		*ft_get_rgb(int color)
{
	static t_color rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (&rgb);

}

void ft_image_set_pixel(t_game *game,  int x, int y, int color)
{
	t_color *rgb;

	rgb = ft_get_rgb(color);
	SDL_SetRenderDrawColor(game->m_pRenderer, 255, rgb->r, rgb->g, rgb->b);
	SDL_RenderDrawPoint(game->m_pRenderer, x, y);
	SDL_SetRenderDrawColor(game->m_pRenderer, 255, 255, 255, 255);
}

double			ft_percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}



static int			ft_put_points(t_game *game,
		t_line *l, t_point *p1)
{
	double percentage;

	if (l->dx > l->dy)
		percentage = ft_percent(l->start.x, l->end.x, p1->x);
	else
		percentage = ft_percent(l->start.y, l->end.y, p1->y);
	ft_image_set_pixel(game, (int)p1->x, (int)p1->y, 0x00000000);
	l->err2 = l->err;
	if (l->err2 > -l->dx)
	{
		l->err -= l->dy;
		p1->x += l->sx;
	}
	if (l->err2 < l->dy)
	{
		l->err += l->dx;
		p1->y += l->sy;
	}
	return (0);
}

void				ft_plotline(t_game *game, t_point p1, t_point p2)
{
	t_line	line;

	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	line.start = p1;
	line.end = p2;
	line.dx = (int)abs((int)p2.x - (int)p1.x);
	line.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	line.dy = (int)abs((int)p2.y - (int)p1.y);
	line.sy = (int)p1.y < (int)p2.y ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
		if (ft_put_points(game, &line, &p1))
			break ;
}
/**************/
int		ft_get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int				ft_get_color(int c1, int c2, double p)
{
	int r;
	int g;
	int b;

	if (c1 == c2)
		return (c1);
	r = ft_get_light((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, p);
	g = ft_get_light((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, p);
	b = ft_get_light(c1 & 0xFF, c2 & 0xFF, p);
	return (r << 16 | g << 8 | b);
}




t_game 		*init(t_game *game)
{
	game = ft_memalloc(sizeof(t_game));
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		ft_putstr("sdl inited\n");
		game->m_pWindow = SDL_CreateWindow("WOLF3D", 0, 0, WIN_W, WIN_H, 0);
		if(game->m_pWindow != 0) // window init success
		{
			ft_putstr("window created\n");
			game->m_pRenderer = SDL_CreateRenderer(game->m_pWindow, -1, 0);
		}
		if (game->m_pRenderer != 0)
		{
			SDL_SetRenderDrawColor(game->m_pRenderer, 255, 255, 255, 255);
		}
		else
			ft_putstr("fail\n");
	}
	game->m_bRunning = 1;

	return(game);
}

void		render(t_game *game)
{
	int k;
	int j;

	k = WIN_W / 2 - 100;
	j = WIN_H  / 2 - 100;

	SDL_RenderClear(game->m_pRenderer);
	// while (j < WIN_H  / 2 + 100)
	// {
	// 	k = WIN_W / 2 - 100;
	// 	while (k < WIN_W / 2 + 100)
	// 	{
	// 		ft_setpixel(game, 0xFF000000, k, j);
	// 		k++;
	// 	}
	// 	j++;
	// }

	ft_plotline(game, (t_point){500,500}, (t_point){300,300});
	SDL_RenderPresent(game->m_pRenderer);
}

void		update()
{}
void		handleEvents(t_game *game)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			game->m_bRunning = 0;
		}
		if (e.type == SDL_KEYDOWN)
		{
			game->m_bRunning = 0;
		}
	}
}
void		clean(t_game *game)
{
		SDL_DestroyWindow(game->m_pWindow);
		SDL_DestroyRenderer(game->m_pRenderer);
		SDL_Quit();
}


t_square			*ft_get_square(int x, int y, int z)
{
	t_square	*v;

	if(!(v = ft_memalloc(sizeof(t_square))))
		ft_error("Malloc allocation failed.");
	v->x = (double)x;
	v->y = (double)y;
	v->z = (double)z;
	return (v);
}

static int				ft_cleanup(t_list **lst, t_map **map)
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_memdel(&(*lst)->content);
		ft_memdel((void **)lst);
		*lst = next;
	}
	if (map && *map)
	{
		ft_memdel((void **)&(*map)->squares);
		ft_memdel((void **)map);
	}
	return (0);
}


void					ft_printMap(t_map *map)
{
	int j = 0;
	int k = 0;
	while (j < map->map_h)
	{
		while (k < map->map_w)
		{
			if (0 <= fabs(ft_square_at(map, k, j).z)
 && fabs(ft_square_at(map, k, j).z) <= 9)
				printf("%0.f  ", ft_square_at(map, k, j).z);
			else
				printf("%0.f ", ft_square_at(map, k, j).z);
			k++;
		}
		printf("\n");
		k = 0;
		j++;
	}
}




static int				ft_populate_map(t_map *m, t_list *list)
{
	t_list	*lst;
	char	**split;
	int		x;
	int		y;

	lst = list;
	y = -1;
	while (++y < m->map_h)
	{
		if ((split = ft_strsplit(lst->content, ' ')) == NULL)
			ft_error("Malloc allocation failed.");
		x = -1;
		while (++x < m->map_w)
		{
			m->squares[y * m->map_w + x] =
				ft_get_square(x, y, ft_atoi(split[x]));
		}
		ft_2darrayclean(&split);
		lst = lst->next;
	}
	ft_cleanup(&list, NULL);
	return (1);
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



static int				ft_get_lines(int fd, t_list **lst)
{
	t_list	*temp;
	int		expected;
	char	*line;

	expected = -1;
	while ((get_next_line(fd, &line)) > 0)
	{
		if (expected == -1)
			expected = (int)ft_countwords(line, ' ');
		temp = ft_lstnew(line, ft_strlen(line) + 1);
		if ((temp) == NULL || !ft_check_line(line))
			return (ft_cleanup(lst, NULL));
		ft_lstadd(lst, temp);
		ft_strdel(&line);
	}
	ft_lstrev(lst);
	return (1);
}

void			get_map(t_map *map, int map_w, int height)
{
	map->map_w = map_w;
	map->map_h = height;
	map->squares = ft_memalloc(sizeof(t_square *) * map_w * height);
	if (map->squares == NULL)
		ft_error("Malloc allocation failed.");
}



int						ft_read_file(int fd, t_map *m)
{
	t_list	*lst;

	lst = NULL;
	if (!(ft_get_lines(fd, &lst)))
		return (0);
	get_map(m ,ft_countwords(lst->content, ' '), ft_lstcount(lst));
	return (ft_populate_map(m, lst));
}



int			main(int argc, char **argv)
{
	t_wolf wolf;

	if (argc != 2)
		ft_error("Usage:./wolf3d map");
	wolf.fd = open(argv[1], O_RDONLY);
	if (wolf.fd < 0 || !ft_read_file(wolf.fd, &wolf.map))
		ft_error("Error: invalid file");
	ft_printMap(&wolf.map);
	wolf.game = init(wolf.game);
	while(wolf.game->m_bRunning)
	{
		handleEvents(wolf.game);
		update();
		render(wolf.game);
		SDL_Delay(10);
	}
	clean(wolf.game);
}