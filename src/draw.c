#include "fdf.h"

void	draw_segment(t_img *img, t_pixel a, t_pixel b)
{
	if (1) //(anti_aliasing)
		xialon_wu(img, a, b);
	else
		bresenham(img, a, b); //Not implemented yet!
}

void	draw_map(t_img img, t_map map)
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

void	render(t_env env)
{
	t_rgb	bkgrnd_color;

	bckgrnd_color = 0x111111;
	draw_background(img, bckgrnd_color);
	draw_map(img, map);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}
