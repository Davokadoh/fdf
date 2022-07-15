#ifndef FDF_H
# define FDF_H

# include "mlx.h" //To check syntax: <> vs ""
# include <stdlib.h>
# include <math.h>

typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

typedef struct	s_pixel
{
	int		x;
	int		y;
	t_rgb	color;
}				t_pixel;

typedef struct	s_vec
{
	int	x;
	int	y;
	int	z;
}				t_vec;

typedef struct	s_map
{
	int		width;
	int		height;
	t_vec	**pts;
}				t_map;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	int		h;
	int		w;
}				t_mlx;

//General
t_map	read_map(int fd);

//Matrices
t_pixel	transform(t_vec vec);
t_vec	translate(t_vec vec, int x, int y, int z);
t_vec	rotate(t_vec vec, int x, int y, int z);
t_vec	scale(t_vec vec, int zoom);

//Render
void	render(t_img img, t_map map);
void	draw_map(t_map map);
void	draw_background(t_map map, t_rgb color);
void	draw_line(t_img *img, t_pixel p1, t_pixel p2);
void	xialon_wu();
void	bresenham();

//Mlx
void	display(t_map map);
void	hooks(t_env env);
void	free_exit(t_env env);

#endif
