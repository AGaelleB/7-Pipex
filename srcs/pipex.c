/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:40:53 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/25 15:55:15 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int child_process_one(char **cmd1, t_data *data, char **av, char **envp)
{
	ft_get_argcs(data, av, envp);
	ft_get_paths(envp, data);
	execve(data->cmd1.path, data->cmd1.args, envp);
	return (0);
}

int child_process_two(char **cmd2, t_data *data, char **av, char **envp)
{
	ft_get_argcs(data, av, envp);
	ft_get_paths(envp, data);
	execve(data->cmd2.path, data->cmd2.args, envp);
	return (0);
}

void	pipex(int f2, t_data *data, char **av, char **envp)
{
	int		fd[2];

	pid_t	pid;
	int		status;

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
		child_process_one(data->cmd1.args, data, av, envp);
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
		child_process_two(data->cmd2.args, data, av, envp);
		close(fd[0]);
		close(f2);
	}
}

int main(int ac, char **av, char **envp)
{
	int	f1;
	int	f2;

	t_data data;
	
	f1 = open(av[1], O_RDONLY);
	f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);

	if (f1 < 0 || f2 < 0)
		return (-1);
	pipex(f2, &data, av, envp);
	return (0);
}
