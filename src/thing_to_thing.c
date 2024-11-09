/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thing_to_thing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:08:24 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/09 19:00:00 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(int i, int argc, t_pipex *spipex)
{
	close_all_fds(argc, spipex);
	if (check_cmd_not_exist(spipex->cmd_args[i][0], spipex->envp) == 127)
		exit(127);
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
		dup2(spipex->pipe_fds[i][WRITE], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	execute(i, argc, spipex);
}

void	pipe_to_pipe(int i, int argc, t_pipex *spipex)
{
	if (i == argc - 4)
		return ;
	if ((dup2(spipex->pipe_fds[i - 1][READ], STDIN_FILENO) == -1 || \
		dup2(spipex->pipe_fds[i][WRITE], STDOUT_FILENO) == -1))
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	execute(i, argc, spipex);
}

void	pipe_to_file(int i, int argc, t_pipex *spipex)
{
	if (spipex->outfile_fd < 0)
		exit(EXIT_FAILURE);
	if (dup2(spipex->pipe_fds[i - 1][READ], STDIN_FILENO) == -1 || \
		dup2(spipex->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	execute(i, argc, spipex);
}

void	thing_to_thing(int i, int argc, t_pipex *spipex)
{
	if (is_here_doc(spipex))
	{
		file_to_pipe_hd(i, argc, spipex);
	}
	file_to_pipe(i, argc, spipex);
	pipe_to_pipe(i, argc, spipex);
	pipe_to_file(i, argc, spipex);
}
