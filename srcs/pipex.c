/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:40:53 by abonnefo          #+#    #+#             */
/*   Updated: 2023/06/06 17:10:12 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_get_argcs(t_data *data, char **av, char **envp)
{
	data->cmd1.args = ft_split(av[2], ' ');
	data->cmd2.args = ft_split(av[3], ' ');
	data->cmd1.path = ft_check_paths(envp, *data->cmd1.args);
	data->cmd2.path = ft_check_paths(envp, *data->cmd2.args);
}

void	child_process_one(t_data *data, char **av, char **envp, int fd[2])
{
	int		f1;

	f1 = open(av[1], O_RDONLY);
	if (f1 < 0)
	{
		ft_free_all_data(data);
		perror(av[1]);
		exit (-1);
	}
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	if ((data->cmd1.path != NULL)
		&& (execve(data->cmd1.path, data->cmd1.args, envp) == -1))
	{
		perror("Error");
		exit (-1);
	}
	close(f1);
	close(fd[1]);
}

void	child_process_two(t_data *data, char **av, char **envp, int fd[2])
{
	int		f2;

	f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f2 < 0)
	{
		ft_free_all_data(data);
		perror(av[4]);
		exit (-1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(f2, STDOUT_FILENO);
	if ((data->cmd2.path != NULL)
		&& (execve(data->cmd2.path, data->cmd2.args, envp) == -1))
	{
		perror("Error");
		exit (-1);
	}
	close(f2);
}

void	pipex(t_data *data, char **av, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	ft_get_argcs(data, av, envp);
	pipe(fd);
	pid = fork();
	if (pid < 0)
		perror("Error");
	if (pid == 0)
		child_process_one(data, av, envp, fd);
	pid = fork();
	if (pid < 0)
		perror("Error");
	if (pid == 0)
	{
		waitpid(pid, &status, 0);
		child_process_two(data, av, envp, fd);
	}
	close(fd[0]);
	close(fd[1]);
	ft_free_all_data(data);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		fd;

	fd = open(av[1], O_DIRECTORY);
	if (fd > 0)
	{
		ft_printf("cat: %s: Is a directory\n", av[1]);
		exit(1);
	}
	if (ac == 5)
	{
		pipex(&data, av, envp);
	}
	else
		ft_printf("Error: Bad numbers of arguments\n");
	(void)ac;
	return (0);
}
