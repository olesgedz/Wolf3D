
#include "SDL2/SDL.h"
#include "libft.h"
#include <stdio.h>

#define WIN_H 780
#define WIN_W 780

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
	printf("x%d y%d\n", x, y);
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


// int			main()
// {
// 	t_game *game;
// 	game = init(game);
// 	while(game->m_bRunning)
// 	{
// 		handleEvents(game);
// 		update();
// 		render(game);
// 		SDL_Delay(10);
// 	}
// 	clean(game);
// }






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
