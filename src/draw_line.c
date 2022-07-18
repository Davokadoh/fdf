#include "fdf.h"


static void		plot(t_env *mlx, t_pixel p, double grad)
{
	unsigned int	c;
	unsigned int	shift;
	shift = (int)(0xFF * grad);
	c = (rgb_to_int(p.color) | (shift << 24));
	put_pixel(mlx, p.x, p.y, int_to_rgb(c));
}

double	fpart(double x)
{
	return (x > 0 ? x - (int)x : x - (int)x - 1);
}

static int		what_color_is_my_stupid_pixel(t_pixel *p1, t_pixel *p2, int mod)
{
	t_vec	r;
	t_vec	g;
	t_vec	b;
	int		dist;
	dist = p2->x - p1->x;
	r.x = ((double)(p2->color.r - p1->color.r) / dist) * mod;
	g.x = ((double)(p2->color.g - p1->color.g) / dist) * mod;
	b.x = ((double)(p2->color.b - p1->color.b) / dist) * mod;




//	r.x = (p1->color & 0xFF0000) >> 16;
//	r.y = (p2->color & 0xFF0000) >> 16;
//	g.x = (p1->color & 0x00FF00) >> 8;
//	g.y = (p2->color & 0x00FF00) >> 8;
//	b.x = p1->color & 0x0000FF;
//	b.y = p2->color & 0x0000FF;
//	r.x += ((double)(r.y - r.x) / dist) * mod;
//	g.x += ((double)(g.y - g.x) / dist) * mod;
//	b.x += ((double)(b.y - b.x) / dist) * mod;
	return ((r.x << 16) + (g.x << 8) + b.x);
}

void	draw_line2(int steep, t_env *mlx, t_pixel *p1, t_pixel *p2)
{
	int		color;
	int		x;
	double	y;
	double	grad;

	x = p1->x;
	y = (double)p1->y;
	grad = p2->x - p1->x
		? (double)(p2->y - p1->y) / (double)(p2->x - p1->x) : 1;
	while (x < p2->x)
	{
		color = what_color_is_my_stupid_pixel(p1, p2, x - p1->x);
		if (steep)
		{
			plot(mlx, (t_pixel){(int)y - 1, x, int_to_rgb(color)}, fpart(y));
			plot(mlx, (t_pixel){(int)y, x, int_to_rgb(color)}, 1 - fpart(y));
		}
		else
		{
			plot(mlx, (t_pixel){x, (int)y - 1, int_to_rgb(color)}, fpart(y));
			plot(mlx, (t_pixel){x, (int)y, int_to_rgb(color)}, 1 - fpart(y));
		}
		y += grad;
		++x;
	}
}

void	swap_color(t_rgb *a, t_rgb *b)
{
	t_rgb swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

void	swap(int *a, int *b)
{
	int swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

void	xiaolin_wu(t_env *mlx, t_pixel p1, t_pixel p2)
{
	int	steep;

	steep = abs(p2.y - p1.y) > abs(p2.x - p1.x);
	if (steep)
	{
		swap(&p1.x, &p1.y);
		swap(&p2.x, &p2.y);
	}
	if (p1.x > p2.x)
	{
		swap(&p1.x, &p2.x);
		swap(&p1.y, &p2.y);
		swap_color(&p1.color, &p2.color);
	}
	draw_line2(steep, mlx, &p1, &p2);
}

