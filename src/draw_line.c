#include "fdf.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void		plot(t_data *mlx, t_point p, double grad)
{
	unsigned int	c;
	unsigned int	shift;
	shift = (int)(0xFF * grad);
	c = (p.color | (shift << 24));
	put_pixel(mlx, p.x, p.y, c);
}

double	fpart(double x)
{
	return (x > 0 ? x - (int)x : x - (int)x - 1);
}

static int		what_color_is_my_stupid_pixel(t_point *p1, t_point *p2, int mod)
{
	t_vec2	r;
	t_vec2	g;
	t_vec2	b;
	int		dist;
	dist = p2->x - p1->x;
	r.x = (p1->color & 0xFF0000) >> 16;
	r.y = (p2->color & 0xFF0000) >> 16;
	g.x = (p1->color & 0x00FF00) >> 8;
	g.y = (p2->color & 0x00FF00) >> 8;
	b.x = p1->color & 0x0000FF;
	b.y = p2->color & 0x0000FF;
	r.x += ((double)(r.y - r.x) / dist) * mod;
	g.x += ((double)(g.y - g.x) / dist) * mod;
	b.x += ((double)(b.y - b.x) / dist) * mod;
	return ((r.x << 16) + (g.x << 8) + b.x);
}

void	draw_line2(int steep, t_data *mlx, t_point *p1, t_point *p2)
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
			plot(mlx, (t_point){(int)y - 1, x, color}, fpart(y));
			plot(mlx, (t_point){(int)y, x, color}, 1 - fpart(y));
		}
		else
		{
			plot(mlx, (t_point){x, (int)y - 1, color}, fpart(y));
			plot(mlx, (t_point){x, (int)y, color}, 1 - fpart(y));
		}
		y += grad;
		++x;
	}
}

void	swap(int *a, int *b)
{
	int swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

void	draw_line(t_data *mlx, t_point p1, t_point p2)
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
		swap(&p1.color, &p2.color);
	}
	draw_line2(steep, mlx, &p1, &p2);
}

