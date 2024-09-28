#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
 
void	freesplit(char **split);
//exec
char	*findcmdpath(char *cmd, char *envp[]);
char	*cmd_split(char argv[], int cmdnum, int cmdpart);
#endif