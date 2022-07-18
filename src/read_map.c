#include "fdf.h"


//Read a file line by line
//Each line is split at spaces
//Each resulting string is converted to ints
t_map	read_map(int fd)
{
	t_map	map;
	char	**nbrs;
	char	*line;
	int		i;
	int		j;

	i = 0;

	while ((line = get_next_line(fd)) > 0)
	{
		nbrs = ft_split(line, ' ');
		j = -1;
		while (nbrs[++j])
			;
		if (map.width == 0)
			map.width = j;
		else if (j < map.width)
			ft_error("The map is not a square!\n");
		i++;
		free_strs(nbrs);
		free(line); //Maybe only free after while(), to test with leaks at exit ?
	}
	map.width = j;
	map.height = i;
	map.pts = ft_malloc(i * j * sizeof(int **)); //protect malloc()!
	i = 0;
	while ((line = get_next_line(fd)) > 0)
	{
		nbrs = ft_split(line, ' ');
		j = -1;
		while (nbrs[++j])
		{
			map.pts[i][j].x = j;
			map.pts[i][j].y = i;
			map.pts[i][j].z = ft_atoi(*nbrs[j]);
		}
		i++;
		free(nbrs);
		free(line); //Maybe only free after while(), to test with leaks at exit ?
	}
	//Check error and print w/ ft_error();
	return (map);
}
