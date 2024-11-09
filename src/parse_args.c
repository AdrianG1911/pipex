/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:09:08 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/09 20:22:54 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_isspace(int c)
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
	int	i;

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

char	*nosep_arg(char *arg)
{
	int		i;
	int		oldi;
	int		j;
	char	*parsed;

	parsed = (char *)ft_calloc(argcountnosep(arg) + 2, sizeof(char));
	if (!parsed)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		while (arg[i] && ft_isspace(arg[i]))
		{
			parsed[j] = arg[i];
			i++;
			j++;
		}
		oldi = i;
		i += fill_any(arg + i, parsed + j);
		j += countargword(arg + oldi);
	}
	return (parsed);
}

int	sep_loop(char **parsed, char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (!ft_isspace(arg[i]) && arg[i])
		{
			parsed[count] = (char *)ft_calloc(countargword(arg) + 1, \
			sizeof(char));
			if (!parsed[count])
				return (-1);
			i += fill_any(arg + i, parsed[count]);
			count++;
		}
		if (arg[i] && ft_isspace(arg[i]))
			i++;
	}
	return (1);
}

char	**sep_arg(char *arg)
{
	char	**parsed;

	parsed = (char **)ft_calloc(countarg(arg) + 2, sizeof(char *));
	if (!parsed)
		return (NULL);
	if (sep_loop(parsed, arg) == -1)
		return (freesplit(parsed), NULL);
	if (parsed[0] == NULL)
		parsed[0] = (char *)ft_calloc(1, sizeof(char));
	if (parsed[0] == NULL)
		return (freesplit(parsed), NULL);
	return (parsed);
}
