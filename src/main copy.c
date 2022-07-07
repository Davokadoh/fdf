#include "fdf.h"

typedef struct s_vec2d
{
	int	x;
	int	y;
	int	color;
}	t_vec2d;

typedef struct s_map
{
	int		width;
	int		height;
	t_vec2d	**points;
}	t_map;

typedef struct s_env
{
	t_map	*map;
	t_mlx	*mlx;
	t_data	*img;
}	t_env;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;












read_and_parse(int fd)
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
			map.points[i][j] = ft_atoi(nbrs[j]);
		i++;
	}
	return (map);
}

void	init_env(t_data *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Fil de Fer");
	init->img(env);
	init->mouse();
}

void	render_frame()
{
	project();
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}

void	hooks()
{
	mlx_loop_hook(data.mlx_ptr, &render_frame, &data);
	mlx_key_hook();
	mlx_hook();
}

void	display(t_data data)
{
	void	*mlx;
	void	*win;
	t_img	img;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, width, height, "Fil de Fer"); //Update to name of the file!
	img = mlx_new_image(mlx, width, height);
	//What is get_data_addr useful for ?
	img.addr = mlx_get_data_addr(
		img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	hooks(win);
	mlx_loop(mlx);
}

int main(int ac, char **av)
{
	t_map	map;
	t_env	env;

	if (argc != 2)
		ft_error("Usage: ./fdf <map_file>\n");
	if ((map = read_and_parse_file(av[1])) == NULL)
		ft_error("Error: invalid map file\n");
	display(map);
	free_data();
}