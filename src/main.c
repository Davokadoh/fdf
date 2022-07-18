#include "fdf.h"

int	key_handler(int keycode, t_env *env)
{
	if (keycode == 53) //change 53 to ESCAPE_KEYCODE
		exit(1); //Or free_exit(env) ?
	//else if (keycode == q)
	//	rotate(ANGLE_DE_ROTATION); //Change name
	render(env);
	return (0);
}

void	hooks(t_env *env)
{
	mlx_loop_hook(env->mlx, render, &env);
	mlx_key_hook(env->win, key_handler, &env);
	mlx_hook(env->win, 17, 0, free_exit, &env);
}

void	display(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->win_w, env->win_h, "Fil de Fer");
	env->img.img = mlx_new_image(env->mlx, env->win_w, env->win_h);
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel, &env->img.line_length, &env->img.endian);
	render(env);
	hooks(env);
	mlx_loop(env->mlx);
}

int	free_exit(t_env	*env)
{
	free(env->map.pts);
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	env->mlx = NULL;
	env->win = NULL;
	//env->LE_RESTE = NULL;
	exit(0);
}

int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

void	init_env(t_env *env)
{
	env->factor = 1;
	env->angle = 0;
}

int main(int ac, char **av)
{
	t_env	env;

	if (ac != 2)
		ft_error("Usage: ./fdf <map_file>\n");
	env.map = read_map(ft_atoi(av[1]));
	if (env.map.height == 0 || env.map.width == 0)
		ft_error("Error: invalid map file\n");
	init_env(&env);
	display(&env);
	free_exit(&env);
}