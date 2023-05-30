/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:40:53 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/30 14:30:53 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process_one(t_data *data, char **av, char **envp)
{
	if ((data->cmd1.path != NULL) && (execve(data->cmd1.path, data->cmd1.args, envp) == -1))
	{
		perror("Error"); // ICI
		exit (-1);
	}
}

void	child_process_two(t_data *data, char **av, char **envp)
{
	if ((data->cmd2.path != NULL) && (execve(data->cmd2.path, data->cmd2.args, envp) == -1))
	{
		perror("Error"); // ICI
		exit (-1);
	}
}

void	pipex(t_data *data, char **av, char **envp)
{
	int		fd[2];
	int		status;
	int		f1;
	int		f2;
	pid_t	pid;

	ft_get_argcs(data, av, envp);
	pipe(fd);
	pid = fork();
	if (pid < 0)
		perror("Error"); // ICI
	if (pid == 0)
	{
		f1 = open(av[1], O_RDONLY);
		if (f1 < 0)
		{
			perror(av[1]);
			exit (-1);
		}
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		child_process_one(data, av, envp);
		close(fd[1]);
		close(f1);
	}
	pid = fork();
	if (pid < 0)
		perror("Error"); // ICI
	if (pid == 0)
	{
		waitpid(pid, &status, 0);
		f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (f2 < 0)
		{
			perror(av[4]);
			exit (-1);
		}
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(f2, STDOUT_FILENO);
		child_process_two(data, av, envp);
		close(f2);
	}
	ft_free_all_data(data);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	if (ac == 5)
		pipex(&data, av, envp);
	else
		ft_printf("Error: Bad numbers of arguments\n");
	return (0);
}


/*
./pipex /dev/stdin cat ls /dev/stdout, et je compare a < /dev/stdin cat | ls /dev/stdout, le pipe classique attend, mon pipex rend la commande de terminal
env -i ./pipex test.txt "cat test.txt" "grep b" result.txt // pour enlever l env

valgrind --trace-children=yes ./pipex infile ls ls outfile //tester les leacks des childs
valgrind --track-fds=yes ./pipex infile ls ls outfile // verifer les close/open des fd
./pipex infile lls ls outfile // la premiere doit foiree ma la deuxieme doit correctement etre executee vis versa
./pipex infile ./a.out cat test   // faire une condition(if av[1] == "./") si il y a un "./" directement envoyer dans le execve
valgrind ./pipex infile ls ls outfile  // a tester avec les droits de infile et de outfile a 0 atention il doit retourner "infile ou outfile : permission denied"


tester avec :
un nom de dossier
un chemin absolu
sans environement env -i (ou  -u)
*/