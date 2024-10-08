/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:11:12 by adrgutie          #+#    #+#             */
/*   Updated: 2024/10/06 17:01:46 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**sep_arg(char *arg, char **parsed)
{
	int	i;
	int	count;

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
	if (parsed[0] == NULL)
		parsed[0] = (char *)ft_calloc(0, sizeof(char));
	if (!parsed[0])
		return (freesplit(parsed), NULL);
	return (parsed);
}
