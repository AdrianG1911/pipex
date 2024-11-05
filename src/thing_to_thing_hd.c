/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thing_to_thing_hd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:00:10 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/05 20:22:24 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_to_pipe_hd(int i, int argc, t_pipex *spipex)
{
	if (i != 1)
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
