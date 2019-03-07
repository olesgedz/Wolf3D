#include "wolf3d.h"

void    ft_ver_line(int x, int start, int end, int color, t_game *game)
{
    int y;

    y = start;
   // printf("start:%d end:%d y:%d\n",start,end,y);
    while (y++ < end)
    {
            //printf("setpixel: x:%d y:%d ",x,y);
            ft_image_set_pixel(game, x, y, color);
    }
}