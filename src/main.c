#include "fdf.h"

void	key_handler(int keycode, t_env *env)
{
	if (keycode == 53) //change 53 to ESCAPE_KEYCODE
		free_exit(*env);
	//else if (keycode == q)
	//	rotate(ANGLE_DE_ROTATION); //Change name
	render(*env);
}

void	hooks(t_env *env)
{
	//mlx_loop_hook(env.mlx, &render, &env);
	mlx_key_hook(env->win, key_handler, &env);
	mlx_hook(env->win, 17, 0, free_exit, &env);
}

void	display(t_env env)
{
	void	*mlx;
	void	*win;
	t_img	img;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, width, height, "Fil de Fer");
	img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	render(mlx, win, img, map);
	hooks(&env);
	mlx_loop(mlx);
	//free(mlx);
	//free(win);
	//free_data(img);
}

int	free_exit(t_env	*env)
{
	free_map(env->map);
	mlx_destroy_image(env->mlx, env->img->img);
	mlx_destroy_window(env->mlx, env->win);
	env->mlx = NULL;
	env->win = NULL;
	env->LE_RESTE = NULL;
	exit(0);
}

int main(int ac, char **av)
{
	t_map	map;
	t_env	env;

	if (ac != 2)
		ft_error("Usage: ./fdf <map_file>\n");
	//map = NULL;
	if ((map = read_map(av[1])) == NULL)
		ft_error("Error: invalid map file\n");
	init_env(&env);
	env.map = map;
	display(env);
	//free_exit(env);
}

