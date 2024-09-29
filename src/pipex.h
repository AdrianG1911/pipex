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
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fds[2];
	char	***holy;
	char	**envp;
	char	*cmd1_path;
	char	*cmd2_path;
}	t_pipex;

//spipex
t_pipex	*init_spipex(char *argv[], char *envp[]);
//free
void	free_spipex(t_pipex *spipex);
void	freesplit(char **split);
void	free_holy_split(char ***holy);
//exec
char	*findcmdpath(char *cmd, char *envp[]);
//parse
int		ft_isspace(int c);
int		countarg(char *arg);
int		pass_any(char *arg);
int		fill_any(char *arg, char *sep);
int		countargword(char *arg);
char	**sep_arg(char *arg, char **parsed);
char	***holy_arg_split(char *argv[]);
//open
int		open_file1_fd(char *filename);
int		open_file2_fd(char *filename);
//error
int		memerror(int error);
#endif