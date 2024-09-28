#include "pipex.h"

int	fill_single(char *arg, char *sep)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (arg[i] != '\'' && arg[i])
	{
		sep[j] = arg[i];
		i++;
		j++;
	}
	if (arg[i])
		i++;
	return (i);
}

int	fill_double(char *arg, char *sep)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (arg[i] != '\"' && arg[i])
	{
		if (arg[i] == '\\')
			i++;
		if (arg[i])
		{
			sep[j] = arg[i];
			i++;
			j++;
		}
	}
	if (arg[i])
		i++;
	return (i);
}

int	fill_stuff(char *arg, char *sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (!ft_isspace(arg[i]) && arg[i])
	{
		if (arg[i] == '\\')
			i++;
		if (arg[i])
		{
			sep[j] = arg[i];
			i++;
			j++;
		}
	}
	return (i);
}

int	fill_any(char *arg, char *sep)
{
	if (*arg == '\'')
		return (fill_single(arg, sep));
	if (*arg == '\"')
		return (fill_double(arg, sep));
	else
		return (fill_stuff(arg, sep));
}

char **sep_arg(char *arg, char **parsed)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (!ft_isspace(arg[i]) && arg[i])
		{
			parsed[count] = (char *)calloc(countargword(arg) + 1, sizeof(char));
			if (!parsed[count])
				return (freesplit(parsed), NULL);
			i += fill_any(arg + i, parsed[count]);
			count++;
		}
		if (arg[i] && ft_isspace(arg[i]))
			i++;
	}
	return (parsed);
}
