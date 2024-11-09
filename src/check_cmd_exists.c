/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_exists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:38:22 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/09 20:12:20 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	checkpaths(char *cmd, char **paths, char **testpath)
{
	if (cmd[0] == 0)
		return (127);
	while (*paths)
	{
		*testpath = joinpaths(cmd, *paths);
		if ((*testpath) == NULL)
			return (0);
		if (access(*testpath, F_OK) == 0)
			return (0);
		free(*testpath);
		*testpath = NULL;
		paths++;
	}
	return (127);
}

int	check_cmd_not_exist(char *cmd, char *envp[])
{
	char	**paths;
	char	*testpath;

	testpath = NULL;
	paths = getpaths(envp);
	if (!paths)
		return (0);
	if (checkpaths(cmd, paths, &testpath) == 127)
		return (free(testpath), 127);
	return (free(testpath), 0);
}
