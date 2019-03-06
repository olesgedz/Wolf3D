#include "wolf3d.h"

void    ft_init_wolf(t_wolf *w)
{
    w->player.pos_x = 22;
    w->player.pos_y = 12;
    w->player.dirx = -1;
    w->player.diry = 0;
    w->player.planex = 0;
    w->player.planey = 0.66;
    w->player.hit = 0;
    w->x = -1;
    w->movespeed = 0.5;
    w->rotspeed = 0.05;
}

void    ft_start_wolf(t_wolf *w)
{
    #define mapWidth 24
    #define mapHeight 24
    int worldMap[mapWidth][mapHeight]=
    {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
    w->x = -1;
  
    while (++w->x < WIN_W)
    {
        w->player.camerax = 2 * w->x / (double)WIN_W - 1;
        w->player.raydir_x = w->player.dirx + w->player.planex * w->player.camerax;
        w->player.raydir_y = w->player.diry + w->player.planey * w->player.camerax;
        w->map.map_x = (int)w->player.pos_x;
        w->map.map_y = (int)w->player.pos_y;
        w->player.delta_distx = fabs(1 / w->player.raydir_x);
        w->player.delta_disty = fabs(1 / w->player.raydir_y);
        w->player.hit = 0;
        if (w->player.raydir_x < 0)
        {
            w->player.stepx = -1;
            w->player.side_distx = (w->player.pos_x - w->map.map_x) * w->player.delta_distx;
        }
        else
        {
            w->player.stepx = 1;
            w->player.side_distx = (w->map.map_x + 1.0 - w->player.pos_x) * w->player.delta_distx;
        }
        if (w->player.raydir_y < 0)
        {
            w->player.stepy = -1;
            w->player.side_disty = (w->player.pos_y - w->map.map_y) * w->player.delta_disty;
        }
        else
        {
            w->player.stepy = 1;
            w->player.side_disty = (w->map.map_y + 1.0 - w->player.pos_y) * w->player.delta_disty;
        }
        w->player.hit = 0;
        while (w->player.hit == 0)
        {
            if (w->player.side_distx < w->player.side_disty)
            {
                w->player.side_distx += w->player.delta_distx;
                w->map.map_x += w->player.stepx;
                w->player.side = 0;
            }
            else
            {
                w->player.side_disty += w->player.delta_disty;
                w->map.map_y += w->player.stepy;
                w->player.side = 1;
            }
            if (worldMap[w->map.map_x][w->map.map_y] > 0)
                w->player.hit = 1;
        }
        if (w->player.side == 0)
        {
            //printf("mapx:%d posx:%f \n",w->map.map_x,w->player.pos_x);
            w->player.perpWallDist = (w->map.map_x - w->player.pos_x + (1 - w->player.stepx) / 2) / w->player.raydir_x;
        }
        else
        {
            w->player.perpWallDist = (w->map.map_y - w->player.pos_y + (1 - w->player.stepy) / 2) / w->player.raydir_y;
        }
        //printf("perp:%f \n",w->player.perpWallDist);
        w->line_height = (int)(WIN_H / w->player.perpWallDist);
        //printf("line_height:%d\n",w->line_height);
        w->drawStart = -w->line_height / 2 + WIN_H / 2;
        if (w->drawStart < 0)
            w->drawStart = 0;
        w->drawEnd = w->line_height / 2 + WIN_H / 2;
        if (w->drawEnd >= WIN_H)
            w->drawEnd = WIN_H - 1;
        switch (worldMap[w->map.map_x][w->map.map_y])
        {
            case 1: w->color = 0x00FF0000;
            case 2: w->color = 0x0000FF00;
            case 3: w->color = 0x000000FF;
            default: w->color = 0x00F0F0FF;
        }
        if (w->player.side ==1)
        {
            w->color /= 3;
        }
        ft_ver_line(w->x, w->drawStart, w->drawEnd, w->color, w->game);
    }
}