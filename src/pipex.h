/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:11:32 by adrgutie          #+#    #+#             */
/*   Updated: 2024/10/06 16:56:40 by adrgutie         ###   ########.fr       */
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

//structure
typedef struct s_pipex
{
	char	**envp;
	int		infile_fd;
	int		outfile_fd;
	char	*infile_name;
	char	*outfile_name;
	char	***cmd_args;
	char	**cmd_paths;
	int		**pipe_fds;
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
//error
int		memerror(int error);
//thing_to_thing
void	thing_to_thing(int i, int argc, t_pipex *spipex);
#endif