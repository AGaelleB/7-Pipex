/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:40:53 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/15 16:26:20 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int child_process(t_data *data, char **av, char **envp)
{
	pid_t pid;

	pid = fork();

	int fd[2];

	if (pid == 0) // executera la 1er cmd
	{
		printf("\n%sJe suis le processus enfant%s\n", MAGENTA, RESET);
		close(fd[1]);
		ft_get_argcs(data, av, envp);
		ft_get_paths(envp, data);
		close(fd[0]);
	}
	else if (pid > 0) // executera la 2e cmd
	{
		printf("\n%sJe suis le processus parent%s\n", BLUE, RESET);
		close(fd[0]);
		ft_get_argcs(data, av, envp);
		ft_get_paths(envp, data);
		close(fd[1]);
	}
	else
	{
		printf("\n%sErreur lors de la création du processus enfant.\n%s", RED, RESET);
	}

	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_data	data;

	child_process(&data, av, envp);
	// ft_get_argcs(&data, av, envp);
	// ft_get_paths(envp, &data);

	// printf("\ncmd1 = %s\n", *data.cmd1.args);
	// printf("cmd2 = %s\n", *data.cmd2.args);
}
