/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:11:12 by adrgutie          #+#    #+#             */
/*   Updated: 2024/10/29 22:26:59 by adrgutie         ###   ########.fr       */
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
