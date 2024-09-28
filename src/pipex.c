#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
	char *rpath;
	char **cmdsplit;

	if (argc < 5)
		return (ft_putstr_fd("error: not enough arguments\n", STDERR_FILENO), 0);
	if (argv)
		argv = argv;
	if (envp)
		envp = envp;
	cmdsplit = ft_split(argv[2], ' ');
	if (!cmdsplit)
		return (0);
	rpath = findcmdpath(cmdsplit[0], envp);
	ft_printf("%s\n", rpath);
	freesplit(cmdsplit);
	free(rpath);
}