#include <mlx.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_point {
	int	x;
	int	y;
}				t_point;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		height = 1080;
	int		width = 1920;
	t_point	point;
	int		color;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, width, height, "Hello world!");
	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	color = 0x00000000;
	point.y = 100;
	while (point.y < height - 100)
	{
		point.x = 100;
		while (point.x < width - 100)
		{
			my_mlx_pixel_put(&img, point.x, point.y, color);
			point.x++;
			if (point.x % 30 == 0)
				color += 0x00000001;
		}
		color = 0x00000100 * point.y / 2;
		point.y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
