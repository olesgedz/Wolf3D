#include "wolf3d.h"

void	ft_init_wolf(t_wolf *w)
{
	w->player.pos.x = 2;
	w->player.pos.y = 2;
	w->player.dir.x = -1;
	w->player.dir.y = 0;
	w->player.plane.x = 0;
	w->player.plane.y = 0.66;
	w->hit = 0;
	w->x = -1;
	w->movespeed = 0.5;
	w->rotspeed = 0.05;
}

void	ft_start_wolf(t_wolf *w)
{
	w->x = -1; 
	while (++w->x < WIN_W)
	{
		w->player.camerax = 2 * w->x / (double)WIN_W - 1;
		w->player.raydir.x = w->player.dir.x + w->player.plane.x * w->player.camerax;
		w->player.raydir.y = w->player.dir.y + w->player.plane.y * w->player.camerax;
		w->map.x = (int)w->player.pos.x;
		w->map.y = (int)w->player.pos.y;
		w->player.delta_dist.x = fabs(1 / w->player.raydir.x);
		w->player.delta_dist.y = fabs(1 / w->player.raydir.y);
		w->hit = 0;
		if (w->player.raydir.x < 0)
		{
			w->player.stepx = -1;
			w->player.side_dist.x = (w->player.pos.x - w->map.x) * w->player.delta_dist.x;
        }
        else
        {
            w->player.stepx = 1;
            w->player.side_dist.x = (w->map.x + 1.0 - w->player.pos.x) * w->player.delta_dist.x;
        }
        if (w->player.raydir.y < 0)
        {
            w->player.stepy = -1;
            w->player.side_dist.y = (w->player.pos.y - w->map.y) * w->player.delta_dist.y;
        }
        else
        {
            w->player.stepy = 1;
            w->player.side_dist.y = (w->map.y + 1.0 - w->player.pos.y) * w->player.delta_dist.y;
        }
        w->hit = 0;
        while (w->hit == 0)
        {
            if (w->player.side_dist.x < w->player.side_dist.y)
            {
                w->player.side_dist.x += w->player.delta_dist.x;
                w->map.x += w->player.stepx;
                w->player.side = 0;
            }
            else
            {
                w->player.side_dist.y += w->player.delta_dist.y;
                w->map.y += w->player.stepy;
                w->player.side = 1;
            }
            if (w->map.map[w->map.x + w->map.y * w->map.map_w] > 0)
                w->hit = 1;
        }
        if (w->player.side == 0)
            w->player.wall_dist = (w->map.x - w->player.pos.x + (1 - w->player.stepx) / 2) / w->player.raydir.x;
        else
            w->player.wall_dist = (w->map.y - w->player.pos.y + (1 - w->player.stepy) / 2) / w->player.raydir.y;
        //printf("perp:%f \n",w->player.wall_dist);
        w->line_height = (int)(WIN_H / w->player.wall_dist);
        //printf("line_height:%d\n",w->line_height);
        w->draw_start = -w->line_height / 2 + WIN_H / 2;
        if (w->draw_start < 0)
            w->draw_start = 0;
        w->draw_end = w->line_height / 2 + WIN_H / 2;
        if (w->draw_end >= WIN_H)
            w->draw_end = WIN_H - 1;
        if (w->map.map[w->map.x + w->map.y * w->map.map_w])
        {
            if (w->map.map[w->map.x + w->map.y * w->map.map_w] == 1)
                w->color = 0x00FF00F0;
            else if (w->map.map[w->map.x + w->map.y * w->map.map_w] == 2)
                w->color = 0x0000FFF0;
            else if (w->map.map[w->map.x + w->map.y * w->map.map_w] == 3)
                w->color = 0x00F000FF;
            else
                w->color = 0x00FF00FF;
        }
        if (w->player.side ==1)
        {
            w->color /= 2;
        }
        ft_ver_line(w->x, w->draw_start, w->draw_end, w->color, w->game);
    }
}