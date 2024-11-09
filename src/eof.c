/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:26:50 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/09 20:22:49 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ctrlderrormsg(int numlines, char *limiter, char *line)
{
	char	*numlinesstr;

	free(line);
	numlinesstr = ft_itoa(numlines);
	if (numlinesstr == NULL)
		return (-1);
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putstr_fd(numlinesstr, 2);
	free(numlinesstr);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("\')\n", 2);
	return (1);
}

void	unlink_hd(t_pipex *spipex)
{
	if (spipex->here_doc_file_path == NULL)
		return ;
	if (unlink(spipex->here_doc_file_path) == -1)
		perror("unlink");
}

char	*flush(char *full)
{
	get_next_line(CLEAR_MEM);
	return (full);
}

void	flush_free_close_open(char *line, t_pipex *spipex)
{
	flush(NULL);
	free(line);
	close(spipex->infile_fd);
	spipex->infile_fd = open(spipex->here_doc_file_path, O_RDONLY);
}

int	put_input_in_file(char *argv[], t_pipex *spipex)
{
	int		numlines;
	int		limlen;
	char	*line;

	limlen = ft_strlen(argv[2]);
	numlines = 1;
	while (1)
	{
		ft_printf("> ");
		line = get_next_line(1);
		if (line == NULL)
			return (-1);
		if (line[0] == '\0')
			return (ctrlderrormsg(numlines, argv[2], line));
		if (ft_strncmp(line, argv[2], limlen) == 0 && line[limlen] == '\n')
			break ;
		if (write(spipex->infile_fd, line, ft_strlen(line)) == -1)
			return (flush(NULL), free(line), perror("write"), -1);
		free(line);
		numlines++;
	}
	flush_free_close_open(line, spipex);
	if (spipex->infile_fd < 0)
		return (perror("open"), -1);
	return (1);
}
