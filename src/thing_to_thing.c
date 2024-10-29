#include "pipex.h"

void	close_all_fds(int argc, t_pipex *spipex)
{
	int	to_close;
	int	i;

	to_close = argc - 4;
	i = 0;
	while (i < to_close)
	{
		if (spipex->pipe_fds[i][0] >= 0)
			close(spipex->pipe_fds[i][0]);
		if (spipex->pipe_fds[i][1] >= 0)
			close(spipex->pipe_fds[i][1]);
		i++;
	}
    if (spipex->infile_fd >= 0)
		close(spipex->infile_fd);
    if (spipex->outfile_fd >= 0)
		close(spipex->outfile_fd);
}

void	file_to_pipe(int i, int argc, t_pipex *spipex)
{
	if (i != 0)
		return ;
	if (dup2(spipex->infile_fd, STDIN_FILENO) == -1 || \
		dup2(spipex->pipe_fds[i][1], STDOUT_FILENO) == -1)
		perror("dup2"), exit(EXIT_FAILURE);
	close_all_fds(argc, spipex);
	if (execve(spipex->cmd_paths[i], spipex->cmd_args[i], spipex->envp) == -1)
		perror("execve"), exit(EXIT_FAILURE);
}

void	pipe_to_pipe(int i, int argc, t_pipex *spipex)
{
	if (i == argc - 4)
		return ;
	if (dup2(spipex->pipe_fds[i - 1][0], STDIN_FILENO) == -1 || \
		dup2(spipex->pipe_fds[i][1], STDOUT_FILENO) == -1)
			perror("dup2"), exit(EXIT_FAILURE);
	close_all_fds(argc, spipex);
	if (execve(spipex->cmd_paths[i], spipex->cmd_args[i], spipex->envp) == -1)
		perror("execve"), exit(EXIT_FAILURE);
}

void	pipe_to_file(int i, int argc, t_pipex *spipex)
{
	if (dup2(spipex->pipe_fds[i - 1][0], STDIN_FILENO) == -1 || \
		dup2(spipex->outfile_fd, STDOUT_FILENO) == -1)
		perror("dup2"), exit(EXIT_FAILURE);
	close_all_fds(argc, spipex);
	if (execve(spipex->cmd_paths[i], spipex->cmd_args[i], spipex->envp) == -1)
		perror("execve"), exit(EXIT_FAILURE);
}

void	thing_to_thing(int i, int argc, t_pipex *spipex)
{
	file_to_pipe(i, argc, spipex);
	pipe_to_pipe(i, argc, spipex);
	pipe_to_file(i, argc, spipex);
}