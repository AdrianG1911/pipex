#include "pipex.h"



void	double_quote(char *arg, int *i, int *j)
{

}

void	single_quote(char *arg, int *i, int *j)
{
	(*j)++;
	while (arg[*j] != '\'' && arg[*j])
	{
		arg[*i] = arg[*j];
		i++;
		j++;
	}
	if (arg[*j] == '\'')
		(*j)++;
}

void	parse_args(char *arg)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (arg[j])
	{
		if (arg[j] == '\'')
			single_quote(arg, &i, &j);
		else if (arg[j] == '\"')
			double_quote(arg, &i, &j);
	}
}

void	well_done_split(char argv[])
{
	int i;

	i = 0;
	while (++i < 5)
		parse_args(argv[i]);
}

char	***holy_arg_split(char **welldone)
{
	char ***holy;

	holy = (char ***)ft_calloc(5, sizeof(char **));
	if (!holy)
		return (NULL);
}