#include "pipex.h"

char *joinpaths(char *cmd, char *path)
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

int iterpaths(char *cmd, char **paths, char **testpath)
{
	if (!(cmd[0]))
	{
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (0);
	}
	while (*paths)
	{
		*testpath = joinpaths(cmd, *paths);
		if (*testpath)
		{
			if (access(*testpath, X_OK) == 0)
				return (1);	
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

char *findexecpath(char *cmd, char **paths)
{
	char *testpath;

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
	}
	return (NULL);
}

char **getpaths(char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return(NULL);
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
