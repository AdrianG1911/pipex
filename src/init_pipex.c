/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:11:02 by adrgutie          #+#    #+#             */
/*   Updated: 2024/10/06 17:01:27 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_spipex(t_pipex *spipex)
{
	if (spipex)
	{
		if (spipex->infile_fd >= 0)
			close(spipex->infile_fd);
		if (spipex->outfile_fd >= 0)
			close(spipex->outfile_fd);
		if (spipex->pipe_fds[0] >= 0)
			close(spipex->pipe_fds[0]);
		if (spipex->pipe_fds[1] >= 0)
			close(spipex->pipe_fds[1]);
		free_holy_split(spipex->holy);
		free(spipex->cmd1_path);
		free(spipex->cmd2_path);
		free(spipex);
	}
}

int	create_pipe(t_pipex *spipex)
{
	if (pipe(spipex->pipe_fds) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	init_spipex_cmdpth(t_pipex *spipex, char ***holy)
{
	if (spipex->infile_fd >= 0)
		spipex->cmd1_path = findcmdpath(holy[1][0], spipex->envp);
	if (spipex->outfile_fd >= 0)
		spipex->cmd2_path = findcmdpath(holy[2][0], spipex->envp);
}

t_pipex	*init_spipex(char *argv[], char *envp[])
{
	t_pipex	*spipex;

	spipex = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (!spipex)
		return (NULL);
	spipex->holy = holy_arg_split(argv);
	if (!spipex->holy)
		return (free_spipex(spipex), NULL);
	spipex->envp = envp;
	spipex->infile_fd = open_file1_fd(spipex->holy[0][0]);
	spipex->outfile_fd = open_file2_fd(spipex->holy[3][0]);
	if (create_pipe(spipex) == -1)
		return (free_spipex(spipex), NULL);
	init_spipex_cmdpth(spipex, spipex->holy);
	return (spipex);
}
