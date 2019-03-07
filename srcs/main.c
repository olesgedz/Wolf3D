
#include "wolf3d.h"

t_color		*ft_get_rgb(int color)
{
	static t_color rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (&rgb);

}

void ft_image_set_pixel(t_sdl *sdl,  int x, int y, int color)
{
	t_color *rgb;

	rgb = ft_get_rgb(color);
	SDL_SetRenderDrawColor(sdl->m_pRenderer, 255, rgb->r, rgb->g, rgb->b);
	SDL_RenderDrawPoint(sdl->m_pRenderer, x, y);
	SDL_SetRenderDrawColor(sdl->m_pRenderer, 255, 255, 255, 255);
}

double			ft_percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}



static int			ft_put_points(t_sdl *sdl,
		t_line *l, t_point *p1)
{
	double percentage;

	if (l->dx > l->dy)
		percentage = ft_percent(l->start.x, l->end.x, p1->x);
	else
		percentage = ft_percent(l->start.y, l->end.y, p1->y);
	ft_image_set_pixel(sdl, (int)p1->x, (int)p1->y, 0x00000000);
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

void				ft_plotline(t_sdl *sdl, t_point p1, t_point p2)
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
		if (ft_put_points(sdl, &line, &p1))
			break ;
}

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

// t_sdl 		*init(t_sdl *sdl)
// {
// 	sdl = ft_memalloc(sizeof(t_sdl));
// 	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
// 	{
// 		ft_putstr("sdl inited\n");
// 		sdl->m_pWindow = SDL_CreateWindow("WOLF3D", 0, 0, WIN_W, WIN_H, 0);
// 		if(sdl->m_pWindow != 0) // window init success
// 		{
// 			ft_putstr("window created\n");
// 			sdl->m_pRenderer = SDL_CreateRenderer(sdl->m_pWindow, -1, 0);
// 		}
// 		if (sdl->m_pRenderer != 0)
// 		{
// 			SDL_SetRenderDrawColor(sdl->m_pRenderer, 255, 255, 255, 255);
// 		}
// 		else
// 			ft_putstr("fail\n");
// 	}
// 	sdl->m_bRunning = 1;
//
// 	return(sdl);
// }

t_sdl		*init(t_sdl *sdl)
{
	sdl = ft_memalloc(sizeof(t_sdl));
	sdl->text_buf = malloc(sizeof(uint32_t) * WIN_W * WIN_H);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
	}
	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &sdl->m_pWindow, &sdl->m_pRenderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
	}
	sdl->tex =  SDL_CreateTexture(sdl->m_pRenderer,
										SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STREAMING,
										WIN_W,
										WIN_H
										);
	if (!sdl->tex)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
	}
	sdl->m_bRunning = 1;
	return (sdl);
}

void		render(t_wolf *wolf)
{
	ft_bzero(wolf->sdl->text_buf, sizeof(uint32_t) * WIN_W * WIN_H);
	SDL_SetRenderDrawColor(wolf->sdl->m_pRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(wolf->sdl->m_pRenderer);
	ft_start_wolf(wolf);
	game_draw_pixel(wolf->sdl, 200, 200, 0xFF0000);
	SDL_UpdateTexture(wolf->sdl->tex, 0, wolf->sdl->text_buf, WIN_W * sizeof(int));
	SDL_RenderCopy(wolf->sdl->m_pRenderer, wolf->sdl->tex, NULL, NULL);
	SDL_RenderPresent(wolf->sdl->m_pRenderer);
}

void		update()
{}
void		handleEvents(t_wolf *w)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			w->sdl->m_bRunning = 0;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				w->sdl->m_bRunning = 0;
			if (e.key.keysym.scancode == SDL_SCANCODE_W)
			{
				w->pl.pos.x += w->pl.dir.x * w->ms;
				w->pl.pos.y += w->pl.dir.y * w->ms;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_S)
			{
				w->pl.pos.x -= w->pl.dir.x * w->ms;
				w->pl.pos.y -= w->pl.dir.y * w->ms;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_A)
			{
				w->pl.old_dirx = w->pl.dir.x;
				w->pl.dir.x = w->pl.dir.x * w->c.crs - w->pl.dir.y * w->c.srs;
				w->pl.dir.y = w->pl.old_dirx * w->c.srs + w->pl.dir.y * w->c.crs;
				w->pl.oldplanex = w->pl.plane.x;
				w->pl.plane.x = w->pl.plane.x * w->c.crs - w->pl.plane.y * w->c.srs;
				w->pl.plane.y = w->pl.oldplanex * w->c.srs + w->pl.plane.y * w->c.crs;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_D)
			{
				w->pl.old_dirx = w->pl.dir.x;
				w->pl.dir.x = w->pl.dir.x * w->c.mcrs - w->pl.dir.y * w->c.msrs;
				w->pl.dir.y = w->pl.old_dirx * w->c.msrs + w->pl.dir.y * w->c.mcrs;
				w->pl.oldplanex = w->pl.plane.x;
				w->pl.plane.x = w->pl.plane.x	* w->c.mcrs - w->pl.plane.y * w->c.msrs;
				w->pl.plane.y = w->pl.oldplanex * w->c.msrs + w->pl.plane.y * w->c.mcrs;
			}
		}
	}
}
void		clean(t_wolf *wolf)
{
		SDL_DestroyWindow(wolf->sdl->m_pWindow);
		SDL_DestroyRenderer(wolf->sdl->m_pRenderer);
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
}




static	void	ft_fill_map(t_map *m, t_list *list)
{
	t_list	*lst;
	char	**split;
	int		x;
	int		y;

	lst = list;
	y = -1;
	while (++y < m->map_h)
	{
		if (!(split = ft_strsplit(lst->content, ' ')))
			ft_error("Malloc allocation failed.");
		x = -1;
		while (++x < m->map_w)
			m->map[y * m->map_w + x] = ft_atoi(split[x]);
		ft_2darrayclean(&split);
		lst = lst->next;
	}
	ft_cleanup(&list);
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
	if (!(m->map = (int*)ft_memalloc(sizeof(int) * map_w * map_h)))
		ft_error("Malloc allocation failed.");
}



void		ft_read_file(int fd, t_map *m)
{
	t_list	*lst;
	int rows;

	lst = NULL;
	rows = ft_get_lines(fd, &lst);
	ft_get_map(m ,ft_countwords(lst->content, ' '), ft_lstcount(lst));
	ft_fill_map(m, lst);
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
	while(wolf.sdl->m_bRunning)
	{
		handleEvents(&wolf);
		update();
		render(&wolf);
	}
	clean(&wolf);
}

// int main(int argc, char *argv[])
// {
//     SDL_Window *window;
//     SDL_Renderer *renderer;
//     SDL_Surface *surface;
//     SDL_Texture *texture;
//     SDL_Event event;
// 	Uint32		*text_buf;
// 	t_sdl sdl;
// 	sdl.text_buf = malloc(sizeof(Uint32) * 320 * 240);
// 	ft_bzero(sdl.text_buf, 320 * 240);
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
//         return 3;
//     }
//
//     if (SDL_CreateWindowAndRenderer(320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
//         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
//         return 3;
//     }
//
//     surface = SDL_LoadBMP("LAND.BMP");
//     if (!surface) {
//         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
//         return 3;
//     }
//     texture =  SDL_CreateTexture(renderer,
// 										SDL_PIXELFORMAT_ARGB8888,
// 										SDL_TEXTUREACCESS_STREAMING,
// 										320,
// 										240
// 										);
//     if (!texture) {
//         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
//         return 3;
//     }
//     SDL_FreeSurface(surface);
//
// 	int c = 0xFF0000;
// 	sdl.text_buf = text_buf;
//     while (1) {
//         SDL_PollEvent(&event);
//         if (event.type == SDL_QUIT) {
//             break;
//         }
//         SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
//         SDL_RenderClear(renderer);
// 		game_draw_pixel(&sdl, 200, 200, c);
// 		SDL_UpdateTexture(texture, 0, sdl.text_buf, 320 * sizeof(Uint32));
//         SDL_RenderCopy(renderer, texture, NULL, NULL);
//         SDL_RenderPresent(renderer);
//     }
//
//     SDL_DestroyTexture(texture);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//
//     SDL_Quit();
//
//     return 0;
// }
