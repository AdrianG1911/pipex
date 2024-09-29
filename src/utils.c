#include "pipex.h"

void	freesplit(char **split)
{
	int i;
	
	if (split)
	{
		i = 0;
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

void	free_holy_split(char ***holy)
{
	int	i;
	int	j;

	if (holy)
	{
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
}
