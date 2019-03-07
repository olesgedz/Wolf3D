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


// void	sdl_draw_pixel(t_sdl *sdl, int x, int y, int c)
// {
// 	sdl->text_buf[x + (y * WIN_W)] = c;
// }


void	game_draw_pixel(t_sdl *sdl, int x, int y, uint32_t c)
{
   sdl->text_buf[x + (y * WIN_W)] = c;
}
