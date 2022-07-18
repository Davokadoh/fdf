#include "fdf.h"

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i] != NULL)
		if (strs[i])
			free(strs[i]);
	free(strs);
}