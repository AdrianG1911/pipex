#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
	if (argc < 5)
		return (ft_putstr_fd("error: not enough arguments\n", STDERR_FILENO), 0);
	if (argc > 5)
		return (ft_putstr_fd("error: too many arguments\n", STDERR_FILENO), 0);
	if (argv)
		argv = argv;
	if (envp)
		envp = envp;
	char ***holy;

	holy = holy_arg_split(argv);
	if (!holy)
		return (0);
	int i;
	int j;
	i = 0;
	while (holy[i])
	{
		ft_printf("Argument %d\n", i + 1);
		j = 0;
		while (holy[i][j])
		{
			ft_printf("%s\n", holy[i][j]);
			j++;
		}
		i++;
	}
	free_holy_split(holy);
}