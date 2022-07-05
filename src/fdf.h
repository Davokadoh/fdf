#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <stdlib.h>
#include <math.h>

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_point {
	int	x;
	int	y;
	int	color;
}				t_point;

typedef struct	s_mlx {
	void	*mlx;
	void	*win;
	int		h;
	int		w;
}				t_mlx;

void	draw_line(t_data *mlx, t_point p1, t_point p2);

#endif
