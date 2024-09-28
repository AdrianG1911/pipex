#include "pipex.h"

void	freesplit(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_holy_split(char ***holy)
{
	int	i;
	int	j;

	i = 0;
	while (holy[i])
	{
		j = 0;
		while (holy[i][j])
		{
			free(holy[i][j]);
			j++;
		}
		free(holy[i]);
		i++;
	}
	free(holy);
}