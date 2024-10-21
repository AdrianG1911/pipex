/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:11:25 by adrgutie          #+#    #+#             */
/*   Updated: 2024/10/08 17:16:01 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	childone(t_pipex *spipex, pid_t pid)
{
	if (pid == 0)
	{
		if (dup2(spipex->infile_fd, STDIN_FILENO) == -1)
			return (perror("dup2 infile_fd"), free_spipex(spipex), -1);
		if (dup2(spipex->pipe_fds[1], STDOUT_FILENO) == -1)
			return (perror("dup2 pipe write end"), free_spipex(spipex), -1);
		close(spipex->pipe_fds[0]);
		close(spipex->infile_fd);
		close(spipex->outfile_fd);
		if (execve(spipex->cmd1_path, spipex->holy[1], spipex->envp) == -1)
			return (perror("execve cmd1"), free_spipex(spipex), -1);
		return (1);
	}
	else
		return (1);
}

int	childtwo(t_pipex *spipex, pid_t pid2)
{
	if (pid2 == 0)
	{
		if (dup2(spipex->pipe_fds[0], STDIN_FILENO) == -1)
			return (perror("dup2 pipe read end"), free_spipex(spipex), -1);
		if (dup2(spipex->outfile_fd, STDOUT_FILENO) == -1)
			return (perror("dup2 outfile_fd"), free_spipex(spipex), -1);
		close(spipex->pipe_fds[1]);
		close(spipex->infile_fd);
		close(spipex->outfile_fd);
		if (execve(spipex->cmd2_path, spipex->holy[2], spipex->envp) == -1)
			return (perror("execve cmd2"), free_spipex(spipex), -1);
		return (1);
	}
	else
		return (1);
}

int	parent(t_pipex *spipex, pid_t pid, pid_t pid2)
{
	int	last_status;

	close(spipex->pipe_fds[0]);
	close(spipex->pipe_fds[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, &last_status, 0);
	if (WIFEXITED(last_status)) 
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (-1);
}

int	pipex(char *argv[], char *envp[])
{
	int		status;
	pid_t	pid;
	pid_t	pid2;
	t_pipex	*spipex;

	spipex = init_spipex(argv, envp);
	if (!spipex)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free_spipex(spipex), -1);
	if (childone(spipex, pid) == -1)
		return (-1);
	pid2 = fork();
	if (pid2 == -1)
		return (perror("fork for cmd2"), free_spipex(spipex), -1);
	if (childtwo(spipex, pid2) == -1)
		return (-1);
	status = parent(spipex, pid, pid2);
	return (free_spipex(spipex), status);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	status;

	if (argc < 5)
		return (ft_putstr_fd("error: not enough arguments\n", STDERR_FILENO), 1);
	if (argc > 5)
		return (ft_putstr_fd("error: too many arguments\n", STDERR_FILENO), 1);
	status = pipex(argv, envp);
	if (status == -1)
		return (memerror(errno));
	else
		return (status);
}
