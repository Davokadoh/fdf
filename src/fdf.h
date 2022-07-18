#ifndef FDF_H
# define FDF_H

# include "../mlx/mlx.h" //To check syntax: <> vs ""
# include "../libft/libft.h" //To check syntax: <> vs ""
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_rgb
{
	char	r;
	char	g;
	char	b;
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

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	int		win_h;
	int		win_w;
	t_img	img;
	t_map	map;
	int		factor;
	int		angle;
}				t_env;

//General
t_map	read_map(int fd);
void	free_strs(char **strs);

//Matrices
t_pixel	transform(t_env *env, t_vec vec);
t_vec	translate(t_vec vec, int x, int y, int z);
t_vec	rotate(t_vec vec, int x, int y, int z);
t_vec	scale(t_vec vec, int zoom);

//Render
int		rgb_to_int(t_rgb color);
t_rgb	int_to_rgb(int color);
void	put_pixel(t_env *env, int x, int y, t_rgb color);
int		render(t_env *env);
void	draw_map(t_env *env, t_img *img, t_map map);
void	draw_background(t_env *env, t_map map, t_rgb color);
void	draw_segment(t_img *img, t_pixel a, t_pixel b);
void	xiaolin_wu();
void	bresenham();

//Mlx
void	display(t_env *env);
void	hooks(t_env *env);
int		free_exit(t_env *env);

#endif
