/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:11:36 by adrgutie          #+#    #+#             */
/*   Updated: 2024/10/29 22:26:57 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freesplit(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

void	free_cmd_args(t_pipex *spipex)
{
	int	i;

	if (spipex->cmd_args == NULL)
		return ;
	i = 0;
	while (spipex->cmd_args[i] != NULL)
	{
		freesplit(spipex->cmd_args[i]);
		i++;
	}
	free (spipex->cmd_args);
}

void	free_pipes(int argc, t_pipex *spipex)
{
	int	i;
	int	to_free;

	if (spipex->pipe_fds == NULL)
		return ;
	to_free = argc - 4;
	i = -1;
	while (++i < to_free)
	{
		if (spipex->pipe_fds[i] == NULL)
			continue ;
		if (spipex->pipe_fds[i][0] >= 0)
			close(spipex->pipe_fds[i][0]);
		if (spipex->pipe_fds[i][1] >= 0)
			close(spipex->pipe_fds[i][1]);
		free(spipex->pipe_fds[i]);
	}
	free(spipex->pipe_fds);
}

void	free_filenames_filefds(t_pipex *spipex)
{
	free(spipex->infile_name);
	free(spipex->outfile_name);
	if (spipex->infile_fd >= 0)
		close(spipex->infile_fd);
	if (spipex->outfile_fd >= 0)
		close(spipex->outfile_fd);
}

void	free_spipex(int argc, t_pipex *spipex)
{
	if (spipex == NULL)
		return ;
	free_filenames_filefds(spipex);
	free_pipes(argc, spipex);
	free_cmd_args(spipex);
	freesplit(spipex->cmd_paths);
	free(spipex->pids);
	free(spipex);
}
