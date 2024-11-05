/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:11:09 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/05 19:58:01 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pass_single(char *arg)
{
	int	i;

	i = 0;
	i++;
	while (arg[i] != '\'' && arg[i])
		i++;
	if (arg[i] == '\'')
		i++;
	return (i);
}

int	pass_double(char *arg)
{
	int	i;

	i = 0;
	i++;
	while (arg[i] != '\"' && arg[i])
	{
		if (arg[i] == '\\')
			i++;
		if (arg[i])
			i++;
	}
	if (arg[i])
		i++;
	return (i);
}

int	pass_stuff(char *arg)
{
	int	i;

	i = 0;
	while (!ft_isspace(arg[i]) && arg[i])
	{
		if (arg[i] == '\\')
			i++;
		if (arg[i])
			i++;
	}
	return (i);
}

int	pass_any(char *arg)
{
	if (*arg == '\'')
		return (pass_single(arg));
	if (*arg == '\"')
		return (pass_double(arg));
	else
		return (pass_stuff(arg));
}

int	countarg(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] && !ft_isspace(arg[i]))
		{
			count++;
			i += pass_any(arg + i);
		}
		if (arg[i] && ft_isspace(arg[i]))
			i++;
	}
	return (count);
}
