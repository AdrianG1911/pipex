#include "pipex.h"

int	memerror(int error)
{
	if (error == ENOMEM)
	{
		ft_putstr_fd("error: not enough memory\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("", STDERR_FILENO);
	return (0);
}