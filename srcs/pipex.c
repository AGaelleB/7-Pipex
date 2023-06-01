/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:40:53 by abonnefo          #+#    #+#             */
/*   Updated: 2023/06/01 14:18:34 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
	if ((data->cmd1.path != NULL) && (execve(data->cmd1.path, data->cmd1.args, envp) == -1))
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
	if ((data->cmd2.path != NULL) && (execve(data->cmd2.path, data->cmd2.args, envp) == -1))
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
	{
		perror("Error");
	}
	if (pid == 0)
			child_process_one(data, av, envp, fd);
	pid = fork();
	if (pid < 0)
	{
		perror("Error");
	}
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

	int fd;

	fd = open(av[1], O_DIRECTORY);
	if (fd > 0)
	{
		ft_printf("MOI cat: %s: Is a directory\n", av[1]);
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


/*
Plusieurs tests : 
./pipex /dev/stdin cat ls /dev/stdout, et je compare a < /dev/stdin cat | ls /dev/stdout, le pipe classique attend, mon pipex rend la commande de terminal
env -i ./pipex test.txt "cat test.txt" "grep b" result.txt // pour enlever l env
valgrind --trace-children=yes ./pipex infile ls ls outfile //tester les leacks des childs
valgrind --track-fds=yes ./pipex infile ls ls outfile // verifer les close/open des fd
./pipex infile lls ls outfile // la premiere doit foiree ma la deuxieme doit correctement etre executee vis versa
./pipex infile ./a.out cat test   // faire une condition(if av[1] == "./") si il y a un "./" directement envoyer dans le execve
valgrind ./pipex infile ls ls outfile  // a tester avec les droits de infile et de outfile a 0 atention il doit retourner "infile ou outfile : permission denied"


tester avec :
un nom de dossier (est ce que autre chose que cat pour ouvrir un dossier en msg d ereur ?)
un chemin absolu / sans environement env -i (ou  -u)
un executable
tester les leaks en fonction des permission chmod 777 / chmod 0


ERREUR A CORRIGER : 

valgrind ./pipex infile "cat infile"  "/usr/bin/wc" outfile 
	prb de leak, trop de free, on free les cases du tab du chemin abso alors qu il n existe pas, il faurait dans ce cas uniquement faire un free() (et non le all tab)

./pipex outfile "cat outfile" "grep i" outfile 
	Erreur: si le fichier d'entree est le meme que celui vers lequel on redirige (d'apres bash on est sensé tout ecrase sans trier) nous trions une premiere fois puis nous ecrasons
SOLUTION: potentielle: suprimer le file(av[1]) avec rm et le recreer avec touch(av[1]) 
*/