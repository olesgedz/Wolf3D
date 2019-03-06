
#include "SDL2/SDL.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

#define WIN_H 780
#define WIN_W 780

typedef struct s_player
{
	float x;
	float y;
	float angle;
	double dirX;
	double dirY;
	double planeX;
	double planeY;

	double time;
	double oldTime;
} t_player;


typedef struct s_game
{
		int				m_bRunning;
		SDL_Window		*m_pWindow;
		SDL_Renderer	*m_pRenderer;

}	t_game;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct		s_vector
{
	double		x;
	double		y;
	double		z;
	int			color;
}					t_vector;
typedef struct		s_map
{
	int			width;
	int			height;
	int			depth_min;
	int			depth_max;
	t_vector	**vectors;
	double		*colors;
	int			ncolor;
}					t_map;

typedef struct			s_line
{
	t_point		start;
	t_point		end;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
}						t_line;
/********

*******/
int			ft_error(char *reason)
{
	ft_putendl(reason);
	exit(-1);
	return (1);
}

t_vector			ft_vector_at(t_map *map, int x, int y)
{
	return (*map->vectors[y * map->width + x]);
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
	line.dx = (int)ABS((int)p2.x - (int)p1.x);
	line.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	line.dy = (int)ABS((int)p2.y - (int)p1.y);
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
		game->m_pWindow = SDL_CreateWindow("WOLF3D", 0, 0, WIN_H, WIN_W, 0);
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


t_vector			*ft_get_vector(int x, int y, int z)
{
	t_vector	*v;

	v = ft_memalloc(sizeof(t_vector));
	if (v == NULL)
		return (NULL);
	v->x = (double)x;
	v->y = (double)y;
	v->z = (double)z;
	v->color = 0xFFFFFF;
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
		ft_memdel((void **)&(*map)->vectors);
		ft_memdel((void **)map);
	}
	return (0);
}


void					ft_printMap(t_map *map)
{
	int j = 0;
	int k = 0;
	while (j < map->height)
	{
		while (k < map->width)
		{
			if (0 <= ABS(ft_vector_at(map, k, j).z)
 && ABS(ft_vector_at(map, k, j).z) <= 9)
				printf("%0.f  ", ft_vector_at(map, k, j).z);
			else
				printf("%0.f ", ft_vector_at(map, k, j).z);
			k++;
		}
		printf("\n");
		k = 0;
		j++;
	}
}




static int				ft_populate_map(t_map **m, t_list *list)
{
	t_list	*lst;
	char	**split;
	int		x;
	int		y;

	lst = list;
	y = -1;
	while (++y < (*m)->height)
	{
		x = 0;
		if ((split = ft_strsplit(lst->content, ' ')) == NULL)
			return (ft_cleanup(&list, m));
		while (x < (*m)->width)
		{
			(*m)->vectors[y * (*m)->width + x] =
				ft_get_vector(x, y, ft_atoi(split[x]));
			x++;
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
		if ((!ft_isdigit(s[i])) && s[i] != '+' && s[i] != '-'
		&& !ft_is_space(s[i]))
			return (0);
		i++;
	}
	return (1);
}



static int				ft_get_lines(int fd, t_list **lst)
{
	t_list	*temp;
	int		expected;
	char	*line;
	int		ret;

	expected = -1;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (expected == -1)
			expected = (int)ft_countwords(line, ' ');
		temp = ft_lstnew(line, ft_strlen(line) + 1);
		if ((temp) == NULL || !ft_check_line(line))
			return (ft_cleanup(lst, NULL));
		ft_lstadd(lst, temp);
		if (expected != (int)ft_countwords(line, ' '))
			return (ft_cleanup(lst, NULL));
		ft_strdel(&line);
	}
	if (expected == -1 || ret == -1)
		return (ft_cleanup(lst, NULL));
	ft_lstrev(lst);
	return (1);
}

t_map				*get_map(int width, int height)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->width = width;
	map->height = height;
	map->depth_min = 0;
	map->depth_max = 0;
	map->vectors = ft_memalloc(sizeof(t_vector *) * width * height);
	if (map->vectors == NULL)
	{
		ft_memdel((void **)&map);
		return (NULL);
	}
	return (map);
}



int						ft_read_file(int fd, t_map **m)
{
	t_list	*lst;

	lst = NULL;
	if (!(ft_get_lines(fd, &lst)))
		return (0);
	*m = get_map(ft_countwords(lst->content, ' '), ft_lstcount(lst));
	if (*m == NULL)
		return (ft_cleanup(&lst, m));
	return (ft_populate_map(m, lst));
}


t_player	*ft_get_player()
{
	static t_player player;

	player.x = 22;
	player.y = 22;
	return (&player);
}


int			main(int argc, char **argv)
{
	t_map	*map;
	t_game *game;

	int		fd;
	fd = open(argv[1], O_RDONLY);
	if (argc != 2)
		return (ft_error("usage:./wolf3d map"));
	if (fd < 0 || !ft_read_file(fd, &map))
		return (ft_error("error: invalid file"));
	ft_printMap(map);
	game = init(game);


	char image[WIN_H][WIN_W];
	while(game->m_bRunning)
	{
		handleEvents(game);
		update();
		render(game);
		SDL_Delay(10);
	}
	clean(game);
}






// int main(int argc, const char * argv[])
// {
//
// 	SDL_Window *g_pWindow;
// 	SDL_Renderer* g_pRenderer = 0;
//
// 	SDL_Init(SDL_INIT_VIDEO);
//
// 	g_pWindow = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 500, SDL_WINDOW_RESIZABLE);
// 	if(g_pWindow != 0)
// 		g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
// 	else
// 	return (1); // sdl could not initialize
// 	SDL_Event e;
// 	int quit = 0;
// 	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
// 	// clear the window to black
// 	SDL_RenderClear(g_pRenderer);
// 	SDL_RenderPresent(g_pRenderer);
//
// 	while (!quit)
// 	{
// 		while (SDL_PollEvent(&e))
// 		{
// 				if (e.type == SDL_QUIT)
// 				{
// 					quit = 1;
// 				}
// 				if (e.type == SDL_KEYDOWN)
// 				{
// 					quit = 1;
// 				}
// 				if (e.type == SDL_MOUSEBUTTONDOWN)
// 				{
// 					quit = 1;
// 				}
// 			}
// 	}
// 	SDL_DestroyWindow(g_pWindow);
// 	SDL_Quit();
// 	return (0);
// }
