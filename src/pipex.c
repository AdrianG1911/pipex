#include "pipex.h"

int	childone(t_pipex *spipex, pid_t pid)
{
	if (pid == 0)
	{
		if (dup2(spipex->infile_fd, STDIN_FILENO) == -1)
			return (perror("dup2 infile_fd"), free_spipex(spipex), -1);
		if (dup2(spipex->pipe_fds[1], STDOUT_FILENO) == -1)
			return (perror("dup2 pipe write end"), free_spipex(spipex), -1);
		close(spipex->pipe_fds[0]);
		close(spipex->infile_fd);
		close(spipex->outfile_fd);
		if (execve(spipex->cmd1_path, spipex->holy[1], spipex->envp) == -1)
			return (perror("execve cmd1"), free_spipex(spipex), -1);
		return (1);
	}
	else
		return (1);
}

int	childtwo(t_pipex *spipex, pid_t pid2)
{
	if (pid2 == 0)
	{
		if (dup2(spipex->pipe_fds[0], STDIN_FILENO) == -1)
			return (perror("dup2 pipe read end"), free_spipex(spipex), -1);
		if (dup2(spipex->outfile_fd, STDOUT_FILENO) == -1)
			return (perror("dup2 outfile_fd"), free_spipex(spipex), -1);
		close(spipex->pipe_fds[1]);
		close(spipex->infile_fd);
		close(spipex->outfile_fd);
		if (execve(spipex->cmd2_path, spipex->holy[2], spipex->envp) == -1)
			return (perror("execve cmd2"), free_spipex(spipex), -1);
		return (1);
	}
	else
		return (1);
}

void	parent(t_pipex *spipex, pid_t pid, pid_t pid2)
{
	close(spipex->pipe_fds[0]);
	close(spipex->pipe_fds[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0); 
}

int	pipex(char *argv[], char *envp[])
{
	pid_t	pid;
	pid_t	pid2;
	t_pipex	*spipex;

	spipex = init_spipex(argv, envp);
	if (!spipex)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free_spipex(spipex), -1);
	if (childone(spipex, pid) == -1)
		return (-1);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			return (perror("fork for cmd2"), free_spipex(spipex), -1);
		if (childtwo(spipex, pid2) == -1)
			return (-1);
		else
			parent(spipex, pid, pid2);
	}
	return (free_spipex(spipex), 1);
}

// void print_spipex(t_pipex *spipex) {
//     if (!spipex) {
//         printf("spipex is NULL\n");
//         return;
//     }

//     printf("Infile FD: %d\n", spipex->infile_fd);
//     printf("Outfile FD: %d\n", spipex->outfile_fd);
//     printf("Pipe FDs: [%d, %d]\n", spipex->pipe_fds[0], spipex->pipe_fds[1]);
    
//     // Print cmd1_path
//     if (spipex->cmd1_path) {
//         printf("Command 1 Path: %s\n", spipex->cmd1_path);
//     } else {
//         printf("Command 1 Path: NULL\n");
//     }

//     // Print cmd2_path
//     if (spipex->cmd2_path) {
//         printf("Command 2 Path: %s\n", spipex->cmd2_path);
//     } else {
//         printf("Command 2 Path: NULL\n");
//     }

//     // Print holy array
//     printf("Holy Array:\n");
//     for (int i = 0; spipex->holy[i]; i++) {
//         printf("  holy[%d]: ", i);
//         for (int j = 0; spipex->holy[i][j]; j++) {
//             printf("%s ", spipex->holy[i][j]);
//         }
//         printf("\n");
//     }
// }

int main(int argc, char *argv[], char *envp[])
{
	if (argc < 5)
		return (ft_putstr_fd("error: not enough arguments\n", STDERR_FILENO), 0);
	if (argc > 5)
		return (ft_putstr_fd("error: too many arguments\n", STDERR_FILENO), 0);
	if (pipex(argv, envp) == -1)
		return (memerror(errno));
	return (0);
}
