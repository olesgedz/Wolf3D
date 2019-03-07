#include "wolf3d.h"

void    ft_ver_line(int x, int start, int end, int color, t_sdl *game)
{
	int y;

	y = start;
	while (y++ < end)
	{
			ft_image_set_pixel(game, x, y, color);
	}
}
