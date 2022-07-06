#include "fdf.h"

int	close(int keycode, t_mlx *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return 0;
}

// Tries to read map file
// Returns 0 if success, 1 if error
// If success, fills in *map with map data
read_and_parse(int fd, t_data *data)
{
	while (get_next_line() > 0)
	{
		data->map[data->map_size] = ft_strsplit(line, ' ');
		data->map_size++;
		
	}
}

typedef struct s_data
{
	int	map_size;
	int	**map;
}	t_data;

statuc void	init_env(t_data *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Fil de Fer");
	init-img(env);
	init->mouse();
}

// Call func to read and parse input file
// If file is valid, init vars then draw map
// Hooks to get keyboard and mous inputs
// Start mlx loop
int main(int argc, char **argv)
{
	t_data env;

	if (argc != 2)
	{
		write(2, "Usage: ./fdf <map.fdf>\n", 26);
		return (1);
	}
	init_env(&env);
	if (read_and_parse_file(argv[1], &env))
		return (1);
	render(env);
	//More hooks still needed
	mlx_hook(vars->win, 2, 0L, close, &vars);
	//mlx_loop_hook(vars->mlx, render, &vars);
	mlx_loop(vars->mlx);
}