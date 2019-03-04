#include "SDL2/SDL.h"

int main(int argc, const char * argv[])
{

	SDL_Window *g_pWindow;
	SDL_Renderer* g_pRenderer = 0;

	SDL_Init(SDL_INIT_VIDEO);

	g_pWindow = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 500, SDL_WINDOW_RESIZABLE);
	if(g_pWindow != 0)
		g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
	else
	return (1); // sdl could not initialize
	SDL_Event e;
	int quit = 0;
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	// clear the window to black
	SDL_RenderClear(g_pRenderer);
	SDL_RenderPresent(g_pRenderer);

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
				if (e.type == SDL_QUIT)
				{
					quit = 1;
				}
				if (e.type == SDL_KEYDOWN)
				{
					quit = 1;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					quit = 1;
				}
			}
	}
	SDL_DestroyWindow(g_pWindow);
	SDL_Quit();
	return (0);
}
