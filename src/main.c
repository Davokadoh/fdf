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

int	main(void)
{
	t_mlx	vars;
	t_data	img;
	t_point	p1;
	t_point	p2;

	vars.h = 1080;
	vars.w = 1920;
	p1.x = 100;
	p1.y = 240;
	p1.color = 0x00FF0F00;
	p2.x = 1500;
	p2.y = 840;
	p2.color = 0x0000F0FF;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.w, vars.h, "Hello FdF!");
	img.img = mlx_new_image(vars.mlx, vars.w, vars.h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_line(&img, p1, p2);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 0L, close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

//TODO
//Draw 2D lines
//	Arbitrary coord.
//	With offset (eg. [0,0] is at [500,500])
//Projections
//argv/c check
//Map file parser
//Free
