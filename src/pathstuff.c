/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathstuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:10:44 by adrgutie          #+#    #+#             */
/*   Updated: 2024/10/06 17:02:15 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*joinpaths(char *cmd, char *path)
{
	char	*joined;
	char	*temp;
	int		plen;

	plen = ft_strlen(path);
	if (path[plen - 1] == '/')
		return (ft_strjoin(path, cmd));
	else
	{
		joined = ft_strjoin(path, "/");
		temp = joined;
		joined = ft_strjoin(joined, cmd);
		free(temp);
		return (joined);
	}
}

static int	iterpaths(char *cmd, char **paths, char **testpath)
{
	if (!cmd[0])
		return (ft_putstr_fd(": command not found\n", STDERR_FILENO), 0);
	while (*paths)
	{
		*testpath = joinpaths(cmd, *paths);
		if (!(*testpath))
			return (0);
		if (*testpath)
		{
			if (access(*testpath, X_OK) == 0)
				return (1);
			if (errno == EACCES)
				return (0);
		}
		free(*testpath);
		*testpath = NULL;
		paths++;
	}
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (0);
}

static char	*findexecpath(char *cmd, char **paths)
{
	char	*testpath;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		perror(cmd);
	}
	else
	{
		if (iterpaths(cmd, paths, &testpath))
			return (testpath);
		if (errno == EACCES)
		{
			perror(testpath);
			free(testpath);
		}
	}
	return (NULL);
}

static char **getpaths(char *envp[])
{
	int i;
	char **emptypath;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
	{
		emptypath = (char **)ft_calloc(2, sizeof(char *));
		if (!emptypath)
			return (NULL);
		emptypath[0] = ft_strdup("");
		return(emptypath);
	}
	return (ft_split(envp[i] + 5, ':'));
}

char	*findcmdpath(char *cmd, char *envp[])
{
	char	**paths;
	char	*path;

	paths = getpaths(envp);
	if (!paths)
		return (NULL);
	path = findexecpath(cmd, paths);
	return (freesplit(paths), path);
}
