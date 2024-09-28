#include "pipex.h"

int ft_isspace(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	argcountnosep(char *arg)
{
	int	len;
	int i;

	len = 0;
	i = 0;
	while (arg[i])
	{
		while (arg[i] && ft_isspace(arg[i]))
		{
			i++;
			len++;
		}
		len += countargword(arg + i);
		i += pass_any(arg + i);
	}
	return (len);
}

char	**nosep_arg(char *arg, char **parsed)
{
	int	i;
	int oldi;
	int	j;

	parsed[0] = (char *)ft_calloc(argcountnosep(arg) + 1, sizeof(char));
	if (!parsed[0])
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		while (arg[i] && ft_isspace(arg[i]))
		{
			parsed[0][j] = arg[i];
			i++;
			j++;
		}
		oldi = i;
		i += fill_any(arg + i, (*parsed) + j);
		j += countargword(arg + oldi);
	}
	return (parsed);
}

char	**sep_arg_split(char *arg, char fORc)
{
	char	**parsed;

	if (fORc == 1)
		parsed = (char **)ft_calloc(2, sizeof(char *));
	else
		parsed = (char **)ft_calloc((countarg(arg) + 1), sizeof(char *));
	if (!parsed)
		return (NULL);
	if (fORc == 1)
		parsed = nosep_arg(arg, parsed);
	else
		parsed = sep_arg(arg, parsed);
	return (parsed);
}

char	***holy_arg_split(char *argv[])
{
	char	***holy;
	int		i;

	holy = (char ***)ft_calloc(5, sizeof(char **));
	if (!holy)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		if (i == 0 || i == 3)
			holy[i] = sep_arg_split(argv[i + 1], 1);
		else
			holy[i] = sep_arg_split(argv[i + 1], 2);
		if (!holy[i])
			return (free_holy_split(holy), NULL);
		i++;
	}
	return (holy);
}
