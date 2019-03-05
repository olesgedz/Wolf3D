
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


t_color		*ft_get_rgb(int color)
{
	static t_color rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (&rgb);

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
void ft_setpixel(t_game *game, int color, int x, int y)
{
	t_color *rgb;

	rgb = ft_get_rgb(color);
	SDL_SetRenderDrawColor(game->m_pRenderer, 255, rgb->r, rgb->g, rgb->b);
	SDL_RenderDrawPoint(game->m_pRenderer, x, y);
	SDL_SetRenderDrawColor(game->m_pRenderer, 255, 255, 255, 255);
}
void		render(t_game *game)
{
	int k;
	int j;

	k = WIN_W / 2 - 100;
	j = WIN_H  / 2 - 100;

	SDL_RenderClear(game->m_pRenderer);
	while (j < WIN_H  / 2 + 100)
	{
		k = WIN_W / 2 - 100;
		while (k < WIN_W / 2 + 100)
		{
			ft_setpixel(game, 0xFF000000, k, j);
			k++;
		}
		j++;
	}
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


int			main()
{
	t_game *game;
	game = init(game);
	while(game->m_bRunning)
	{
		handleEvents(game);
		update();
		render(game);
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
