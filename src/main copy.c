#include "fdf.h"

typedef struct s_vec2d
{
	int		x;
	int		y;
	t_rgb	color;
}	t_vec2d;

typedef struct s_vec3d
{
	int		x;
	int		y;
	int		z;
	t_rgb	color;
}	t_vec3d;

typedef struct s_map
{
	int	width;
	int	height;
	int	**pts;
}	t_map;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_rgb {
	//int	a;
	int	r;
	int	g;
	int	b;
}	t_rgb;







read_map(int fd)
{
	t_map	map;
	char	**nbrs;
	char	*line;
	int		i;
	int		j;

	i = 0;
	while ((line = get_next_line(fd)) > 0)
	{
		nbrs = ft_strsplit(line, ' ');
		j = -1;
		while (nbrs[++j])
			map.pts[i][j] = ft_atoi(nbrs[j]);
		i++;
	}
	ft_error();
	return (map);
}

void	draw_segment(t_img img, t_vec2d a, t_vec2d b)
{
	if (anti_aliasing)
		wu(img, a, b);
	else
		bresenham(img, a, b);
}

t_vec3d	translate(t_vec3d pt, int x, int y, int z)
{
	t_vec3d	res;

	res.x = pt.x + x;
	res.y = pt.y + y;
	res.z = pt.z + z;
	return (res);
}

t_vec3d	scale(t_vec3d pt, int zoom)
{
	t_vec3d	res;

	res.x = pt.x * zoom;
	res.y = pt.y * zoom;
	res.z = pt.z * zoom;
	return (res);
}

//a = alpha, b = beta, c = gamma
t_vec3d	rotate(t_vec3d pt, int a, int b, int c)
{
	t_vec3d	res;

	res.x = pt.x * cos(b) * cos(c)\
			+ pt.y * (sin(a) * sin(b) * cos(c) - cos(a) * sin(c))\
			+ pt.z * (cos(a) * sin(b) * cos(c) + sin(a) * sin(c));
	res.y = pt.y;
	res.z = pt.z;
	return (res);
}

//1. Translate map so center is @ origin
//2. Scale x,y,z
//3. Apply rotations
//4. Translate back to center of window
//5. Translate more if env
//6. Get color
t_vec2d	transform(t_vec3d pt)
{
	t_vec3d	res;

	res = translate(pt, -mid_map_w, -mid_map_h, -mid_map_z);
	res = scale(res, zoom);
	res = rotate(res, angle);
	res = translate(res, win_w / 2, win_h / 2, 0);
	res = translate(res, more);
	res.color = get_color(pt.z);
	return (project(res));
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

void	render(t_img img, t_map map)
{
	t_rgb	bkgrnd_color;

	bckgrnd_color = 0x111111;
	draw_background(img, bckgrnd_color);
	draw_map(img, map);
	//draw_menu();
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}

void	hooks()
{
	mlx_loop_hook(data.mlx_ptr, &render, &data); //Render each frames, could render on input only
	//mlx_key_hook();
	//mlx_hook();
}

void	display(t_map map)
{
	void	*mlx;
	void	*win;
	t_img	img;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, width, height, "Fil de Fer"); //Update to name of the file!
	img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(
		img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	hooks(win);
	render(img, map);
	mlx_loop(mlx);
	free_data(mlx);
	free_data(win);
	free_data(img);
}

int main(int ac, char **av)
{
	t_map	map;
	t_env	env;

	if (argc != 2)
		ft_error("Usage: ./fdf <map_file>\n");
	if ((map = read_map(av[1])) == NULL)
		ft_error("Error: invalid map file\n");
	display(map);
	free_data(map);
}

