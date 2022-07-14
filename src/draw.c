#include "fdf.h"

void	draw_segment(t_img img, t_vec2d a, t_vec2d b)
{
	if (anti_aliasing)
		wu(img, a, b);
	else
		bresenham(img, a, b);
}

void	draw_map(t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y][x])
	{
		while (map[y][x])
		{
			x = 0;
			if (map[y+1][x])
				draw_segment(img, transform(map[y][x]), transform(map[y+1][x]));
			if (map[y][x+1])
				draw_segment(img, transform(map[y][x]), transform(map[y][x+1]));
			x++;
		}
		y++;
	}
}

void	draw_background(t_map map, t_rgb bckgrnd_color)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= map->height) //Strict < or <=
	{
		j = -1;
		while (++j <= map->width) //Strict < or <=
		{
			put_pixel(i, j, bckgrnd_color);
		}
	}
}

