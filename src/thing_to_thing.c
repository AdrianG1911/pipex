/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thing_to_thing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:26:36 by adrgutie          #+#    #+#             */
/*   Updated: 2024/10/29 22:27:03 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(int i, t_pipex *spipex)
{
	if (spipex->cmd_paths[i][0] == 0)
		exit(EXIT_FAILURE);
	if (access(spipex->cmd_paths[i], X_OK) != 0)
		exit(EXIT_FAILURE);
	if (execve(spipex->cmd_paths[i], spipex->cmd_args[i], spipex->envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	file_to_pipe(int i, int argc, t_pipex *spipex)
{
	if (i != 0)
		return ;
	if (spipex->infile_fd < 0)
		exit(EXIT_FAILURE);
	if (dup2(spipex->infile_fd, STDIN_FILENO) == -1 || \
		dup2(spipex->pipe_fds[i][1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close_all_fds(argc, spipex);
	execute(i, spipex);
}

void	pipe_to_pipe(int i, int argc, t_pipex *spipex)
{
	if (i == argc - 4)
		return ;
	if (dup2(spipex->pipe_fds[i - 1][0], STDIN_FILENO) == -1 || \
		dup2(spipex->pipe_fds[i][1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close_all_fds(argc, spipex);
	execute(i, spipex);
}

void	pipe_to_file(int i, int argc, t_pipex *spipex)
{
	if (spipex->outfile_fd < 0)
		exit(EXIT_FAILURE);
	if (dup2(spipex->pipe_fds[i - 1][0], STDIN_FILENO) == -1 || \
		dup2(spipex->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close_all_fds(argc, spipex);
	execute(i, spipex);
}

void	thing_to_thing(int i, int argc, t_pipex *spipex)
{
	file_to_pipe(i, argc, spipex);
	pipe_to_pipe(i, argc, spipex);
	pipe_to_file(i, argc, spipex);
}
