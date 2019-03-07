#include "wolf3d.h"

void	ft_init_wolf(t_wolf *w)
{
	w->pl.pos.x = 10;
	w->pl.pos.y = 5;
	w->pl.dir.x = -1;
	w->pl.dir.y = 0;
	w->pl.plane.x = 0;
	w->pl.plane.y = 0.66;
	w->hit = 0;
	w->x = -1;
	w->ms = 0.5;
	w->rs = 0.05;
	w->c.crs = cos(w->rs);
	w->c.srs = sin(w->rs);
	w->c.mcrs = cos(- w->rs);
	w->c.msrs = sin(- w->rs);
	w->c.half_height = (WIN_H >> 1);
}

void	ft_start_wolf(t_wolf *w)
{
	w->x = -1;
	while (++w->x < WIN_W)
	{
		w->pl.camerax = 2 * w->x / (double)WIN_W - 1;
		w->pl.raydir.x = w->pl.dir.x + w->pl.plane.x * w->pl.camerax;
		w->pl.raydir.y = w->pl.dir.y + w->pl.plane.y * w->pl.camerax;
		w->map.x = (int)w->pl.pos.x;
		w->map.y = (int)w->pl.pos.y;
		w->pl.delta_dist.x = fabs(1 / w->pl.raydir.x);
		w->pl.delta_dist.y = fabs(1 / w->pl.raydir.y);
		w->hit = 0;
		if (w->pl.raydir.x < 0)
		{
			w->pl.stepx = -1;
			w->pl.side_dist.x = (w->pl.pos.x - w->map.x) * w->pl.delta_dist.x;
		}
		else
		{
			w->pl.stepx = 1;
			w->pl.side_dist.x = (w->map.x + 1.0 - w->pl.pos.x) * w->pl.delta_dist.x;
		}
		if (w->pl.raydir.y < 0)
		{
			w->pl.stepy = -1;
			w->pl.side_dist.y = (w->pl.pos.y - w->map.y) * w->pl.delta_dist.y;
		}
		else
		{
			w->pl.stepy = 1;
			w->pl.side_dist.y = (w->map.y + 1.0 - w->pl.pos.y) * w->pl.delta_dist.y;
		}
		w->hit = 0;
		while (w->hit == 0)
		{
			if (w->pl.side_dist.x < w->pl.side_dist.y)
<<<<<<< HEAD
			{
				w->pl.side_dist.x += w->pl.delta_dist.x;
				w->map.x += w->pl.stepx;
				w->pl.side = 0;
			}
			else
			{
				w->pl.side_dist.y += w->pl.delta_dist.y;
				w->map.y += w->pl.stepy;
				w->pl.side = 1;
			}
			if (w->map.map[w->map.x + w->map.y * w->map.map_w] > 0)
				w->hit = 1;
		}
		if (w->pl.side == 0)
			w->pl.wall_dist = (w->map.x - w->pl.pos.x + ((1 - w->pl.stepx) >> 1)) / w->pl.raydir.x;
		else
			w->pl.wall_dist = (w->map.y - w->pl.pos.y + ((1 - w->pl.stepy) >> 1)) / w->pl.raydir.y;
		w->line_height = (int)(WIN_H / w->pl.wall_dist);
		w->draw_start = - (w->line_height >> 1) + w->c.half_height;
		if (w->draw_start < 0)
			w->draw_start = 0;
		w->draw_end = (w->line_height >> 1) + w->c.half_height;
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
		if (w->pl.side ==1)
		{
			w->color /= 2;
		}
		ft_ver_line(w->x, w->draw_start, w->draw_end, w->color, w->game);
	}
}
=======
            {
                w->pl.side_dist.x += w->pl.delta_dist.x;
                w->map.x += w->pl.stepx;
                w->pl.side = 0;
            }
            else
            {
                w->pl.side_dist.y += w->pl.delta_dist.y;
                w->map.y += w->pl.stepy;
                w->pl.side = 1;
            }
            if (w->map.map[w->map.x + w->map.y * w->map.map_w] > 0)
                w->hit = 1;
        }
        if (w->pl.side == 0)
            w->pl.wall_dist = (w->map.x - w->pl.pos.x + ((1 - w->pl.stepx) >> 1)) / w->pl.raydir.x;
        else
            w->pl.wall_dist = (w->map.y - w->pl.pos.y + ((1 - w->pl.stepy) >> 1)) / w->pl.raydir.y;
        w->line_height = (int)(WIN_H / w->pl.wall_dist);
        w->draw_start = - (w->line_height >> 1) + w->c.half_height;
        if (w->draw_start < 0)
            w->draw_start = 0;
        w->draw_end = (w->line_height >> 1) + w->c.half_height;
        if (w->draw_end >= WIN_H)
            w->draw_end = WIN_H - 1;
        if (w->map.map[w->map.x + w->map.y * w->map.map_w])
        {
            if (w->map.map[w->map.x + w->map.y * w->map.map_w] == 1)
                w->color = 0xafceff;
            else if (w->map.map[w->map.x + w->map.y * w->map.map_w] == 2)
                w->color = 0x00FFF0;
            else if (w->map.map[w->map.x + w->map.y * w->map.map_w] == 3)
                w->color = 0xF000FF;
            else
                w->color = 0xFF00FF;
        }
        if (w->pl.side ==1)
        {
            w->color /= 2;
        }
        ft_ver_line(w->x, w->draw_start, w->draw_end, w->color, w->sdl);
    }
}
>>>>>>> d4fdd87cdc85a5dcf827e345f9114d0effc756f5
