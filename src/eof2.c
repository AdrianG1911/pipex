/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:22:09 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/09 20:41:42 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_itoa_noalloc(char *cnum, int number)
{
	int	nlen;
	int	i;

	i = number;
	nlen = 0;
	while (i != 0)
	{
		i /= 10;
		nlen++;
	}
	if (number < 0)
		i = 1;
	if (nlen == 0)
		nlen = 1;
	cnum[0] = '-';
	nlen = nlen + i;
	cnum[nlen] = '\0';
	while ((nlen - 1) >= i)
	{
		cnum[nlen - 1] = number % 10 + '0';
		if (number < 0)
			cnum[nlen - 1] = -(number % 10) + 10;
		number /= 10;
		nlen--;
	}
}

void	path_with_number(char *name, int number)
{
	char	cnum[30];

	ft_strlcat(name, "/tmp/here_doc", 30);
	ft_itoa_noalloc(cnum, number);
	ft_strlcat(name, cnum, 30);
}

int	find_unique_file_name(char *name)
{
	int	numender;

	numender = 0;
	while (numender < INT_MAX)
	{
		name[0] = 0;
		path_with_number(name, numender);
		if (access(name, F_OK) != 0)
			return (1);
		numender++;
	}
	return (-1);
}

int	get_here_doc_fd_path(t_pipex *spipex)
{
	char	name[30];

	if (access("/tmp", F_OK) != 0)
		return (perror("need /tmp folder"), -1);
	ft_bzero(name, sizeof(name));
	if (find_unique_file_name(name) == -1)
		return (perror("open here_doc"), -1);
	spipex->infile_fd = open(name, O_WRONLY | O_CREAT, 0600);
	if (spipex->infile_fd == -1)
		return (-1);
	spipex->here_doc_file_path = ft_strdup(name);
	if (spipex->here_doc_file_path == NULL)
		return (-1);
	return (1);
}
