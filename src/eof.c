/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:26:50 by adrgutie          #+#    #+#             */
/*   Updated: 2024/10/29 22:26:55 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ctrlderrormsg(int numlines, char *limiter, char *full)
{
	char	*numlinesstr;

	numlinesstr = ft_itoa(numlines);
	if (numlinesstr == NULL)
		return (free(full), NULL);
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putstr_fd(numlinesstr, 2);
	free(numlinesstr);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("\')\n", 2);
	return (full);
}

char	*flush(char *full)
{
	get_next_line(CLEAR_MEM);
	return (full);
}

char	*input_loop(char *limiter, char *full, int numlines, int limlen)
{
	char	*temp;
	char	*line;

	while (1)
	{
		ft_printf("> ");
		line = get_next_line(1);
		if (line == NULL)
			return (free(full), flush(NULL));
		if (line[0] == 0)
			return (free(line), ctrlderrormsg(numlines, limiter, full));
		if (ft_strncmp(line, limiter, limlen) == 0 && line[limlen] == '\n')
			return (free(line), flush(full));
		temp = full;
		full = ft_strjoin(full, line);
		numlines++;
		free(temp);
		free(line);
		if (full == NULL)
			return (flush(NULL));
	}
}

char	*get_input(char *limiter)
{
	int		limlen;
	char	*full;
	int		numlines;

	full = (char *)ft_calloc(1, sizeof(char));
	if (full == NULL)
		return (NULL);
	limlen = ft_strlen(limiter);
	numlines = 1;
	full = input_loop(limiter, full, numlines, limlen);
	return (full);
}

int	put_input_in_pipe(char *argv[], t_pipex *spipex)
{
	char	*doc;

	doc = get_input(argv[2]);
	if (doc == NULL)
		return (-1);
	if (write(spipex->pipe_fds[0][1], doc, ft_strlen(doc)) == -1)
		return (free(doc), perror("write"), -1);
	close(spipex->pipe_fds[0][1]);
	return (free(doc), 1);
}
