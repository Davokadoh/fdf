#include "fdf.h"

void	hooks(t_env *env)
{
	mlx_loop_hook(env.mlx_ptr, &render, &env); //Render each frames, could render on input only
	mlx_key_hook();
	mlx_hook(env.win, 17, 0, free_exit, &env);
	mlx_hook();
}

void	display(t_env env)
{
	void	*mlx;
	void	*win;
	t_img	img;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, width, height, "Fil de Fer"); //Update to name of the file!
	img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	render(mlx, win, img, map);
	hooks(&env);
	mlx_loop(mlx);
	//free(mlx);
	//free(win);
	//free_data(img);
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
	env.map = map;
	display(env);
	//free_exit(env);
}

