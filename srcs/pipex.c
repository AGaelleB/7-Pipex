/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:40:53 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/25 16:56:19 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	child_process_one(t_data *data, char **av, char **envp)
{
	ft_get_argcs(data, av, envp);
	ft_get_paths(envp);
	execve(data->cmd1.path, data->cmd1.args, envp);
	return (0);
}

int	child_process_two(t_data *data, char **av, char **envp)
{
	ft_get_argcs(data, av, envp);
	ft_get_paths(envp);
	execve(data->cmd2.path, data->cmd2.args, envp);
	return (0);
}

void	pipex(int f2, t_data *data, char **av, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
	{
		// free ?
		return (perror("Fork: "));
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		child_process_one(data, av, envp);
		close(fd[1]);
	}
	pid = fork();
	if (pid < 0)
	{
		return (perror("Fork: "));
	}
	if (pid == 0)
	{
		waitpid(pid, &status, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(f2, STDOUT_FILENO);
		child_process_two(data, av, envp);
		close(fd[0]);
		close(f2);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		f1;
	int		f2;
	t_data	data;

	(void)ac;
	f1 = open(av[1], O_RDONLY);
	f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (-1);
	pipex(f2, &data, av, envp);
	close(f1);
	return (0);
}
