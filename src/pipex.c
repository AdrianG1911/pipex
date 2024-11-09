/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:08:45 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/09 20:22:56 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	waitforpids(int argc, t_pipex *spipex)
{
	int	i;
	int	last_status;

	close_all_fds(argc, spipex);
	last_status = -1;
	i = 0;
	if (is_here_doc(spipex))
		i++;
	while (i < argc - 3)
	{
		if (spipex->pids[i] == -1 || spipex->pids[i] == -2)
			break ;
		waitpid(spipex->pids[i], &last_status, 0);
		i++;
	}
	free_spipex(argc, spipex);
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (-1);
}

void	close_pipe(int pipe[])
{
	close_set_fd(&pipe[READ]);
	close_set_fd(&pipe[WRITE]);
}

int	pipex_loop(int i, int argc, t_pipex *spipex)
{
	while (++i < (argc - 3))
	{
		spipex->pids[i] = fork();
		if (spipex->pids[i] < 0)
			return (perror("fork"), waitforpids(argc, spipex));
		if (spipex->pids[i] > 0)
			continue ;
		thing_to_thing(i, argc, spipex);
	}
	return (waitforpids(argc, spipex));
}

int	pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	*spipex;
	int		i;

	spipex = init_spipex(argc, argv, envp);
	if (spipex == NULL)
		return (-1);
	i = -1;
	i += here_doc_check(argc, argv, spipex);
	return (pipex_loop(i, argc, spipex));
}

int	main(int argc, char *argv[], char *envp[])
{
	int	status;

	if (argc < 5)
		return (ft_putstr_fd("error: not enough arguments\n", \
		STDERR_FILENO), 1);
	if (argc == 5 && (ft_strncmp(argv[1], "here_doc", 9) == 0))
		return (ft_putstr_fd("error: not enough arguments\n", \
		STDERR_FILENO), 1);
	status = pipex(argc, argv, envp);
	if (status == -1)
		return (memerror(errno));
	else
		return (status);
}
