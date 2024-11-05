/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_wc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:11:15 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/05 19:58:00 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_single(char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i++;
	while (arg[i] != '\'' && arg[i])
	{
		i++;
		j++;
	}
	return (j);
}

int	count_double(char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i++;
	while (arg[i] != '\"' && arg[i])
	{
		if (arg[i] == '\\')
			i++;
		if (arg[i])
		{
			i++;
			j++;
		}
	}
	if (arg[i])
		i++;
	return (j);
}

int	count_stuff(char *arg)
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
			i++;
			j++;
		}
	}
	return (j);
}

int	countargword(char *arg)
{
	if (*arg == '\'')
		return (count_single(arg));
	if (*arg == '\"')
		return (count_double(arg));
	else
		return (count_stuff(arg));
}
