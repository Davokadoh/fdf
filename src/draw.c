#include "fdf.h"

t_rgb	int_to_rgb(int color)
{
	t_rgb rgb;

	rgb.r = color;
	rgb.g = color;
	rgb.b = color;
	return (rgb);
}

int	rgb_to_int(t_rgb color)
{
	int	rgb;

	rgb = 0;
	rgb += color.r;
	rgb += color.g;
	rgb += color.b;
	return (rgb);
}

void	put_pixel(t_env *env, int x, int y, t_rgb color)
{
	char	*dst;

	dst = env->img.addr + (y * env->win_w + x * (env->img.bits_per_pixel / 8));
	*(unsigned int*)dst = rgb_to_int(color);
}

void	draw_segment(t_img *img, t_pixel a, t_pixel b)
{
	if (1) //(anti_aliasing)
		xiaolin_wu(img, a, b);
	else
		bresenham(img, a, b); //Not implemented yet!
}

void	draw_map(t_env *env, t_img *img, t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		while (x < map.width)
		{
			x = 0;
			if (map.pts[y+1][x].z)
				draw_segment(img, transform(env, map.pts[y][x]), transform(env, map.pts[y+1][x]));
			if (map.pts[y][x+1].z)
				draw_segment(img, transform(env, map.pts[y][x]), transform(env, map.pts[y][x+1]));
			x++;
		}
		y++;
	}
}

void	draw_background(t_env *env, t_map map, t_rgb bckgrnd_color)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= map.height) //Strict < or <=
	{
		j = -1;
		while (++j <= map.width) //Strict < or <=
		{
			put_pixel(env, i, j, bckgrnd_color);
		}
	}
}

int	render(t_env *env)
{
	t_rgb	bckgrnd_color;

	bckgrnd_color.r = 0;
	bckgrnd_color.g = 0;
	bckgrnd_color.b = 0;
	draw_background(env, env->map, bckgrnd_color);
	draw_map(env, &env->img, env->map);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
