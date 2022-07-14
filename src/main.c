#include "fdf.h"

void	render(t_img img, t_map map)
{
	t_rgb	bkgrnd_color;

	bckgrnd_color = 0x111111;
	draw_background(img, bckgrnd_color);
	draw_map(img, map);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}

void	hooks()
{
	mlx_loop_hook(env.mlx_ptr, &render, &env); //Render each frames, could render on input only
	mlx_key_hook();
	mlx_hook(env.win, 17, 0, free_exit, &env);
	mlx_hook();
}

void	display(t_map map)
{
	void	*mlx;
	void	*win;
	t_img	img;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, width, height, "Fil de Fer"); //Update to name of the file!
	img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	render(img, map);
	hooks();
	mlx_loop(mlx);
	free(mlx);
	free(win);
	free_data(img);
}

int	free_exit(void	*env)
{
	free_map(&env->map);
	mlx_destroy_image(env->mlx, env->img->img);
	mlx_destroy_window(env->mlx, env->win);
	env->mlx_ptr = NULL;
	env->win_ptr = NULL;
	exit(0);
}

int main(int ac, char **av)
{
	t_map	map;
	t_env	env;

	if (ac != 2)
		ft_error("Usage: ./fdf <map_file>\n");
	if ((map = read_map(av[1])) == NULL)
		ft_error("Error: invalid map file\n");
	display(map);
	free_exit(env);
}

