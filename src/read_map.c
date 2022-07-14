#include "fdf.h"

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
