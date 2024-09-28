#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
 


//exec
char	*findcmdpath(char *cmd, char *envp[]);
void	freesplit(char **split);
//parse
void	free_holy_split(char ***holy);
int		ft_isspace(int c);
int		countarg(char *arg);
int		pass_any(char *arg);
int		fill_any(char *arg, char *sep);
int		countargword(char *arg);
char	**sep_arg(char *arg, char **parsed);
char	***holy_arg_split(char *argv[]);
#endif