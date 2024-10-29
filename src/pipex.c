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


	// if (WIFEXITED(last_status)) 
	// 	return (WEXITSTATUS(last_status));
	// else if (WIFSIGNALED(last_status))
	// 	return (128 + WTERMSIG(last_status));
	// return (-1);

int	waitforpids(int argc, t_pipex *spipex)
{
	int	i;
	int last_status;

	close_all_fds(argc, spipex);
	last_status = -1;
	i = 0;
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

int pipex(int argc, char *argv[], char *envp[])
{
	t_pipex *spipex;
	int		i;

	spipex = init_spipex(argc, argv, envp);
	if (spipex == NULL)
		return(-1);
	i  = -1;
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


int	main(int argc, char *argv[], char *envp[])
{
	int	status;

	if (argc < 5)
		return (ft_putstr_fd("error: not enough arguments\n", STDERR_FILENO), 1);
	status = pipex(argc, argv, envp);
	if (status == -1)
		return (memerror(errno));
	else
		return (status);
}
