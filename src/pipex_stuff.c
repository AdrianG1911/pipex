/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:08:57 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/09 20:22:55 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_here_doc(t_pipex *spipex)
{
	if (ft_strncmp(spipex->infile_name, "here_doc", 9) == 0)
		return (1);
	return (0);
}

int	here_doc_check(int argc, char *argv[], t_pipex *spipex)
{
	if (ft_strncmp(spipex->infile_name, "here_doc", 9) == 0)
	{
		if (put_input_in_file(argv, spipex) == -1)
		{
			free_spipex(argc, spipex);
			memerror(errno);
			exit(1);
		}
		return (1);
	}
	return (0);
}

void	close_set_fd(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
}

void	close_all_fds(int argc, t_pipex *spipex)
{
	int	to_close;
	int	i;

	to_close = argc - 4;
	i = 0;
	while (i < to_close)
	{
		close_set_fd(&spipex->pipe_fds[i][0]);
		close_set_fd(&spipex->pipe_fds[i][1]);
		i++;
	}
	close_set_fd(&spipex->infile_fd);
	close_set_fd(&spipex->outfile_fd);
}
