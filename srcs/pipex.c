/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnefo <abonnefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:40:53 by abonnefo          #+#    #+#             */
/*   Updated: 2023/05/25 13:06:42 by abonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int child_process_one(int f2, char **cmd2, t_data *data, char **av, char **envp)
{
	printf("%schild_process_one%s\n", BLUE, RESET);

	ft_get_argcs(data, av, envp);
	ft_get_paths(envp, data);

	printf("\ncmd1 = %s\n", *data->cmd1.args);
	printf("PATH cmd1 = %s\n", data->cmd1.path);
	
	execve(data->cmd1.path, data->cmd1.args, envp);
	
	printf("%sEND child_process_one%s\n", BLUE, RESET);

	return (0);
}

int child_process_two(int f1, char **cmd1, t_data *data, char **av, char **envp)
{
	printf("%schild_process_two\n%s", MAGENTA, RESET);

	ft_get_argcs(data, av, envp);
	ft_get_paths(envp, data);

	printf("\ncmd2 = %s\n", *data->cmd2.args);
	printf("PATH cmd2 = %s\n", data->cmd2.path);
	
	execve(data->cmd2.path, data->cmd2.args, envp);

	printf("%sEND child_process_two%s\n", MAGENTA, RESET);

	return (0);
}

void	pipex(int f1, int f2, t_data *data, char **av, char **envp)
{
	// int	end[2];

	pid_t	pid;
	// pid_t	wait_pid;
	// int		status;

	// pipe(end);

	pid = fork();
	printf("\npid = %d\n", pid);
	
	if (pid < 0) //Erreur lors de la création du processus enfant
	{
		// free
		return (perror("Fork: "));
	}
	if (pid == 0) // executera la 1er cmd
	{
		printf("\n%sJe suis le processus one%s\n", MAGENTA, RESET);
		
		// close(end[0]); // Ferme l'extrémité de lecture de la pipe
		// dup2(end[1], STDOUT_FILENO); // Redirige la sortie standard vers l'extrémité d'écriture de la pipe
		child_process_one(f1, data->cmd1.args, data, av, envp);
		printf("END de pipex enfant one\n");
		// close(end[1]); // Ferme l'extrémité d'écriture de la pipe
	}

	pid = fork();
	printf("\npid = %d\n", pid);
	
	if (pid < 0) //Erreur lors de la création du processus enfant
	{
		// free
		return (perror("Fork: "));
	}
	if (pid == 0) // executera la 2e cmd
	{
		printf("\n%sJe suis le processus two%s\n", BLUE, RESET);
		
		// wait_pid = waitpid(pid, &status, 0); // Attend la terminaison du processus enfant
		// waitpid(pid, &status, 0); // Attend la terminaison du processus enfant
		// close(end[1]); // Ferme l'extrémité d'écriture de la pipe
		// dup2(end[0], STDIN_FILENO); // Redirige l'entrée standard vers l'extrémité de lecture de la pipe
		
		child_process_two(f2, data->cmd2.args, data, av, envp);
		printf("END pipex enfant two\n");
		// close(end[0]); // Ferme l'extrémité de lecture de la pipe
	}
	printf("END de pipex\n");
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
		
	pipex(f1, f2, &data, av, envp);
	
	printf("END je suis sortie youpie\n");

	return (0);
}
