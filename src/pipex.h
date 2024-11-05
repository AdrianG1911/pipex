/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:08:37 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/05 19:57:56 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
//get_next_line
# include "get_next_line/get_next_line.h"

# define WRITE 1
# define READ 0

//structure
typedef struct s_pipex
{
	char	**envp;
	int		infile_fd;
	int		outfile_fd;
	char	*infile_name;
	char	*outfile_name;
	char	*here_doc_file_path;
	char	***cmd_args;
	char	**cmd_paths;
	int		(*pipe_fds)[2];
	pid_t	*pids;
}	t_pipex;

//spipex
t_pipex	*init_spipex(int argc, char *argv[], char *envp[]);
//free
void	free_spipex(int argc, t_pipex *spipex);
void	free_pipes(int argc, t_pipex *spipex);
void	free_cmd_args(t_pipex *spipex);
void	freesplit(char **split);
//close
void	close_set_fd(int *fd);
void	close_all_fds(int argc, t_pipex *spipex);
//exec
char	*findcmdpath(char *cmd, char *envp[]);
//parse helper
int		ft_isspace(int c);
int		countarg(char *arg);
int		pass_any(char *arg);
int		fill_any(char *arg, char *sep);
int		countargword(char *arg);
//parse
char	**sep_arg(char *arg);
char	*nosep_arg(char *arg);
//open
int		open_file1_fd(char *filename);
int		open_file2_fd(char *filename);
int		open_file_here_doc(char *filename);
//error
int		memerror(int error);
//thing_to_thing
void	thing_to_thing(int i, int argc, t_pipex *spipex);
void	execute(int i, int argc, t_pipex *spipex);
void	file_to_file_hd(int i, int argc, t_pipex *spipex);
void	file_to_pipe_hd(int i, int argc, t_pipex *spipex);
//here_doc
int		is_here_doc(t_pipex *spipex);
int		put_input_in_file(char *argv[], t_pipex *spipex);
int		get_here_doc_fd_path(t_pipex *spipex);
int		here_doc_check(int argc, char *argv[], t_pipex *spipex);
void	unlink_hd(t_pipex *spipex);

#endif